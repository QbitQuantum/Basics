void testIdsDeleteAtom()
{
  OBMol mol;
  for (int i = 0; i < 10; ++i)
    mol.NewAtom();

  OB_REQUIRE( mol.GetAtomById(3) );
  OB_REQUIRE( mol.GetAtomById(4) );
  OB_REQUIRE( mol.GetAtomById(5) );

  mol.DeleteAtom(mol.GetAtomById(4));

  OB_REQUIRE( mol.GetAtomById(3) );
  OB_REQUIRE( mol.GetAtomById(3)->GetId() == 3 );
  OB_REQUIRE( !mol.GetAtomById(4) );
  OB_REQUIRE( mol.GetAtomById(5) );
  OB_REQUIRE( mol.GetAtomById(5)->GetId() == 5 );
}