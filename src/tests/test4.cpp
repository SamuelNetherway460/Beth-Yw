


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
#include <tuple>

#include "../lib_cxxopts.hpp"
#include "../lib_cxxopts_argv.hpp"

#include "../bethyw.h"

SCENARIO( "the years program argument can be parsed correctly", "[args][years]" ) {

  GIVEN( "a --years argument with a value" ) {

    WHEN( "the value is a single four-digit year ('2010')" ) {

      Argv argv({"test", "--years", "2010"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseYearsArg(args) );
        
        AND_THEN( "the response is a two-pair tuple where both values are equal to the argument value" ) {

          auto years = BethYw::parseYearsArg(args);
          REQUIRE( std::get<0>(years) == 2010 );
          REQUIRE( std::get<1>(years) == 2010 );
      
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is nill ('0')" ) {

      Argv argv({"test", "--years", "0"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseYearsArg(args) );
        
        AND_THEN( "the response is a two-pair tuple where both values are equal to 0" ) {

          auto years = BethYw::parseYearsArg(args);
          REQUIRE( std::get<0>(years) == 0 );
          REQUIRE( std::get<1>(years) == 0 );
      
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is nill ('0-0')" ) {

      Argv argv({"test", "--years", "0-0"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseYearsArg(args) );
        
        AND_THEN( "the response is a two-pair tuple where both values are equal to 0" ) {

          auto years = BethYw::parseYearsArg(args);
          REQUIRE( std::get<0>(years) == 0 );
          REQUIRE( std::get<1>(years) == 0 );
      
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is two four-digit years as a range ('2010-2015')" ) {

      Argv argv({"test", "--years", "2010-2015"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( BethYw::parseYearsArg(args) );
        
        AND_THEN( "the response is a two-pair tuple where the values are 2010 and 2015 respectively" ) {

          auto years = BethYw::parseYearsArg(args);
          REQUIRE( std::get<0>(years) == 2010 );
          REQUIRE( std::get<1>(years) == 2015 );
      
        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN( "the value is not a number ('qwerty')" ) {

      Argv argv({"test", "--years", "qwerty"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      const std::string exceptionMessage = "Invalid input for years argument";
      
      THEN( "a std::invalid_argument exception is thrown with the message '" + exceptionMessage + "'" ) {

        REQUIRE_THROWS_AS(   BethYw::parseYearsArg(args), std::invalid_argument );
        REQUIRE_THROWS_WITH( BethYw::parseYearsArg(args), exceptionMessage      );

      } // THEN

    } // WHEN

    WHEN( "the value is partially numeric ('2010-qwerty')" ) {

      Argv argv({"test", "--years", "2010-qwerty"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = BethYw::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      const std::string exceptionMessage = "Invalid input for years argument";
      
      THEN( "a std::invalid_argument exception is thrown with the message '" + exceptionMessage + "'" ) {

        REQUIRE_THROWS_AS(    BethYw::parseYearsArg(args), std::invalid_argument );
        REQUIRE_THROWS_WITH(  BethYw::parseYearsArg(args), exceptionMessage      );

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO