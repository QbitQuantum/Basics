void TrajectoryPlannerTest::checkGoalDistance()
{
    //let's box a cell in and make sure that its distance gets set to max
    map_->operator () (1, 2).target_dist = 1;
    map_->operator () (1, 1).target_dist = 1;
    map_->operator () (1, 0).target_dist = 1;
    map_->operator () (2, 0).target_dist = 1;
    map_->operator () (3, 0).target_dist = 1;
    map_->operator () (3, 1).target_dist = 1;
    map_->operator () (3, 2).target_dist = 1;
    map_->operator () (2, 2).target_dist = 1;
    wa->synchronize();

    //set a goal
    tc.path_map_.resetPathDist();
    queue<MapCell*> target_dist_queue;
    MapCell& current = tc.path_map_ (4, 9);
    current.target_dist = 0.0;
    current.target_mark = true;
    target_dist_queue.push (&current);
    tc.path_map_.computeTargetDistance (target_dist_queue, tc.costmap_);

    EXPECT_FLOAT_EQ (tc.path_map_ (4, 8).target_dist, 1.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 7).target_dist, 2.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 6).target_dist, 100.0); //there's an obstacle here placed above
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 5).target_dist, 6.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 4).target_dist, 7.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 3).target_dist, 8.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 2).target_dist, 9.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 1).target_dist, 10.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (4, 0).target_dist, 11.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (5, 8).target_dist, 2.0);
    EXPECT_FLOAT_EQ (tc.path_map_ (9, 4).target_dist, 10.0);

    //check the boxed in cell
    EXPECT_FLOAT_EQ (100.0, tc.path_map_ (2, 2).target_dist);

}