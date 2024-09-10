void JacobianTest::TestChangeRefFrame(){
    //Create a random jacobian
    Jacobian j1(5);
    j1.data.setRandom();
    //Create a random frame
    Frame f;
    random(f);
    
    Jacobian j2(5);
    CPPUNIT_ASSERT(changeRefFrame(j1,f,j2));
    CPPUNIT_ASSERT(j1!=j2);
    Jacobian j3(4);
    CPPUNIT_ASSERT(!changeRefFrame(j1,f,j3));
    j3.resize(5);
    CPPUNIT_ASSERT(changeRefFrame(j2,f.Inverse(),j3));
    CPPUNIT_ASSERT_EQUAL(j1,j3);
}