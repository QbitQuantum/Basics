/*
bool FeaturePartImportStep::MustExecute(void)
{
	Base::Console().Log("PartBoxFeature::MustExecute()\n");
	return false;
}
*/
Standard_Integer FeatureImportIges::Execute(void)
{
	Base::Console().Log("FeaturePartImportIges::Execute()\n");

/*  cout << GetFloatProperty("x") << endl;
  cout << GetFloatProperty("y") << endl;
  cout << GetFloatProperty("z") << endl;
  cout << GetFloatProperty("l") << endl;
  cout << GetFloatProperty("h") << endl;
  cout << GetFloatProperty("w") << endl;*/

  try{

    IGESControl_Reader aReader;
    TopoDS_Shape aShape;

    std::string FileName = getPropertyString("FileName");

    int i=_open(FileName.c_str(),O_RDONLY);
	  if( i != -1)
	  {
		  _close(i);
	  }else{
      Base::Console().Log("FeaturePartImportIges::Execute() not able to open %s!\n",FileName.c_str());
		  return 1;
	  }

    // just do show the wait cursor when the Gui is up
    Base::Sequencer().start("Load IGES", 1);
    Base::Sequencer().next();

    // read iges-file
    if (aReader.ReadFile((const Standard_CString)FileName.c_str()) != IFSelect_RetDone)
      throw Base::Exception("IGES read failed (load file)");
  
    // check iges-file (memory)
    //if (!aReader.Check(Standard_True))
    //  Base::Console().Warning( "IGES model contains errors! try loading anyway....\n" );
  
    // make brep
    aReader.TransferRoots();
    // one shape, who contain's all subshapes
    aShape = aReader.OneShape();

	  setShape(aShape);
    Base::Sequencer().stop();
  }
  catch(...){
    Base::Sequencer().halt();
    Base::Console().Error("FeaturePartImportIges::Execute() failed!");
    return 1;
  }

  return 0;
}