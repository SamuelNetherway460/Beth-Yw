


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

#include "../input.h"

SCENARIO( "a source file can be opened and read", "[InputFile][existent]" ) {

  auto file_exists = [](const std::string &path) {
    // fstream destructor closes the file
    return std::ifstream(path).is_open();
  };

  const std::string test_file = "datasets/areas.csv";
  REQUIRE( file_exists(test_file) );

  GIVEN( "a valid file path" ) {

    THEN( "an InputFile instance can be constructed" ) {

      REQUIRE_NOTHROW( InputFile(test_file) );

    } // THEN

  } // GIVEN

  GIVEN( "a constructed InputFile instance" ) {
    
    InputFile input(test_file);

    THEN( "the source value can be retrieved" ) {

      REQUIRE( input.getSource() == test_file );

    } // THEN

    THEN( "a stream to source file can be opened without exception" ) {

      REQUIRE_NOTHROW( input.open() );
      REQUIRE_NOTHROW( dynamic_cast<std::istream&> (input.open()) );

      AND_THEN( "the stream remains open after open() returns" ) {

        std::istream &stream = input.open();

        REQUIRE_NOTHROW( stream.seekg(1, stream.beg) );
        REQUIRE_FALSE( stream.eof() );
        REQUIRE_NOTHROW( stream.seekg(0, stream.beg) );

      } // AND_THEN

    } // THEN

  } // GIVEN

} // SCENARIO

SCENARIO( "a nonexistant source file cannot be opened for reading", "[InputFile][nonexistent]" ) {

  auto file_exists = [](const std::string &path) {
    // fstream destructor closes the file
    return std::ifstream(path).is_open();
  };
  
  const std::string test_file = "datasets/jibberish.json";
  REQUIRE_FALSE(file_exists(test_file));

  GIVEN( "a valid file path" ) {

    THEN( "an InputFile instance can be constructed" ) {

      REQUIRE_NOTHROW( InputFile(test_file) );

    } // THEN

  } // GIVEN

  GIVEN( "a constructed InputFile instance" ) {

    InputFile input(test_file);

    THEN( "the source value can be retrieved" ) {

      REQUIRE( input.getSource() == test_file );

      const std::string exceptionMessage = "InputFile::open: Failed to open file " + test_file;

      AND_THEN( "when the source file is attempted to be read, a std::runtime_error is thrown with message " + exceptionMessage ) {

        REQUIRE_THROWS_AS( input.open(), std::runtime_error );
        REQUIRE_THROWS_WITH( input.open(), exceptionMessage );

      } // THEN

    } // THEN

  } // GIVEN

} // SCENARIO