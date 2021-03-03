


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

SCENARIO( "the measures program argument can be parsed correctly", "[args][measures]" ) {

  GIVEN( "a --measures program argument and value" ) {

    WHEN( "the value is a single measure ('pop')" ) {

      Argv argv({"test", "--measures", "pop"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseMeasuresArg(args) );
        
        AND_THEN( "the response is a container with 1 value" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.size() == 1 );
      
        } // AND_THEN
        
        AND_THEN ( "the container contains the measure in the program argument" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.find("pop") != measures.end() );
    
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is multiple comma-separated measures ('pop', 'dens')" ) {

      Argv argv({"test", "--measures", "pop,dens"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseMeasuresArg(args) );
        
        AND_THEN( "the response is a container with 2 values" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.size() == 2 );
      
        } // AND_THEN
        
        AND_THEN ( "the container contains the measures in the program argument" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.find("pop") != measures.end() );
          REQUIRE( measures.find("dens") != measures.end() );
    
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is 'all'" ) {

      Argv argv({"test", "--measures", "all"});
      auto** actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseMeasuresArg(args) );
        
        AND_THEN( "the response is a container with 0 values" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.size() == 0 );

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value contains 'all' among other values ('dens')" ) {

      Argv argv({"test", "--measures", "dens,all"});
      auto** actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseMeasuresArg(args) );

        AND_THEN( "the response is a container with 0 values" ) {

          auto measures = BethYw::parseMeasuresArg(args);
          REQUIRE( measures.size() == 0 );

        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN
  
} // SCENARIO
