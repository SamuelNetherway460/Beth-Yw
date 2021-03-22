#ifndef BETHYW_H_
#define BETHYW_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains declarations for the helper functions for initialising and
  running Beth Yw?
 */

#include <string>
#include <unordered_set>
#include <vector>

#include "lib_cxxopts.hpp"

#include "datasets.h"
#include "areas.h"

const char DIR_SEP =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

namespace BethYw {

const std::string STUDENT_NUMBER = "955794";

/*
  Run Beth Yw?, parsing the command line arguments and acting upon them.
*/
int run(int argc, char *argv[]);

/*
  Create a cxxopts instance.
*/
cxxopts::Options cxxoptsSetup();

/*
  Parse the datasets argument and return a std::vector of all the datasets
  to import. InputFileSource is declared in datasets.h.
*/
std::vector<BethYw::InputFileSource> parseDatasetsArg(
  cxxopts::ParseResult& args);

/*
  Parse the areas argument and return a std::unordered_set of all the
  areas to import, or an empty set if all areas should be imported.
*/
StringFilterSet parseAreasArg(cxxopts::ParseResult& args);

/*
  Parse the measures argument and return a std::unordered_set of all the
  measures to import, or an empty set if all measures should be imported.
 */
std::unordered_set<std::string> parseMeasuresArg(cxxopts::ParseResult& args);

/*
  Parse the years argument and return a std::tuple<int, int> of the start
  and end years of the dataset(s) to import.
 */
std::tuple<int, int> parseYearsArg(cxxopts::ParseResult& args);

void loadAreas(Areas &areas,
               std::string dir,
               StringFilterSet * const areasFilter = nullptr);//TODO: Possibly make const

void loadDatasets(Areas &areas,
                  std::string dir,
                  const std::vector<InputFileSource> * const datasetsToImport,
                  const StringFilterSet * const areasFilter = nullptr,
                  const StringFilterSet * const measuresFilter = nullptr,
                  const YearFilterTuple * const yearsFilter= nullptr) noexcept;

void loadBiz(Areas &areas,
             std::string dir,
             const StringFilterSet * const areasFilter,
             const StringFilterSet * const measuresFilter,
             const YearFilterTuple * const yearsFilter) noexcept;

void loadAqi(Areas &areas,
             std::string dir,
             const StringFilterSet * const areasFilter,
             const StringFilterSet * const measuresFilter,
             const YearFilterTuple * const yearsFilter) noexcept;

void loadPopden(Areas &areas,
                std::string dir,
                const StringFilterSet * const areasFilter,
                const StringFilterSet * const measuresFilter,
                const YearFilterTuple * const yearsFilter) noexcept;

void loadTrains(Areas &areas,
                std::string dir,
                const StringFilterSet * const areasFilter,
                const StringFilterSet * const measuresFilter,
                const YearFilterTuple * const yearsFilter) noexcept;

void loadCompletePopden(Areas &areas,
                        std::string dir,
                        const StringFilterSet * const areasFilter,
                        const StringFilterSet * const measuresFilter,
                        const YearFilterTuple * const yearsFilter) noexcept;

void loadCompletePop(Areas &areas,
                     std::string dir,
                     const StringFilterSet * const areasFilter,
                     const StringFilterSet * const measuresFilter,
                     const YearFilterTuple * const yearsFilter) noexcept;

void loadCompleteArea(Areas &areas,
                      std::string dir,
                      const StringFilterSet * const areasFilter,
                      const StringFilterSet * const measuresFilter,
                      const YearFilterTuple * const yearsFilter) noexcept;

} // namespace BethYw

#endif // BETHYW_H_