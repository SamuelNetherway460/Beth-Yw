


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

#include "../areas.h"
#include "../area.h"
#include "../measure.h"

SCENARIO( "an Areas instance can be constructed", "[Areas][construct]" ) {

  REQUIRE_NOTHROW( Areas() );

} // SCENARIO

SCENARIO( "an Areas instance can contain Area instances", "[Areas][contain]" ) {

  GIVEN( "a newly constructed Areas" ) {

    Areas areas;

    THEN( "the Areas instance has size 0" ) {

      REQUIRE_NOTHROW( areas.size() == 0 );

    } // THEN
    
    AND_GIVEN( "a newly constructed Area instance ('W06000011')" ) {
      
      std::string localAuthorityCode = "W06000011";
      Area area(localAuthorityCode);
      
      THEN( "the Area instance can be emplaced in the Areas instance without exception" ) {

        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area) );

        AND_THEN( "the Areas instance has size 1" ) {

          REQUIRE_NOTHROW( areas.size() == 1 );

        } // AND_THEN

        AND_THEN( "the Area instance can be retrieved using the local authority code" ) {

          Area &newArea = areas.getArea(localAuthorityCode);
          REQUIRE( area == newArea );

        } // AND_THEN

      } // THEN
    
    } // AND_GIVEN
    
    AND_GIVEN( "two newly constructed Area instances with different local authority codes ('W06000011' and 'W06000012') " ) {
      
      std::string localAuthorityCode1 = "W06000011";
      std::string localAuthorityCode2 = "W06000012";

      Area area1(localAuthorityCode1);
      Area area2(localAuthorityCode2);
      
      THEN( "the Area instancse can be emplaced in the Areas instance without exception" ) {

        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode1, area1) );
        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode2, area2) );

        AND_THEN( "the Areas instance has size 2" ) {

          REQUIRE_NOTHROW( areas.size() == 2 );

        } // AND_THEN

        AND_THEN( "the Area instances can be retrieved using the local authority code" ) {

          Area &newArea1 = areas.getArea(localAuthorityCode1);
          Area &newArea2 = areas.getArea(localAuthorityCode2);
          
          REQUIRE( area1 == newArea1 );
          REQUIRE( area2 == newArea2 );

        } // AND_THEN

      } // THEN
    
    } // AND_GIVEN
    
    AND_GIVEN( "two newly constructed Area instances with the same local authority codes ('W06000011') " ) {
      
      std::string localAuthorityCode = "W06000011";

      Area area1(localAuthorityCode);
      Area area2(localAuthorityCode);
      
      THEN( "the Area instances can be emplaced in the Areas instance without exception" ) {

        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area1) );
        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area2) );

        AND_THEN( "the Areas instance has size 1" ) {

          REQUIRE_NOTHROW( areas.size() == 1 );

        } // AND_THEN

      } // THEN
    
    } // AND_GIVEN
    
    AND_GIVEN( "two newly constructed Area instances with the same local authority codes ('W06000011') but different sets of names" ) {
      
      std::string localAuthorityCode = "W06000011";
      std::string name1 = "Original name (should be replaced)";
      std::string name2 = "Original name (should persist)";
      std::string name3 = "New name (should have replaced an original name)";

      Area area1(localAuthorityCode);
      Area area2(localAuthorityCode);
      Area areaCombined(localAuthorityCode);
      
      area1.setName("eng", name1);
      area1.setName("cym", name2);
      
      area2.setName("eng", name3);
      area2.setName("tes", name2);
      
      areaCombined.setName("eng", name3);
      areaCombined.setName("cym", name2);
      areaCombined.setName("tes", name2);
      
      THEN( "the Area instances can be emplaced in the Areas instance without exception" ) {

        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area1) );
        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area2) );

        AND_THEN( "the Areas instance has size 1" ) {

          REQUIRE_NOTHROW( areas.size() == 1 );

        } // AND_THEN

        AND_THEN( "the names of the second Area instances will overwrite the first" ) {

          Area &newArea = areas.getArea(localAuthorityCode);
          
          REQUIRE( newArea == areaCombined );

        } // AND_THEN

      } // THEN
    
    } // AND_GIVEN
    
    AND_GIVEN( "two newly constructed Area instances with the same local authority codes ('W06000011') but overlapping Measures" ) {
      
      std::string localAuthorityCode = "W06000011";
      Area area1(localAuthorityCode);
      Area area2(localAuthorityCode);
      Area areaCombined(localAuthorityCode);

      const std::string codename1 = "pop";
      const std::string label1 = "Population";
      Measure measure1(codename1, label1);
      
      const std::string codename2 = "dens";
      const std::string label2 = "Population density";
      Measure measure2(codename2, label2);
      
      area1.setMeasure(codename1, measure1);
      area2.setMeasure(codename2, measure2);
      
      areaCombined.setMeasure(codename1, measure1);
      areaCombined.setMeasure(codename2, measure2);
      
      THEN( "the Area instances can be emplaced in the Areas instance without exception" ) {

        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area1) );
        REQUIRE_NOTHROW( areas.setArea(localAuthorityCode, area2) );

        AND_THEN( "the Areas instance has size 1" ) {

          REQUIRE_NOTHROW( areas.size() == 1 );

        } // AND_THEN

      } // THEN
    
    } // AND_GIVEN

  } // THEN

} // SCENARIO
