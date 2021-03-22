


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

  TODO: This file contains numerous functions you must implement. Each one
  is denoted with a TODO in the block comment. Note that some code has been
  provided in some functions to get you started, but you should read through
  this code and make sure it is safe and complete. You may need to remove or
  modify the provided code to get your program to work fully. You may implement
  additional functions not specified.
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
    std::cerr << runtimeError.what();
    return 0;//TODO: Possibly change to an error code
  }

  if (args.count("json")) {
    // The output as JSON
    std::cout << data.toJSON() << std::endl;
  } else {
    // The output as tables
    std::cout << data;
  }

  return 0;
}


/*
  This function sets up and returns a valid cxxopts object. You do not need to
  modify this function.

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
  Parse the datasets argument passed into the command line. 

  The datasets argument is optional, and if it is not included, all datasets 
  should be imported. If it is included, it should be a comma-separated list of 
  datasets to import. If the argument contains the value "all"
  (case-insensitive), all datasets should be imported.

  This function validates the passed in dataset names against the codes in
  DATASETS array in the InputFiles namespace in datasets.h. If an invalid code
  is entered, throw a std::invalid_argument with the message:
  No dataset matches key: <input code>
  where <input name> is the name supplied by the user through the argument.

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

  // Retrieve all valid datasets, see datasets.h
  size_t numDatasets = InputFiles::NUM_DATASETS;
  auto &allDatasets = InputFiles::DATASETS;

  // Create the container for the return type
  std::vector<InputFileSource> datasetsToImport;

  // You can get the std::vector of arguments from cxxopts like this.
  // Note that this function will throw an exception if datasets is not set as 
  // an argument. Check the documentation! Read it and understand it.
  std::vector<std::string> inputDatasets;
  try {
      inputDatasets = args["datasets"].as<std::vector<std::string>>();
  } catch (const std::domain_error) {
      for(unsigned int i = 0; i < numDatasets; i++)
          datasetsToImport.push_back(allDatasets[i]);//TODO: Look into
      return datasetsToImport;
  } catch (const std::bad_cast) {
      for(unsigned int i = 0; i < numDatasets; i++)
          datasetsToImport.push_back(allDatasets[i]);
      return datasetsToImport;
  }

  for (unsigned int i = 0; i < inputDatasets.size(); i++) {
      transform(inputDatasets[i].begin(), inputDatasets[i].end(), inputDatasets[i].begin(), ::tolower);
  }

  // You now need to compare the strings in this vector to the keys in
  // allDatasets above. Populate datasetsToImport with the values
  // from allDatasets above and then return a vector
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
  Parses the areas command line argument, which is optional. If it doesn't 
  exist or exists and contains "all" as value (any case), all areas should be
  imported, i.e., the filter should be an empty set.

  Unlike datasets we can't check the validity of the values as it depends
  on each individual file imported (which hasn't happened until runtime).
  Therefore, we simply fetch the list of areas and later pass it to the
  Areas::populate() function.

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

  std::regex str_expr("W[0-9]+");
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
  Parse the years command line argument. Years is either a four digit year 
  value, or two four digit year values separated by a hyphen (i.e. either 
  YYYY or YYYY-ZZZZ).

  This should be parsed as two integers and inserted into a std::tuple,
  representing the start and end year (inclusive). If one or both values are 0,
  then there is no filter to be applied. If no year argument is given return
  <0,0> (i.e. to import all years). You will have to search
  the web for how to construct std::tuple objects! 

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
  TODO: Documentation & check exception handling

  Load the areas.csv file from the directory `dir`. Parse the file and
  create the appropriate Area objects inside the Areas object passed to
  the function in the `areas` argument.

  @param areas
    An Areas instance that should be modified (i.e. the populate() function
    in the instance should be called)

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
void BethYw::loadAreas(Areas &areas, std::string dir, StringFilterSet *const areasFilter) {
  InputFile input(dir + InputFiles::AREAS.FILE);
  //InputFile input("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/areas.csv"); //TODO:* Remove after testing
  auto cols = InputFiles::AREAS.COLS;
  areas.populate(input.open(),
                SourceDataType::AuthorityCodeCSV,
                cols,
                areasFilter,
                nullptr,
                nullptr);
}


/*
  TODO: Documentation

  Import datasets from `datasetsToImport` as files in `dir` into areas, and
  filtering them with the `areasFilter`, `measuresFilter`, and `yearsFilter`.

  The actual filtering will be done by the Areas::populate() function, thus 
  you need to merely pass pointers on to these filters.

  This function should promise not to throw an exception. If there is an
  error/exception thrown in any function called by thus function, catch it and
  output 'Error importing dataset:', followed by a new line and then the output
  of the what() function on the exception.

  @param areas
    An Areas instance that should be modified (i.e. datasets loaded into it)

  @param dir
    The directory where the datasets are

  @param datasetsToImport
    A vector of InputFileSource objects

  @param areasFilter
    An unordered set of areas (as authority codes encoded in std::strings)
    to filter, or empty to import all areas

  @param measuresFilter
    An unordered set of measures (as measure codes encoded in std::strings)
    to filter, or empty to import all measures

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
  //TODO: Documentation
 */
