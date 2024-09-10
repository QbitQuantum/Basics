TEST(ReachabilitySphere, getPrincipalComponents)
{
    ReachabilitySphere sphere;
    std::vector<Vector> vectors;
    std::vector<Vector> components;

    // a line in x direction should give the main principal component lying in x direction
    vectors.push_back(Vector(0.0, 0.0, 0.0));
    vectors.push_back(Vector(1.0, 0.0, 0.0));
    vectors.push_back(Vector(2.0, 0.0, 0.0));
    vectors.push_back(Vector(3.0, 0.0, 0.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[2].x == 1.0);
    ASSERT_TRUE(components[2].y == 0.0);
    ASSERT_TRUE(components[2].z == 0.0);

    vectors.clear();

    // a line in y direction should give the main principal component lying in y direction
    vectors.push_back(Vector(0.0, 0.0, 0.0));
    vectors.push_back(Vector(0.0, 1.0, 0.0));
    vectors.push_back(Vector(0.0, 2.0, 0.0));
    vectors.push_back(Vector(0.0, 3.0, 0.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[2].x == 0.0);
    ASSERT_TRUE(components[2].y == 1.0);
    ASSERT_TRUE(components[2].z == 0.0);

    vectors.clear();

    // a line in z direction should give the main principal component lying in z direction
    vectors.push_back(Vector(0.0, 0.0, 0.0));
    vectors.push_back(Vector(0.0, 0.0, 1.0));
    vectors.push_back(Vector(0.0, 0.0, 2.0));
    vectors.push_back(Vector(0.0, 0.0, 3.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[2].x == 0.0);
    ASSERT_TRUE(components[2].y == 0.0);
    ASSERT_TRUE(components[2].z == 1.0);

    vectors.clear();

    // filling just x and y directions should give the least principal component in z direction
    vectors.push_back(Vector(1.0, 2.0, 0.0));
    vectors.push_back(Vector(2.0, 1.0, 0.0));
    vectors.push_back(Vector(1.0, 0.0, 0.0));
    vectors.push_back(Vector(0.0, 1.0, 0.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[0].x == 0.0);
    ASSERT_TRUE(components[0].y == 0.0);
    ASSERT_TRUE(components[0].z == 1.0);

    vectors.clear();

    // filling just y and z directions should give the least principal component in x direction
    vectors.push_back(Vector(0.0, 2.0, 0.0));
    vectors.push_back(Vector(0.0, 1.0, 2.0));
    vectors.push_back(Vector(0.0, 0.0, 1.0));
    vectors.push_back(Vector(0.0, 1.0, 1.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[0].x == 1.0);
    ASSERT_TRUE(components[0].y == 0.0);
    ASSERT_TRUE(components[0].z == 0.0);

    vectors.clear();

    // filling just x and z directions should give the least principal component in y direction
    vectors.push_back(Vector(1.0, 0.0, 0.0));
    vectors.push_back(Vector(2.0, 0.0, 2.0));
    vectors.push_back(Vector(2.0, 0.0, 1.0));
    vectors.push_back(Vector(0.0, 0.0, 1.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(components[0].x == 0.0);
    ASSERT_TRUE(components[0].y == 1.0);
    ASSERT_TRUE(components[0].z == 0.0);

    vectors.clear();

    // a line in x-y direction should give the main principal component lying in x-y direction
    vectors.push_back(Vector(0.0, 0.0, 0.0));
    vectors.push_back(Vector(1.0, 1.0, 0.0));
    vectors.push_back(Vector(2.0, 2.0, 0.0));
    vectors.push_back(Vector(3.0, 3.0, 0.0));
    
    components = sphere.getPrincipalComponents(vectors);

    ASSERT_TRUE(fuzzyEquals(std::abs(components[2].x), 0.707106781));
    ASSERT_TRUE(fuzzyEquals(std::abs(components[2].y), 0.707106781));
    ASSERT_TRUE(components[2].z == 0.0);


    // test Capability of type cone
    Capability cone(CONE, 70.0, 55.0, 35.0);
    
    sphere = createReachabilitySphereFromCapability(cone, 400);

    components = sphere.getPrincipalComponents(sphere._reachableDirections);

    // test phi
    ASSERT_TRUE(atan2(components[0].y, components[0].x) * 180.0 / M_PI < 72.0);
    ASSERT_TRUE(atan2(components[0].y, components[0].x) * 180.0 / M_PI > 68.0);

    // test theta
    ASSERT_TRUE(acos(components[0].z) * 180.0 / M_PI < 56.0);
    ASSERT_TRUE(acos(components[0].z) * 180.0 / M_PI > 54.0);


    // test Capability of type cylinder_1
    Capability cylinder1(CYLINDER_1, 70.0, 55.0, 35.0);
    
    sphere = createReachabilitySphereFromCapability(cylinder1, 400);

    components = sphere.getPrincipalComponents(sphere._reachableDirections);

    // test phi
    ASSERT_TRUE(atan2(components[2].y, components[2].x) * 180.0 / M_PI < 72.0);
    ASSERT_TRUE(atan2(components[2].y, components[2].x) * 180.0 / M_PI > 68.0);

    // test theta
    ASSERT_TRUE(acos(components[2].z) * 180.0 / M_PI < 56.0);
    ASSERT_TRUE(acos(components[2].z) * 180.0 / M_PI > 54.0);


    // test Capability of type cylinder_2
    Capability cylinder2(CYLINDER_2, 70.0, 55.0, 35.0);
    
    sphere = createReachabilitySphereFromCapability(cylinder2, 400);

    components = sphere.getPrincipalComponents(sphere._reachableDirections);

    // test phi
    ASSERT_TRUE(atan2(components[0].y, components[0].x) * 180.0 / M_PI < 72.0);
    ASSERT_TRUE(atan2(components[0].y, components[0].x) * 180.0 / M_PI > 68.0);

    // test theta
    ASSERT_TRUE(acos(components[0].z) * 180.0 / M_PI < 56.0);
    ASSERT_TRUE(acos(components[0].z) * 180.0 / M_PI > 54.0);
}