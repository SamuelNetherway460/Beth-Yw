


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: Dr Martin Porcheron

  Catch2 test script — https://github.com/catchorg/Catch2
  Catch2 is licensed under the BOOST license.
 */

#include "../lib_catch.hpp"

#include <fstream>
#include <string>

#include "../datasets.h"
#include "../areas.h"

SCENARIO( "popu1009.json can be correctly parsed", "[Areas][popu1009]" ) {

  auto get_istream = [](const std::string &path) {
    return std::ifstream(path);
  };

  GIVEN( "a newly constructed Areas instance" ) {

    Areas areas = Areas();

    AND_GIVEN( "a valid popu1009.json file as an open std::istream" ) {

      const std::string test_file = "datasets/popu1009.json";
      auto stream                 = get_istream(test_file);

      REQUIRE( stream.is_open() );

      AND_GIVEN( "an empty areasFilter, measuresFilter, and yearsFilter" ) {

        std::unordered_set<std::string> areasFilter(0);
        std::unordered_set<std::string> measuresFilter(0);
        std::tuple<unsigned int, unsigned int> yearsFilter = std::make_tuple(0,0);

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromWelshStatsJSON(stream, BethYw::InputFiles::DATASETS[0].COLS, &areasFilter, &measuresFilter, &yearsFilter) );

          AND_THEN( "the Areas instance has size 12" ) {

            REQUIRE( areas.size() == 12 );

          } // AND_THEN

          AND_THEN( "each Area in the Areas instance has correct size (3)" ) {

            REQUIRE( areas.getArea("W06000001").size() == 3 );
            REQUIRE( areas.getArea("W06000002").size() == 3 );
            REQUIRE( areas.getArea("W06000003").size() == 3 );
            REQUIRE( areas.getArea("W06000004").size() == 3 );
            REQUIRE( areas.getArea("W06000005").size() == 3 );
            REQUIRE( areas.getArea("W06000006").size() == 3 );
            REQUIRE( areas.getArea("W06000008").size() == 3 );
            REQUIRE( areas.getArea("W06000009").size() == 3 );
            REQUIRE( areas.getArea("W06000010").size() == 3 );
            REQUIRE( areas.getArea("W06000011").size() == 3 );
            REQUIRE( areas.getArea("W06000012").size() == 3 );
            REQUIRE( areas.getArea("W06000023").size() == 3 );

          } // AND_THEN

          AND_THEN( "each Measure in each Area in the Areas instance has correct size (mixed)" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").size() == 16 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").size() == 29 );

            REQUIRE( areas.getArea("W06000001").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").size() == 13 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").size() == 29 );

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").size() == 29 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").size() == 14 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").size() == 29 );

          } // AND_THEN

          AND_THEN( "each year in each Measure in each Area in the Areas instance has the correct value" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1991) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1992) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1993) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1994) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1995) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1996) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1997) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1998) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1999) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2000) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2001) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2002) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2003) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2004) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2005) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2006) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2007) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2008) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2009) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2010) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2011) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2012) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2013) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2014) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2015) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2016) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2017) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2018) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2019) == 711.6801 );

            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1991) == 97.126504 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1992) == 97.486216 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1993) == 98.03843 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1994) == 97.216432 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1995) == 96.147131 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1996) == 96.380382 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1997) == 95.701706 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1998) == 95.115769 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1999) == 95.517635 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2000) == 95.405225 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2001) == 95.275953 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2002) == 95.378528 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2003) == 95.745265 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2004) == 96.606607 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2005) == 97.08716 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2006) == 97.498862 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2007) == 97.937261 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2008) == 98.240769 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2009) == 98.195805 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2010) == 98.124143 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2011) == 98.236553 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2012) == 98.410789 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2013) == 98.461373 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2014) == 98.556922 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2015) == 98.268871 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2016) == 97.888082 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2017) == 98.069343 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2018) == 98.303999 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2019) == 98.41922 );

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1991) == 69123.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1992) == 69379.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1993) == 69772.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1994) == 69187.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1995) == 68426.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1996) == 68592.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1997) == 68109.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1998) == 67692.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1999) == 67978.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2000) == 67898.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2001) == 67806.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2002) == 67879.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2003) == 68140.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2004) == 68753.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2005) == 69095.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2006) == 69388.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2007) == 69700.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2008) == 69916.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2009) == 69884.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2010) == 69833.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2011) == 69913.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2012) == 70037.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2013) == 70073.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2014) == 70141.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2015) == 69936.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2016) == 69665.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2017) == 69794.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2018) == 69961.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2019) == 70043.0 );

            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1991) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1992) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1993) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1994) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1995) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1996) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1997) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1998) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(1999) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2000) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2001) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2002) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2003) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2004) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2005) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2006) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2007) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2008) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2009) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2010) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2011) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2012) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2013) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2014) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2015) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2016) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2017) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2018) == 2534.7422 );
            REQUIRE( areas.getArea("W06000002").getMeasure("area").getValue(2019) == 2534.7422 );

            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1991) == 45.372267 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1992) == 45.53757 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1993) == 45.652374 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1994) == 45.894214 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1995) == 46.366056 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1996) == 46.350276 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1997) == 46.397618 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1998) == 46.310035 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(1999) == 45.906838 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2000) == 46.039791 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2001) == 46.096996 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2002) == 46.294254 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2003) == 46.561737 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2004) == 46.837505 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2005) == 46.805943 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2006) == 46.975191 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2007) == 47.104593 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2008) == 47.241885 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2009) == 47.477807 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2010) == 47.79776 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2011) == 47.942943 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2012) == 48.133889 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2013) == 47.99423 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2014) == 48.090492 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2015) == 48.381646 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2016) == 48.653074 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2017) == 48.818377 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2018) == 48.990386 );
            REQUIRE( areas.getArea("W06000002").getMeasure("dens").getValue(2019) == 49.141092 );

            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1991) == 115007.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1992) == 115426.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1993) == 115717.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1994) == 116330.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1995) == 117526.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1996) == 117486.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1997) == 117606.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1998) == 117384.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(1999) == 116362.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2000) == 116699.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2001) == 116844.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2002) == 117344.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2003) == 118022.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2004) == 118721.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2005) == 118641.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2006) == 119070.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2007) == 119398.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2008) == 119746.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2009) == 120344.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2010) == 121155.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2011) == 121523.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2012) == 122007.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2013) == 121653.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2014) == 121897.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2015) == 122635.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2016) == 123323.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2017) == 123742.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2018) == 124178.0 );
            REQUIRE( areas.getArea("W06000002").getMeasure("pop").getValue(2019) == 124560.0 );

            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1991) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1992) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1993) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1994) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1995) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1996) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1997) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1998) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(1999) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2000) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2001) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2002) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2003) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2004) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2005) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2006) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2007) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2008) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2009) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2010) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2011) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2012) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2013) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2014) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2015) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2016) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2017) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2018) == 1125.8409 );
            REQUIRE( areas.getArea("W06000003").getMeasure("area").getValue(2019) == 1125.8409 );

            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1991) == 95.884774 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1992) == 95.734664 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1993) == 96.054425 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1994) == 96.719705 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1995) == 96.763228 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1996) == 95.83681 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1997) == 96.082848 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1998) == 96.345763 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(1999) == 96.214305 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2000) == 96.506531 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2001) == 97.415185 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2002) == 98.258999 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2003) == 98.813251 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2004) == 99.722794 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2005) == 99.813393 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2006) == 100.372975 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2007) == 101.060461 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2008) == 101.587178 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2009) == 101.811011 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2010) == 101.863416 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2011) == 102.435433 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2012) == 102.63706 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2013) == 102.955933 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2014) == 103.407151 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2015) == 103.433798 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2016) == 103.762441 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2017) == 103.800635 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2018) == 104.08309 );
            REQUIRE( areas.getArea("W06000003").getMeasure("dens").getValue(2019) == 104.102631 );

            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1991) == 107951.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1992) == 107782.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1993) == 108142.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1994) == 108891.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1995) == 108940.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1996) == 107897.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1997) == 108174.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1998) == 108470.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(1999) == 108322.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2000) == 108651.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2001) == 109674.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2002) == 110624.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2003) == 111248.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2004) == 112272.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2005) == 112374.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2006) == 113004.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2007) == 113778.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2008) == 114371.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2009) == 114623.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2010) == 114682.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2011) == 115326.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2012) == 115553.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2013) == 115912.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2014) == 116420.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2015) == 116450.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2016) == 116820.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2017) == 116863.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2018) == 117181.0 );
            REQUIRE( areas.getArea("W06000003").getMeasure("pop").getValue(2019) == 117203.0 );

            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1991) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1992) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1993) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1994) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1995) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1996) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1997) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1998) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(1999) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2000) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2001) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2002) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2003) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2004) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2005) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2006) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2007) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2008) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2009) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2010) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2011) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2012) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2013) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2014) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2015) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2016) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2017) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2018) == 836.7704 );
            REQUIRE( areas.getArea("W06000004").getMeasure("area").getValue(2019) == 836.7704 );

            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1991) == 106.833368 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1992) == 106.503528 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1993) == 106.809466 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1994) == 107.044895 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1995) == 107.450025 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1996) == 108.300915 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1997) == 108.29255 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1998) == 108.692898 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(1999) == 109.359748 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2000) == 110.57394 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2001) == 111.225254 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2002) == 111.712843 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2003) == 112.183701 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2004) == 112.34862 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2005) == 112.310378 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2006) == 112.316353 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2007) == 112.970057 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2008) == 113.219827 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2009) == 112.867281 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2010) == 112.51832 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2011) == 112.239869 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2012) == 112.400008 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2013) == 112.955716 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2014) == 113.336944 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2015) == 113.335749 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2016) == 113.512619 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2017) == 113.721757 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2018) == 113.926114 );
            REQUIRE( areas.getArea("W06000004").getMeasure("dens").getValue(2019) == 114.36351 );

            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1991) == 89395.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1992) == 89119.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1993) == 89375.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1994) == 89572.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1995) == 89911.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1996) == 90623.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1997) == 90616.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1998) == 90951.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(1999) == 91509.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2000) == 92525.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2001) == 93070.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2002) == 93478.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2003) == 93872.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2004) == 94010.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2005) == 93978.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2006) == 93983.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2007) == 94530.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2008) == 94739.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2009) == 94444.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2010) == 94152.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2011) == 93919.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2012) == 94053.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2013) == 94518.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2014) == 94837.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2015) == 94836.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2016) == 94984.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2017) == 95159.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2018) == 95330.0 );
            REQUIRE( areas.getArea("W06000004").getMeasure("pop").getValue(2019) == 95696.0 );

            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1991) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1992) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1993) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1994) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1995) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1996) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1997) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1998) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(1999) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2000) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2001) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2002) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2003) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2004) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2005) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2006) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2007) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2008) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2009) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2010) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2011) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2012) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2013) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2014) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2015) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2016) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2017) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2018) == 439.7241 );
            REQUIRE( areas.getArea("W06000005").getMeasure("area").getValue(2019) == 439.7241 );

            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1991) == 323.011634 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1992) == 326.325075 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1993) == 327.589504 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1994) == 328.70384 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1995) == 329.397456 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1996) == 327.719131 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1997) == 328.940351 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1998) == 332.619931 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(1999) == 333.90028 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2000) == 336.415493 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2001) == 338.005126 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2002) == 338.728307 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2003) == 339.249088 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2004) == 340.397536 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2005) == 340.872834 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2006) == 341.40726 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2007) == 342.9787 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2008) == 344.536495 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2009) == 345.637185 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2010) == 345.853229 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2011) == 347.185883 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2012) == 347.43604 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2013) == 348.452587 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2014) == 349.807982 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2015) == 350.412907 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2016) == 351.643224 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2017) == 352.846251 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2018) == 353.84233 );
            REQUIRE( areas.getArea("W06000005").getMeasure("dens").getValue(2019) == 354.995325 );

            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1991) == 142036.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1992) == 143493.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1993) == 144049.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1994) == 144539.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1995) == 144844.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1996) == 144106.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1997) == 144643.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1998) == 146261.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(1999) == 146824.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2000) == 147930.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2001) == 148629.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2002) == 148947.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2003) == 149176.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2004) == 149681.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2005) == 149890.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2006) == 150125.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2007) == 150816.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2008) == 151501.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2009) == 151985.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2010) == 152080.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2011) == 152666.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2012) == 152776.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2013) == 153223.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2014) == 153819.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2015) == 154085.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2016) == 154626.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2017) == 155155.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2018) == 155593.0 );
            REQUIRE( areas.getArea("W06000005").getMeasure("pop").getValue(2019) == 156100.0 );

            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1991) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1992) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1993) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1994) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1995) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1996) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1997) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1998) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(1999) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2000) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2001) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2002) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2003) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2004) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2005) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2006) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2007) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2008) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2009) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2010) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2011) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2012) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2013) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2014) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2015) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2016) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2017) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2018) == 503.7739 );
            REQUIRE( areas.getArea("W06000006").getMeasure("area").getValue(2019) == 503.7739 );

            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1991) == 246.499471 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1992) == 247.386774 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1993) == 248.02595 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1994) == 248.718721 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1995) == 248.982728 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1996) == 249.17329 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1997) == 249.391642 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1998) == 250.465536 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(1999) == 251.912614 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2000) == 253.393437 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2001) == 255.154148 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2002) == 255.263323 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2003) == 255.896544 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2004) == 256.077181 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2005) == 256.561525 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2006) == 258.669613 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2007) == 260.55935 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2008) == 262.75875 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2009) == 264.592906 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2010) == 266.010208 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2011) == 268.116312 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2012) == 268.965899 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2013) == 269.567359 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2014) == 269.869082 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2015) == 268.807098 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2016) == 268.787248 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2017) == 269.110805 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2018) == 270.21249 );
            REQUIRE( areas.getArea("W06000006").getMeasure("dens").getValue(2019) == 269.877022 );

            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1991) == 124180.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1992) == 124627.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1993) == 124949.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1994) == 125298.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1995) == 125431.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1996) == 125527.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1997) == 125637.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1998) == 126178.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(1999) == 126907.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2000) == 127653.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2001) == 128540.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2002) == 128595.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2003) == 128914.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2004) == 129005.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2005) == 129249.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2006) == 130311.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2007) == 131263.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2008) == 132371.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2009) == 133295.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2010) == 134009.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2011) == 135070.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2012) == 135498.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2013) == 135801.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2014) == 135953.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2015) == 135418.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2016) == 135408.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2017) == 135571.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2018) == 136126.0 );
            REQUIRE( areas.getArea("W06000006").getMeasure("pop").getValue(2019) == 135957.0 );

            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1991) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1992) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1993) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1994) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1995) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1996) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1997) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1998) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(1999) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2000) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2001) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2002) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2003) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2004) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2005) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2006) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2007) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2008) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2009) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2010) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2011) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2012) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2013) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2014) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2015) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2016) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2017) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2018) == 1785.5105 );
            REQUIRE( areas.getArea("W06000008").getMeasure("area").getValue(2019) == 1785.5105 );

            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1991) == 36.926694 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1992) == 37.824477 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1993) == 38.562641 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1994) == 39.16919 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1995) == 39.662606 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1996) == 39.545553 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1997) == 40.21651 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1998) == 40.614715 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(1999) == 41.470493 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2000) == 41.97231 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2001) == 42.23834 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2002) == 42.284826 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2003) == 42.330191 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2004) == 42.438843 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2005) == 42.276425 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2006) == 42.196335 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2007) == 42.187374 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2008) == 41.988552 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2009) == 41.804291 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2010) == 42.126327 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2011) == 42.168892 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2012) == 42.526773 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2013) == 42.446684 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2014) == 42.079282 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2015) == 41.562903 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2016) == 41.257108 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2017) == 40.927231 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2018) == 40.880185 );
            REQUIRE( areas.getArea("W06000008").getMeasure("dens").getValue(2019) == 40.713846 );

            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1991) == 65933.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1992) == 67536.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1993) == 68854.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1994) == 69937.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1995) == 70818.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1996) == 70609.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1997) == 71807.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1998) == 72518.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(1999) == 74046.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2000) == 74942.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2001) == 75417.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2002) == 75500.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2003) == 75581.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2004) == 75775.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2005) == 75485.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2006) == 75342.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2007) == 75326.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2008) == 74971.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2009) == 74642.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2010) == 75217.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2011) == 75293.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2012) == 75932.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2013) == 75789.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2014) == 75133.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2015) == 74211.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2016) == 73665.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2017) == 73076.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2018) == 72992.0 );
            REQUIRE( areas.getArea("W06000008").getMeasure("pop").getValue(2019) == 72695.0 );

            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1991) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1992) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1993) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1994) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1995) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1996) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1997) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1998) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(1999) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2000) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2001) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2002) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2003) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2004) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2005) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2006) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2007) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2008) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2009) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2010) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2011) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2012) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2013) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2014) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2015) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2016) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2017) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2018) == 1618.3449 );
            REQUIRE( areas.getArea("W06000009").getMeasure("area").getValue(2019) == 1618.3449 );

            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1991) == 69.482099 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1992) == 69.914639 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1993) == 69.753363 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1994) == 69.877564 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1995) == 69.360369 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1996) == 69.293635 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1997) == 68.984059 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1998) == 69.091576 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(1999) == 69.000743 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2000) == 69.538947 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2001) == 69.860263 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2002) == 70.532555 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2003) == 71.151088 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2004) == 71.942637 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2005) == 72.422139 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2006) == 73.08578 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2007) == 73.927381 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2008) == 74.850546 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2009) == 75.115632 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2010) == 75.369595 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2011) == 75.764443 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2012) == 76.086995 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2013) == 76.235294 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2014) == 76.513974 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2015) == 76.418197 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2016) == 76.767937 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2017) == 77.060829 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2018) == 77.273392 );
            REQUIRE( areas.getArea("W06000009").getMeasure("dens").getValue(2019) == 77.744861 );

            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1991) == 112446.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1992) == 113146.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1993) == 112885.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1994) == 113086.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1995) == 112249.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1996) == 112141.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1997) == 111640.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1998) == 111814.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(1999) == 111667.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2000) == 112538.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2001) == 113058.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2002) == 114146.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2003) == 115147.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2004) == 116428.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2005) == 117204.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2006) == 118278.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2007) == 119640.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2008) == 121134.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2009) == 121563.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2010) == 121974.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2011) == 122613.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2012) == 123135.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2013) == 123375.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2014) == 123826.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2015) == 123671.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2016) == 124237.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2017) == 124711.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2018) == 125055.0 );
            REQUIRE( areas.getArea("W06000009").getMeasure("pop").getValue(2019) == 125818.0 );

            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1991) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1992) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1993) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1994) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1995) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1996) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1997) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1998) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(1999) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2000) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2001) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2002) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2003) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2004) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2005) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2006) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2007) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2008) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2009) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2010) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2011) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2012) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2013) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2014) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2015) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2016) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2017) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2018) == 2370.2762 );
            REQUIRE( areas.getArea("W06000010").getMeasure("area").getValue(2019) == 2370.2762 );

            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1991) == 71.605579 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1992) == 71.411509 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1993) == 71.40729 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1994) == 71.705567 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1995) == 72.168805 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1996) == 72.204665 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1997) == 72.368781 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1998) == 72.581837 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(1999) == 72.704185 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2000) == 72.934116 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2001) == 73.262348 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2002) == 73.674114 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2003) == 74.309062 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2004) == 74.880303 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2005) == 75.193347 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2006) == 75.731259 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2007) == 76.494883 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2008) == 77.002419 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2009) == 77.141221 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2010) == 77.20788 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2011) == 77.61163 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2012) == 77.768152 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2013) == 77.91033 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2014) == 78.036475 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2015) == 78.154183 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2016) == 78.368082 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2017) == 78.662563 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2018) == 79.133394 );
            REQUIRE( areas.getArea("W06000010").getMeasure("dens").getValue(2019) == 79.64093 );

            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1991) == 169725.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1992) == 169265.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1993) == 169255.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1994) == 169962.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1995) == 171060.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1996) == 171145.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1997) == 171534.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1998) == 172039.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(1999) == 172329.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2000) == 172874.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2001) == 173652.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2002) == 174628.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2003) == 176133.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2004) == 177487.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2005) == 178229.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2006) == 179504.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2007) == 181314.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2008) == 182517.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2009) == 182846.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2010) == 183004.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2011) == 183961.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2012) == 184332.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2013) == 184669.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2014) == 184968.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2015) == 185247.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2016) == 185754.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2017) == 186452.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2018) == 187568.0 );
            REQUIRE( areas.getArea("W06000010").getMeasure("pop").getValue(2019) == 188771.0 );

            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1991) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1992) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1993) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1994) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1995) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1996) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1997) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1998) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(1999) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2000) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2001) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2002) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2003) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2004) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2005) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2006) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2007) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2008) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2009) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2010) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2011) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2012) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2013) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2014) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2015) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2016) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2017) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2018) == 377.5964 );
            REQUIRE( areas.getArea("W06000011").getMeasure("area").getValue(2019) == 377.5964 );

            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1991) == 608.435356 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1992) == 608.083128 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1993) == 607.391914 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1994) == 604.452267 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1995) == 603.196958 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1996) == 601.698003 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1997) == 600.54598 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1998) == 597.733453 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(1999) == 596.086191 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2000) == 594.483952 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2001) == 591.803841 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2002) == 595.225484 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2003) == 599.449571 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2004) == 604.285422 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2005) == 607.386617 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2006) == 611.216103 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2007) == 615.630869 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2008) == 620.077416 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2009) == 623.949275 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2010) == 628.47792 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2011) == 632.132616 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2012) == 634.169182 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2013) == 635.8853 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2014) == 638.157567 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2015) == 641.732813 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2016) == 647.41613 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2017) == 650.11213 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2018) == 652.723384 );
            REQUIRE( areas.getArea("W06000011").getMeasure("dens").getValue(2019) == 654.119054 );

            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1991) == 229743.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1992) == 229610.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1993) == 229349.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1994) == 228239.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1995) == 227765.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1996) == 227199.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1997) == 226764.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1998) == 225702.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(1999) == 225080.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2000) == 224475.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2001) == 223463.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2002) == 224755.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2003) == 226350.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2004) == 228176.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2005) == 229347.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2006) == 230793.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2007) == 232460.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2008) == 234139.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2009) == 235601.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2010) == 237311.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2011) == 238691.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2012) == 239460.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2013) == 240108.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2014) == 240966.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2015) == 242316.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2016) == 244462.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2017) == 245480.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2018) == 246466.0 );
            REQUIRE( areas.getArea("W06000011").getMeasure("pop").getValue(2019) == 246993.0 );

            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1991) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1992) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1993) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1996) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1998) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(1999) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2003) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2004) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2012) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2013) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2014) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2015) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2016) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2017) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2018) == 441.2447 );
            REQUIRE( areas.getArea("W06000012").getMeasure("area").getValue(2019) == 441.2447 );

            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(1991) == 314.664403 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(1992) == 313.875725 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(1993) == 313.247955 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(1998) == 308.411636 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(1999) == 306.759492 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2003) == 308.747051 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2013) == 316.982844 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2014) == 318.310905 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2015) == 319.428199 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2016) == 321.087143 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2017) == 322.020865 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2018) == 323.870179 );
            REQUIRE( areas.getArea("W06000012").getMeasure("dens").getValue(2019) == 324.797102 );

            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(1991) == 138844.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(1992) == 138496.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(1998) == 136085.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(1999) == 135356.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2001) == 134380.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2002) == 134931.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2004) == 137144.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2005) == 137670.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2013) == 139867.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2014) == 140453.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2015) == 140946.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2016) == 141678.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2018) == 142906.0 );
            REQUIRE( areas.getArea("W06000012").getMeasure("pop").getValue(2019) == 143315.0 );

            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1991) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1992) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1993) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1994) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1995) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1996) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1997) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1998) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(1999) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2000) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2001) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2002) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2003) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2004) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2005) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2006) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2007) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2008) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2009) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2010) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2011) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2012) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2013) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2014) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2015) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2016) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2017) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2018) == 5180.6716 );
            REQUIRE( areas.getArea("W06000023").getMeasure("area").getValue(2019) == 5180.6716 );

            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1991) == 23.105692 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1992) == 23.234053 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1993) == 23.369943 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1994) == 23.433255 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1995) == 23.518765 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1996) == 23.926242 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1997) == 24.051708 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1998) == 24.212691 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(1999) == 24.250138 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2000) == 24.347036 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2001) == 24.397995 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2002) == 24.542185 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2003) == 24.764164 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2004) == 25.009885 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2005) == 25.133807 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2006) == 25.293439 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2007) == 25.475848 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2008) == 25.646289 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2009) == 25.689719 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2010) == 25.648798 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2011) == 25.686052 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2012) == 25.675243 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2013) == 25.63104 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2014) == 25.629303 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2015) == 25.62023 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2016) == 25.544372 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2017) == 25.57873 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2018) == 25.565604 );
            REQUIRE( areas.getArea("W06000023").getMeasure("dens").getValue(2019) == 25.563288 );

            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1991) == 119703.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1992) == 120368.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1993) == 121072.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1994) == 121400.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1995) == 121843.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1996) == 123954.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1997) == 124604.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1998) == 125438.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(1999) == 125632.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2000) == 126134.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2001) == 126398.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2002) == 127145.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2003) == 128295.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2004) == 129568.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2005) == 130210.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2006) == 131037.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2007) == 131982.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2008) == 132865.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2009) == 133090.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2010) == 132878.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2011) == 133071.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2012) == 133015.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2013) == 132786.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2014) == 132777.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2015) == 132730.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2016) == 132337.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2017) == 132515.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2018) == 132447.0 );
            REQUIRE( areas.getArea("W06000023").getMeasure("pop").getValue(2019) == 132435.0 );

          } // AND_THEN

        } // THEN

      } // AND_GIVEN

      AND_GIVEN( "an areaFilter with a single area only ('W06000001'), an empty measuresFilter, and an empty yearsFilter" ) {

        std::unordered_set<std::string> areasFilter(1);
        areasFilter.emplace("W06000001");
        std::unordered_set<std::string> measuresFilter(0);
        std::tuple<unsigned int, unsigned int> yearsFilter = std::make_tuple(0,0);

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromWelshStatsJSON(stream, BethYw::InputFiles::DATASETS[0].COLS, &areasFilter, &measuresFilter, &yearsFilter) );

          AND_THEN( "the Areas instance has size 1" ) {

            REQUIRE( areas.size() == 1 );

          } // AND_THEN

          AND_THEN( "each imported Area in the Areas instance has correct size (3)" ) {

            REQUIRE( areas.getArea("W06000001").size() == 3 );


          } // AND_THEN

          const std::string exceptionMessage = "No area found matching W06000002";
          AND_THEN( "attempting to retrieve an Area with an unexpected local authority code ('W06000002') throws a std::out_of_range error with exception message '" + exceptionMessage +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000002"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000002"), exceptionMessage );

          } // AND_THEN

          AND_THEN( "each Measure in each imported Area in the Areas instance has correct size (29)" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("area").size() == 29 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").size() == 29 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").size() == 29 );

          } // AND_THEN

          AND_THEN( "each year in each Measure in each Area in the Areas instance has the correct value" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1991) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1992) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1993) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1994) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1995) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1996) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1997) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1998) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(1999) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2000) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2001) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2002) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2003) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2004) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2005) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2006) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2007) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2008) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2009) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2010) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2011) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2012) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2013) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2014) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2015) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2016) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2017) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2018) == 711.6801 );
            REQUIRE( areas.getArea("W06000001").getMeasure("area").getValue(2019) == 711.6801 );

            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1991) == 97.126504 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1992) == 97.486216 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1993) == 98.03843 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1994) == 97.216432 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1995) == 96.147131 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1996) == 96.380382 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1997) == 95.701706 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1998) == 95.115769 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(1999) == 95.517635 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2000) == 95.405225 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2001) == 95.275953 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2002) == 95.378528 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2003) == 95.745265 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2004) == 96.606607 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2005) == 97.08716 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2006) == 97.498862 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2007) == 97.937261 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2008) == 98.240769 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2009) == 98.195805 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2010) == 98.124143 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2011) == 98.236553 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2012) == 98.410789 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2013) == 98.461373 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2014) == 98.556922 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2015) == 98.268871 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2016) == 97.888082 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2017) == 98.069343 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2018) == 98.303999 );
            REQUIRE( areas.getArea("W06000001").getMeasure("dens").getValue(2019) == 98.41922 );

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1991) == 69123.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1992) == 69379.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1993) == 69772.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1994) == 69187.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1995) == 68426.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1996) == 68592.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1997) == 68109.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1998) == 67692.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1999) == 67978.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2000) == 67898.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2001) == 67806.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2002) == 67879.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2003) == 68140.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2004) == 68753.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2005) == 69095.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2006) == 69388.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2007) == 69700.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2008) == 69916.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2009) == 69884.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2010) == 69833.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2011) == 69913.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2012) == 70037.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2013) == 70073.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2014) == 70141.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2015) == 69936.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2016) == 69665.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2017) == 69794.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2018) == 69961.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2019) == 70043.0 );

          } // AND_THEN

        } // THEN

      } // AND_GIVEN

      AND_GIVEN( "an areaFilter with a single area only ('W06000001'), a measuresFilter with a single measure ('pop'), and an empty yearsFilter" ) {

        std::unordered_set<std::string> areasFilter(1);
        areasFilter.emplace("W06000001");
        std::unordered_set<std::string> measuresFilter(0);
        measuresFilter.emplace("pop");
        std::tuple<unsigned int, unsigned int> yearsFilter = std::make_tuple(0,0);

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromWelshStatsJSON(stream, BethYw::InputFiles::DATASETS[0].COLS, &areasFilter, &measuresFilter, &yearsFilter) );

          AND_THEN( "the Areas instance has size 1" ) {

            REQUIRE( areas.size() == 1 );

          } // AND_THEN

          AND_THEN( "each imported Area in the Areas instance has correct size (1)" ) {

            REQUIRE( areas.getArea("W06000001").size() == 1 );

          } // AND_THEN

          const std::string exceptionMessage = "No area found matching W06000002";
          AND_THEN( "attempting to retrieve an Area with an unexpected local authority code ('W06000002') throws a std::out_of_range error with exception message '" + exceptionMessage +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000002"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000002"), exceptionMessage );

          } // AND_THEN

          const std::string exceptionMessage2 = "No measure found matching dens";
          AND_THEN( "attempting to retrieve a Measure with an unexpected codename ('dens') throws a std::out_of_range error with exception message '" + exceptionMessage2 +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000001").getMeasure("dens"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000001").getMeasure("dens"), exceptionMessage2 );

          } // AND_THEN

          AND_THEN( "each Measure in each imported Area in the Areas instance has correct size (29)" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").size() == 29 );

          } // AND_THEN

          AND_THEN( "each year in each Measure in each Area in the Areas instance has the correct value" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1991) == 69123.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1992) == 69379.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1993) == 69772.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1994) == 69187.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1995) == 68426.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1996) == 68592.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1997) == 68109.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1998) == 67692.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1999) == 67978.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2000) == 67898.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2001) == 67806.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2002) == 67879.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2003) == 68140.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2004) == 68753.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2005) == 69095.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2006) == 69388.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2007) == 69700.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2008) == 69916.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2009) == 69884.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2010) == 69833.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2011) == 69913.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2012) == 70037.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2013) == 70073.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2014) == 70141.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2015) == 69936.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2016) == 69665.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2017) == 69794.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2018) == 69961.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(2019) == 70043.0 );

          } // AND_THEN

        } // THEN

      } // AND_GIVEN

      AND_GIVEN( "an areaFilter with a single area only ('W06000001'), a measuresFilter wth a single measure ('pop'), and a yearsFilter with a range ('1991-1995')" ) {

        std::unordered_set<std::string> areasFilter(1);
        areasFilter.emplace("W06000001");
        std::unordered_set<std::string> measuresFilter(0);
        measuresFilter.emplace("pop");
        std::tuple<unsigned int, unsigned int> yearsFilter = std::make_tuple(1991,1995);

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromWelshStatsJSON(stream, BethYw::InputFiles::DATASETS[0].COLS, &areasFilter, &measuresFilter, &yearsFilter) );

          AND_THEN( "the Areas instance has size 1" ) {

            REQUIRE( areas.size() == 1 );

          } // AND_THEN

          AND_THEN( "each imported Area in the Areas instance has correct size (1)" ) {

            REQUIRE( areas.getArea("W06000001").size() == 1 );

          } // AND_THEN

          const std::string exceptionMessage = "No area found matching W06000002";
          AND_THEN( "attempting to retrieve an Area with an unexpected local authority code ('W06000002') throws a std::out_of_range error with exception message '" + exceptionMessage +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000002"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000002"), exceptionMessage );

          } // AND_THEN

          const std::string exceptionMessage2 = "No measure found matching dens";
          AND_THEN( "attempting to retrieve a Measure with an unexpected codename ('dens') throws a std::out_of_range error with exception message '" + exceptionMessage2 +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000001").getMeasure("dens"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000001").getMeasure("dens"), exceptionMessage2 );

          } // AND_THEN

          AND_THEN( "each Measure in each imported Area in the Areas instance has correct size (5)" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").size() == 5 );

          } // AND_THEN

          const std::string exceptionMessage3 = "No value found for year 2000";
          AND_THEN( "attempting to retrieve a value with an unexpected year ('2000') throws a std::out_of_range error with exception message '" + exceptionMessage3 +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("W06000001").getMeasure("pop").getValue(2000), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("W06000001").getMeasure("pop").getValue(2000), exceptionMessage3 );

          } // AND_THEN

          AND_THEN( "each year in each Measure in each Area in the Areas instance has the correct value" ) {

            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1991) == 69123.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1992) == 69379.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1993) == 69772.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1994) == 69187.0 );
            REQUIRE( areas.getArea("W06000001").getMeasure("pop").getValue(1995) == 68426.0 );

          } // AND_THEN

        } // THEN

      } // AND_GIVEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO