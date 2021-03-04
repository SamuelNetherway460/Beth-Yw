


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

SCENARIO( "an Area instance be constructed with a local authority code", "[Area][construct]" ) {

  GIVEN( "a local authority code as a std::string" ) {

    std::string localAuthorityCode = "W06000011";

    THEN( "an Area instance can be constructed" ) {

      REQUIRE_NOTHROW( Area(localAuthorityCode) );

    } // THEN
    
  } // GIVEN

} // SCENARIO

SCENARIO( "an Area instance can have names in multiple languages", "[Area][names]" ) {

  GIVEN( "a newly constructed Area instance" ) {

    std::string localAuthorityCode = "W06000011";
    Area area(localAuthorityCode);

    THEN( "the local authority code can be retrieved" ) {

      REQUIRE( area.getLocalAuthorityCode() == localAuthorityCode );

    } // THEN

    THEN( "names in multiple languages can be set" ) {
      
      auto langCode = GENERATE( as<std::string>{}, "eng", "cym" );
      auto name     = GENERATE( as<std::string>{}, "Name in English", "Name in Welsh" );

      REQUIRE_NOTHROW( area.setName(langCode, name) );
      REQUIRE( area.getName(langCode) == name );

    } // THEN

    THEN( "language codes are converted to lower case" ) {
      
      const std::string name = "Name";

      REQUIRE_NOTHROW( area.setName("eNg", name) );
      REQUIRE( area.getName("eng") == name );

    } // THEN

    const std::string exceptionMessage = "Area::setName: Language code must be three alphabetical letters only";
    
    THEN( "setting a name with a non-three letter code throws an std::invalid_argumet with the message " + exceptionMessage ) {

      auto langCode          = GENERATE( as<std::string>{}, "", "test", "123" );
      const std::string name = "Name";

      REQUIRE_THROWS_AS( area.setName(langCode, name), std::invalid_argument );
      REQUIRE_THROWS_WITH( area.setName(langCode, name), exceptionMessage );

    } // THEN

    THEN( "the object contains no Measures" ) {

      REQUIRE_NOTHROW( area.size() == 0 );

    } // THEN

  } // GIVEN

} // SCENARIO