


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: Dr Martin Porcheron

  Catch2 test script — https://github.com/catchorg/Catch2
  Catch2 is licensed under the BOOST license.
 */

#include "../lib_catch.hpp"

#include <stdexcept>
#include <string>

#include "../measure.h"

SCENARIO( "a Measure object can be populated with values", "[Measure][populate]" ) {

  GIVEN( "a newly constructed Measure instance" ) {

    const std::string codename = "pop";
    const std::string label = "Population";
    Measure measure(codename, label);

    WHEN( "there is a single year:value to insert" ) {

      const int year     = 2010;
      const double value = 1000;

      THEN( "they will be emplaced without exception" ) {

        REQUIRE_NOTHROW( measure.setValue(year, value) );

        AND_THEN( "the size will be 1" ) {

          REQUIRE( measure.size() == 1 );

        AND_THEN( "the value can be retrieved" ) {

          REQUIRE( measure.getValue(year) == value );

        } // AND_THEN

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "there are two different year:value pairs to insert" ) {

      const int year1     = 2010;
      const double value1 = 1000;
      const int year2     = 2011;
      const double value2 = 2000;

      THEN( "they will both be emplaced without exception" ) {

        REQUIRE_NOTHROW( measure.setValue(year1, value1) );
        REQUIRE_NOTHROW( measure.setValue(year2, value2) );

        AND_THEN( "the size will be 2" ) {

          REQUIRE( measure.size() == 2 );

        } // AND_THEN

        AND_THEN( "both values can be retrieved" ) {

          REQUIRE( measure.getValue(year1) == value1 );
          REQUIRE( measure.getValue(year2) == value2 );

        } // AND THEN

      } // THEN

    } // WHEN

    WHEN( "there are two year:value pairs to insert, both with the same year" ) {

      const int year1     = 2010;
      const double value1 = 1000;
      const int year2     = 2010;
      const double value2 = 2000;

      THEN( "they will both be emplaced without exception" ) {

        REQUIRE_NOTHROW( measure.setValue(year1, value1) );
        REQUIRE_NOTHROW( measure.setValue(year2, value2) );

        AND_THEN( "the size will be 1" ) {

          REQUIRE( measure.size() == 1 );

        } // AND_THEN

        AND_THEN( "the second value will have replaced the first value" ) {

          REQUIRE( measure.getValue(year2) == value2 );

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "there are no inserted values" ) {

      THEN( "the size will be 0" ) {

        REQUIRE( measure.size() == 0 );

        AND_THEN( "a std::out_of_range exception will be thrown when you a value is requested for a given year" ) {

          REQUIRE_THROWS_AS( measure.getValue(1234), std::out_of_range );

        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

