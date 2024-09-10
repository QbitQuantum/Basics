void octomap_distance_test(S env_scale, std::size_t env_size, bool use_mesh, bool use_mesh_octomap, double resolution)
{
    // srand(1);
    std::vector<CollisionObject<S>*> env;
    if(use_mesh)
        test::generateEnvironmentsMesh(env, env_scale, env_size);
    else
        test::generateEnvironments(env, env_scale, env_size);

    OcTree<S>* tree = new OcTree<S>(std::shared_ptr<const octomap::OcTree>(test::generateOcTree(resolution)));
    CollisionObject<S> tree_obj((std::shared_ptr<CollisionGeometry<S>>(tree)));

    DynamicAABBTreeCollisionManager<S>* manager = new DynamicAABBTreeCollisionManager<S>();
    manager->registerObjects(env);
    manager->setup();

    test::DistanceData<S> cdata;
    test::TStruct t1;
    test::Timer timer1;
    timer1.start();
    manager->octree_as_geometry_collide = false;
    manager->octree_as_geometry_distance = false;
    manager->distance(&tree_obj, &cdata, test::defaultDistanceFunction);
    timer1.stop();
    t1.push_back(timer1.getElapsedTime());


    test::DistanceData<S> cdata3;
    test::TStruct t3;
    test::Timer timer3;
    timer3.start();
    manager->octree_as_geometry_collide = true;
    manager->octree_as_geometry_distance = true;
    manager->distance(&tree_obj, &cdata3, test::defaultDistanceFunction);
    timer3.stop();
    t3.push_back(timer3.getElapsedTime());


    test::TStruct t2;
    test::Timer timer2;
    timer2.start();
    std::vector<CollisionObject<S>*> boxes;
    if(use_mesh_octomap)
        test::generateBoxesFromOctomapMesh(boxes, *tree);
    else
        test::generateBoxesFromOctomap(boxes, *tree);
    timer2.stop();
    t2.push_back(timer2.getElapsedTime());

    timer2.start();
    DynamicAABBTreeCollisionManager<S>* manager2 = new DynamicAABBTreeCollisionManager<S>();
    manager2->registerObjects(boxes);
    manager2->setup();
    timer2.stop();
    t2.push_back(timer2.getElapsedTime());


    test::DistanceData<S> cdata2;

    timer2.start();
    manager->distance(manager2, &cdata2, test::defaultDistanceFunction);
    timer2.stop();
    t2.push_back(timer2.getElapsedTime());

    std::cout << cdata.result.min_distance << " " << cdata3.result.min_distance << " " << cdata2.result.min_distance << std::endl;

    if(cdata.result.min_distance < 0)
        EXPECT_TRUE(cdata2.result.min_distance <= 0);
    else
        EXPECT_TRUE(std::abs(cdata.result.min_distance - cdata2.result.min_distance) < 1e-3);

    delete manager;
    delete manager2;
    for(size_t i = 0; i < boxes.size(); ++i)
        delete boxes[i];


    std::cout << "1) octomap overall time: " << t1.overall_time << std::endl;
    std::cout << "1') octomap overall time (as geometry): " << t3.overall_time << std::endl;
    std::cout << "2) boxes overall time: " << t2.overall_time << std::endl;
    std::cout << "  a) to boxes: " << t2.records[0] << std::endl;
    std::cout << "  b) structure init: " << t2.records[1] << std::endl;
    std::cout << "  c) distance: " << t2.records[2] << std::endl;
    std::cout << "Note: octomap may need more collides when using mesh, because octomap collision uses box primitive inside" << std::endl;
}