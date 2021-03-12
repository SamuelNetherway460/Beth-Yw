#ifndef DATASETS_H_
#define DATASETS_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: Dr Martin Porcheron

  This file contains information about the files in the datasets directory. 
  This file is designed to simulate what might be returned from a
  dynamically-generated code, although all the information is actually embedded
  here in code, and constructed as your program begins execution automatically.
  This is so that you can easily read and understand it (i.e., I didn't want
  this to be the focus of the coursework).

  You must not modify this file as it will be replaced with a fresh copy
  during marking.
 */


#include <string>
#include <unordered_map>

namespace BethYw {

/*
  Enums (short for enumerations) are similar to their Java implementation.
  It is a user-defined type, used to assign names to internal constants
  in code, instead of simply passing in integers/strings etc.

  For example, functions can take a value/constant from a specific enum
  and use it in a switch statement, doing different things

  As such, it is a useful way for us to specify information in both a
  machine and human-readable format.

  Unlike Java, enum in C++ only map to intenger values. You can either let
  the compiler generate the values automatically, in which it allocates a
  unique integer (0-indexed). Or, you can set the value by giving the name
  followed by = <value> (e.g. AuthorityCodeCSV=1).

  This enum specifies the format types that the Areas class can parse.
  We could have implemented an if statement that parsed a string for the data
  type, or perhaps used integers. But with a enum both in code and to anyone
  who just glances at the code can infer the meaning.
*/
enum SourceDataType {
  None,
  AuthorityCodeCSV,
  WelshStatsJSON,
  AuthorityByYearCSV
};

/*
  Data from the different sources typically hagve different column headings
  for the same value (e.g. some might say "Year" whereas others might say
  "Year_Code"). Here we create another enum for these column headings for
  the parser.

  Each input passed to the Areas object will have to specifiy a
  an unordered map to match each of these enum values into a string that
  the source contains.
*/
enum SourceColumn {
  AUTH_CODE,
  AUTH_NAME_ENG,
  AUTH_NAME_CYM,
  MEASURE_CODE,
  MEASURE_NAME,
  SINGLE_MEASURE_CODE,
  SINGLE_MEASURE_NAME,
  YEAR,
  VALUE
};

/*
  Finally, we create a mapping type for mapping the SourceColumn enum above
  to a std::string, which will be the name of the key/column in the dataset.

  i.e. the mapping of AUTH_CODE could be to "Authority_Code", and so on
*/
using SourceColumnMapping = std::unordered_map<SourceColumn, std::string>;

/*
  This is a simple container that we use for storing information about the
  datasets in the data directory.
*/
struct InputFileSource {
  // CODE is the string used in the program arguments
  const std::string CODE;

  // NAME is the name given to this dataset
  const std::string NAME;

  // FILE is the name of the file in the datasets directory
  const std::string FILE;

  // PARSER is a SourceDataType that tells the populate() function in Areas how
  // to parse the text from the file
  const SourceDataType PARSER;

  // COLS is a map of the column headings for this dataset
  //   - the key is a SourceColumn enum value
  //   - the value is the name of the column in the data file
  const SourceColumnMapping COLS;
};

/*
  In this namespace, we store all the data for the various datasets that can
  be found in the datasets directory.
*/
namespace InputFiles {

const InputFileSource AREAS = {
  "areas",
  "areas",
  "areas.csv",
  BethYw::SourceDataType::AuthorityCodeCSV,
  {
      {AUTH_CODE,     "Local authority code"},
      {AUTH_NAME_ENG, "Name (eng)"},
      {AUTH_NAME_CYM, "Name (cym)"}
  }
}; // const InputFileSource AREAS

const InputFileSource POPDEN = {
  "popden",
  "Population density",
  "popu1009.json",
  BethYw::SourceDataType::WelshStatsJSON,
  {
    {AUTH_CODE,     "Localauthority_Code"},
    {AUTH_NAME_ENG, "Localauthority_ItemName_ENG"},
    {MEASURE_CODE,  "Measure_Code"},
    {MEASURE_NAME,  "Measure_ItemName_ENG"},
    {YEAR,          "Year_Code"},
    {VALUE,         "Data"}
  }
}; // const InputFileSource POPDEN

const InputFileSource BIZ = {
  "biz",
  "Active Businesses",
  "econ0080.json",
  BethYw::SourceDataType::WelshStatsJSON,
  {
    {AUTH_CODE,     "Area_Code"},
    {AUTH_NAME_ENG, "Area_ItemName_ENG"},
    {MEASURE_CODE,  "Variable_Code"},
    {MEASURE_NAME,  "Variable_ItemNotes_ENG"},
    {YEAR,          "Year_Code"},
    {VALUE,         "Data"}
  }
}; // const InputFileSource BIZ

const InputFileSource AQI = {
  "aqi",
  "Air Quality Indicators",
  "envi0201.json",
  BethYw::SourceDataType::WelshStatsJSON,
  {
    {AUTH_CODE,     "Area_Code"},
    {AUTH_NAME_ENG, "Area_ItemName_ENG"},
    {MEASURE_CODE,  "Pollutant_ItemName_ENG"},
    {MEASURE_NAME,  "Pollutant_ItemName_ENG"},
    {YEAR,          "Year_Code"},
    {VALUE,         "Data"}
  }
}; // const InputFileSource AQI

const InputFileSource TRAINS = {
  "trains",
  "Rail passenger journeys",
  "tran0152.json",
  BethYw::SourceDataType::WelshStatsJSON,
  {
    {AUTH_CODE,           "LocalAuthority_Code"},
    {AUTH_NAME_ENG,       "LocalAuthority_ItemName_ENG"},
    {SINGLE_MEASURE_CODE, "rail"},
    {SINGLE_MEASURE_NAME, "Rail passenger journeys"},
    {YEAR,                "Year_Code"},
    {VALUE,               "Data"}
  }
}; // const InputFileSource TRAINS

const InputFileSource COMPLETE_POPDEN = {
  "complete-popden",
  "Population density",
  "complete-popu1009-popden.csv",
  BethYw::SourceDataType::AuthorityByYearCSV,
  {
    {AUTH_CODE,           "AuthorityCode"},
    {SINGLE_MEASURE_CODE, "Dens"},
    {SINGLE_MEASURE_NAME, "Population density"}
  }
}; // const InputFileSource COMPLETE_POPDEN

const InputFileSource COMPLETE_POP = {
  "complete-pop",
  "Population",
  "complete-popu1009-pop.csv",
  BethYw::SourceDataType::AuthorityByYearCSV,
  {
    {AUTH_CODE,           "AuthorityCode"},
    {SINGLE_MEASURE_CODE, "Pop"},
    {SINGLE_MEASURE_NAME, "Population"}
  }
}; // const InputFileSource COMPLETE_POP

const InputFileSource COMPLETE_AREA = {
  "complete-area",
  "Land area",
  "complete-popu1009-area.csv",
  BethYw::SourceDataType::AuthorityByYearCSV,
  {
    {AUTH_CODE,           "AuthorityCode"},
    {SINGLE_MEASURE_CODE, "Area"},
    {SINGLE_MEASURE_NAME, "Land area"}
  }
}; // const InputFileSource COMPLETE_AREA

constexpr size_t NUM_DATASETS = 7;

const InputFileSource DATASETS[NUM_DATASETS] = { POPDEN,
                                                 BIZ,
                                                 AQI,
                                                 TRAINS,
                                                 COMPLETE_POPDEN,
                                                 COMPLETE_POP,
                                                 COMPLETE_AREA };

} // namespace InputFiles

} // namespace BethYw

#endif // DATASETS_H_