


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains all the helper functions for initialising and running
  Beth Yw? In languages such as Java, this would be a class, but we really
  don't need a class here. Classes are for modelling data, and so forth, but
  here the code is pretty much a sequential block of code (BethYw::run())
  calling a series of helper functions.
*/

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>
#include <regex>

#include "lib_cxxopts.hpp"

#include "areas.h"
#include "datasets.h"
#include "bethyw.h"
#include "input.h"

/*
  Run Beth Yw?, parsing the command line arguments, importing the data,
  and outputting the requested data to the standard output/error.

  TODO: Read documentation
  Hint: cxxopts.parse() throws exceptions you'll need to catch. Read the cxxopts
  documentation for more information.

  @param argc
    Number of program arguments

  @param argv
    Program arguments

  @return
    Exit code
*/
int BethYw::run(int argc, char *argv[]) {
  try {
    auto cxxopts = BethYw::cxxoptsSetup();
    auto args = cxxopts.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cerr << cxxopts.help() << std::endl;
      return 0;
    }

    // Parse data directory argument
    std::string dir = args["dir"].as<std::string>() + DIR_SEP;

    // Parse other arguments and import data
    std::vector<BethYw::InputFileSource> datasetsToImport;
    StringFilterSet areasFilter;
    StringFilterSet measuresFilter;
    YearFilterTuple yearsFilter;
    try {
      datasetsToImport = BethYw::parseDatasetsArg(args);
      areasFilter = BethYw::parseAreasArg(args);
      measuresFilter = BethYw::parseMeasuresArg(args);
      yearsFilter = BethYw::parseYearsArg(args);
    } catch (std::invalid_argument invalidArgument) {
      std::cerr << invalidArgument.what();
      return 0;//TODO: Possibly change to an error code
    }

    Areas data = Areas();
    try {
      BethYw::loadAreas(data, dir, &areasFilter);
      BethYw::loadDatasets(data,
                           dir,
                           &datasetsToImport,
                           &areasFilter,
                           &measuresFilter,
                           &yearsFilter);
    } catch (std::runtime_error runtimeError) {
      std::cerr << "Error importing dataset:" << std::endl;
      std::cerr << runtimeError.what() << std::endl;
      return 0;//TODO: Possibly change to an error code
    }

    if (args.count("json")) {
      // The output as JSON
      std::cout << data.toJSON() << std::endl;
    } else {
      // The output as tables
      std::cout << data;
    }
  } catch (cxxopts::option_not_exists_exception optionNotExistsException) {
    std::cerr << "Invalid program argument:" << std::endl << optionNotExistsException.what();
  }

  return 0;
}


/*
  Sets up and returns a valid cxxopts object.

  @return
     A constructed cxxopts object

  @example
    auto cxxopts = BethYw::cxxoptsSetup();
    auto args = cxxopts.parse(argc, argv);
*/
cxxopts::Options BethYw::cxxoptsSetup() {
  cxxopts::Options cxxopts(
        "bethyw",
        "Student ID: " + STUDENT_NUMBER + "\n\n"
        "This program is designed to parse official Welsh Government"
        " statistics data files.\n");
    
  cxxopts.add_options()(
      "dir",
      "Directory for input data passed in as files",
      cxxopts::value<std::string>()->default_value("datasets"))(

      "d,datasets",
      "The dataset(s) to import and analyse as a comma-separated list of codes "
      "(omit or set to 'all' to import and analyse all datasets)",
      cxxopts::value<std::vector<std::string>>())(

      "a,areas",
      "The areas(s) to import and analyse as a comma-separated list of "
      "authority codes (omit or set to 'all' to import and analyse all areas)",
      cxxopts::value<std::vector<std::string>>())(

      "m,measures",
      "Select a subset of measures from the dataset(s) "
      "(omit or set to 'all' to import and analyse all measures)",
      cxxopts::value<std::vector<std::string>>())(

      "y,years",
      "Focus on a particular year (YYYY) or "
      "inclusive range of years (YYYY-ZZZZ)",
      cxxopts::value<std::string>()->default_value("0"))(

      "j,json",
      "Print the output as JSON instead of tables.")(

      "h,help",
      "Print usage.");

  return cxxopts;
}


