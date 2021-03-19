


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  TODO: Documentation
  This file contains the implementation of the Measure class. Measure is a
  very simple class that needs to contain a few member variables for its name,
  codename, and a Standard Library container for data. The data you need to 
  store is values, organised by year. I'd recommend storing the values as 
  doubles.
*/

#include <stdexcept>
#include <string>
#include <regex>
#include <iomanip>

#include "measure.h"

/*
  Basic constructor for a new Measure object.
 */
Measure::Measure() {}


/*
  Constructs a single Measure, that has values across many years.

  @param codename
    The codename for the measure

  @param label
    Human-readable (i.e. nice/explanatory) label for the measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);
*/
Measure::Measure(std::string codename, const std::string &label) : label(label) {
  transform(codename.begin(), codename.end(), codename.begin(), ::tolower); //TODO Check this works
  this->codename = codename;
}


/*
  Retrieve the code for the Measure.

  @return
    The codename for the Measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto codename2 = measure.getCodename();
*/
std::string Measure::getCodename() const noexcept {
  return codename;
}


/*
  Retrieve the human-friendly label for the Measure.

  @return
    The human-friendly label for the Measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto label = measure.getLabel();
*/
std::string Measure::getLabel() const noexcept {
  return label;
}


/*
  Change the label for the Measure.

  @param label
    The new label for the Measure

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    ...
    measure.setLabel("New Population");
*/
void Measure::setLabel(const std::string label) {
  this->label = label;
}


/*
  Retrieve a Measure's value for a given year.

  @param key
    The year to find the value for

  @return
    The value stored for the given year

  @throws
    std::out_of_range if year does not exist in Measure with the message
    No value found for year <year>

  @return
    The value

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto value = measure.getValue(1999); // returns 12345678.9
*/
double Measure::getValue(const int key) const {
  std::regex yearExpr("[1-9][0-9][0-9][0-9]");
  if (data.find(key) != data.end() && std::regex_match(std::to_string(key), yearExpr)) {
    return data.find(key)->second; // TODO: Check that this second thing works correctly
  } else {

    throw std::out_of_range("No value found for year " + std::to_string(key));
  }
}


/*
  Adds a particular year's value to the Measure object. If a value already
  exists for the year, it is replaced.

  @param key
    The year to insert a value at

  @param value
    The value for the given year

  @return
    void

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
*/
void Measure::setValue(const int key, const double value) {
  data[key] = value;
}


/*
  Retrieves the number of years data we have for this measure.

  @return
    The size of the measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    auto size = measure.size(); // returns 1
*/
int Measure::size() const noexcept {
  return data.size();
}


/*
  Calculates the difference between the first and last year imported.

  @return
    The difference/change in value from the first to the last year, or 0 if it
    cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    measure.setValue(2001, 12345679.9);
    auto diff = measure.getDifference(); // returns 1.0
*/
double Measure::getDifference() const noexcept {
  if (data.size() > 1) {
    return data.end()->second - data.begin()->second;
  } else {
    return 0;
  }
}


/*
  Calculates the difference between the first and last year imported as a
  percentage.

  @return
    The difference/change in value from the first to the last year as a decminal
    value, or 0 if it cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1990, 12345678.9);
    measure.setValue(2010, 12345679.9);
    auto diff = measure.getDifferenceAsPercentage();
*/
double Measure::getDifferenceAsPercentage() const noexcept {
  if (data.size() > 1) {
    return ((data.end()->second - data.begin()->second) / data.end()->second) * 100;
  } else {
    return 0;
  }
}


/*
  Calculates the average/mean value for all the values.

  @return
    The average value for all the years, or 0 if it cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    measure.setValue(2001, 12345679.9);
    auto diff = measure.getAverage(); // returns 12345678.4
*/
double Measure::getAverage() const noexcept {
  double total = 0.0;
  for (auto iterator = data.begin(); iterator != data.end(); iterator++) {
    total += iterator->second;
  }
  return total / data.size();
}


/*
  TODO: Check formatting of output
  Adds measure's imported data to a os stream. Years are added in
  chronological order on a single line with the average value across the
  years, the difference between the first and last year, and the
  percentage difference between the first and last year at the end.

  If there is no data in this measure, the name and code is printed with
  <no data> printed on the next line.

  Years are right aligned respective to the values for clarity.

  @param os
    The output stream to write to

  @param measure
    The Measure to write to the output stream

  @return
    Reference to the output stream

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    std::cout << measure << std::end;
*/
std::ostream& operator<<(std::ostream &os, const Measure &measure) {
  os << measure.label << " (" << measure.getCodename() << ")" << std::endl;

  if (measure.data.empty()) {
    os << "<no data>";
  } else {
    for (auto iterator = measure.data.begin(); iterator != measure.data.end(); iterator++) {
      int width = std::to_string(iterator->second).size();
      os << std::setw(width) << std::right << std::to_string(iterator->first) << " ";
    }

    int averageWidth = std::to_string(measure.getAverage()).size();
    os << std::setw(averageWidth) << std::right << "Average ";

    int differenceWidth = std::to_string(measure.getDifference()).size();
    os << std::setw(differenceWidth) << std::right << "Diff. ";

    int differencePercentWidth = std::to_string(measure.getDifferenceAsPercentage()).size();
    os << std::setw(differencePercentWidth) << std::right << "% Diff." << std::endl;

    for (auto iterator = measure.data.begin(); iterator != measure.data.end(); iterator++) {
      os << std::to_string(iterator->second) << " ";
    }

    os << std::to_string(measure.getAverage()) << " ";
    os << std::to_string(measure.getDifference()) << " ";
    os << std::to_string(measure.getDifferenceAsPercentage());
  }

  return os;
}


/*
  TODO: Check logic
  Compares two Measure objects. Two Measure objects
  are only equal when their codename, label and data are all equal.

  @param lhs
    A Measure object

  @param lhs
    A second Measure object

  @return
    true if both Measure objects have the same codename, label and data; false
    otherwise
*/
bool operator==(const Measure &lhs, const Measure &rhs) {
  if (lhs.codename == rhs.codename) {
    if (lhs.label == rhs.label) {
      if (lhs.size() == rhs.size()) {
        return lhs.data == rhs.data;
      }
    }
  }
  return false;
}


/*
  TODO: Check
  Combines two Measure objects.

  @param measure
    The Measure object whose values taken from when combining.

  @return measure
    The Measure object which will contain the combined, most recent values.
 */
Measure& Measure::overwrite(Measure &measure) {
  this->label = measure.label;
  for (auto iterator = measure.data.begin(); iterator != measure.data.end(); iterator++) {
    this->setValue(iterator->first, iterator->second);
  }
  return *this;
}