


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: Dr Martin Porcheron

  Catch2 test script — https://github.com/catchorg/Catch2
  Catch2 is licensed under the BOOST license.
 */

#include "../lib_catch.hpp"

#include <string>

#include "../area.h"
#include "../measure.h"

SCENARIO( "an Area instance can contain Measure instances", "[Area][Measures]" ) {

  GIVEN( "a newly constructed Area instance" ) {

    std::string localAuthorityCode = "W06000011";
    Area area(localAuthorityCode);

    AND_GIVEN( "a newly constructed Measure instance ('Pop')" ) {

      const std::string codename      = "Pop";
      const std::string codenameLower = "pop";
      const std::string label         = "Population";
      Measure measure(codename, label);

      THEN( "the Measure instance can be emplace into the Area instance without exception" ) {

        REQUIRE_NOTHROW( area.setMeasure(codename, measure) );

        AND_THEN( "the Area instance size will be 1" ) {

          REQUIRE( area.size() == 1 );

        } // AND_THEN

        AND_THEN( "the Measure instance can be retrieved without exception with a lowercase codename" ) {

          REQUIRE_NOTHROW( area.getMeasure(codenameLower) );

        } // AND_THEN

        AND_THEN( "the Measure instance is equal to the original" ) {

          Measure &newMeasure = area.getMeasure(codenameLower);
          REQUIRE( measure == newMeasure );

        } // AND_THEN

      } // THEN

    } // AND_GIVEN

    AND_GIVEN( "two newly constructed Measure instances with two different codenames ('pop', 'dens')" ) {

      const std::string codename1 = "pop";
      const std::string label1 = "Population";
      Measure measure1(codename1, label1);
      
      const std::string codename2 = "dens";
      const std::string label2 = "Population density";
      Measure measure2(codename2, label2);

      THEN( "the Measure instances can be emplace into the Area instance without exception" ) {

        REQUIRE_NOTHROW( area.setMeasure(codename1, measure1) );
        REQUIRE_NOTHROW( area.setMeasure(codename2, measure2) );

        AND_THEN( "the Area instance size will be 2" ) {

          REQUIRE( area.size() == 2 );

        } // AND_THEN

        AND_THEN( "the Measure instances can be retrieved without exception" ) {

          REQUIRE_NOTHROW( area.getMeasure(codename1) );
          REQUIRE_NOTHROW( area.getMeasure(codename2) );

        } // AND_THEN

        AND_THEN( "the Measure instances are equal to the original" ) {

          Measure &newMeasure1 = area.getMeasure(codename1);
          REQUIRE( measure1 == newMeasure1 );

          Measure &newMeasure2 = area.getMeasure(codename2);
          REQUIRE( measure2 == newMeasure2 );

        } // AND_THEN

      } // THEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO