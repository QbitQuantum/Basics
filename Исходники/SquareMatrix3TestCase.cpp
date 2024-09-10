void SquareMatrix3TestCase::testOtherMemberFunctions() {
    //test inverse
    RotMat3x3d ident = RotMat3x3d::identity();
    CPPUNIT_ASSERT(ident == ident.inverse());

    RotMat3x3d m1;
    m1(0,0) = 1.0;
    m1(0,1) = 5.0;
    m1(0,2) = 3.0;
    m1(1,0) = 3.0;
    m1(1,1) = 1.0;
    m1(1,2) = 2.0;
    m1(2,0) = 0.0;
    m1(2,1) = -21.0;
    m1(2,2) = -81.0; 
    
    CPPUNIT_ASSERT(m1 == (m1.inverse()).inverse());
    
    //test determinant
    RotMat3x3d m2;
    m2(0,0) = 1.0;
    m2(0,1) = 5.0;
    m2(0,2) = 3.0;
    m2(1,0) = 6.0;
    m2(1,1) = 0.0;
    m2(1,2) = 2.0;
    m2(2,0) = 0.0;
    m2(2,1) = -1.0;
    m2(2,2) = 1.0; 
    CPPUNIT_ASSERT_DOUBLES_EQUAL(m2.determinant(), -46.0, OpenMD::NumericConstant::epsilon);
}