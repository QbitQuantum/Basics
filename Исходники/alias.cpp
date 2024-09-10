void AliasData::DeleteExpandedAtoms(OBMol& mol)
{
  //The atom that carries the AliasData object remains as an Xx atom with no charge;
  //the others are deleted. All the attached hydrogens are also deleted.
  for(unsigned i=0;i<_expandedatoms.size();++i)
  {
    OBAtom* at = mol.GetAtomById(_expandedatoms[i]);
    if(!at)
      continue;
    mol.DeleteHydrogens(at);
    if(at->HasData(AliasDataType))
    {
      at->SetAtomicNum(0);
      at->SetFormalCharge(0);
      at->SetSpinMultiplicity(0);
    }
    else
      mol.DeleteAtom(at);
  }
  _expandedatoms.clear();
}