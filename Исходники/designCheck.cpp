void reportPositionMetrics(System &_sys, Options &_opt){ 

       System ref;
       if (_opt.ref != ""){
	 ref.readPdb(_opt.ref);
       }

	SysEnv env;
	PhiPsiReader ppr(env.getEnv("MSL_PHIPSI_TABLE"));
	ppr.open();
	ppr.read();
	ppr.close();
	PhiPsiStatistics pps = ppr.getPhiPsiStatistics();
	

	int unpaired_cys_index = 1;
	for (uint c = 0; c < _sys.chainSize();c++){
	  for (uint r = 0; r < _sys.getChain(c).positionSize();r++){
	    Residue &res = _sys.getChain(c).getResidue(r);

	    // Remove non-amino acids... bad way to do this, but should work.
	    string oneLetter = MslTools::getOneLetterCode(res.getResidueName());
	    if (oneLetter == "X") continue;



	    if (r == 0 || r == _sys.positionSize()-1 ||
		MslTools::getOneLetterCode(_sys.getChain(c).getResidue(r+1).getResidueName()) == "X"  || 
		MslTools::getOneLetterCode(_sys.getChain(c).getResidue(r-1).getResidueName()) == "X") continue;

	    
	    Residue & nm1 = _sys.getChain(c).getResidue(r-1);
	    Residue & np1 = _sys.getChain(c).getResidue(r+1);

	    // Get Phi-Psi
	    double phi = PhiPsiStatistics::getPhi(nm1,res);
	    double psi = PhiPsiStatistics::getPsi(res,np1);

	    // Check glycine/proline populations
	    int resCounts  = pps.getCounts(res.getResidueName(),phi,psi);
	    int glyCounts  = pps.getCounts("GLY",phi,psi);
	    double glyFreq = pps.getFreqInBin("GLY",phi,psi);
	    int proCounts  = pps.getCounts("PRO",phi,psi);
	    double proFreq = pps.getFreqInBin("PRO",phi,psi);
	    
	    string refStr = "";
	    if (_opt.ref != ""){
	      if (ref.positionExists(res.getPositionId())){
		if (ref.getPosition(res.getPositionId()).getResidueName() == res.getResidueName()){
		  refStr = "**** IN REF STRUCTURE ****";
		}
	      }

	    }


	    // if glyFreq > 0.25 
	    if (glyFreq > 0.25){
	      fprintf(stdout, "%-40s %10s %8d %8d %8.3f %s\n","High freq. Gly",res.getIdentityId().c_str(),resCounts,glyCounts,glyFreq,refStr.c_str());
	    }
	    // if proFreq > 0.25
	    if (proFreq > 0.25){
	      fprintf(stdout, "%-40s %10s %8d %8d %8.3f %s\n","High freq. Pro",res.getIdentityId().c_str(),resCounts,proCounts,proFreq,refStr.c_str());
	    }


	    // if CYS, check for pairing
	    if (res.getResidueName() == "CYS"){

	      if (!res.atomExists("SG")){
		cerr << "ERROR CYS residue "<<res.getPositionId()<<" does not have a SG atom"<<endl;
	      }
	      bool unpairedCys = true;
	      double minDist = MslTools::doubleMax;
	      string minId = "";
	      for (uint p = 0; p < _sys.positionSize();p++){
	        Residue &res2 = _sys.getResidue(p);

		if (res2.getPositionId() == res.getPositionId()) continue;
		if (res2.getResidueName() != "CYS") continue;
		if (!res2.atomExists("SG")) continue;

		double dist = res2.getAtom("SG").distance(res.getAtom("SG"));
		if (dist < minDist){
		  minDist = dist;
		  minId   = res2.getPositionId();
		}
		if (dist < 2.2){
		  unpairedCys = false;
		  break;
		}


	      } // FOR system positions p


	      if (unpairedCys){
		fprintf(stdout, "%-40s %10s %8.3f %10s %s\n","Unpaired Cys",res.getPositionId().c_str(),minDist,minId.c_str(),refStr.c_str());
		if (refStr != "") continue;

		string selStr = MslTools::stringf("%s and chain %1s and resi %d",MslTools::getFileName(_opt.pdb).c_str(),res.getChainId().c_str(), res.getResidueNumber());
		if (res.getChainId() == "" || res.getChainId() == " "){
		  selStr = MslTools::stringf("%s and resi %d",MslTools::getFileName(_opt.pdb).c_str(),res.getResidueNumber());
		}
		string selName = MslTools::stringf("%s-%s-%-d",MslTools::getFileName(_opt.pdb).c_str(),"UNPAIRED_CYS",unpaired_cys_index++);
		_opt.pymol.createSelection(selName,selStr);
	      }


	    } // IF res == CYS
				    
	  } // Positions on chain
	} // Chains in system
}