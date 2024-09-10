void testSFIssue1653802() {
  BOOST_LOG(rdErrorLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdErrorLog) << "    Testing SFIssue1653802." << std::endl;

  RWMol *mol;
  int needMore;
  ForceFields::ForceField *field;

  std::string pathName = getenv("RDBASE");
  pathName += "/Code/GraphMol/ForceFieldHelpers/MMFF/test_data";

  mol = MolFileToMol(pathName + "/cyclobutadiene.mol", false);
  TEST_ASSERT(mol);
  MolOps::sanitizeMol(*mol);
  MMFF::MMFFMolProperties *mmffMolProperties =
      new MMFF::MMFFMolProperties(*mol);
  TEST_ASSERT(mmffMolProperties);

  boost::shared_array<boost::uint8_t> nbrMat;
  field = new ForceFields::ForceField();
  MMFF::Tools::addBonds(*mol, mmffMolProperties, field);
  TEST_ASSERT(field->contribs().size() == 8);

  nbrMat = MMFF::Tools::buildNeighborMatrix(*mol);
  MMFF::Tools::addAngles(*mol, mmffMolProperties, field);
  TEST_ASSERT(field->contribs().size() == 20);
  MMFF::Tools::addTorsions(*mol, mmffMolProperties, field);
  // std::cout << field->contribs().size() << std::endl;
  TEST_ASSERT(field->contribs().size() == 36);
  MMFF::Tools::addVdW(*mol, 0, mmffMolProperties, field, nbrMat);
  delete field;

  field = MMFF::constructForceField(*mol);
  field->initialize();
  needMore = field->minimize(200, 1.0e-6, 1.0e-3);
  TEST_ASSERT(!needMore);

  delete mol;
  delete field;
  delete mmffMolProperties;
  BOOST_LOG(rdErrorLog) << "  done" << std::endl;
}