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

  TODO: Read the block comments with TODO in area.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string>
#include <unordered_set>
#include <vector>
#include <map>

#include "measure.h"

/*
  An Area object consists of a unique authority code, a container for names
  for the area in any number of different languages, and a container for the
  Measures objects.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/
class Area {
private:
  std::string localAuthorityCode;
  std::map<std::string, std::string> names;
  std::map<std::string, Measure> measures;

public:
  Area(const std::string& localAuthorityCode);

  std::string getLocalAuthorityCode() const;
  std::string getName(std::string lang) const;
  std::map<std::string, std::string> getNames() const;
  void setName(std::string lang, std::string name);
  Measure getMeasure(std::string key) const;
  std::map<std::string, Measure> getMeasures() const;
  void setMeasure(std::string codename, Measure measure);
  int size() const;
  friend std::ostream& operator<<(std::ostream &os, const Area &area);
  friend bool operator==(const Area &lhs, const Area &rhs);
};

#endif // AREA_H_