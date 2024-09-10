void testCrippenO3AConstraints() {
  ROMol *m = SmilesToMol("n1ccc(cc1)-c1ccccc1");
  TEST_ASSERT(m);
  ROMol *m1 = MolOps::addHs(*m);
  delete m;
  TEST_ASSERT(m1);
  DGeomHelpers::EmbedMolecule(*m1);
  MMFF::sanitizeMMFFMol((RWMol &)(*m1));
  MMFF::MMFFMolProperties mp(*m1);
  TEST_ASSERT(mp.isValid());
  ForceFields::ForceField *field = MMFF::constructForceField(*m1, &mp);
  field->initialize();
  field->minimize();
  RWMol *patt = SmartsToMol("nccc-cccc");
  MatchVectType matchVect;
  TEST_ASSERT(SubstructMatch(*m1, (ROMol &)*patt, matchVect));
  unsigned int nIdx = matchVect[0].second;
  unsigned int cIdx = matchVect[matchVect.size() - 1].second;
  MolTransforms::setDihedralDeg(m1->getConformer(), matchVect[2].second,
    matchVect[3].second, matchVect[4].second, matchVect[5].second, 0.0);
  ROMol m2(*m1);
  MolAlign::randomTransform(m2);
  ROMol m3(m2);
  unsigned int prbNAtoms = m2.getNumAtoms();
  std::vector<double> prbLogpContribs(prbNAtoms);
  std::vector<double> prbMRContribs(prbNAtoms);
  std::vector<unsigned int> prbAtomTypes(prbNAtoms);
  std::vector<std::string> prbAtomTypeLabels(prbNAtoms);
  Descriptors::getCrippenAtomContribs(m2, prbLogpContribs,
    prbMRContribs, true, &prbAtomTypes, &prbAtomTypeLabels);
  MolAlign::O3A *o3a = new MolAlign::O3A(m2, *m1,
    &prbLogpContribs, &prbLogpContribs, MolAlign::O3A::CRIPPEN);
  TEST_ASSERT(o3a);
  o3a->align();
  delete o3a;
  double d = (m2.getConformer().getAtomPos(cIdx)
    - m1->getConformer().getAtomPos(cIdx)).length();
  TEST_ASSERT(feq(d, 0.0, 1));
  MatchVectType constraintMap;
  constraintMap.push_back(std::make_pair(cIdx, nIdx));
  o3a = new MolAlign::O3A(m3, *m1, &prbLogpContribs, &prbLogpContribs,
    MolAlign::O3A::CRIPPEN, -1, -1, false, 50, 0, &constraintMap);
  TEST_ASSERT(o3a);
  o3a->align();
  delete o3a;
  d = (m3.getConformer().getAtomPos(cIdx)
    - m1->getConformer().getAtomPos(cIdx)).length();
  TEST_ASSERT(feq(d, 7.0, 1.0));
  delete m1;
}