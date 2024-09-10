TEST(CjsonTest, atoms)
{
  CjsonFormat cjson;
  Molecule molecule;
  bool success = cjson.readFile(std::string(AVOGADRO_DATA) +
                                "/data/ethane.cjson", molecule);
  EXPECT_TRUE(success);
  EXPECT_EQ(cjson.error(), "");
  EXPECT_EQ(molecule.data("name").toString(), "Ethane");
  EXPECT_EQ(molecule.atomCount(), static_cast<size_t>(8));
  Atom atom = molecule.atom(0);
  EXPECT_EQ(atom.atomicNumber(), static_cast<unsigned char>(1));
  atom = molecule.atom(1);
  EXPECT_EQ(atom.atomicNumber(), static_cast<unsigned char>(6));
  EXPECT_EQ(atom.position3d().x(),  0.751621);
  EXPECT_EQ(atom.position3d().y(), -0.022441);
  EXPECT_EQ(atom.position3d().z(), -0.020839);

  atom = molecule.atom(7);
  EXPECT_EQ(atom.atomicNumber(), static_cast<unsigned char>(1));
  EXPECT_EQ(atom.position3d().x(), -1.184988);
  EXPECT_EQ(atom.position3d().y(),  0.004424);
  EXPECT_EQ(atom.position3d().z(), -0.987522);
}