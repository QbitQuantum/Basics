TEST_F(FFITest, CStackTooManyArgument) {
    // we assume this
    ASSERT_TRUE(sizeof(uint64_t) >= sizeof(intptr_t));

    CStack cstack;
    for (int i = 0; i < CStack::MAX_ARGC + CStack::MAX_REG; i++) {
        EXPECT_TRUE(cstack.push(Object::makeFixnum(3), CStack::SIGNATURE_INT));
    }
    const bool result = cstack.push(Object::makeFixnum(3), CStack::SIGNATURE_INT);
    EXPECT_FALSE(result);
    ucs4string err = cstack.getLastError();
    EXPECT_STREQ("too many ffi arguments", err.ascii_c_str());
}