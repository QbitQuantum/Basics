   bool CartTrajPlanner::jspace_trivial_path_planner(Eigen::VectorXd q_start,Eigen::VectorXd q_end,std::vector<Eigen::VectorXd> &optimal_path) {
       Eigen::VectorXd qx_start(NJNTS),qx_end(NJNTS);// need to convert to this type

       cout<<"jspace_trivial_path_planner: "<<endl;
       cout<<"q_start: "<<q_start.transpose()<<endl;
       cout<<"q_end: "<<q_end.transpose()<<endl;
       optimal_path.clear();
       optimal_path.push_back(q_start);
       optimal_path.push_back(q_end);
       return true;
   }