/*
  Parses the datasets argument passed into the command line.

  The datasets argument is optional, and if it is not included, all datasets 
  are imported. If it is included, it should be a comma-separated list of
  datasets to import. If the argument contains the value "all"
  (case-insensitive), all datasets are imported.

  @param args
    Parsed program arguments

  @return
    A std::vector of BethYw::InputFileSource instances to import

  @throws
    std::invalid_argument if the argument contains an invalid dataset with
    message: No dataset matches key <input code>

  @example
    auto cxxopts = BethYw::cxxoptsSetup();
    auto args = cxxopts.parse(argc, argv);

    auto datasetsToImport = BethYw::parseDatasetsArg(args);
 */
std::vector<BethYw::InputFileSource> BethYw::parseDatasetsArg(
    cxxopts::ParseResult& args) {

  // Retrieve all valid datasets
  size_t numDatasets = InputFiles::NUM_DATASETS;
  auto &allDatasets = InputFiles::DATASETS;

  std::vector<InputFileSource> datasetsToImport;

  // Getting dataset command line arguments
  std::vector<std::string> inputDatasets;
  try {
      inputDatasets = args["datasets"].as<std::vector<std::string>>();
  } catch (const std::domain_error) {
      for(unsigned int i = 0; i < numDatasets; i++)
          datasetsToImport.push_back(allDatasets[i]);
      return datasetsToImport;
  } catch (const std::bad_cast) {
      for(unsigned int i = 0; i < numDatasets; i++)
          datasetsToImport.push_back(allDatasets[i]);
      return datasetsToImport;
  }

  for (unsigned int i = 0; i < inputDatasets.size(); i++) {
      transform(inputDatasets[i].begin(), inputDatasets[i].end(), inputDatasets[i].begin(), ::tolower);
  }

  // Validating command line argument datasets and building a vector of datasets to import
  for (unsigned int x = 0; x < inputDatasets.size(); x++) {
      if (inputDatasets[x] == "all") {
          datasetsToImport.clear();
          for (unsigned int i = 0; i < numDatasets; i++)
              datasetsToImport.push_back(allDatasets[i]);
          return datasetsToImport;
      }

      bool isInvalidArg = true;
      for (unsigned int y = 0; y < numDatasets; y++) {
          if (inputDatasets[x] == allDatasets[y].CODE) {
              datasetsToImport.push_back(allDatasets[y]);
              isInvalidArg = false;
          }
      }

      if (isInvalidArg) throw std::invalid_argument("No dataset matches key: " + inputDatasets[x]);
  }

  return datasetsToImport;
}


/*
  Parses the optional areas command line argument. If it doesn't
  exist or exists and contains "all" as value (any case), all areas should be
  imported, i.e., the filter should be an empty set.

  The filtering of inputs should be case insensitive.

  @param args
    Parsed program arguments

  @return 
    An std::unordered_set of std::strings corresponding to specific areas
    to import, or an empty set if all areas should be imported.

  @throws
    std::invalid_argument if the argument contains an invalid areas value with
    message: Invalid input for area argument
*/
std::unordered_set<std::string> BethYw::parseAreasArg(
    cxxopts::ParseResult& args) {
  // The unordered set you will return
  std::unordered_set<std::string> areas;

  // Retrieve the areas argument like so:
  std::vector<std::string> temp;
  try {
      temp = args["areas"].as<std::vector<std::string>>();
  } catch (const std::domain_error) {
      return areas;
  } catch (const std::bad_cast) {
      return areas;
  }

  for (unsigned int i = 0; i < temp.size(); i++) {
      transform(temp[i].begin(), temp[i].end(), temp[i].begin(), ::toupper);
  }

  for (unsigned int i = 0; i < temp.size(); i++) {
      if (temp[i] == "ALL") {
          areas.clear();
          return areas;
      } else {
        areas.insert(temp[i]);
      }
  }
  
  return areas;
}


/*
  TODO: Add exception throw for invalid measures or remove documentation if not possible

  Parse the measures command line argument, which is optional. If it doesn't 
  exist or exists and contains "all" as value (any case), all measures should
  be imported.

  Unlike datasets we can't check the validity of the values as it depends
  on each individual file imported (which hasn't happened until runtime).
  Therefore, we simply fetch the list of areas and later pass it to the
  Areas::populate() function.

  The filtering of inputs should be case insensitive.

  @param args
    Parsed program arguments

  @return 
    An std::unordered_set of std::strings corresponding to specific measures
    to import, or an empty set if all measures should be imported.

  @throws
    std::invalid_argument if the argument contains an invalid measures value
    with the message: Invalid input for measures argument
*/
std::unordered_set<std::string> BethYw::parseMeasuresArg(
        cxxopts::ParseResult& args) {
    std::unordered_set<std::string> measures;

    std::vector<std::string> temp;
    try {
        temp = args["measures"].as<std::vector<std::string>>();
    } catch (const std::domain_error) {
        return measures;
    } catch (const std::bad_cast) {
        return measures;
    }

    for (unsigned int i = 0; i < temp.size(); i++) {
        transform(temp[i].begin(), temp[i].end(), temp[i].begin(), ::tolower);
    }

    for (unsigned int i = 0; i < temp.size(); i++) {
        if (temp[i] == "all") {
            measures.clear();
            return measures;
        } else {
            measures.insert(temp[i]);
        }
    }
    return measures;
}


