#ifndef AREA_H_
#define AREA_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains the Area class declaration. Area objects contain all the
  Measure objects for a given local area, along with names for that area and a
  unique authority code.
 */

#include <string>
#include <unordered_set>
#include <vector>
#include <map>

#include "measure.h"
#include "lib_json.hpp"

/*
  An Area object consists of a unique authority code, a container for names
  for the area in any number of different languages, and a container for the
  Measures objects.
*/
class Area {
private:
  std::string localAuthorityCode;
  std::map<std::string, std::string> names;
  std::map<std::string, Measure> measures;

public:
  Area();
  Area(const std::string& localAuthorityCode);

  std::string getLocalAuthorityCode() const;
  std::string getName(const std::string lang) const;
  void setName(std::string lang, const std::string name);
  Measure& getMeasure(const std::string key);
  void setMeasure(std::string codename, const Measure measure);
  std::map<std::string, Measure> getMeasures() const;
  int size() const noexcept;
  Area& overwrite(Area &area);
  nlohmann::json getJsonMeasures() const;
  nlohmann::json getJsonNames() const;

  friend std::ostream& operator<<(std::ostream &os, const Area &area);
  friend bool operator==(const Area &lhs, const Area &rhs);
};

#endif // AREA_H_