void BethYw::loadBiz(Areas &areas,
                     std::string dir,
                     const StringFilterSet * const areasFilter,
                     const StringFilterSet * const measuresFilter,
                     const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile bizInput(dir + InputFiles::BIZ.FILE);
    //InputFile bizInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/econ0080.json");//TODO:* Remove once testing is done
    auto biz = InputFiles::BIZ.COLS;
    areas.populateFromWelshStatsJSON(bizInput.open(), biz, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::BIZ.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadAqi(Areas &areas,
                     std::string dir,
                     const StringFilterSet * const areasFilter,
                     const StringFilterSet * const measuresFilter,
                     const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile aqiInput(dir + InputFiles::AQI.FILE);
    //InputFile aqiInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/envi0201.json");//TODO:* Remove once testing is done
    auto aqi = InputFiles::AQI.COLS;
    areas.populateFromWelshStatsJSON(aqiInput.open(), aqi, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::AQI.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadPopden(Areas &areas,
                        std::string dir,
                        const StringFilterSet * const areasFilter,
                        const StringFilterSet * const measuresFilter,
                        const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile popdenInput(dir + InputFiles::POPDEN.FILE);
    //InputFile popdenInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/popu1009.json");//TODO:* Remove once testing is done
    auto popden = InputFiles::POPDEN.COLS;
    areas.populateFromWelshStatsJSON(popdenInput.open(), popden, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::POPDEN.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadTrains(Areas &areas,
                        std::string dir,
                        const StringFilterSet * const areasFilter,
                        const StringFilterSet * const measuresFilter,
                        const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile trainsInput(dir + InputFiles::TRAINS.FILE);
    //InputFile trainsInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/tran0152.json");//TODO:* Remove once testing is done
    auto trains = InputFiles::TRAINS.COLS;
    areas.populateFromWelshStatsJSON(trainsInput.open(), trains, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::TRAINS.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadCompletePopden(Areas &areas,
                                std::string dir,
                                const StringFilterSet * const areasFilter,
                                const StringFilterSet * const measuresFilter,
                                const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completePopdenInput(dir + InputFiles::COMPLETE_POPDEN.FILE);
    //InputFile completePopdenInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/complete-popu1009-popden.csv");//TODO:* Remove once testing is done
    auto completePopden = InputFiles::COMPLETE_POPDEN.COLS;
    areas.populateFromAuthorityByYearCSV(completePopdenInput.open(), completePopden, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::COMPLETE_POPDEN.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadCompletePop(Areas &areas,
                             std::string dir,
                             const StringFilterSet * const areasFilter,
                             const StringFilterSet * const measuresFilter,
                             const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completePopInput(dir + InputFiles::COMPLETE_POP.FILE);
    //InputFile completePopInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/complete-popu1009-pop.csv");//TODO:* Remove once testing is done
    auto completePop = InputFiles::COMPLETE_POP.COLS;
    areas.populateFromAuthorityByYearCSV(completePopInput.open(), completePop, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::COMPLETE_POP.FILE << std::endl << e.what();
  }
}


/*
  //TODO: Documentation
 */
void BethYw::loadCompleteArea(Areas &areas,
                              std::string dir,
                              const StringFilterSet * const areasFilter,
                              const StringFilterSet * const measuresFilter,
                              const YearFilterTuple * const yearsFilter) noexcept {
  try {
    InputFile completeAreaInput(dir + InputFiles::COMPLETE_AREA.FILE);
    //InputFile completeAreaInput("/Users/samuelnetherway/Nextcloud/Development/C++/BethYw/datasets/complete-popu1009-area.csv");//TODO:* Remove once testing is done
    auto completeArea = InputFiles::COMPLETE_AREA.COLS;
    areas.populateFromAuthorityByYearCSV(completeAreaInput.open(), completeArea, areasFilter, measuresFilter, yearsFilter);
  } catch (std::exception e) {//TODO: Possibly replace with multiple different exception types
    std::cout << "Error importing dataset: " << InputFiles::COMPLETE_AREA.FILE << std::endl << e.what();
  }
}