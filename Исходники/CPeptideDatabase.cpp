bool CPeptideDatabase::readMascot(char* mascotFile, char* dataFile){
  MSReader r;
  MascotParser p;
  Spectrum s;
  MascotLite m;

  int i;
  int percent=0;

  p.clear();
  p.readText(mascotFile);

  if(p.isDistiller()){
    cout << mascotFile << "\t" << p.size() << " peptides from Distiller, no need for RT lookup." << endl;
  } else if(p.hasRTime()){
    cout << mascotFile << "\t" << p.size() << " peptides have RT already, no need for lookup." << endl;
  } else {
    cout << mascotFile << "\tLooking up retention times for " << p.size() << " Mascot peptides..." << endl;
    cout << percent;
    r.readFile(dataFile,s);
  }

  for(i=0;i<p.size();i++){
    if(p.isDistiller()||p.hasRTime()){ 
      m.rTime=p[i].rTime;
    } else {
      if( (int)i*100/p.size() > percent){
        percent=(int)i*100/p.size();
        cout << "\b\b\b" << percent;
      }

      r.readFile(NULL,s,p[i].scanNum);
      if(s.getScanNumber()==0){
        cout << "Scan not found. Please check that correct data file is used. Stopping Mascot parsing." << endl;
        return false;
      }
      m.rTime=s.getRTime();
    }
    m.charge=p[i].charge;
    m.fileID=fileID;
    m.monoMass=p[i].zeroMass;
    m.scanNum=p[i].scanNum;
    strcpy(m.peptide,p[i].sequence_Long);
    strcpy(m.protein,p[i].gene);
    mascot.push_back(m);
  }
  cout << "  Done!" << endl;

  fileID++;

  return true;
}