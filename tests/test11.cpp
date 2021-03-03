


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
#include <unordered_set>

#include "../datasets.h"
#include "../areas.h"

SCENARIO( "areas.csv can be correctly parsed", "[Areas][authorityCodeCSV]" ) {

  auto get_istream = [](const std::string &path) {
    return std::ifstream(path);
  };

  GIVEN( "a newly constructed Areas instance" ) {

      Areas areas = Areas();

    AND_GIVEN( "a valid areas.csv file as an open std::istream" ) {

      const std::string test_file = "datasets/areas.csv";
      auto stream                 = get_istream(test_file);

      REQUIRE( stream.is_open() );

      AND_GIVEN( "an empty areasFilter" ) {

        std::unordered_set<std::string> areasFilter(0);

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromAuthorityCodeCSV(stream, BethYw::InputFiles::AREAS.COLS, &areasFilter) );

          AND_THEN( "the Areas instance has size 22" ) {

            REQUIRE( areas.size() == 22 );

          } // AND_THEN

          AND_THEN( "each area has been imported with the correct local authority code as an Area instance (mixed)" ) {

            REQUIRE_NOTHROW( areas.getArea("W06000001") );
            REQUIRE_NOTHROW( areas.getArea("W06000002") );
            REQUIRE_NOTHROW( areas.getArea("W06000003") );
            REQUIRE_NOTHROW( areas.getArea("W06000004") );
            REQUIRE_NOTHROW( areas.getArea("W06000005") );
            REQUIRE_NOTHROW( areas.getArea("W06000006") );
            REQUIRE_NOTHROW( areas.getArea("W06000008") );
            REQUIRE_NOTHROW( areas.getArea("W06000009") );
            REQUIRE_NOTHROW( areas.getArea("W06000010") );
            REQUIRE_NOTHROW( areas.getArea("W06000011") );
            REQUIRE_NOTHROW( areas.getArea("W06000012") );
            REQUIRE_NOTHROW( areas.getArea("W06000013") );
            REQUIRE_NOTHROW( areas.getArea("W06000014") );
            REQUIRE_NOTHROW( areas.getArea("W06000015") );
            REQUIRE_NOTHROW( areas.getArea("W06000016") );
            REQUIRE_NOTHROW( areas.getArea("W06000018") );
            REQUIRE_NOTHROW( areas.getArea("W06000019") );
            REQUIRE_NOTHROW( areas.getArea("W06000020") );
            REQUIRE_NOTHROW( areas.getArea("W06000021") );
            REQUIRE_NOTHROW( areas.getArea("W06000022") );
            REQUIRE_NOTHROW( areas.getArea("W06000023") );
            REQUIRE_NOTHROW( areas.getArea("W06000024") );

            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000001")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000002")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000003")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000004")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000005")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000006")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000008")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000009")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000010")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000011")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000012")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000013")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000014")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000015")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000016")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000018")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000019")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000020")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000021")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000022")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000023")) );
            REQUIRE_NOTHROW( dynamic_cast<Area&> (areas.getArea("W06000024")) );

          } // AND_THEN

          AND_THEN( "each area has been correctly imported with the correct names (mixed)" ) {

            REQUIRE( areas.getArea("W06000001").getName("eng") == "Isle of Anglesey" );
            REQUIRE( areas.getArea("W06000001").getName("cym") == "Ynys Môn" );

            REQUIRE( areas.getArea("W06000002").getName("eng") == "Gwynedd" );
            REQUIRE( areas.getArea("W06000002").getName("cym") == "Gwynedd" );

            REQUIRE( areas.getArea("W06000003").getName("eng") == "Conwy" );
            REQUIRE( areas.getArea("W06000003").getName("cym") == "Conwy" );

            REQUIRE( areas.getArea("W06000004").getName("eng") == "Denbighshire" );
            REQUIRE( areas.getArea("W06000004").getName("cym") == "Sir Ddinbych" );

            REQUIRE( areas.getArea("W06000005").getName("eng") == "Flintshire" );
            REQUIRE( areas.getArea("W06000005").getName("cym") == "Sir y Fflint" );

            REQUIRE( areas.getArea("W06000006").getName("eng") == "Wrexham" );
            REQUIRE( areas.getArea("W06000006").getName("cym") == "Wrecsam" );

            REQUIRE( areas.getArea("W06000008").getName("eng") == "Ceredigion" );
            REQUIRE( areas.getArea("W06000008").getName("cym") == "Ceredigion" );

            REQUIRE( areas.getArea("W06000009").getName("eng") == "Pembrokeshire" );
            REQUIRE( areas.getArea("W06000009").getName("cym") == "Sir Benfro" );

            REQUIRE( areas.getArea("W06000010").getName("eng") == "Carmarthenshire" );
            REQUIRE( areas.getArea("W06000010").getName("cym") == "Sir Gaerfyrddin" );

            REQUIRE( areas.getArea("W06000011").getName("eng") == "Swansea" );
            REQUIRE( areas.getArea("W06000011").getName("cym") == "Abertawe" );

            REQUIRE( areas.getArea("W06000012").getName("eng") == "Neath Port Talbot" );
            REQUIRE( areas.getArea("W06000012").getName("cym") == "Castell-nedd Port Talbot" );

            REQUIRE( areas.getArea("W06000013").getName("eng") == "Bridgend" );
            REQUIRE( areas.getArea("W06000013").getName("cym") == "Pen-y-bont ar Ogwr" );

            REQUIRE( areas.getArea("W06000014").getName("eng") == "Vale of Glamorgan" );
            REQUIRE( areas.getArea("W06000014").getName("cym") == "Bro Morgannwg" );

            REQUIRE( areas.getArea("W06000015").getName("eng") == "Cardiff" );
            REQUIRE( areas.getArea("W06000015").getName("cym") == "Caerdydd" );

            REQUIRE( areas.getArea("W06000016").getName("eng") == "Rhondda Cynon Taf" );
            REQUIRE( areas.getArea("W06000016").getName("cym") == "Rhondda Cynon Taf" );

            REQUIRE( areas.getArea("W06000018").getName("eng") == "Caerphilly" );
            REQUIRE( areas.getArea("W06000018").getName("cym") == "Caerffili" );

            REQUIRE( areas.getArea("W06000019").getName("eng") == "Blaenau Gwent" );
            REQUIRE( areas.getArea("W06000019").getName("cym") == "Blaenau Gwent" );

            REQUIRE( areas.getArea("W06000020").getName("eng") == "Torfaen" );
            REQUIRE( areas.getArea("W06000020").getName("cym") == "Torfaen" );

            REQUIRE( areas.getArea("W06000021").getName("eng") == "Monmouthshire" );
            REQUIRE( areas.getArea("W06000021").getName("cym") == "Sir Fynwy" );

            REQUIRE( areas.getArea("W06000022").getName("eng") == "Newport" );
            REQUIRE( areas.getArea("W06000022").getName("cym") == "Casnewydd" );

            REQUIRE( areas.getArea("W06000023").getName("eng") == "Powys" );
            REQUIRE( areas.getArea("W06000023").getName("cym") == "Powys" );

            REQUIRE( areas.getArea("W06000024").getName("eng") == "Merthyr Tydfil" );
            REQUIRE( areas.getArea("W06000024").getName("cym") == "Merthyr Tudful" );

          } // AND_THEN

          const std::string exceptionMessage = "No area found matching junk";
          AND_THEN( "attempting to retrieve an Area with an unexpected local authority code ('junk') throws a std::out_of_range error with exception message '" + exceptionMessage +"'" ) {

            REQUIRE_THROWS_AS( areas.getArea("junk"), std::out_of_range );
            REQUIRE_THROWS_WITH( areas.getArea("junk"), exceptionMessage );

          } // AND_THEN

        } // THEN

      } // AND_GIVEN

      AND_GIVEN( "a nullptr for an areasFilter" ) {

        THEN( "the Areas instance will be populated without exception" ) {

          REQUIRE_NOTHROW( areas.populateFromAuthorityCodeCSV(stream, BethYw::InputFiles::AREAS.COLS, nullptr) );

          AND_THEN( "the Areas instance has size 22" ) {

            REQUIRE( areas.size() == 22 );

          } // AND_THEN
          
        } // THEN  
      
      } // AND_GIVEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO