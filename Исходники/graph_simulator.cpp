void GraphSimulator::simulate(int samples, int trajectories, bool interClosures, bool lookForClosures, const Isometry2d& offset)
{
    // grid size
    int size = 50;

    // some parameters for the generation of the samples
    int forwardSteps = 3;
    double stepLength = 1.0;
    Isometry2d maxStepTransform(utility::v2t(Vector3d(forwardSteps * stepLength, 0, 0)));

    // Fake sensor for loop-closure detection
    double fov = (forwardSteps - 1) << 1;
    cout << "FOV: " << fov << endl;

    Vector2d grid(size >> 1, size >> 1);
    cout << "Grid: " << grid.x() << ", " << grid.y() << endl;

    VectorXd probLimits(POSSIBLE_MOTIONS);
    for(int i = 0; i < probLimits.size(); ++i)
    {
        probLimits[i] = (i + 1) / (double) POSSIBLE_MOTIONS;
    }

    Matrix3d covariance;
    covariance.fill(0.);
    covariance(0, 0) = _noise[0] * _noise[0];
    covariance(1, 1) = _noise[1] * _noise[1];
    covariance(2, 2) = _noise[2] * _noise[2];
    Matrix3d information = covariance.inverse();

    SimNode start;
    start.id = 0;
    start.real_pose = offset;
    start.noisy_pose = offset;

    for(short int k = 0; k < trajectories; ++k)
    {
        _trajectories.push_back(SimGraph());
        SimGraph& traj = _trajectories.back();

        Poses& poses = traj._poses;
        poses.clear();
        poses.push_back(start);

        // Nodes
        while((int) poses.size() < samples)
        {
            // go straight for some steps ...
            for(int i = 1; i < forwardSteps && (int) poses.size() < samples; ++i)
            {
                SimNode nextPose = generatePose(poses.back(), utility::v2t(Vector3d(stepLength, 0, 0)));
                poses.push_back(nextPose);
            }
            if((int) poses.size() == samples)
            {
                break;
            }

            // ... now some other direction
            double uniform_value = Noise::uniform(0., 1.);
            int direction = 0;
            while(probLimits[direction] < uniform_value && direction + 1 < POSSIBLE_MOTIONS)
            {
                direction++;
            }
            Isometry2d nextMotion = generateMotion(direction, stepLength);
            SimNode nextPose = generatePose(poses.back(), nextMotion);

            Isometry2d nextStepFinalPose = nextPose.real_pose * maxStepTransform;
            if(fabs(nextStepFinalPose.translation().x()) >= grid[0] || fabs(nextStepFinalPose.translation().y()) >= grid[1])
            {
                for(int i = 0; i < POSSIBLE_MOTIONS; ++i)
                {
                    nextMotion = generateMotion(i, stepLength);
                    nextPose = generatePose(poses.back(), nextMotion);
                    nextStepFinalPose = nextPose.real_pose * maxStepTransform;
                    if(fabs(nextStepFinalPose.translation().x()) < grid[0] && fabs(nextStepFinalPose.translation().y()) < grid[1])
                    {
                        break;
                    }
                }
            }
            poses.push_back(nextPose);
        }
        cout << "Added Nodes" << endl;

        // Edges
        Edges& edges = traj._edges;
        edges.clear();
        for(size_t i = 1; i < poses.size(); ++i)
        {
            SimNode& prev = poses[i-1];
            SimNode& curr = poses[i];

            SimEdge* edge = new SimEdge;
            edge->from_id = prev.id;
            edge->to_id = curr.id;
            edge->real_transform = prev.real_pose.inverse() * curr.real_pose;
            edge->noisy_transform = prev.noisy_pose.inverse() * curr.noisy_pose;
            edge->information = information;

            edges.insert(edge);
            prev._connections.insert(edge);
        }
        cout << "Added Edges" << endl;

        // Loop Closures
        if(lookForClosures)
        {
            // Closures
            for(int i = poses.size()-1; i >= 0; i--)
            {
                SimNode& sp = poses[i];
//                for(int j = 0; j < i; j+=20)
                for(int j = 0; j < i; j+=5)
                {
                    SimNode& candidate = poses[j];
                    Isometry2d transform = sp.real_pose.inverse() * candidate.real_pose;
                    double distance = utility::t2v(transform).squaredNorm();
                    if(fabs(distance) <= fov)
                    {
                        SimEdge* loopClosure = new SimEdge;
                        loopClosure->from_id = sp.id;
                        loopClosure->to_id = candidate.id;
                        loopClosure->real_transform = transform;
                        loopClosure->noisy_transform = transform;
                        loopClosure->information = information;

                        edges.insert(loopClosure);
                        sp._connections.insert(loopClosure);
                    }
                }
            }
        }
    }
    cout << "Added Loop Closures" << endl;

    // Inter Graph Closures
    if(interClosures)
    {
        Edges& closures = _closures;

        for(uint i = 1; i < _trajectories.size(); ++i)
        {
            SimGraph& t1 = _trajectories[i-1];
            SimGraph& t2 = _trajectories[i];
            const Poses& g1_poses = t1.poses();
            const Poses& g2_poses = t2.poses();
            for(uint i = 0; i < g2_poses.size(); i+=5)
            {
                const SimNode& sp = g2_poses[i];
                for(uint j = 0; j < g1_poses.size(); j+=5)
                {
                    const SimNode& candidate = g1_poses[j];
                    Isometry2d transform = sp.real_pose.inverse() * candidate.real_pose;
                    double distance = utility::t2v(transform).squaredNorm();
                    if(fabs(distance) <= fov)
                    {
                        SimEdge* graphClosure = new SimEdge;
                        graphClosure->from_id = sp.id;
                        graphClosure->to_id = candidate.id;
                        graphClosure->real_transform = transform;
                        graphClosure->noisy_transform = transform;

                        graphClosure->information = information;

                        closures.insert(graphClosure);
                    }
                }
            }
        }
        cout << "Added Inter Graph Closures" << endl;
    }
}