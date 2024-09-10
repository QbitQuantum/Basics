void Graph::solve(unsigned int iterations){
    ROS_INFO(":: SOLVING! ::");
    //Setup solver
    g2o::SparseOptimizer sparseOptimizer;
    SlamLinearSolver* linearSolver = new SlamLinearSolver();
    linearSolver->setBlockOrdering(false);
    SlamBlockSolver* blockSolver = new SlamBlockSolver(linearSolver);
    g2o::OptimizationAlgorithmGaussNewton* solverGauss = 
            new g2o::OptimizationAlgorithmGaussNewton(blockSolver);
    sparseOptimizer.setAlgorithm(solverGauss);

    //Convert pose nodes to g2o node structure and add in the graph.
    for(unsigned int i = 0; i < node_list.size(); i ++){
        Node* curNode = node_list[i];
        // ROS_INFO("Curnode id: %d", curNode->id);
        // Convert the node.
        GraphPose graph_pose = curNode->graph_pose;
        g2o::SE2 converted_pose(graph_pose.x, graph_pose.y, graph_pose.theta);        
        // Create the vertex to put in the graph.
        g2o::VertexSE2* vertex = new g2o::VertexSE2;
        vertex->setId(curNode->id);
        // ROS_INFO("Converted node id: %d", vertex->id());
        vertex->setEstimate(converted_pose);
        // Add to the graph
        sparseOptimizer.addVertex(vertex);
    }

    // Set one pose fixed, to reduce complexity. This pose wont be changed by the optimizer.
    sparseOptimizer.vertex(1)->setFixed(true);

    // Convert the edges to g2o edges and add them in the graph
    for(unsigned int i = 0; i < edge_list.size(); i++) {
        // ROS_INFO("Adding edge: %d", i);
        Edge* edge = edge_list[i];
        //ROS_INFO("Edge parent id: %d, child id: %d", edge->parent_id, edge->child_id);
        //Actually make the edge for the optimizer.
        g2o::EdgeSE2* graph_edge = new g2o::EdgeSE2;
        graph_edge->vertices()[0] = sparseOptimizer.vertex(edge->parent_id);
        graph_edge->vertices()[1] = sparseOptimizer.vertex(edge->child_id);
        //
        g2o::SE2 se_mean(edge->mean[0], edge->mean[1], edge->mean[2]);
        graph_edge->setMeasurement(se_mean);
        Matrix3d cov;
        cov = MatrixXd::Zero(3,3);
        for(unsigned int i = 0; i < 3; i++) {
            for(unsigned int j = 0; j < 3; j++) {
              cov(i, j) = edge->covariance[i][j];
              // ROS_INFO("Covariance[%d]: %f", i+j, covariance[i][j]);
            }
        }
        graph_edge->setInformation(cov.inverse());
        //Add edge to optimizer
        sparseOptimizer.addEdge(graph_edge);
    }

    //Optimize!
    sparseOptimizer.setVerbose(false);
    sparseOptimizer.initializeOptimization();
    sparseOptimizer.optimize(iterations);

    //Convert the solved poses back
    for(unsigned int i = 0; i < node_list.size(); i++){
        GraphPose* currentPose = &(node_list[i]->graph_pose);
        g2o::SE2 optimized_pose = ((g2o::VertexSE2*) sparseOptimizer.vertex(node_list[i]->id))->estimate();
        //
        if(rot_distance(currentPose->theta, optimized_pose[2]) != 0. || distance(currentPose->x, optimized_pose[0], currentPose->y, optimized_pose[1]) > 0.) {
            ROS_INFO("Node %d, pose before optimize: x %f, y %f, t %f", node_list[i]->id, currentPose->x, currentPose->y, currentPose->theta);
            ROS_INFO("Node %d, pose after optimize: x %f, y %f, t %f", node_list[i]->id, optimized_pose[0], optimized_pose[1], optimized_pose[2]);
        }
        currentPose->x = optimized_pose[0];
        currentPose->y = optimized_pose[1];
        currentPose->theta = optimized_pose[2];
    }
    sparseOptimizer.clear();
};