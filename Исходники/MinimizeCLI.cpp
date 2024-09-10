void runMol(ROMol *mol,int checkEvery=10,bool verbose=true){
  ForceFields::ForceField *field;

  std::cout << MolToMolBlock(*mol) << "$$$$" << std::endl;

  try{
    field=UFF::constructForceField(*mol,2.5);
  } catch (...) {
    field=0;
  }
  if(field){
    field->initialize();
    int needMore=1;
    int nPasses=0;
    while(needMore){
#if 1
      needMore = field->minimize(checkEvery);
      if(verbose) std::cerr << "\t" << ++nPasses << std::endl;
#else
      needMore = field->minimize(1);
      std::cout << MolToMolBlock(mol) << "$$$$" << std::endl;
#endif
    }
    std::cout << MolToMolBlock(*mol) << "$$$$" << std::endl;
    delete field;
  } else {
    std::cerr << "failed";
  }
  
}