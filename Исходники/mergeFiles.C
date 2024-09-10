void WriteMergeObjects( TFile *target ) {
  cout << "Writing the merged data." << endl;

  TIterator *nextobj = MergeObjects.MakeIterator();
  TObjString *pathname_obj;
  while( (pathname_obj = (TObjString *)nextobj->Next()) ) {
    TString path,name;
    SplitPathName(pathname_obj->String(),&path,&name);

    TObject *obj = MergeObjects.GetValue(pathname_obj);
    target->cd(path);

    obj->Write( name );

    delete obj;
  }
  MergeObjects.Clear();

  target->Write();

  // Temporarily let multiple root files remain if > 2GB
  // Prevent Target_1.root Target_2.root, ... from happening.
  //  long long max_tree_size = 200000000000LL; // 200 GB
  //  if(TTree::GetMaxTreeSize() < max_tree_size ) {
  //    TTree::SetMaxTreeSize(max_tree_size);
  //  }

  nextobj = MergeChains.MakeIterator();
  TObjString *pathname_obj;
  while( (pathname_obj = (TObjString *)nextobj->Next()) ) {
    TString path,name;
    SplitPathName(pathname_obj->String(),&path,&name);

    TChain *ch = (TChain *)MergeChains.GetValue(pathname_obj);
    target->cd(path);
    ch->Merge(target,0,"KEEP");

    delete ch;

	// in case of multiple objects with same pathname, must remove
	// this one from the list so we don't get the same (deleted)
	// one next time we look up the same name
	MergeChains.Remove(pathname_obj);
  }
  MergeChains.Clear();

  InitializedMergeObjects = false;
}