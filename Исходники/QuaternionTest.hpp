    void testIdentityOps( void) {
        Quaternion id = Quaternion::identity();
        Quaternion test(Vector3f(1,0,0),0.5);
        TS_ASSERT_EQUALS(test*id, test);
        TS_ASSERT_EQUALS(id*test, test);
        assert_near(id.normal(), id);

        Quaternion inverseid = id.inverse();
        TS_ASSERT_EQUALS(inverseid, id);

    }