#ifndef MEASURE_H_
#define MEASURE_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains the declaration of the Measure class.

  TODO: Read the block comments with TODO in measure.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string>
#include <map>

#include "lib_json.hpp"

/*
  The Measure class contains a measure code, label, and a container for readings
  from across a number of years.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/
class Measure {
private:
  std::string name;
  std::string codename;
  std::string label;
  std::map<int, double> data;

public:
  Measure();
  Measure(std::string code, const std::string &label);

  std::string getCodename() const noexcept;
  std::string getLabel() const noexcept;
  void setLabel(const std::string label);
  double getValue(const int key) const;
  void setValue(const int key, const double value);
  int size() const noexcept;
  double getDifference() const noexcept;
  double getDifferenceAsPercentage() const noexcept;
  double getAverage() const noexcept;
  Measure& overwrite(Measure &measure);
  nlohmann::json getJsonMeasure() const;

  friend std::ostream& operator<<(std::ostream &os, const Measure &measure);
  friend bool operator==(const Measure &lhs, const Measure &rhs);
};

#endif // MEASURE_H_