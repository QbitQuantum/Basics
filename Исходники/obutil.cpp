  //! Transform the supplied vector<OBInternalCoord*> into cartesian and update
  //! the OBMol accordingly. The size of supplied internal coordinate vector
  //! has to be the same as the number of atoms in molecule (+ NULL in the
  //! beginning).
  //! Implements <a href="http://qsar.sourceforge.net/dicts/blue-obelisk/index.xhtml#zmatrixCoordinatesIntoCartesianCoordinates">blue-obelisk:zmatrixCoordinatesIntoCartesianCoordinates</a>
  void InternalToCartesian(std::vector<OBInternalCoord*> &vic,OBMol &mol)
  {
    vector3 n,nn,v1,v2,v3,avec,bvec,cvec;
    double dst = 0.0, ang = 0.0, tor = 0.0;
    OBAtom *atom;
    vector<OBAtom*>::iterator i;
    unsigned int index;

    if (vic.empty())
      return;

    if (vic[0] != NULL) {
      std::vector<OBInternalCoord*>::iterator it = vic.begin();
      vic.insert(it, static_cast<OBInternalCoord*>(NULL));
    }

    if (vic.size() != mol.NumAtoms() + 1) {
      string error = "Number of internal coordinates is not the same as";
      error += " the number of atoms in molecule";
      obErrorLog.ThrowError(__FUNCTION__, error, obError);
      return;
    }

    obErrorLog.ThrowError(__FUNCTION__,
                          "Ran OpenBabel::InternalToCartesian", obAuditMsg);

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        index = atom->GetIdx();

        // make sure we always have valid pointers
        if (index >= vic.size() || !vic[index])
          return;

        if (vic[index]->_a) // make sure we have a valid ptr
          {
            avec = vic[index]->_a->GetVector();
            dst = vic[index]->_dst;
          }
        else
          {
            // atom 1
            atom->SetVector(0.0, 0.0, 0.0);
            continue;
          }

        if (vic[index]->_b)
          {
            bvec = vic[index]->_b->GetVector();
            ang = vic[index]->_ang * DEG_TO_RAD;
          }
        else
          {
            // atom 2
            atom->SetVector(dst, 0.0, 0.0);
            continue;
          }

        if (vic[index]->_c)
          {
            cvec = vic[index]->_c->GetVector();
            tor = vic[index]->_tor * DEG_TO_RAD;
          }
        else
          {
            // atom 3
            cvec = VY;
            tor = 90. * DEG_TO_RAD;
          }

        v1 = avec - bvec;
        v2 = avec - cvec;
        n = cross(v1,v2);
        nn = cross(v1,n);
        n.normalize();
        nn.normalize();

        n  *= -sin(tor);
        nn *= cos(tor);
        v3 = n + nn;
        v3.normalize();
        v3 *= dst * sin(ang);
        v1.normalize();
        v1 *= dst * cos(ang);
        v2 = avec + v3 - v1;

        atom->SetVector(v2);
      }

    // Delete dummy atoms
    vector<OBAtom*> for_deletion;
    FOR_ATOMS_OF_MOL(a, mol)
      if (a->GetAtomicNum() == 0)
        for_deletion.push_back(&(*a));
    for(vector<OBAtom*>::iterator a_it=for_deletion.begin(); a_it!=for_deletion.end(); ++a_it)
      mol.DeleteAtom(*a_it);

  }