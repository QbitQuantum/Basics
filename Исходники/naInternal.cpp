    void nanPayloadsUnitTest() {
        REQUIRE_START(testNanPayloads);
        REQUIRE(nanPayloadf(nanf("0"))    == 0); 
        REQUIRE(nanPayloadf(nanf("1954")) == 1954); 
        REQUIRE(nanPayloadf(nanf("0") + 99) == 0); 
        REQUIRE(nanPayloadf(nanf("1954")+ 99) == 1954); 

        REQUIRE(nanPayload (nan("0"))    == 0); 
        REQUIRE(nanPayload (nan("1954")) == 1954); 
        REQUIRE(nanPayload (nan("0") + 99) == 0); 
        REQUIRE(nanPayload (nan("1954")+ 99) == 1954); 

        // something wrong with nanPayloadl() at the moment
        //REQUIRE(nanPayloadl(nan("0")).low    == 0); 
        //REQUIRE(nanPayloadl(nan("1954")).low == 1954); 
        //REQUIRE(nanPayloadl(nan("0") + 99).low == 0); 
        //REQUIRE(nanPayloadl(nan("1954")+ 99).low == 1954); 
        //int errs = REQUIRE_END(testnanPayloads);
    }