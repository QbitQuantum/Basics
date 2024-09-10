void actionMakeReps()
{
  ldieif(argvc<3,"syntax: "+efile(argv[0]).basename()+" -makereps <alignment> <otu>");
  estrhashof<INDTYPE> seqind;

  estrarray uarr;

  cout << "# loading seqs file: " << argv[1] << endl;
  load_seqs_compressed(argv[1],arr,seqind,seqlen);
  load_seqs(argv[1],uarr);

  earray<ebasicarray<INDTYPE> > otus;

  efile f;
  estr line;
  estrarray parts;
  f.open(argv[2],"r");
  while (!f.eof()){
    f.readln(line);
    if (line.len()==0 || line[0]=='#') continue;
    if (line[0]=='>'){
      otus.add(ebasicarray<INDTYPE>());
      continue;
    }
    ldieif(otus.size()==0,"first entry not start of OTU or missing '>'");
    parts=line.explode("\t");
    ldieif(parts.size()==0,"array empty: "+line);
    ldieif(!seqind.exists(parts[0]),"sequence not found: "+parts[0]);
    otus[otus.size()-1].add(seqind[parts[0]]);
  }

  cerr << endl;

  ebasicarray<INDTYPE> tuniqind;
  earray<ebasicarray<INDTYPE> > dupslist;
  finduniq(tuniqind,dupslist);

  eintarray uniqmask;
  uniqmask.init(arr.size(),0);
  for (long i=0; i<tuniqind.size(); ++i)
    uniqmask[tuniqind[i]]=dupslist[i].size();


//  ebasicarray<INDTYPE> uniqind;
  taskman.createThread(nthreads);

  ebasicarray<INDTYPE> uniqind;
  const float t=0.0;
  efloatarray avgdist;
  for (long j=0; j<otus.size(); ++j){
//    cout << "# computing distances for otu "<< j << " size: " << otus[j].size() <<  endl;
    if (otus[j].size()==1){
      cout << ">OTU" << j << " " << arr.keys(otus[j][0]) << " avg_id=1.0 otu_size=1" << endl;
      cout << uarr.values(otus[j][0]) << endl;
      continue;
    }
    uniqind.clear();
    for (long l=0; l<otus[j].size(); ++l){
      if (uniqmask[otus[j][l]]!=0)
        uniqind.add(otus[j][l]);
    }
//    uniqind=otus[j];
    ldieif(uniqind.size()==0,"empty OTU");

    if (uniqind.size()==1){
      cout << ">OTU" << j << " " << arr.keys(uniqind[0]) << " avg_id=1.0 otu_size=" << otus[j].size() << endl;
      cout << uarr.values(uniqind[0]) << endl;
      continue;
    }
    avgdist.clear();
    avgdist.init(arr.size(),0.0);
    dists.clear();
  
    partsTotal=10000;
    if (partsTotal>(uniqind.size()-1l)*uniqind.size()/20l) partsTotal=(uniqind.size()-1l)*uniqind.size()/20l; // make fewer tasks if to few calculations per task
    if (partsTotal<=0) partsTotal=1;
    
    taskman.clear();
    for (long i=0; i<partsTotal; ++i)
      taskman.addTask(dfunc.value().calcfunc,evararray(mutex,uniqind,arr,dists,(const int&)seqlen,(const long int&)i,(const long int&)partsTotal,(const float&)t,(const int&)winlen));
    taskman.wait();
    for (long i=0; i<dists.size(); ++i){
      eseqdist& d(dists[i]);
      avgdist[d.x]+=d.dist*uniqmask[d.y];
      avgdist[d.y]+=d.dist*uniqmask[d.x];
//      cout << "# "<< arr.keys(d.x) << " " << arr.keys(d.y) << " " << d.dist << " " << uniqmask[d.x] << " " << uniqmask[d.y] << endl;
    }
    long k=uniqind[0];
    for (long i=0; i<uniqind.size(); ++i){
      long ti=uniqind[i];
      avgdist[ti]+=uniqmask[ti]-1;
      if (avgdist[k]<avgdist[ti]) {
//        cout << "# " << arr.keys(ti) << " " << ti << " " << uniqmask[ti] << " " << avgdist[ti] << " " << counts[ti] << endl;
        k=ti;
      }
    }
//    cout << "OTU" << j << " " << otus[j].size() << " " << arr.keys(k) << " " << avgdist[k]/(otus[j].size()-1) << " " << dists.size() << endl;
    cout << ">OTU" << j << " " << arr.keys(k) << " avg_id=" << avgdist[k]/(otus[j].size()-1) << " otu_size=" << otus[j].size() << endl;
    cout << uarr.values(k) << endl;
  }
  cerr << endl;

  exit(0);
}