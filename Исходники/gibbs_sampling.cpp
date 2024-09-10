void dd::GibbsSampling::learn(const int & n_epoch, const int & n_sample_per_epoch, 
                              const double & stepsize, const double & decay, 
                              const double reg_param, const double reg1_param,
                              const bool is_quiet){
			      //const std::string meta_file, const bool is_quiet){

  Timer t_total;

  double current_stepsize = stepsize;

  Timer t;
  int nvar = this->factorgraphs[0].n_var;
  int nnode = n_numa_nodes + 1;
  int nweight = this->factorgraphs[0].n_weight;

//  int num_sources_per_var[nvar];
//  for (int i = 0; i < nvar; i++) {
//    num_sources_per_var[i] = 1;
//  }
//  std::string full_feature_names[nvar];
//  int feature_values[nvar];
//  std::map<std::string, int*> feature_var_map;
//  std::map<std::string,int*>::iterator it;
//  int num_feature_names = 0;
//
//  std::cout<<"Opening file "<<meta_file<<std::endl;
//  std::ifstream myfile;
//  std::string data;
//  myfile.open (meta_file);
//  if (myfile.good()) {
//    while ( std::getline(myfile,data)) {
//      istringstream iss(data);
//      std::string temp;
//      std::getline(iss, temp, '\t');
//      int feature_id = std::stoi(temp, nullptr);
//      std::string table_name;
//      std::getline(iss, table_name, '\t');
//      std::string feature_data;
//      std::getline(iss, feature_data);
//      feature_data = feature_data.substr(1, feature_data.length() - 2);
//      temp = feature_data.substr(14 + feature_data.find("source_count\":"), feature_data.find(",feature_name") - feature_data.find("source_count\":") - 14 );
//      num_sources_per_var[feature_id] = std::stoi(temp, nullptr);
//      temp = feature_data.substr(13 + feature_data.find("feature_name:"), feature_data.find(",feature_value") - feature_data.find("feature_name:") - 13 );
//      full_feature_names[feature_id] = table_name + "." + temp;
//      temp = feature_data.substr(14 + feature_data.find("feature_value:"), feature_data.find("}") - feature_data.find("feature_value:") - 14 );
//      feature_values[feature_id] = (int)std::stod(temp, nullptr);
//      it = feature_var_map.find(full_feature_names[feature_id]);
//      if (it != feature_var_map.end()) {
//        int* arr = it;
//        arr[feature_values[feature_id]] = feature_id;
//      } else {
//        feature_var_map[full_feature_names[feature_id]] = new int[10]; // NOTE: Hardcoded, change later.
//      }
//      feature_var_map[full_feature_names[feature_id]] = ;
//      std::cout << feature_id << " -- " << table_name << " - " << full_feature_names[feature_id] << " ;; " << feature_values[feature_id] << " ,, " << num_sources_per_var[feature_id] << std::endl;
//    }
//  }
//  myfile.close();
  
  
  // single node samplers
  std::vector<SingleNodeSampler> single_node_samplers;
  for(int i=0;i<=n_numa_nodes;i++){
    single_node_samplers.push_back(SingleNodeSampler(&this->factorgraphs[i], 
      n_thread_per_numa, i, false, 0, learn_non_evidence));
  }

  std::unique_ptr<double[]> ori_weights(new double[nweight]);
  memcpy(ori_weights.get(), this->factorgraphs[0].infrs->weight_values, sizeof(double)*nweight);

  // learning epochs
  for(int i_epoch=0;i_epoch<n_epoch;i_epoch++){

    if (!is_quiet) {
      std::cout << std::setprecision(2) << "LEARNING EPOCH " << i_epoch * nnode <<  "~" 
        << ((i_epoch+1) * nnode) << "...." << std::flush;
    }

    t.restart();
    
    // set stepsize
    for(int i=0;i<nnode;i++){
      single_node_samplers[i].p_fg->stepsize = current_stepsize;
    }

    // performs stochastic gradient descent with sampling
    for(int i=0;i<nnode;i++){
      single_node_samplers[i].sample_sgd();
    }

    // wait the samplers to finish
    for(int i=0;i<nnode;i++){
      single_node_samplers[i].wait_sgd();
    }

    FactorGraph & cfg = this->factorgraphs[0];

    // sum the weights and store in the first factor graph
    // the average weights will be calculated and assigned to all factor graphs 
    for(int i=1;i<=n_numa_nodes;i++){
      FactorGraph & cfg_other = this->factorgraphs[i];
      for(int j=0;j<nweight;j++){
        cfg.infrs->weight_values[j] += cfg_other.infrs->weight_values[j];
      }
    }

    // calculate average weights and regularize weights
    for(int j=0;j<nweight;j++){
      cfg.infrs->weight_values[j] /= nnode;
      if(cfg.infrs->weights_isfixed[j] == false){
        cfg.infrs->weight_values[j] *= (1.0/(1.0+reg_param*current_stepsize));
	double l1delta = reg1_param * current_stepsize;
	if (cfg.infrs->weight_values[j] > l1delta) {		
	  cfg.infrs->weight_values[j] -= l1delta;
	} else if (cfg.infrs->weight_values[j] < - l1delta) {
	  cfg.infrs->weight_values[j] += l1delta;
	} else {
	  cfg.infrs->weight_values[j] = 0;
	}
      }
    }

    // set weights for other factor graph to be the same as the first factor graph
    for(int i=1;i<=n_numa_nodes;i++){
      FactorGraph &cfg_other = this->factorgraphs[i];
      for(int j=0;j<nweight;j++){
        if(cfg.infrs->weights_isfixed[j] == false){
          cfg_other.infrs->weight_values[j] = cfg.infrs->weight_values[j];
        }
      }
    }    

    // calculate the norms of the difference of weights from the current epoch
    // and last epoch
    double lmax = -1000000;
    double l2=0.0;
    for(int i=0;i<nweight;i++){
      double diff = fabs(ori_weights[i] - cfg.infrs->weight_values[i]);
      ori_weights[i] = cfg.infrs->weight_values[i];
      l2 += diff*diff;
      if(lmax < diff){
        lmax = diff;
      }
    }
    lmax = lmax/current_stepsize;
    
    double elapsed = t.elapsed();
    if (!is_quiet) {
      std::cout << "" << elapsed << " sec.";
      std::cout << ","  << (nvar*nnode)/elapsed << " vars/sec." << ",stepsize=" << current_stepsize << ",lmax=" << lmax << ",l2=" << sqrt(l2)/current_stepsize << std::endl;
    }

    current_stepsize = current_stepsize * decay;

  }

  double elapsed = t_total.elapsed();
  std::cout << "TOTAL LEARNING TIME: " << elapsed << " sec." << std::endl;
}