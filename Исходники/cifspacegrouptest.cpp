void testDecayToP1()
{
  // See https://github.com/openbabel/openbabel/pull/261
  OBConversion conv;
  OBMol mol;
  conv.SetInFormat("cif");
  conv.ReadFile(&mol, GetFilename("test03.cif"));
  OBUnitCell* pUC = (OBUnitCell*)mol.GetData(OBGenericDataType::UnitCell);
  const SpaceGroup* pSG = pUC->GetSpaceGroup();
  SpaceGroup* sg = new SpaceGroup(*pSG);
  pSG = SpaceGroup::Find(sg);
  OB_ASSERT( pSG != NULL );

  // Check also for errors and warnings
  string summary = obErrorLog.GetMessageSummary();
  OB_ASSERT( summary.find("2 warnings") != string::npos);

  OB_ASSERT( pSG->GetId() == 1 );
}