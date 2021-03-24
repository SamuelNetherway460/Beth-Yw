


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
  This function specifically parses the compiled areas.csv file of local
  authority codes, and their names in English and Welsh. The areas filter
  is applied to limit output to user specified areas.

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

  @throws std::runtime_error
    If a parsing error occurs (e.g. due to a malformed file)

  @throws std::out_of_range
    If there are not enough columns in cols
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
  if (tokens.size() == 3) {
    // Check for correct column names
    if (tokens[0] == cols.at(BethYw::SourceColumn::AUTH_CODE) &&
        tokens[1] == cols.at(BethYw::SourceColumn::AUTH_NAME_ENG) &&
        tokens[2] == cols.at(BethYw::SourceColumn::AUTH_NAME_CYM)) {

      // Parse column data
      while (std::getline(is, line)) {
        tokens = getLineTokens(ls, line, ',');

        if (areasFilter == nullptr) {
          parseAreaFromAuthorityCodeCSV(tokens);
        } else if (areasFilter->size() == 0) {
          parseAreaFromAuthorityCodeCSV(tokens);
        } else {
          // Advanced area filtering
          for (auto iterator = areasFilter->begin(); iterator != areasFilter->end(); iterator++) {
            if (contains(tokens[0], iterator->data()) ||
                contains(tokens[1], iterator->data()) ||
                contains(tokens[2], iterator->data())) {
              parseAreaFromAuthorityCodeCSV(tokens);
            }
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
  Parses a single area found in the area.csv file and adds it to the areas map.

  @param lineTokens
    A vector of std::string containing each individual piece of data.
 */
void Areas::parseAreaFromAuthorityCodeCSV(std::vector<std::string> lineTokens) noexcept {
  Area area(lineTokens[0]);
  try {
    area.setName("eng", lineTokens[1]);
    area.setName("cym", lineTokens[2]);
    areas[lineTokens[0]] = area;
  } catch (std::invalid_argument invalidArgument) {
    std::cerr << invalidArgument.what();
  }
}


/*
  Parses the following four JSON datasets:
  - econ0080.json
  - envi0201.json
  - popu1009.json
  - tran0152.json

  Data extracted is used to generate Area objects containing their respective
  measures and names in different languages.

  Data from StatsWales is in the JSON format that contains three
  top-level keys: odata.metadata, value, odata.nextLink. value contains the
  data we need. Rather than been hierarchical, it contains data as a
  continuous list (e.g. as you would find in a table). For each row in value,
  there is a mapping of various column headings and their respective values.

  @param is
    The input stream from InputSource.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the JSON data names.

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings of areas to import,
    or an empty set if all areas should be imported.

  @param measuresFilter
    An unmodifiable pointer to set of unmodifiable strings of measures to import,
    or an empty set if all measures should be imported.

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as the range of years to be imported (inclusively).

  @return
    void

  @throws std::runtime_error
    If a parsing error occurs (e.g. due to a malformed file).

  @throws std::out_of_range
    If there are not enough columns in cols.

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
  checkFileStatus(is);

  std::string str;
  std::string fileContents;

  // Get entire file contents
  while (std::getline(is, str))
  {
    fileContents += str;
    fileContents.push_back('\n');
  }

  json j = json::parse(fileContents);

  // Iterate through the contents of the JSON and extract all relevant area data
  for (auto& el : j["value"].items()) {
    nlohmann::basic_json<> &data = el.value();
    std::string localAuthorityCode = data[cols.at(BethYw::SourceColumn::AUTH_CODE)];
    std::string authNameEnglish = data[cols.at(BethYw::SourceColumn::AUTH_NAME_ENG)];

    std::string measureCode = retrieveMeasureCodeFromJSON(cols, data);
    std::string measureName = retrieveMeasureNameFromJSON(cols, data);
    unsigned int year = safeStringToInt(data[cols.at(BethYw::SourceColumn::YEAR)]);
    double value = retrieveMeasureValueFromJSON(cols, data);

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
    } else if (areasFilter->size() == 0) {
      this->setArea(localAuthorityCode, area);
    } else {
      // Advanced area filtering
      for (auto iterator = areasFilter->begin(); iterator != areasFilter->end(); iterator++) {
        if (contains(localAuthorityCode, iterator->data()) ||
            contains(authNameEnglish, iterator->data())) {
          this->setArea(localAuthorityCode, area);
        }
      }
    }
  }
}


/*
  Retrieves the measure code for a particular measure from a JSON dataset.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the JSON data names.

  @param data
    The data for the current JSON object being processed.

  @return
    A std::string measure code.
 */
std::string Areas::retrieveMeasureCodeFromJSON(const BethYw::SourceColumnMapping& cols,
                                               nlohmann::basic_json<> &data) {
  std::string measureCode;
  if (cols.find(BethYw::SourceColumn::MEASURE_CODE) == cols.end()) {
    measureCode = cols.at(BethYw::SourceColumn::SINGLE_MEASURE_CODE);
  } else {
    measureCode = data[cols.at(BethYw::SourceColumn::MEASURE_CODE)];
  }
  transform(measureCode.begin(), measureCode.end(), measureCode.begin(), ::tolower);
  return measureCode;
}


/*
  Retrieves the measure name for a particular measure from a JSON dataset.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the JSON data names.

  @param data
    The data for the current JSON object being processed.

  @return
    A std::string measure name.
 */
std::string Areas::retrieveMeasureNameFromJSON(const BethYw::SourceColumnMapping& cols,
                                               nlohmann::basic_json<> &data) {
  std::string measureName;
  if (cols.find(BethYw::SourceColumn::MEASURE_CODE) == cols.end()) {
    measureName = cols.at(BethYw::SourceColumn::SINGLE_MEASURE_NAME);
  } else {
    measureName = data[cols.at(BethYw::SourceColumn::MEASURE_NAME)];
  }
  return measureName;
}


/*
  Retrieves the measure value for a particular year from a JSON dataset.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the JSON data names.

  @param data
    The data for the current JSON object being processed.

  @return
    The measure value for a particular year as a double type.
 */
double Areas::retrieveMeasureValueFromJSON(const BethYw::SourceColumnMapping& cols,
                                               nlohmann::basic_json<> &data) {
  double value;
  if (data[cols.at(BethYw::SourceColumn::VALUE)].is_number()) {
    value = data[cols.at(BethYw::SourceColumn::VALUE)];
  } else {
    value = safeStringToDouble(data[cols.at(BethYw::SourceColumn::VALUE)]);
  }
  return value;
}


/*
  This function imports CSV files that contain a single measure. The 
  CSV file consists of columns containing the authority code and years.
  Each row contains an authority code and values for each year (or no value
  if the data doesn't exist).

  The datasets that will be parsed by this function are
   - complete-popu1009-area.csv
   - complete-popu1009-pop.csv
   - complete-popu1009-opden.csv

  @param is
    The input stream from InputSource.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file.

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings for areas to import,
    or an empty set if all areas should be imported

  @param measuresFilter
    An unmodifiable pointer to set of strings for measures to import, or an empty
    set if all measures should be imported.

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported.

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

  @throws std::runtime_error
    If a parsing error occurs (e.g. due to a malformed file)

  @throws std::out_of_range
    If there are not enough columns in cols.
*/
void Areas::populateFromAuthorityByYearCSV(std::istream& is,
                                           const BethYw::SourceColumnMapping& cols,
                                           const StringFilterSet * const areasFilter,
                                           const StringFilterSet * const measuresFilter,
                                           const YearFilterTuple * const yearsFilter) {
  checkFileStatus(is);

  std::string line, token;
  std::vector<std::string> lineTokens;

  std::getline(is, line);
  std::stringstream ls(line);
  lineTokens = getLineTokens(ls, line, ',');

  std::vector<unsigned int> years;

  // Check format of input dataset for correctness
  if (lineTokens[0] == cols.at(BethYw::SourceColumn::AUTH_CODE)) {
    if (lineTokens.size() == 12) {

      years = parseYearColumns(lineTokens);
      // Parse each line of data
      while (std::getline(is, line)) {
        lineTokens = getLineTokens(ls, line, ',');

        // Apply areas filtering and parse if should be included
        // Avoid computation of parsing an area and its measures if not required by filter
        if (areasFilter == nullptr) {
          parseAreaSingleCSV(lineTokens, cols, years, measuresFilter, yearsFilter);
        } else if (areasFilter->size() == 0) {
          parseAreaSingleCSV(lineTokens, cols, years, measuresFilter, yearsFilter);
        } else {
          // Advanced area filtering
          for (auto iterator = areasFilter->begin(); iterator != areasFilter->end(); iterator++) {
            if (contains(lineTokens[0], iterator->data())) {
              parseAreaSingleCSV(lineTokens, cols, years, measuresFilter, yearsFilter);
            }
          }
        }

      }
    } else {
      throw std::out_of_range("Invalid number of columns");
    }
  } else {
    throw std::runtime_error("No column found with title: " + cols.at(BethYw::SourceColumn::AUTH_CODE));
  }
}



/*
  Generates a vector containing all of the year column titles.

  @param lineTokens
    A vector of std::strings representing each individual token in a line;

  @return
    A vector containing all years or empty if an error occurred.
 */
std::vector<unsigned int> Areas::parseYearColumns(std::vector<std::string> lineTokens) const noexcept {
  std::vector<unsigned int> years;
  try {
    for (unsigned int i = 1; i < lineTokens.size(); i++) {
      std::string t = lineTokens[i];
      years.push_back(std::stoi(lineTokens[i]));
    }
  } catch (std::exception e) {
    return years;
  }
  return years;
}


/*
  Parses a single Area and applies the measures and years filter.

  @param lineTokens
    A vector containing all individual pieces of data for the current line.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file.

  @param years
    A vector containing all of the years which have a measure value.

  @param measuresFilter
    An unmodifiable pointer to set of strings for measures to import, or an empty
    set if all measures should be imported.

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported.
 */
void Areas::parseAreaSingleCSV(std::vector<std::string> lineTokens,
                               const BethYw::SourceColumnMapping& cols,
                               const std::vector<unsigned int> years,
                               const StringFilterSet * const measuresFilter,
                               const YearFilterTuple * const yearsFilter) {
  Area area(lineTokens[0]);
  Measure measure;

  // Apply measures filtering and parse if measure should be included
  // Avoid computation of parsing measure if not required by filter
  if (measuresFilter == nullptr) {
    measure = parseMeasureSingleCSV(lineTokens, cols, years, yearsFilter);
    area.setMeasure(measure.getCodename(), measure);
  } else if (measuresFilter->find(cols.at(BethYw::SourceColumn::SINGLE_MEASURE_CODE)) != measuresFilter->end() ||
             measuresFilter->size() == 0) {
    measure = parseMeasureSingleCSV(lineTokens, cols, years, yearsFilter);
    area.setMeasure(measure.getCodename(), measure);
  }

  this->setArea(lineTokens[0], area);
}


/*
  Parses a single Measure and applies the years filter.

  @param lineTokens
    A vector containing all individual pieces of data for the current line.

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file.

  @param years
    A vector containing all of the years which have a measure value.

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported.

  @return
    The parse Measure object.
 */
Measure Areas::parseMeasureSingleCSV(std::vector<std::string> lineTokens,
                                     const BethYw::SourceColumnMapping& cols,
                                     const std::vector<unsigned int> years,
                                     const YearFilterTuple * const yearsFilter) {

  Measure measure(cols.at(BethYw::SourceColumn::SINGLE_MEASURE_CODE),
                  cols.at(BethYw::SourceColumn::SINGLE_MEASURE_NAME));

  // Add all values to the measure
  try {
    // Parse each year in the dataset for this particular Area
    for (unsigned int i = 0; i < years.size(); i++) {
      std::stringstream ss(lineTokens[i + 1]);
      double value;
      ss >> value;

      // Apply years filtering
      if (yearsFilter == nullptr) {
        measure.setValue(years[i], value);
      } else if ((years[i] >= std::get<0>(*yearsFilter) && years[i] <= std::get<1>(*yearsFilter)) ||
                 (std::get<0>(*yearsFilter) == 0 && std::get<1>(*yearsFilter) == 0)) {
        measure.setValue(years[i], value);
      }
    }
  } catch (std::invalid_argument invalidArgument) {
    std::cerr << invalidArgument.what();
  }

  return measure;
}


/*
  Parse data from an standard input stream `is`, that has data of a particular
  `type`, and with a given column mapping in `cols`.

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

  @throws std::runtime_error
    If a parsing error occurs (e.g. due to a malformed file),
    the stream is not open/valid/has any contents, or an unexpected type
    is passed in.

   @throws std::out_of_range
    If there are not enough columns in cols.

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

  checkFileStatus(is);

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
  Parses data from a standard input stream, that is of a particular type,
  and with a given column mapping, filtering for specific areas, measures,
  and years, and fill the container.

  @param is
    The input stream from InputSource

  @param type
    A value from the BethYw::SourceDataType enum which states the underlying
    data file structure

  @param cols
    A map of the enum BethyYw::SourceColumnMapping (see datasets.h) to strings
    that give the column header in the CSV file

  @param areasFilter
    An unmodifiable pointer to set of unmodifiable strings for areas to import,
    or an empty set if all areas should be imported

  @param measuresFilter
    An unmodifiable pointer to set of unmodifiable strings for measures to import,
    or an empty set if all measures should be imported

  @param yearsFilter
    An unmodifiable pointer to an unmodifiable tuple of two unsigned integers,
    where if both values are 0, then all years should be imported, otherwise
    they should be treated as a the range of years to be imported

  @return
    void

  @throws std::runtime_error
    If a parsing error occurs (e.g. due to a malformed file),
    the stream is not open/valid/has any contents, or an unexpected type
    is passed in.

   @throws std::out_of_range
    If there are not enough columns in cols.

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

  checkFileStatus(is);

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
  Checks the status of the istream. Checks that the stream is open and has content.

  @param is
    A reference to the stream which is being checked.

  @return
    void

  @throws std::runtime_error
    If the stream isn't open.

  @throws std::runtime_error
    If the stream is open but the file has no content.
 */
void Areas::checkFileStatus(std::istream &is) const {
  if (is.bad()) {
    throw std::runtime_error("Failed to open file");
  }
  std::string test;
  std::getline(is, test);
  if (test.empty()) throw std::runtime_error("File has no content");
  is.seekg(0); // Reset the position
}


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
  if ((ss >> num).fail()) throw std::runtime_error("Invalid value in file: " + str + " is not an integer\n");
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
double Areas::safeStringToDouble(const std::string& str) const {
  std::stringstream ss(str);
  double num;
  if ((ss >> num).fail()) throw std::runtime_error("Invalid value in file: " + str + " is not a number");
  return num;
}


/*
  Checks whether a given string contains another string.

  @param base
    The string that will be searched through.

  @param search
    The string that will be searched for.

  @return
    A boolean value indicating whether the base string contains the search string.
 */
bool Areas::contains(std::string base, std::string search) const noexcept {
  transform(base.begin(), base.end(), base.begin(), ::tolower);
  transform(search.begin(), search.end(), search.begin(), ::tolower);
  return base.find(search) != std::string::npos;
}


/*
  Converts an Areas object into a JSON in the form of a std::string. The JSON contains
  all areas and their respective measures and names. If the Areas object is empty, an
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