/*
  Parses the years command line argument. Years is either a four digit year
  value, or two four digit year values separated by a hyphen (i.e. either 
  YYYY or YYYY-ZZZZ).

  @param args
    Parsed program arguments

  @return
    A std::tuple containing two unsigned ints

  @throws
    std::invalid_argument if the argument contains an invalid years value with
    the message: Invalid input for years argument
*/
std::tuple<int, int> BethYw::parseYearsArg(
        cxxopts::ParseResult& args) {
    std::tuple<int, int> years = std::make_tuple(0, 0);

    std::string temp;
    try {
        temp = args["years"].as<std::string>();
    } catch (const std::domain_error) {
        return years;
    } catch (const std::bad_cast) {
        return years;
    }

    std::regex singleAllExpr("0");
    std::regex dualAllExpr("0-0");
    std::regex singleYearExpr("[0-9][0-9][0-9][0-9]");
    std::regex dualYearExpr("[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]");

    if (std::regex_match(temp, singleAllExpr)) {
        return years;
    } else if (std::regex_match(temp, dualAllExpr)) {
        return years;
    } else if (std::regex_match(temp, singleYearExpr)) {
        return std::make_tuple(std::stoi(temp), std::stoi(temp));
    } else if (std::regex_match(temp, dualYearExpr)) {
        return std::make_tuple(std::stoi(temp.substr(0,4)), std::stoi(temp.substr(5,4)));
    } else {
        throw std::invalid_argument("Invalid input for years argument");
    }
}


