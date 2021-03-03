


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
#include <unordered_set>

#include "../lib_cxxopts.hpp"
#include "../lib_cxxopts_argv.hpp"

#include "../bethyw.h"

SCENARIO( "the areas program argument can be parsed correctly", "[args][areas]" ) {

  GIVEN( "a --areas program argument and value" ) {

    WHEN( "the value is a single area ('W06000011')" ) {

      Argv argv({"test", "--areas", "W06000011"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseAreasArg(args) );
        
        AND_THEN( "the response is a container with 1 value" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.size() == 1 );
      
        } // AND_THEN
        
        AND_THEN ( "the container contains the area in the program argument" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.find("W06000011") != areas.end() );
    
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is multiple comma-separated areas ('W06000011', 'W06000001')" ) {

      Argv argv({"test", "--areas", "W06000011,W06000001"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseAreasArg(args) );
        
        AND_THEN( "the response is a container with 2 values" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.size() == 2 );
      
        } // AND_THEN
      
        AND_THEN ( "the container contains the areas in the program argument" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.find("W06000011") != areas.end() );
          REQUIRE( areas.find("W06000001") != areas.end() );
    
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is 'all'" ) {

      Argv argv({"test", "--areas", "all"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseAreasArg(args) );
        
        AND_THEN( "the response is a container with 0 values" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.size() == 0 );

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value contains 'all' among other values ('W06000011')" ) {

      Argv argv({"test", "--areas", "W06000011,all"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseAreasArg(args) );
        
        AND_THEN( "the response is a container with 0 values" ) {

          auto areas = BethYw::parseAreasArg(args);
          REQUIRE( areas.size() == 0 );

        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
