#ifndef AREAS_H
#define AREAS_H

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains the Areas class, which is responsible for parsing data
  from a standard input stream and converting it into a series of objects:

  Measure       — Represents a single measure for an area, e.g.
   |              population. Contains a human-readable label and a map of
   |              the measure across a number of years.
   |
   +-> Area       Represents an area. Contains a unique local authority code
        |         used in national statistics, a map of the names of the area 
        |         (i.e. in English and Welsh), and a map of various Measure 
        |         objects.
        |
        +-> Areas A class that contains all Area objects.
 */

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>

#include "datasets.h"
#include "area.h"

/*
  An alias for filters based on strings such as categorisations e.g. area,
  and measures.
*/
using StringFilterSet = std::unordered_set<std::string>;

/*
  An alias for a year filter.
*/
using YearFilterTuple = std::tuple<unsigned int, unsigned int>;

/*
  An alias for the data within an Areas object stores Area objects.
*/
using AreasContainer = std::map<std::string, Area>;

/*
  Areas is a class that stores all the data categorised by area. The 
  underlying Standard Library container is customisable using the alias above.

  To understand the functions declared below, read the comments in areas.cpp
  and the coursework worksheet. Briefly: populate() is called by bethyw.cpp to
  populate data inside an Areas instance. This function will hand off the
  specific parsing of code to other functions, based on the value of 
  BethYw::SourceDataType.
*/
class Areas {
private:
  AreasContainer areas;

  std::vector<std::string> getLineTokens(
      std::istream &ls,
      std::string line,
      char delimiter);

  int safeStringToInt(const std::string& str) const;
  double safeStringToDouble(const std::string& str) const;

public:
  Areas();

  void setArea(const std::string key, Area &area);
  Area& getArea(const std::string key);
  int size() const noexcept;
  
  void populateFromAuthorityCodeCSV(
      std::istream& is,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areas = nullptr)
      noexcept(false);

  void populateFromWelshStatsJSON(
      std::istream& is,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areas = nullptr,
      const StringFilterSet * const measures = nullptr,
      const YearFilterTuple * const years = nullptr);

  void populateFromAuthorityByYearCSV(
      std::istream& is,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areas = nullptr,
      const StringFilterSet * const measures = nullptr,
      const YearFilterTuple * const years = nullptr);

  void populate(
      std::istream& is,
      const BethYw::SourceDataType& type,
      const BethYw::SourceColumnMapping& cols) noexcept(false);

  void populate(
      std::istream& is,
      const BethYw::SourceDataType& type,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areasFilter,
      const StringFilterSet * const measuresFilter,
      const YearFilterTuple * const yearsFilter)
      noexcept(false);

  std::string toJSON() const;
  friend std::ostream& operator<<(std::ostream &os, const Areas &areas);
};

#endif // AREAS_H