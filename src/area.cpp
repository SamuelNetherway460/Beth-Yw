


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  TODO: Documentation
  This file contains the implementation for the Area class. Area is a relatively
  simple class that contains a local authority code, a container of names in
  different languages (perhaps stored in an associative container?) and a series
  of Measure objects (also in some form of container).
*/

#include <stdexcept>
#include <regex>
#include <iomanip>

#include "area.h"

/*
  TODO: Documentation
 */
Area::Area() {}

/*
  Constructs an Area with a given local authority code.

  @param localAuthorityCode
    The local authority code of the Area

  @example
    Area("W06000023");
*/
Area::Area(const std::string& localAuthorityCode) : localAuthorityCode(localAuthorityCode) {}

/*
  Retrieves the local authority code for this Area.
  
  @return
    The Area's local authority code

  @example
    Area area("W06000023");
    ...
    auto authCode = area.getLocalAuthorityCode();
*/
std::string Area::getLocalAuthorityCode() const {
  return localAuthorityCode;
}


/*
  Gets the name for the Area in a specified language.

  @param lang
    A three-letter language code in ISO 639-3 format, e.g. cym or eng

  @return
    The name for the area in the given language

  @throws
    std::out_of_range if lang does not correspond to a language of a name stored
    inside the Area instance

  @example
    Area area("W06000023");
    std::string langCode  = "eng";
    std::string langValue = "Powys";
    area.setName(langCode, langValue);
    ...
    auto name = area.getName(langCode);
*/
std::string Area::getName(const std::string lang) const {
  if (names.find(lang) != names.end()) {
    return names.find(lang)->second;
  } else {
    throw std::out_of_range("No name in language " + lang);
  }
}


/*
  Sets the name for the Area in a specified language.

  @param lang
    A three-letter (alphabetical) language code in ISO 639-3 format,
    e.g. cym or eng, which should be converted to lowercase

  @param name
    The name of the Area in `lang`

  @throws
    std::invalid_argument if lang is not a three letter alphabetic code

  @example
    Area area("W06000023");
    std::string langCodeEnglish  = "eng";
    std::string langValueEnglish = "Powys";
    area.setName(langCodeEnglish, langValueEnglish);

    std::string langCodeWelsh  = "cym";
    std::string langValueWelsh = "Powys";
    area.setName(langCodeWelsh, langValueWelsh);
*/
void Area::setName(std::string lang, const std::string name) {
  transform(lang.begin(), lang.end(), lang.begin(), ::tolower);
  std::regex langExpr("[a-z][a-z][a-z]");
  if (!std::regex_match(lang, langExpr))
    throw std::invalid_argument("Area::setName: Language code must be three alphabetical letters only");
  names[lang] = name;
}


/*
  Retrieves a Measure object, given its codename.

  @param key
    The codename for the measure you want to retrieve

  @return
    A Measure object

  @throws
    std::out_of_range if there is no measure with the given code, throwing
    the message:
    No measure found matching <codename>

  @example
    Area area("W06000023");
    Measure measure("Pop", "Population");
    area.setMeasure("Pop", measure);
    ...
    auto measure2 = area.getMeasure("pop");
*/
Measure& Area::getMeasure(const std::string key) {
  if (measures.find(key) != measures.end()) {
    return measures.find(key)->second;
  } else {
    throw std::out_of_range("No measure found matching " + key);
  }
}


/*
  Adds a particular Measure to this Area object. If a Measure already exists
  with the same codename in this Area, the existing Measure's values are
  overwritten with the new Measure.

  @param key
    The codename for the Measure

  @param measure
    The Measure object

  @return
    void

  @example
    Area area("W06000023");

    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    double value = 12345678.9;
    measure.setValue(1999, value);

    area.setMeasure(code, measure);
*/
void Area::setMeasure(std::string codename, Measure measure) {
  transform(codename.begin(), codename.end(), codename.begin(), ::tolower);
  if (measures.find(codename) != measures.end()) {
    measures.find(codename)->second.overwrite(measure);
  } else {
    measures[codename] = measure;
  }
}


/*
  Retrieves the number of Measures contained for this Area.

  @return
    The size of the Area (i.e., the number of Measures)

  @example
    Area area("W06000023");
    std::string langCode  = "eng";
    std::string langValue = "Powys";
    area.setName(langCode, langValue);

    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    area.setMeasure(code, measure);
    auto size = area.size();
*/
int Area::size() const noexcept {
  return measures.size();
}


/*
  TODO: Documentation & implement rest of logic

  Overload the stream output operator as a free/global function.

  Outputs the name of the Area in English and Welsh, followed by the local
  authority code.

  If the Area only has only one name, only this is output. If the area has no names,
  "Unnamed" is outputted.

  Measures should be ordered by their Measure codename. If there are no measures
  output the line "<no measures>" after you have output the area names.

  See the coursework specification for more examples.

  @param os
    The output stream to write to

  @param area
    Area to write to the output stream

  @return
    Reference to the output stream

  @example
    Area area("W06000023");
    area.setName("eng", "Powys");
    std::cout << area << std::endl;
*/
std::ostream& operator<<(std::ostream &os, const Area &area) {
  os << area.names.find("eng")->second  << " / " << area.names.find("cym")->second << " ("
      << area.localAuthorityCode << ")";

  for (auto iterator = area.measures.begin(); iterator != area.measures.end(); iterator++) {
    os << iterator->second << std::endl;
  }
  return os;
}


/*
  Compares two Area objects for equivalence. Two Area objects are only equal when
  their local authority code, all names, and all data are equal.

  @param lhs
    An Area object

  @param lhs
    A second Area object

  @return
    true if both Area instances have the same local authority code, names
    and data; false otherwise.

  @example
    Area area1("MYCODE1");
    Area area2("MYCODE1");

    bool eq = area1 == area2;
*/
bool operator==(const Area &lhs, const Area &rhs) {
  if (lhs.getLocalAuthorityCode() == rhs.localAuthorityCode) {
    if (lhs.names == rhs.names) {
      return lhs.measures == rhs.measures;
    }
  }
  return false;
}


/*
  Combines two Area objects.

  @param area
    The Area object whose values taken from when combining.

  @return area
    The Area object which will contain the combined, most recent values.

 */
Area& Area::overwrite(Area &area) {
  for (auto iterator = area.names.begin(); iterator != area.names.end(); iterator++) {
    this->setName(iterator->first, iterator->second);
  }

  for (auto iterator = area.measures.begin(); iterator != area.measures.end(); iterator++) {
    this->setMeasure(iterator->first, iterator->second);
  }

  return *this;
}