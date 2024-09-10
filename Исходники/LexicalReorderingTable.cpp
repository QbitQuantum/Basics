bool LexicalReorderingTableTree::Create(std::istream& inFile,
                                        const std::string& outFileName)
{
  std::string line;
  //TRACE_ERR("Entering Create...\n");
  std::string
  ofn(outFileName+".binlexr.srctree"),
      oft(outFileName+".binlexr.tgtdata"),
      ofi(outFileName+".binlexr.idx"),
      ofsv(outFileName+".binlexr.voc0"),
      oftv(outFileName+".binlexr.voc1");


  FILE *os = fOpen(ofn.c_str(),"wb");
  FILE *ot = fOpen(oft.c_str(),"wb");

  //TRACE_ERR("opend files....\n");

  typedef PrefixTreeSA<LabelId,OFF_T> PSA;
  PSA *psa = new PSA;
  PSA::setDefault(InvalidOffT);
  WordVoc* voc[3];

  LabelId currFirstWord = InvalidLabelId;
  IPhrase currKey;

  Candidates         cands;
  std::vector<OFF_T> vo;
  size_t lnc = 0;
  size_t numTokens    = 0;
  size_t numKeyTokens = 0;
  while(getline(inFile, line)) {
    ++lnc;
    if(0 == lnc % 10000) {
      TRACE_ERR(".");
    }
    IPhrase key;
    Scores   score;

    std::vector<std::string> tokens = TokenizeMultiCharSeparator(line, "|||");
    std::string w;
    if(1 == lnc) {
      //do some init stuff in the first line
      numTokens = tokens.size();
      if(tokens.size() == 2) { //f ||| score
        numKeyTokens = 1;
        voc[0] = new WordVoc();
        voc[1] = 0;
      } else if(3 == tokens.size() || 4 == tokens.size()) { //either f ||| e ||| score or f ||| e ||| c ||| score
        numKeyTokens = 2;
        voc[0] = new WordVoc(); //f voc
        voc[1] = new WordVoc(); //e voc
        voc[2] = voc[1];        //c & e share voc
      }
    } else {
      //sanity check ALL lines must have same number of tokens
      CHECK(numTokens == tokens.size());
    }
    size_t phrase = 0;
    for(; phrase < numKeyTokens; ++phrase) {
      //conditioned on more than just f... need |||
      if(phrase >=1) {
        key.push_back(PrefixTreeMap::MagicWord);
      }
      std::istringstream is(tokens[phrase]);
      while(is >> w) {
        key.push_back(voc[phrase]->add(w));
      }
    }
    //collect all non key phrases, i.e. c
    std::vector<IPhrase> tgt_phrases;
    tgt_phrases.resize(numTokens - numKeyTokens - 1);
    for(size_t j = 0; j < tgt_phrases.size(); ++j, ++phrase) {
      std::istringstream is(tokens[numKeyTokens + j]);
      while(is >> w) {
        tgt_phrases[j].push_back(voc[phrase]->add(w));
      }
    }
    //last token is score
    std::istringstream is(tokens[numTokens-1]);
    while(is >> w) {
      score.push_back(atof(w.c_str()));
    }
    //transform score now...
    std::transform(score.begin(),score.end(),score.begin(),TransformScore);
    std::transform(score.begin(),score.end(),score.begin(),FloorScore);
    std::vector<Scores> scores;
    scores.push_back(score);

    if(key.empty()) {
      TRACE_ERR("WARNING: empty source phrase in line '"<<line<<"'\n");
      continue;
    }
    //first time inits
    if(currFirstWord == InvalidLabelId) {
      currFirstWord = key[0];
    }
    if(currKey.empty()) {
      currKey = key;
      //insert key into tree
      CHECK(psa);
      PSA::Data& d = psa->insert(key);
      if(d == InvalidOffT) {
        d = fTell(ot);
      } else {
        TRACE_ERR("ERROR: source phrase already inserted (A)!\nline(" << lnc << "): '" << line << "\n");
        return false;
      }
    }
    if(currKey != key) {
      //ok new key
      currKey = key;
      //a) write cands for old key
      cands.writeBin(ot);
      cands.clear();
      //b) check if we need to move on to new tree root
      if(key[0] != currFirstWord) {
        // write key prefix tree to file and clear
        PTF pf;
        if(currFirstWord >= vo.size()) {
          vo.resize(currFirstWord+1,InvalidOffT);
        }
        vo[currFirstWord] = fTell(os);
        pf.create(*psa, os);
        // clear
        delete psa;
        psa = new PSA;
        currFirstWord = key[0];
      }
      //c) insert key into tree
      CHECK(psa);
      PSA::Data& d = psa->insert(key);
      if(d == InvalidOffT) {
        d = fTell(ot);
      } else {
        TRACE_ERR("ERROR: source phrase already inserted (A)!\nline(" << lnc << "): '" << line << "\n");
        return false;
      }
    }
    cands.push_back(GenericCandidate(tgt_phrases, scores));
  }
  if (lnc == 0) {
    TRACE_ERR("ERROR: empty lexicalised reordering file\n" << std::endl);
    return false;
  }
  //flush remainders
  cands.writeBin(ot);
  cands.clear();
  //process last currFirstWord
  PTF pf;
  if(currFirstWord >= vo.size()) {
    vo.resize(currFirstWord+1,InvalidOffT);
  }
  vo[currFirstWord] = fTell(os);
  pf.create(*psa,os);
  delete psa;
  psa=0;

  fClose(os);
  fClose(ot);
  /*
  std::vector<size_t> inv;
  for(size_t i = 0; i < vo.size(); ++i){
    if(vo[i] == InvalidOffT){
      inv.push_back(i);
    }
  }
  if(inv.size()) {
    TRACE_ERR("WARNING: there are src voc entries with no phrase "
        "translation: count "<<inv.size()<<"\n"
        "There exists phrase translations for "<<vo.size()-inv.size()
        <<" entries\n");
  }
  */
  FILE *oi = fOpen(ofi.c_str(),"wb");
  fWriteVector(oi,vo);
  fClose(oi);

  if(voc[0]) {
    voc[0]->Write(ofsv);
    delete voc[0];
  }
  if(voc[1]) {
    voc[1]->Write(oftv);
    delete voc[1];
  }
  return true;
}