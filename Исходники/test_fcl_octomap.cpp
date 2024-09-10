void octomap_distance_test_BVH(std::size_t n)
{
  std::vector<Vec3f> p1;
  std::vector<Triangle> t1;
  boost::filesystem::path path(TEST_RESOURCES_DIR);
  loadOBJFile((path / "env.obj").string().c_str(), p1, t1);

  BVHModel<BV>* m1 = new BVHModel<BV>();
  boost::shared_ptr<CollisionGeometry> m1_ptr(m1);

  m1->beginModel();
  m1->addSubModel(p1, t1);
  m1->endModel();

  OcTree* tree = new OcTree(boost::shared_ptr<octomap::OcTree>(generateOcTree()));
  boost::shared_ptr<CollisionGeometry> tree_ptr(tree);

  std::vector<Transform3f> transforms;
  FCL_REAL extents[] = {-10, -10, 10, 10, 10, 10};

  generateRandomTransforms(extents, transforms, n);
  
  for(std::size_t i = 0; i < n; ++i)
  {
    Transform3f tf(transforms[i]);

    CollisionObject obj1(m1_ptr, tf);
    CollisionObject obj2(tree_ptr, tf);
    DistanceData cdata;
    FCL_REAL dist1 = std::numeric_limits<FCL_REAL>::max();
    defaultDistanceFunction(&obj1, &obj2, &cdata, dist1);


    std::vector<CollisionObject*> boxes;
    generateBoxesFromOctomap(boxes, *tree);
    for(std::size_t j = 0; j < boxes.size(); ++j)
      boxes[j]->setTransform(tf * boxes[j]->getTransform());
  
    DynamicAABBTreeCollisionManager* manager = new DynamicAABBTreeCollisionManager();
    manager->registerObjects(boxes);
    manager->setup();

    DistanceData cdata2;
    manager->distance(&obj1, &cdata2, defaultDistanceFunction);
    FCL_REAL dist2 = cdata2.result.min_distance;

    for(std::size_t j = 0; j < boxes.size(); ++j)
      delete boxes[j];
    delete manager;

    std::cout << dist1 << " " << dist2 << std::endl;
    BOOST_CHECK(std::abs(dist1 - dist2) < 0.001);
  }
}