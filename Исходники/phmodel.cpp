  bool OBChemTsfm::Apply(OBMol &mol)
  {
    if (!_bgn.Match(mol))
      return(false);

    vector<vector<int> > mlist = _bgn.GetUMapList();

    obErrorLog.ThrowError(__FUNCTION__,
                          "Ran OpenBabel::OBChemTransform", obAuditMsg);

    if (!_vchrg.empty()) //modify charges
      {
        vector<vector<int> >::iterator i;
        vector<pair<int,int> >::iterator j;

        for (i = mlist.begin();i != mlist.end();++i)
          for (j = _vchrg.begin();j != _vchrg.end();++j)
            if (j->first < (signed)i->size()) //goof proofing
              mol.GetAtom((*i)[j->first])->SetFormalCharge(j->second);

        mol.UnsetImplicitValencePerceived();
      }

    if (!_vbond.empty()) //modify bond orders
      {
        OBBond *bond;
        vector<vector<int> >::iterator i;
        vector<pair<pair<int,int>,int> >::iterator j;
        for (i = mlist.begin();i != mlist.end();++i)
          for (j = _vbond.begin();j != _vbond.end();++j)
            {
              bond = mol.GetBond((*i)[j->first.first],(*i)[j->first.second]);
              if (!bond)
                {
                  obErrorLog.ThrowError(__FUNCTION__, "unable to find bond", obDebug);
                  continue;
                }

              bond->SetBO(j->second);
            }
      }

    if (!_vadel.empty() || !_vele.empty()) //delete atoms and change elements
      {
        vector<int>::iterator j;
        vector<vector<int> >::iterator i;

        if (!_vele.empty())
          {
            vector<pair<int,int> >::iterator k;
            for (i = mlist.begin();i != mlist.end();++i)
              for (k = _vele.begin();k != _vele.end();++k)
                mol.GetAtom((*i)[k->first])->SetAtomicNum(k->second);
          }

        //make sure same atom isn't deleted twice
        vector<bool> vda;
        vector<OBAtom*> vdel;
        vda.resize(mol.NumAtoms()+1,false);
        for (i = mlist.begin();i != mlist.end();++i)
          for (j = _vadel.begin();j != _vadel.end();++j)
            if (!vda[(*i)[*j]])
              {
                vda[(*i)[*j]] = true;
                vdel.push_back(mol.GetAtom((*i)[*j]));
              }

        vector<OBAtom*>::iterator k;
        for (k = vdel.begin();k != vdel.end();++k)
          mol.DeleteAtom((OBAtom*)*k);
      }

    return(true);
  }