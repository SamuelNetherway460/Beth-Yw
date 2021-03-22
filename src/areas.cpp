


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  The file contains the Areas class implementation. Areas are the top
  level of the data structure in Beth Yw? for now.

  Areas is also responsible for importing data from a stream (using the
  various populate() functions) and creating the Area and Measure objects.
*/

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

#include "lib_json.hpp"

#include "datasets.h"
#include "areas.h"
#include "measure.h"

/*
  An alias for the imported JSON parsing library.
*/
using json = nlohmann::json;

/*
  Basic constructor for an Areas object.

  @example
    Areas data = Areas();
*/
Areas::Areas() {}


/*
  Separates a line into individual tokens separated by the specified delimiter.

  @param ls
    A std::istream for the line.

  @param line
    The std::string line to be separated into tokens.

  @param delimiter
    The character used to know where to separate the line into tokens.

  @return
    A std::vector containing the std::string tokens.

 */
std::vector<std::string> Areas::getLineTokens(std::istream &ls,
                                              std::string line,
                                              char delimiter) {
  std::string token;
  std::vector<std::string> tokens;
  std::stringstream lineStream(line);

  // Split each line into individual tokens separated by the delimiter
  while (std::getline(lineStream, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}


/*
  Adds a particular Area to the Areas object.

  If an Area already exists with the same local authority code, all
  data contained within the existing Area is overwritten with those in
  the new Area (i.e. they are combined, but the new Area's data takes
  precedence).

  @param key
    The local authority code of the Area

  @param value
    The Area object that will contain the Measure objects

  @return
    void

  @example
    Areas data = Areas();
    std::string localAuthorityCode = "W06000023";
    Area area(localAuthorityCode);
    data.setArea(localAuthorityCode, area);
*/
void Areas::setArea(const std::string key, Area &area) {
  if (areas.find(key) != areas.end()) {
    areas.find(key)->second.overwrite(area);
  } else {
    areas[key] = area;
  }
}


/*
  Retrieves an Area instance with a given local authority code.

  @param key
    The local authority code to find the Area instance of

  @return
    An Area object

  @throws
    std::out_of_range if an Area with the set local authority code does not
    exist in this Areas instance

  @example
    Areas data = Areas();
    std::string localAuthorityCode = "W06000023";
    Area area(localAuthorityCode);
    data.setArea(localAuthorityCode, area);
    ...
    Area area2 = areas.getArea("W06000023");
*/
Area& Areas::getArea(const std::string key) {
  if (areas.find(key) != areas.end()) {
    return areas.find(key)->second;
  } else {
    throw std::out_of_range("No area found matching " + key);
  }
}


/*
  Retrieves the number of Areas within the container.

  @return
    The number of Area instances

  @example
    Areas data = Areas();
    std::string localAuthorityCode = "W06000023";
    Area area(localAuthorityCode);
    data.setArea(localAuthorityCode, area);
    
    auto size = areas.size(); // returns 1
*/
int Areas::size() const noexcept {
  return areas.size();
}


/*
  TODO: Documentation & check , possibly add more exceptions
  TODO: Possibly split into more methods

  This function specifically parses the compiled areas.csv file of local 
  authority codes, and their names in English and Welsh.

  This is a simple dataset that is a comma-separated values file (CSV), where
  the first row gives the name of the columns, and then each row is a set of
  data.

  For this coursework, you can assume that areas.csv will always have the same
  three columns in the same order.

  Once the data is parsed, you need to create the appropriate Area objects and
  insert them in to a Standard Library container within Areas.

  @param is
    The input stream from InputSource

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings for areas to import,
    or an empty set if all areas should be imported

  @return
    void

  @see
    See datasets.h for details of how the variable cols is organised

  @see
    See bethyw.cpp for details of how the variable areasFilter is created

  @example
    InputFile input("data/areas.csv");
    auto is = input.open();

    auto cols = InputFiles::AREAS.COLS;

    auto areasFilter = BethYw::parseAreasArg();

    Areas data = Areas();
    areas.populateFromAuthorityCodeCSV(is, cols, &areasFilter);

  @throws 
    std::runtime_error if a parsing error occurs (e.g. due to a malformed file)
    std::out_of_range if there are not enough columns in cols
*/
void Areas::populateFromAuthorityCodeCSV(
    std::istream &is,
    const BethYw::SourceColumnMapping &cols,
    const StringFilterSet * const areasFilter) {

  std::string line, token;
  std::vector<std::string> tokens;

  std::getline(is, line);
  std::stringstream ls(line);
  tokens = getLineTokens(ls, line, ',');

  // Check for correct number of columns
  if (cols.size() == 3) {
    // Check for correct column names
    if (tokens[0] == cols.at(BethYw::SourceColumn::AUTH_CODE) &&
        tokens[1] == cols.at(BethYw::SourceColumn::AUTH_NAME_ENG) &&
        tokens[2] == cols.at(BethYw::SourceColumn::AUTH_NAME_CYM)) {

      // Parse column data
      while (std::getline(is, line)) {
        tokens = getLineTokens(ls, line, ',');
        if (areasFilter == nullptr) {
          Area area(tokens[0]);
          try {
            area.setName("eng", tokens[1]);
            area.setName("cym", tokens[2]);
            areas[tokens[0]] = area;
          } catch (std::invalid_argument invalidArgument) {
            std::cerr << invalidArgument.what();
          }
        } else if (areasFilter->find(tokens[0]) != areasFilter->end() ||
            areasFilter->size() == 0) {
          Area area(tokens[0]);
          try {
            area.setName("eng", tokens[1]);
            area.setName("cym", tokens[2]);
            areas[tokens[0]] = area;
          } catch (std::invalid_argument invalidArgument) {
            std::cerr << invalidArgument.what();
          }
        }
      }
    } else {
      throw std::out_of_range("Incorrect column names");
    }
  } else {
    throw std::out_of_range("Not enough columns");
  }
}


/*
  TODO: Areas::populateFromWelshStatsJSON(is,
                                          cols,
                                          areasFilter,
                                          measuresFilter,
                                          yearsFilter)
  TODO: Possibly break up into further methods - look at comments

  Data from StatsWales is in the JSON format, and contains three
  top-level keys: odata.metadata, value, odata.nextLink. value contains the
  data we need. Rather than been hierarchical, it contains data as a
  continuous list (e.g. as you would find in a table). For each row in value,
  there is a mapping of various column headings and their respective values.

  Therefore, you need to go through the items in value (in a loop)
  using a JSON library. To help you, I've selected the nlohmann::json
  library that you must use for your coursework. Read up on how to use it here:
  https://github.com/nlohmann/json

  Example of using this library:
    - Reading/parsing in from a stream is very simply using the >> operator:
        json j;
        stream >> j;

    - Looping through parsed JSON is done with a simple for each loop. Inside
      the loop, you can access each using the array syntax, with the key/
      column name, e.g. data["Localauthority_ItemName_ENG"] gives you the
      local authority name:
        for (auto& el : j["value"].items()) {
           auto &data = el.value();
           std::string localAuthorityCode = data["Localauthority_ItemName_ENG"];
           // do stuff here...
        }

  In this function, you will have to parse the JSON datasets, extracting
  the local authority code, English name (the files only contain the English
  names), and each measure by year.

  If you encounter an Area that does not exist in the Areas container, you
  should create the Area object

  If areasFilter is a non-empty set only include areas matching the filter. If
  measuresFilter is a non-empty set only include measures matching the filter.
  If yearsFilter is not equal to <0,0>, only import years within the range
  specified by the tuple (inclusive).

  I've provided the column names for each JSON file that you need to parse
  as std::strings in datasets.h. This mapping should be passed through to the
  cols parameter of this function.

  Note that in the JSON format, years are stored as strings, but we need
  them as ints. When retrieving values from the JSON library, you will
  have to cast them to the right type.

  @param is
    The input stream from InputSource

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings of areas to import,
    or an empty set if all areas should be imported

  @param measuresFilter
    An unmodifiable pointer to set of unmodifiable strings of measures to import,
    or an empty set if all measures should be imported

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as the range of years to be imported (inclusively)

  @return
    void

  @throws 
    std::runtime_error if a parsing error occurs (e.g. due to a malformed file)
    std::out_of_range if there are not enough columns in cols

  @see
    See datasets.h for details of how the variable cols is organised

  @see
    See bethyw.cpp for details of how the variable areasFilter is created

  @example
    InputFile input("data/popu1009.json");
    auto is = input.open();

    auto cols = InputFiles::DATASETS["popden"].COLS;

    auto areasFilter = BethYw::parseAreasArg();
    auto measuresFilter = BethYw::parseMeasuresArg();
    auto yearsFilter = BethYw::parseMeasuresArg();

    Areas data = Areas();
    areas.populateFromWelshStatsJSON(
      is,
      cols,
      &areasFilter,
      &measuresFilter,
      &yearsFilter);
*/
void Areas::populateFromWelshStatsJSON(std::istream& is,
                                       const BethYw::SourceColumnMapping& cols,
                                       const StringFilterSet * const areasFilter,
                                       const StringFilterSet * const measuresFilter,
                                       const YearFilterTuple * const yearsFilter) {
  std::string str;
  std::string fileContents;

  //TODO: Throw exception if cannot get content from file
  while (std::getline(is, str))
  {
    fileContents += str;
    fileContents.push_back('\n');
  }

  json j = json::parse(fileContents);

  for (auto& el : j["value"].items()) {
    auto &data = el.value();
    std::string localAuthorityCode = data[cols.at(BethYw::SourceColumn::AUTH_CODE)];
    std::string authNameEnglish = data[cols.at(BethYw::SourceColumn::AUTH_NAME_ENG)];

    // Retrieve measure code and convert to lower case
    std::string measureCode;
    if (cols.find(BethYw::SourceColumn::MEASURE_CODE) == cols.end()) {
      measureCode = cols.at(BethYw::SourceColumn::SINGLE_MEASURE_CODE);
    } else {
      measureCode = data[cols.at(BethYw::SourceColumn::MEASURE_CODE)];
    }
    transform(measureCode.begin(), measureCode.end(), measureCode.begin(), ::tolower);

    // Retrieve measure name and convert to lower case
    std::string measureName;
    if (cols.find(BethYw::SourceColumn::MEASURE_CODE) == cols.end()) {
      measureName = cols.at(BethYw::SourceColumn::SINGLE_MEASURE_NAME);
    } else {
      measureName = data[cols.at(BethYw::SourceColumn::MEASURE_NAME)];
    }

    unsigned int year = safeStringToInt(data[cols.at(BethYw::SourceColumn::YEAR)]);

    // Retrieve value and convert to double if necessary
    double value;
    if (data[cols.at(BethYw::SourceColumn::VALUE)].is_number()) {
      value = data[cols.at(BethYw::SourceColumn::VALUE)];
    } else {
      value = safeStringToDouble(data[cols.at(BethYw::SourceColumn::VALUE)]);
    }

    Area area(localAuthorityCode);
    try {
      area.setName("eng", authNameEnglish);
    } catch (std::invalid_argument invalidArgument) {
      std::cerr << invalidArgument.what();
    }
    Measure measure(measureCode, measureName);

    // Apply years filtering
    if (yearsFilter == nullptr) {
      measure.setValue(year, value);
    } else if ((year >= std::get<0>(*yearsFilter) && year <= std::get<1>(*yearsFilter)) ||
               (std::get<0>(*yearsFilter) == 0 && std::get<1>(*yearsFilter) == 0)) {
      measure.setValue(year, value);
    }

    // Apply measures filtering
    if (measuresFilter == nullptr) {
      area.setMeasure(measureCode, measure);
    } else if (measuresFilter->find(measureCode) != measuresFilter->end() ||
               measuresFilter->size() == 0) {
      area.setMeasure(measureCode, measure);
    }

    // Apply areas filtering
    if (areasFilter == nullptr) {
      this->setArea(localAuthorityCode, area);
    } else if (areasFilter->find(localAuthorityCode) != areasFilter->end() ||
               areasFilter->size() == 0) {
      this->setArea(localAuthorityCode, area);
    }
  }
}


/*
  Safely converts a std::string to an int.

  @param str
    The std::string to convert to an int.

  @return
    The integer value converted from the string.

  @throws
    std::runtime_error if the std::string could not be converted to an int.
 */
int Areas::safeStringToInt(const std::string &str) const {
  std::stringstream ss(str);
  int num;
  if ((ss >> num).fail()) throw std::runtime_error("Cannot cast std::string " + str + " to int");
  return num;
}


/*
  Safely converts a std::string to an int.

  @param str
    The std::string to convert to an int.

  @return
    The integer value converted from the string.

  @throws
    std::runtime_error if the std::string could not be converted to an int.
 */
double Areas::safeStringToDouble(const std::string &str) const {
  std::stringstream ss(str);
  double num;
  if ((ss >> num).fail()) throw std::runtime_error("Cannot cast std::string " + str + " to int");
  return num;
}


/*
  TODO: Areas::populateFromAuthorityByYearCSV(is,
                                              cols,
                                              areasFilter,
                                              yearFilter)
  TODO: Check that the correct cols are being passed in

  This function imports CSV files that contain a single measure. The 
  CSV file consists of columns containing the authority code and years.
  Each row contains an authority code and values for each year (or no value
  if the data doesn't exist).

  Note that these files do not include the names for areas, instead you 
  have to rely on the names already populated through 
  Areas::populateFromAuthorityCodeCSV();

  The datasets that will be parsed by this function are
   - complete-popu1009-area.csv
   - complete-popu1009-pop.csv
   - complete-popu1009-opden.csv

  @param is
    The input stream from InputSource

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings for areas to import,
    or an empty set if all areas should be imported

  @param measuresFilter
    An unmodifiable pointer to set of strings for measures to import, or an empty
    set if all measures should be imported

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported

  @return
    void

  @see
    See datasets.h for details of how the variable cols is organised

  @see
    See bethyw.cpp for details of how the variable areasFilter is created

  @example
    InputFile input("data/complete-popu1009-pop.csv");
    auto is = input.open();

    auto cols = InputFiles::DATASETS["complete-pop"].COLS;

    auto areasFilter = BethYw::parseAreasArg();
    auto yearsFilter = BethYw::parseYearsArg();

    Areas data = Areas();
    areas.populateFromAuthorityCodeCSV(is, cols, &areasFilter, &yearsFilter);

  @throws 
    std::runtime_error if a parsing error occurs (e.g. due to a malformed file)
    std::out_of_range if there are not enough columns in cols
*/
void Areas::populateFromAuthorityByYearCSV(std::istream& is,
                                           const BethYw::SourceColumnMapping& cols,
                                           const StringFilterSet * const areasFilter,
                                           const StringFilterSet * const measuresFilter,
                                           const YearFilterTuple * const yearsFilter) {

}


/*
  TODO: Add check for working stream and has content
  TODO: Check that the correct cols are being passed in

  Parse data from an standard input stream `is`, that has data of a particular
  `type`, and with a given column mapping in `cols`.

  This function should look at the `type` and hand off to one of the three 
  functions populate………() functions.

  The function must check if the stream is in working order and has content.

  @param is
    The input stream from InputSource

  @param type
    A value from the BethYw::SourceDataType enum which states the underlying
    data file structure

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @return
    void

  @throws 
    std::runtime_error if a parsing error occurs (e.g. due to a malformed file),
    the stream is not open/valid/has any contents, or an unexpected type
    is passed in.
    std::out_of_range if there are not enough columns in cols

  @see
    See datasets.h for details of the values variable type can have

  @see
    See datasets.h for details of how the variable cols is organised

  @see
    See bethyw.cpp for details of how the variable areasFilter is created

  @example
    InputFile input("data/popu1009.json");
    auto is = input.open();

    auto cols = InputFiles::DATASETS["popden"].COLS;

    Areas data = Areas();
    areas.populate(
      is,
      DataType::WelshStatsJSON,
      cols);
*/
void Areas::populate(std::istream &is,
                     const BethYw::SourceDataType &type,
                     const BethYw::SourceColumnMapping &cols) {
  if (type == BethYw::AuthorityCodeCSV) {
    populateFromAuthorityCodeCSV(is, cols);
  } else if (type == BethYw::AuthorityByYearCSV) {
    populateFromAuthorityByYearCSV(is, cols);
  } else if (type == BethYw::WelshStatsJSON) {
    populateFromWelshStatsJSON(is, cols);
  } else {
    throw std::runtime_error("Areas::populate: Unexpected data type");
  }
}


/*
  TODO: Add check for working stream and has content
  TODO: Check that the correct cols are being passed in

  Parse data from an standard input stream, that is of a particular type,
  and with a given column mapping, filtering for specific areas, measures,
  and years, and fill the container.

  This function should look at the `type` and hand off to one of the three 
  functions you've implemented above.

  The function must check if the stream is in working order and has content.

  This overloaded function includes pointers to the three filters for areas,
  measures, and years.

  @param is
    The input stream from InputSource

  @param type
    A value from the BethYw::SourceDataType enum which states the underlying
    data file structure

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @param areasFilter
    An umodifiable pointer to set of umodifiable strings for areas to import,
    or an empty set if all areas should be imported

  @param measuresFilter
    An umodifiable pointer to set of umodifiable strings for measures to import,
    or an empty set if all measures should be imported

  @param yearsFilter
    An umodifiable pointer to an umodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported

  @return
    void

  @throws 
    std::runtime_error if a parsing error occurs (e.g. due to a malformed file),
    the stream is not open/valid/has any contents, or an unexpected type
    is passed in.
    std::out_of_range if there are not enough columns in cols

  @see
    See datasets.h for details of the values variable type can have

  @see
    See datasets.h for details of how the variable cols is organised

  @see
    See bethyw.cpp for details of how the variables areasFilter, measuresFilter,
    and yearsFilter are created

  @example
    InputFile input("data/popu1009.json");
    auto is = input.open();

    auto cols = InputFiles::DATASETS["popden"].COLS;

    auto areasFilter = BethYw::parseAreasArg();
    auto measuresFilter = BethYw::parseMeasuresArg();
    auto yearsFilter = BethYw::parseMeasuresArg();

    Areas data = Areas();
    areas.populate(
      is,
      DataType::WelshStatsJSON,
      cols,
      &areasFilter,
      &measuresFilter,
      &yearsFilter);
*/
void Areas::populate(
    std::istream &is,
    const BethYw::SourceDataType &type,
    const BethYw::SourceColumnMapping &cols,
    const StringFilterSet * const areasFilter,
    const StringFilterSet * const measuresFilter,
    const YearFilterTuple * const yearsFilter) {
  if (type == BethYw::AuthorityCodeCSV) {
    populateFromAuthorityCodeCSV(is, cols, areasFilter);
  } else if (type == BethYw::AuthorityByYearCSV) {
    populateFromAuthorityByYearCSV(is, cols, areasFilter, measuresFilter, yearsFilter);
  } else if (type == BethYw::WelshStatsJSON) {
    populateFromWelshStatsJSON(is, cols, areasFilter, measuresFilter, yearsFilter);
  } else {
    throw std::runtime_error("Areas::populate: Unexpected data type");
  }
}


/*
  Converts an Areas object into a JSON in the form of a std::string. The JSON contains
  all areas and their respective measures and names.If the Areas object is empty, an
  empty JSON object is printed.
  
  @return
    std::string of JSON

  @see
    area.cpp for the generation of a JSON object containing the Measure(s) for an Area object.

  @see
    area.cpp for the generation of a JSON object containing names for an Area object.

  @example
    InputFile input("data/popu1009.json");
    auto is = input.open();

    auto cols = InputFiles::DATASETS["popden"].COLS;

    auto areasFilter = BethYw::parseAreasArg();
    auto measuresFilter = BethYw::parseMeasuresArg();
    auto yearsFilter = BethYw::parseMeasuresArg();

    Areas data = Areas();
    std::cout << data.toJSON();
*/
std::string Areas::toJSON() const {
  if (areas.empty()) return "{}";

  json a;
  for (auto iterator = areas.begin(); iterator != areas.end(); iterator++) {
    a[iterator->first];
    if(!iterator->second.getMeasures().empty())
      a[iterator->first]["measures"] = iterator->second.getJsonMeasures();
    a[iterator->first]["names"] = iterator->second.getJsonNames();
  }

  std::string dump = a.dump();
  return a.dump();
}


/*
  Adds all imported area data to a os stream. Area objects are ordered alphabetically by
  their local authority code. Measure objects within each Area are ordered alphabetically
  by their codename.

  @param os
    The output stream to write to

  @param areas
    The Areas object to write to the output stream

  @return
    Reference to the output stream

  @example
    Areas areas();
    std::cout << areas << std::end;
*/
std::ostream& operator<<(std::ostream &os, const Areas &areas) {
  for (auto iterator = areas.areas.begin(); iterator != areas.areas.end(); iterator++) {
    os << iterator->second;
  }
  return os;
}

