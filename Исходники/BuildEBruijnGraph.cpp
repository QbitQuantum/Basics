int main(int argc, char* argv[]) {
  
  CommandLineParser clp;
  string readsFileName;
  string alignmentsFileName;
  string outputFileName;
  float minMergeIdentity = 0.70;
  clp.RegisterStringOption("reads", &readsFileName, "Reads used for alignments.");
  clp.RegisterStringOption("alignments", &alignmentsFileName, "SAM formatted alignments.");
  clp.RegisterIntOption("k", &vertexSize, "Minimum match length", CommandLineParser::PositiveInteger);
  clp.RegisterStringOption("outfile", &outputFileName, "Alignment output.");
  clp.RegisterPreviousFlagsAsHidden();
  clp.RegisterFlagOption("v", &verbose, "");
  clp.RegisterFloatOption("minMergeIdentity", 
                          &minMergeIdentity, 
                          "Minimum identity to merge paths.", CommandLineParser::PositiveFloat);
  
  clp.ParseCommandLine(argc, argv);

  if (minMergeIdentity < 0 or minMergeIdentity > 1) {
    cout << "ERROR. minMergeIdentity must be between 0 and 1" << endl;
    exit(1);
  }
  
  vector<FASTASequence> reads;

  FASTAReader fastaReader;
  fastaReader.Initialize(readsFileName);
  fastaReader.ReadAllSequences(reads);

  //
  // It is necessary to go from read title to index in the list of reads. 
  //
  map<string, int> readNameToIndex;
  BuildReadNameToIndexMap(reads, readNameToIndex);

  ReadWordMatchVector readWordMatches;
  InitializeFromReads(reads, readWordMatches);
  
  //
  // Get ready to read in the alignments.
  //
  SAMReader<SAMFullReferenceSequence, SAMReadGroup, SAMPosAlignment> samReader;
  samReader.Initialize(alignmentsFileName);
  AlignmentSet<SAMFullReferenceSequence, SAMReadGroup, SAMPosAlignment> alignmentSet;
  samReader.ReadHeader(alignmentSet);
  
  SAMAlignment samAlignment;
  AlignmentCandidate<> alignment;
  int numAlignedBases = 0;
  int alignmentIndex = 0;
  while ( samReader.GetNextAlignment( samAlignment ) ) {
    vector<AlignmentCandidate<> > alignments;
    SAMAlignmentsToCandidates(samAlignment,
                              reads,
                              readNameToIndex,
                              alignments, false, true);

    int i;
    ++alignmentIndex;
    int a;
    for (a = 0; a < alignments.size();a++) {
      if (alignments[a].qName != alignments[a].tName) {
        MarkMatches(alignments[a], readNameToIndex, vertexSize, readWordMatches);
      }
    }
    if (alignmentIndex % 1000 == 0) {
      cout << alignmentIndex << endl;
    }
  }


  int numMatches = 0;
  int parentIndex = 1;
  int r;
  for (r = 0; r < readWordMatches.size(); r++) {
    readWordMatches[r].CreateParents();
    numMatches += readWordMatches[r].pos.size();
  }

  vector<int> parentIndices;
  parentIndices.resize(2*numMatches + 1);
  fill(parentIndices.begin(), parentIndices.end(), 0);
  //
  // Start indexing off at 1 so that 0 does not need to be treated in
  // a special case.
  //
  int curParentIndex = 1;
  cout << "There are " << numMatches << " matches." << endl;

  samReader.Close();
  samReader.Initialize(alignmentsFileName);
  AlignmentSet<SAMFullReferenceSequence, SAMReadGroup, SAMPosAlignment> alignmentSet2;
  samReader.ReadHeader(alignmentSet2);
  
  numAlignedBases = 0;
  alignmentIndex = 0;
  while ( samReader.GetNextAlignment( samAlignment ) ) {
    vector<AlignmentCandidate<> > alignments;
    SAMAlignmentsToCandidates(samAlignment,
                              reads,
                              readNameToIndex,
                              alignments, false, true);

    int i;
    ++alignmentIndex;
    int a;
    for (a = 0; a < alignments.size();a++) {
      if (alignments[a].qName != alignments[a].tName) {
        JoinVertices(alignments[a], vertexSize, readNameToIndex, readWordMatches, curParentIndex, parentIndices);
      }
    }
    if (alignmentIndex % 1000 == 0) {
      cout << alignmentIndex << endl;
    }
  }
  vector<int> parentCounts;
  parentCounts.resize(parentIndices.size());
  fill(parentCounts.begin(), parentCounts.end(), 0);
  int p;
  PromoteAll(parentIndices);
  int i;
  for (r = 0; r < readWordMatches.size(); r++) {
    for (i = 0; i < readWordMatches[r].parents.size(); i++) {
      readWordMatches[r].parents[i] = parentIndices[readWordMatches[r].parents[i]];
      parentCounts[readWordMatches[r].parents[i]]++;
    }
  }
  /*
  for (i = 0; i < readWordMatches.size(); i++) {
    readWordMatches[i].PrintPos(cout);
    readWordMatches[i].PrintParents(cout);
  }
  */

  map<int,int> hist;
  int numParents = 0;
  for (i = 1; i < parentCounts.size() && parentIndices[i] != 0; i++) {
    if (parentCounts[i] != 0) {
      ++numParents;
    }
    if (hist.find(parentCounts[i]) == hist.end()) {
      hist[parentCounts[i]] = 1;
    }
    else {
      hist[parentCounts[i]]++;
    }
  }

  map<int,int>::iterator histIt;
  cout << " freq count" << endl;
  for(histIt = hist.begin(); histIt != hist.end(); ++histIt) {
    cout << (*histIt).second << " " << (*histIt).first << endl;
  }

  MatchVertexList vertices;
  vertices.resize(numParents);
  cout << "there are " << numParents << " parents. " << endl;
  
}