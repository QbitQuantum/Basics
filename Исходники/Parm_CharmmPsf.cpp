int Parm_CharmmPsf::WriteParm(FileName const& fname, Topology const& parm) {
  // TODO: CMAP etc info
  CpptrajFile outfile;
  if (outfile.OpenWrite(fname)) return 1;
  // Write PSF
  outfile.Printf("PSF\n\n");
  // Write title
  std::string titleOut = parm.ParmName();
  titleOut.resize(78);
  outfile.Printf("%8i !NTITLE\n* %-78s\n\n", 1, titleOut.c_str());
  // Write NATOM section
  outfile.Printf("%8i !NATOM\n", parm.Natom());
  unsigned int idx = 1;
  // Make fake segment ids for now.
  char segid[2];
  segid[0] = 'A';
  segid[1] = '\0';
  mprintf("Warning: Assigning single letter segment IDs.\n");
  int currentMol = 0;
  bool inSolvent = false;
  for (Topology::atom_iterator atom = parm.begin(); atom != parm.end(); ++atom, ++idx) {
    int resnum = atom->ResNum();
    if (atom->MolNum() != currentMol) {
      if (!inSolvent) {
        inSolvent = parm.Mol(atom->MolNum()).IsSolvent();
        currentMol = atom->MolNum();
        segid[0]++;
      } else
        inSolvent = parm.Mol(atom->MolNum()).IsSolvent();
    }
    // TODO: Print type name for xplor-like PSF
    int typeindex = atom->TypeIndex() + 1;
    // If type begins with digit, assume charmm numbers were read as
    // type. Currently Amber types all begin with letters.
    if (isdigit(atom->Type()[0]))
      typeindex = convertToInteger( *(atom->Type()) );
    // ATOM# SEGID RES# RES ATNAME ATTYPE CHRG MASS (REST OF COLUMNS ARE LIKELY FOR CMAP AND CHEQ)
    outfile.Printf("%8i %-4s %-4i %-4s %-4s %4i %14.6G %9g  %10i\n", idx, segid,
                   parm.Res(resnum).OriginalResNum(), parm.Res(resnum).c_str(),
                   atom->c_str(), typeindex, atom->Charge(),
                   atom->Mass(), 0);
  }
  outfile.Printf("\n");
  // Write NBOND section
  outfile.Printf("%8u !NBOND: bonds\n", parm.Bonds().size() + parm.BondsH().size());
  idx = 1;
  for (BondArray::const_iterator bond = parm.BondsH().begin();
                                 bond != parm.BondsH().end(); ++bond, ++idx)
  {
    outfile.Printf("%8i%8i", bond->A1()+1, bond->A2()+1);
    if ((idx % 4)==0) outfile.Printf("\n"); 
  }
  for (BondArray::const_iterator bond = parm.Bonds().begin();
                                 bond != parm.Bonds().end(); ++bond, ++idx)
  {
    outfile.Printf("%8i%8i", bond->A1()+1, bond->A2()+1);
    if ((idx % 4)==0) outfile.Printf("\n"); 
  }
  if ((idx % 4)!=0) outfile.Printf("\n");
  outfile.Printf("\n");
  // Write NTHETA section
  outfile.Printf("%8u !NTHETA: angles\n", parm.Angles().size() + parm.AnglesH().size());
  idx = 1;
  for (AngleArray::const_iterator ang = parm.AnglesH().begin();
                                  ang != parm.AnglesH().end(); ++ang, ++idx)
  {
    outfile.Printf("%8i%8i%8i", ang->A1()+1, ang->A2()+1, ang->A3()+1);
    if ((idx % 3)==0) outfile.Printf("\n");
  }
  for (AngleArray::const_iterator ang = parm.Angles().begin();
                                  ang != parm.Angles().end(); ++ang, ++idx)
  {
    outfile.Printf("%8i%8i%8i", ang->A1()+1, ang->A2()+1, ang->A3()+1);
    if ((idx % 3)==0) outfile.Printf("\n");
  }
  if ((idx % 3)==0) outfile.Printf("\n");
  outfile.Printf("\n");
  // Write out NPHI section
  outfile.Printf("%8u !NPHI: dihedrals\n", parm.Dihedrals().size() + parm.DihedralsH().size());
  idx = 1;
  for (DihedralArray::const_iterator dih = parm.DihedralsH().begin();
                                     dih != parm.DihedralsH().end(); ++dih, ++idx)
  {
    outfile.Printf("%8i%8i%8i%8i", dih->A1()+1, dih->A2()+1, dih->A3()+1, dih->A4()+1);
    if ((idx % 2)==0) outfile.Printf("\n");
  }
  for (DihedralArray::const_iterator dih = parm.Dihedrals().begin();
                                     dih != parm.Dihedrals().end(); ++dih, ++idx)
  {
    outfile.Printf("%8i%8i%8i%8i", dih->A1()+1, dih->A2()+1, dih->A3()+1, dih->A4()+1);
    if ((idx % 2)==0) outfile.Printf("\n");
  }
  if ((idx % 2)==0) outfile.Printf("\n");
  outfile.Printf("\n");

  outfile.CloseFile();
  return 0;
}