/*
  Loads the areas.csv file from the directory `dir`. Parses the file and
  create the appropriate Area objects inside the Areas object passed to
  the function in the `areas` argument.

  @param areas
    The areas instance which the areas will be added to.

  @param dir
    Directory where the areas.csv file is

  @param areasFilter
    An unordered set of areas to filter, or empty to import all areas

  @return
    void

  @example
    Areas areas();

    BethYw::loadAreas(areas, "data", BethYw::parseAreasArg(args));
*/
void BethYw::loadAreas(Areas &areas, std::string dir, const StringFilterSet * const areasFilter) {
  InputFile input(dir + InputFiles::AREAS.FILE);
  auto cols = InputFiles::AREAS.COLS;
  try {
    areas.populate(input.open(),
                   SourceDataType::AuthorityCodeCSV,
                   cols,
                   areasFilter,
                   nullptr,
                   nullptr);
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::AREAS.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports datasets from `datasetsToImport` as files in `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the areas and measures will be added to.

  @param dir
    The directory where the datasets are.

  @param datasetsToImport
    A vector of InputFileSource objects.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years 
    to import, which should both be 0 to import all years.

  @return
    void

  @example
    Areas areas();

    BethYw::loadDatasets(
      areas,
      "data",
      BethYw::parseDatasetsArgument(args),
      BethYw::parseAreasArg(args),
      BethYw::parseMeasuresArg(args),
      BethYw::parseYearsArg(args));
*/
void BethYw::loadDatasets(Areas &areas,
                          std::string dir,
                          const std::vector<InputFileSource> * const datasetsToImport,
                          const StringFilterSet * const areasFilter,
                          const StringFilterSet * const measuresFilter,
                          const YearFilterTuple * const yearsFilter) noexcept {

  // Identify the dataset being imported and call the correct sub function
  for (auto iterator = datasetsToImport->begin(); iterator != datasetsToImport->end(); iterator++) {
    if (iterator->NAME == InputFiles::BIZ.NAME) {
      loadBiz(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::AQI.NAME) {
      loadAqi(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::POPDEN.NAME) {
      loadPopden(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::TRAINS.NAME) {
      loadTrains(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::COMPLETE_POPDEN.NAME) {
      loadCompletePopden(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::COMPLETE_POP.NAME) {
      loadCompletePop(areas, dir, areasFilter, measuresFilter, yearsFilter);
    } else if (iterator->NAME == InputFiles::COMPLETE_AREA.NAME) {
      loadCompleteArea(areas, dir, areasFilter, measuresFilter, yearsFilter);
    }
  }
}


/*
  Imports the Active Businesses dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Active Businesses dataset will be added to.

  @param dir
    The directory where the Active Businesses dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadBiz(Areas &areas,
                     std::string dir,
                     const StringFilterSet * const areasFilter,
                     const StringFilterSet * const measuresFilter,
                     const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile bizInput(dir + InputFiles::BIZ.FILE);
    auto biz = InputFiles::BIZ.COLS;
    areas.populateFromWelshStatsJSON(bizInput.open(), biz, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::BIZ.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::BIZ.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Air Quality Indicators dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Air Quality Indicators dataset will be added to.

  @param dir
    The directory where the Air Quality Indicators dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadAqi(Areas &areas,
                     std::string dir,
                     const StringFilterSet * const areasFilter,
                     const StringFilterSet * const measuresFilter,
                     const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile aqiInput(dir + InputFiles::AQI.FILE);
    auto aqi = InputFiles::AQI.COLS;
    areas.populateFromWelshStatsJSON(aqiInput.open(), aqi, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::AQI.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::AQI.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Population density dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Population density dataset will be added to.

  @param dir
    The directory where the Population density dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadPopden(Areas &areas,
                        std::string dir,
                        const StringFilterSet * const areasFilter,
                        const StringFilterSet * const measuresFilter,
                        const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile popdenInput(dir + InputFiles::POPDEN.FILE);
    auto popden = InputFiles::POPDEN.COLS;
    areas.populateFromWelshStatsJSON(popdenInput.open(), popden, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::POPDEN.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::POPDEN.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Rail passenger journeys dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Rail passenger journeys dataset will be added to.

  @param dir
    The directory where the Rail passenger journeys dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadTrains(Areas &areas,
                        std::string dir,
                        const StringFilterSet * const areasFilter,
                        const StringFilterSet * const measuresFilter,
                        const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile trainsInput(dir + InputFiles::TRAINS.FILE);
    auto trains = InputFiles::TRAINS.COLS;
    areas.populateFromWelshStatsJSON(trainsInput.open(), trains, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::TRAINS.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::TRAINS.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Complete Population density dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Complete Population density dataset will be added to.

  @param dir
    The directory where the Complete Population density dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadCompletePopden(Areas &areas,
                                std::string dir,
                                const StringFilterSet * const areasFilter,
                                const StringFilterSet * const measuresFilter,
                                const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completePopdenInput(dir + InputFiles::COMPLETE_POPDEN.FILE);
    auto completePopden = InputFiles::COMPLETE_POPDEN.COLS;
    areas.populateFromAuthorityByYearCSV(completePopdenInput.open(), completePopden, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_POPDEN.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_POPDEN.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Complete Population dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Complete Population density dataset will be added to.

  @param dir
    The directory where the Complete Population density dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadCompletePop(Areas &areas,
                             std::string dir,
                             const StringFilterSet * const areasFilter,
                             const StringFilterSet * const measuresFilter,
                             const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completePopInput(dir + InputFiles::COMPLETE_POP.FILE);
    auto completePop = InputFiles::COMPLETE_POP.COLS;
    areas.populateFromAuthorityByYearCSV(completePopInput.open(), completePop, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_POP.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_POP.FILE << std::endl << out_of_range.what();
  }
}


/*
  Imports the Complete Land area dataset in the directory `dir` into areas, and
  filters them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  @param areas
    The areas instance which the Complete Land area density dataset will be added to.

  @param dir
    The directory where the Complete Land area density dataset is.

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas.

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures.

  @param yearsFilter
    An two-pair tuple of unsigned ints corresponding to the range of years
    to import, which should both be 0 to import all years.

  @return
    void
 */
void BethYw::loadCompleteArea(Areas &areas,
                              std::string dir,
                              const StringFilterSet * const areasFilter,
                              const StringFilterSet * const measuresFilter,
                              const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completeAreaInput(dir + InputFiles::COMPLETE_AREA.FILE);
    auto completeArea = InputFiles::COMPLETE_AREA.COLS;
    areas.populateFromAuthorityByYearCSV(completeAreaInput.open(), completeArea, areasFilter, measuresFilter, yearsFilter);
  } catch (std::runtime_error runtimeError) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_AREA.FILE << std::endl << runtimeError.what();
  } catch (std::out_of_range out_of_range) {
    std::cerr << "Error importing dataset: " << InputFiles::COMPLETE_AREA.FILE << std::endl << out_of_range.what();
  }
}