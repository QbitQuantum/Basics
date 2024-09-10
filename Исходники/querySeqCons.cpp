int main(int argc, char *argv[]) {

  // Parse commandline options
  Options opt = setupOptions(argc,argv);


  // Read multiple sequence alignment and create a PSSM
  PSSMCreator pssm;
  MSLOUT.stream() << "Add FASTA to PSSM"<<endl;
  pssm.addMultipleSequenceAlignment(opt.fasta,opt.regexForFasta);

  if (opt.refAACounts != ""){
    MSLOUT.stream() << "Add refAACounts to PSSM"<<endl;
    pssm.readReferenceCounts(opt.refAACounts);
  }

  MSLOUT.stream() << "Create the PSSM"<<endl;
  if (opt.logodds){
    pssm.create(PSSMCreator::logodds);
  } else {
    pssm.create(PSSMCreator::freq);
  }


  if (opt.pdb != ""){
    // Read in the reference pdb file
    System sys;
    sys.readPdb(opt.pdb);
  
    AtomSelection select(sys.getAtomPointers());
    AtomPointerVector ats = select.select(opt.sel);
    string seq = PolymerSequence::toOneLetterCode(ats);

    MSLOUT.stream() << "Getting scoring function for sequence: "<<seq<<endl;

    MSLOUT.stream() << "refSeqName is: "<<opt.refSeqName<<endl;
    string scoreType = "";
    switch (opt.valueType) {
      case Options::freq:
	scoreType = "";
      break;
      case Options::entropy:
	scoreType = "entropy";
      break;
      case Options::mostfreq:
	scoreType = "mostfreq";
      break;
    }
    vector<double> scores = pssm.getScoreFunction(seq,opt.refSeqName,opt.refSeqOffset,scoreType);

    MSLOUT.stream() << "Add score to pdb file"<<endl;
    System selSys;
    selSys.addAtoms(ats);
    if (selSys.positionSize() != scores.size()){
      cerr << "ERROR 234 Selection position size is : "<<selSys.positionSize()<< " score vector is size: "<<scores.size()<<" "<<seq.length()<<endl;
      selSys.writePdb("sel.pdb");
      exit(234);
    }

    // Clear all temp-factors
    for (uint i = 0; i < sys.positionSize();i++){
      Position &pos = sys.getPosition(i);
      for (uint a = 0; a < pos.atomSize();a++){
	pos.getAtom(a).setTempFactor(0.0);
      }      
    }    
    selSys.writePdb("foo.pdb");

    // Re-assign with score
    for (uint i = 0; i < selSys.positionSize();i++){

      Position &pos = sys.getPosition(selSys.getPosition(i).getPositionId());      
      for (uint c = 0; c < sys.chainSize();c++){
	
	if (!(opt.applyToAllChains || sys.getChain(c).getChainId() == pos.getChainId())) continue;

	Position &chainPos = sys.getPosition(MslTools::stringf("%s,%d%s",sys.getChain(c).getChainId().c_str(),pos.getResidueNumber(),pos.getResidueIcode().c_str()));
	cout << "Setting chainPos "<<chainPos.getCurrentIdentity().getIdentityId()<<" "<<i<<endl;
	for (uint a = 0; a < chainPos.atomSize();a++){
	       chainPos.getAtom(a).setTempFactor(scores[i]);
	}
	MSLOUT.fprintf(stdout,"%8s %8.3f\n", chainPos.getPositionId().c_str(),scores[i]);


      }
      
      
    }

    sys.writePdb(opt.outPdb);

  } // IF opt.pdb

  if (opt.seq != ""){
    vector<string> toks = MslTools::tokenize(opt.seq, ",");
    
    if (toks.size() != 3){
      cerr << "ERROR opt.seq needs to be in the format REFNAME,STARTINDEX,ENDINDEX and it is: "<<opt.seq<<endl;
    }
    string refName = toks[0];
    int start      = MslTools::toInt(toks[1]);
    int end        = MslTools::toInt(toks[2]);

    MSLOUT.stream() << "Get frequencies of "<<refName<<" "<<start<<" "<<end<<endl;
    vector<map<string,double> > freqs = pssm.getFrequencies(refName,start,end);
    MSLOUT.stream() << "Get sequence    of "<<refName<<" "<<start<<" "<<end<<endl;
    string seq = pssm.getSequence(refName,start,end);

    MSLOUT.stream() << "Got sequence       "<<seq<<endl;
    // ******   CRAZY FORMATTING CODE.... THIS SUCKS ***** //

    // For each position
    int largestVariation = 0;
    for (uint i = 0;i < freqs.size();i++){
      if (freqs[i].size() > largestVariation){
	largestVariation = freqs[i].size();
      }
    }

    MSLOUT.stream() << "Make output largest variation: "<<largestVariation<<endl;
    int resNum = start;

    vector<string> rows;
    rows.resize(21,"");
    for (uint i = 0;i < freqs.size();i++){


      priority_queue<aaDat> orderedMap = orderMap(freqs[i]);
      int blanks = largestVariation - orderedMap.size();
      for (uint v = 0; v < blanks;v++){
	if (v <= blanks) {
	  rows[v] += MslTools::stringf("%1s %6.2f\t", "-", 00.00);
	  continue;
	}
      }

      int v = blanks;
      while (orderedMap.size() > 0){
	  aaDat data = orderedMap.top();
	  orderedMap.pop();
	  if (data.aa == "entropy" || data.aa == "mostfreq") continue;
	  rows[v++] += MslTools::stringf("%1s %6.2f\t", data.aa.c_str(), data.freq*100);
	  //cout << "ROW IS: "<<MslTools::stringf("%1s %8.2f ", data.aa.c_str(), data.freq*100)<<endl;
      }
      
       
      // Add residue number at very end
      rows[20] += MslTools::stringf("=%c-%-4d=\t",seq[i],resNum++);
      
    } // FOR freqs.size()

    MSLOUT.stream() << "Make output2"<<endl;
    for (uint r = 0; r < rows.size();r++){
      if (rows[r] == "") continue;
      if (r == 20){
	fprintf(stdout,"\n");
      }
      fprintf(stdout, "%s\n",rows[r].c_str());
    }

  } // IF opt.seq

  MSLOUT.stream() << "Done."<<endl;
}