  bool FreeFormFractionalFormat::WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;

    //Define some references so we can use the old parameter names
    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    char buffer[BUFF_SIZE];
    OBUnitCell *uc = NULL;

    ofs << mol.GetTitle() << endl;

    if (!mol.HasData(OBGenericDataType::UnitCell))
      ofs << "   1.00000   1.00000   1.00000  90.00000  90.00000  90.00000\n";
    else
      {
        uc = (OBUnitCell*)mol.GetData(OBGenericDataType::UnitCell);
        snprintf(buffer, BUFF_SIZE,
                 "%10.5f%10.5f%10.5f%10.5f%10.5f%10.5f",
                 uc->GetA(), uc->GetB(), uc->GetC(),
                 uc->GetAlpha() , uc->GetBeta(), uc->GetGamma());
        ofs << buffer << "\n";
      }

    vector3 v;
    FOR_ATOMS_OF_MOL(atom, mol)
      {
        v = atom->GetVector();
        if (uc != NULL)
          v = uc->CartesianToFractional(v);

        snprintf(buffer, BUFF_SIZE, "%s %10.5f%10.5f%10.5f",
                 etab.GetSymbol(atom->GetAtomicNum()),
                 v.x(),
                 v.y(),
                 v.z());
        ofs << buffer << endl;
      }