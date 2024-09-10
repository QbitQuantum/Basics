  bool CacaoFormat::WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;

    //Define some references so we can use the old parameter names
    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    OBAtom *atom;
    char buffer[BUFF_SIZE];
    vector<OBAtom*>::iterator i;

    snprintf(buffer, BUFF_SIZE, "%s\n",mol.GetTitle());
    ofs << buffer;
    snprintf(buffer, BUFF_SIZE, "%3d   DIST  0  0  0\n",mol.NumAtoms());
    ofs << buffer;

    if (!mol.HasData(OBGenericDataType::UnitCell))
      ofs << "CELL 1.,1.,1.,90.,90.,90.\n";
    else
      {
        OBUnitCell *uc = (OBUnitCell*)mol.GetData(OBGenericDataType::UnitCell);
        snprintf(buffer, BUFF_SIZE, "CELL %f,%f,%f,%f,%f,%f\n",
                 uc->GetA(), uc->GetB(), uc->GetC(),
                 uc->GetAlpha(), uc->GetBeta(), uc->GetGamma());
        ofs << buffer;
      }

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        snprintf(buffer,BUFF_SIZE,"%2s %7.4f, %7.4f, %7.4f\n",
                 etab.GetSymbol(atom->GetAtomicNum()),
                 atom->x(),
                 atom->y(),
                 atom->z());
        ofs << buffer;
      }

    return(true);
  }