VOID TEST(AMF0Test, ApiAnyAssert) 
{
    SrsStream s;
    SrsAmf0Any* o = NULL;
    
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    EXPECT_EQ(ERROR_SUCCESS, s.initialize(buf, sizeof(buf)));
    
    // read any
    if (true) {
        s.reset();
        s.current()[0] = 0x12;
        EXPECT_NE(ERROR_SUCCESS, srs_amf0_read_any(&s, &o));
        EXPECT_TRUE(NULL == o);
        srs_freep(o);
    }
    
    // any convert
    if (true) {
        o = SrsAmf0Any::str();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_string());
    }
    if (true) {
        o = SrsAmf0Any::number();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_number());
    }
    if (true) {
        o = SrsAmf0Any::boolean();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_boolean());
    }
    if (true) {
        o = SrsAmf0Any::null();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_null());
    }
    if (true) {
        o = SrsAmf0Any::undefined();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_undefined());
    }
    if (true) {
        o = SrsAmf0Any::object();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_object());
    }
    if (true) {
        o = SrsAmf0Any::ecma_array();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_ecma_array());
    }
    if (true) {
        o = SrsAmf0Any::strict_array();
        SrsAutoFree(SrsAmf0Any, o);
        EXPECT_TRUE(o->is_strict_array());
    }
    
    // empty object
    if (true) {
        o = SrsAmf0Any::object();
        SrsAutoFree(SrsAmf0Any, o);
        s.reset();
        EXPECT_EQ(ERROR_SUCCESS, o->write(&s));
        EXPECT_EQ(1+3, s.pos());
    }
    
    // empty ecma array
    if (true) {
        o = SrsAmf0Any::ecma_array();
        SrsAutoFree(SrsAmf0Any, o);
        s.reset();
        EXPECT_EQ(ERROR_SUCCESS, o->write(&s));
        EXPECT_EQ(1+4+3, s.pos());
    }
    
    // strict array
    if (true) {
        o = SrsAmf0Any::strict_array();
        SrsAutoFree(SrsAmf0Any, o);
        s.reset();
        EXPECT_EQ(ERROR_SUCCESS, o->write(&s));
        EXPECT_EQ(1+4, s.pos());
    }
}