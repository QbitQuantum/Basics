  bool BGFFormat::WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;

    //Define some references so we can use the old parameter names
    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    vector<OBAtom*>::iterator i;
    int max_val;
    OBAtom *atom;
    char buffer[BUFF_SIZE];
    char elmnt_typ[8], dreid_typ[8], atm_sym[16], max_val_str[8];

    mol.Kekulize();

    ofs << "BIOGRF 200\n";
    snprintf(buffer, BUFF_SIZE, "DESCRP %s\n",mol.GetTitle());
    ofs << buffer;
    snprintf(buffer, BUFF_SIZE, "REMARK BGF file created by Open Babel %s\n",BABEL_VERSION);
    ofs << "FORCEFIELD DREIDING  \n";

    // write unit cell if available
    if (mol.HasData(OBGenericDataType::UnitCell))
      {
        OBUnitCell *uc = (OBUnitCell*)mol.GetData(OBGenericDataType::UnitCell);
        // e.g. CRYSTX    49.30287   49.23010   25.45631   90.00008   89.99995   57.10041
        snprintf(buffer, BUFF_SIZE,
                 "CRYSTX%12.5f%12.5f%12.5f%12.5f%12.5f%12.5f",
                 uc->GetA(), uc->GetB(), uc->GetC(),
                 uc->GetAlpha() , uc->GetBeta(), uc->GetGamma());
        ofs << buffer << "\n";
      }

    ofs << "FORMAT ATOM   (a6,1x,i5,1x,a5,1x,a3,1x,a1,1x,a5,3f10.5,1x,a5,i3,i2,1x,f8.5)\n";

    ttab.SetFromType("INT");

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        strncpy(elmnt_typ,etab.GetSymbol(atom->GetAtomicNum()), 7); // make sure to null-terminate
        elmnt_typ[sizeof(elmnt_typ) - 1] = '0';
        ToUpper(elmnt_typ);

        ttab.SetToType("DRE");
        ttab.Translate(dreid_typ,atom->GetType());
        ttab.SetToType("HAD");
        ttab.Translate(max_val_str,atom->GetType());
        max_val = atoi(max_val_str);
        if (max_val == 0)
          max_val = 1;
        snprintf(atm_sym,16,"%s%d",elmnt_typ,atom->GetIdx());
        snprintf(buffer,BUFF_SIZE,"%6s %5d %-5s %3s %1s %5s%10.5f%10.5f%10.5f %-5s%3d%2d %8.5f\n",
                "HETATM",
                atom->GetIdx(),
                atm_sym,
                "RES",
                "A",
                "444",
                atom->GetX(),
                atom->GetY(),
                atom->GetZ(),
                dreid_typ,
                max_val,
                0,
                atom->GetPartialCharge());
        ofs << buffer;
      }
    ofs<< "FORMAT CONECT (a6,12i6)\n\n";

    OBAtom *nbr;
    vector<OBBond*>::iterator j;
    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      if (atom->GetValence())
        {
          snprintf(buffer,BUFF_SIZE,"CONECT%6d",atom->GetIdx());
          ofs << buffer;
          for (nbr = atom->BeginNbrAtom(j);nbr;nbr = atom->NextNbrAtom(j))
            {
              snprintf(buffer,BUFF_SIZE,"%6d",nbr->GetIdx());
              ofs << buffer;
            }
          ofs << endl;

          snprintf(buffer,BUFF_SIZE,"ORDER %6d",atom->GetIdx());
          ofs << buffer;
          for (nbr = atom->BeginNbrAtom(j);nbr;nbr = atom->NextNbrAtom(j))
            {
              snprintf(buffer,BUFF_SIZE,"%6d",(*j)->GetBO());
              ofs << buffer;
            }
          ofs << endl;
        }

    ofs << "END" << endl;
    return(true);
  }