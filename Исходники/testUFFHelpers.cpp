void testUFFBuilder2(){
  BOOST_LOG(rdErrorLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdErrorLog) << "    Testing UFF builder+minimization." << std::endl;

  RWMol *mol;
  std::string key;
  int needMore;

  ForceFields::ForceField *field;

  std::string pathName=getenv("RDBASE");
  pathName += "/Code/GraphMol/ForceFieldHelpers/UFF/test_data";
  mol = MolFileToMol(pathName+"/small1.mol",false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);

  field=UFF::constructForceField(*mol);
  TEST_ASSERT(field);
  field->initialize();
  needMore = field->minimize();
  TEST_ASSERT(!needMore);
  //std::cout << MolToMolBlock(mol);
  delete mol;
  delete field;

  mol = MolFileToMol(pathName+"/small2.mol",false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);

  field=UFF::constructForceField(*mol);
  TEST_ASSERT(field);
  field->initialize();
  needMore = field->minimize(150);
  TEST_ASSERT(!needMore);
  //std::cout << MolToMolBlock(mol);
  delete mol;
  delete field;

  mol = MolFileToMol(pathName+"/benzene.mol",false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);

  field=UFF::constructForceField(*mol);
  TEST_ASSERT(field);
  field->initialize();
  needMore = field->minimize();
  TEST_ASSERT(!needMore);
  //std::cout << MolToMolBlock(mol);
  delete mol;
  delete field;
  
  mol = MolFileToMol(pathName+"/toluene.mol",false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);

  field=UFF::constructForceField(*mol);
  TEST_ASSERT(field);
  field->initialize();
  needMore = field->minimize();
  TEST_ASSERT(!needMore);
  //std::cout << MolToMolBlock(mol);
  delete mol;
  delete field;

  mol = MolFileToMol(pathName+"/complex1.mol",false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);

  field=UFF::constructForceField(*mol);
  TEST_ASSERT(field);
  field->initialize();
  needMore = field->minimize();
  TEST_ASSERT(!needMore);
  //std::cout << MolToMolBlock(mol);
  delete mol;
  delete field;

  

  BOOST_LOG(rdErrorLog) << "  done" << std::endl;
}