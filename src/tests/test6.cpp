


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

SCENARIO( "a Measure object can be constructed with a codename and label", "[Measure][construct]" ) {

  GIVEN( "a codename and a label as std::string instances" ) {

    const std::string codename = "Pop";
    const std::string label = "Population";

    THEN( "a Measure instance can be constructed" ) {

      REQUIRE_NOTHROW( Measure(codename, label) );

    } // THEN

  } // GIVEN

  GIVEN( "a newly constructed Measure instance with a codename and label" ) {

    THEN( "the codename can be retrieved" ) {

      const std::string codename = "pop";
      const std::string label = "Population";
      Measure measure(codename, "Population");

      REQUIRE( measure.getCodename() == codename );

    } // THEN

    THEN( "the codename will be converted to lowercase" ) {

      const std::string codename = "POP";
      const std::string codenameLower = "pop";
      const std::string label = "Population";
      Measure measure(codename, label);

      REQUIRE_NOTHROW( measure.getCodename() == codenameLower );

    } // THEN

    THEN( "the label can be retreived" ) {

      const std::string codename = "pop";
      const std::string label = "Population";
      Measure measure(codename, label);

      REQUIRE_NOTHROW( measure.getLabel() == label );

    } // THEN

    THEN( "the instance has size 0" ) {

      const std::string codename = "pop";
      const std::string label = "Population";
      Measure measure(codename, label);

      REQUIRE_NOTHROW( measure.size() == 0 );

    } // THEN

  } // GIVEN

} // SCENARIO

