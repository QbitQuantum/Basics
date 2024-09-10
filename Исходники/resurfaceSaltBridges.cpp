void runModelSaltBridges(
			 System &_sys,
			 Options &_opt,
			 std::priority_queue< std::pair<saltBridgeResult,subSeq>, std::vector< std::pair<saltBridgeResult,subSeq> >, compareScores> &_mcData){


  // TODO: Use sorted rotamer library..

  System baseModel = _sys;
  
  // Loop over solutions
  uint model = 0;
  vector<pair<saltBridgeResult,subSeq> > sbResultInOrder;
  while (!_mcData.empty() && model <= _opt.numStructuralModels){
    sbResultInOrder.push_back(_mcData.top());
    _mcData.pop();
    model++;
  }
  model = 0;
  for (int sb = sbResultInOrder.size()-1; sb >= 0; sb--){

    //fprintf(stdout, "WT : %s %8.3f\n", wtSeq.c_str(),wt_sbresult.score);
    //fprintf(stdout, "SEQ: %s %8.3f\n",mcData.top().second.seq.c_str(),mcData.top().first.score);
    saltBridgeResult sbr = sbResultInOrder[sb].first;

    MSLOUT.fprintf(stdout, "SOLUTION: %8.3f\n",sbr.score);
    vector<int> variablePositions;
    for (uint i = 0; i < sbr.mutations.size();i++){
      MSLOUT.fprintf(stdout,"\t%s %s\n",sbr.mutations[i].first.c_str(),sbr.mutations[i].second.c_str());

      // Mutate System, return position id of mutated position , blank string if no mutation...
      string posId = mutate(baseModel, sbr.mutations[i].first,_opt);
      if (posId != ""){
	MSLOUT.fprintf(stdout,"\t\t Mutating1 %s to %s\n", posId.c_str(),sbr.mutations[i].first.c_str());
	variablePositions.push_back(baseModel.getPositionIndex(posId));
      }
      
      posId = mutate(baseModel, sbr.mutations[i].second,_opt);
      if (posId != ""){
	MSLOUT.fprintf(stdout,"\t\t Mutating2 %s to %s\n", posId.c_str(),sbr.mutations[i].second.c_str());
	variablePositions.push_back(baseModel.getPositionIndex(posId));
      }
    }

    // Change HIS to HSD
    for (uint i = 0 ; i < baseModel.positionSize();i++){
      if (baseModel.getPosition(i).getResidueName() == "HIS"){
	baseModel.getPosition(i).setResidueName("HSD");
      }
    }
    MSLOUT.stream() << " Quenching..."<<endl;
    // Quench model..
    Quench quencher(_opt.topfile, _opt.parfile, _opt.rotlib);    
    quencher.setVariableNumberRotamers(50,10); // Big residues, Small residues
    System quenchedSys = quencher.runQuench(baseModel,variablePositions);

    // Write out model..
    quenchedSys.writePdb(MslTools::stringf("%s_resurfaced_%06d.pdb", MslTools::getFileName(_opt.pdb).c_str(),model+1));

    // Increment the models
    model++;

    baseModel = _sys;
  }

  MSLOUT.stream() << "Done salt-bridge modeling"<<endl;

}