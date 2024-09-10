bool OpAlign::Do(OBBase* pOb, const char* OptionText, OpMap* pmap, OBConversion* pConv)
{
  OBMol* pmol = dynamic_cast<OBMol*>(pOb);
  if(!pmol)
    return false;

  map<string,string>::const_iterator itr;

  // Is there an -s option?
  if(pConv->IsFirstInput())
  {
    _pOpIsoM = NULL; //assume no -s option
    itr = pmap->find("s");
    if(itr!=pmap->end())
    {
      //There is an -s option; check it is ok
      _pOpIsoM = static_cast<OpNewS*>(OBOp::FindType("s"));
      _stext = itr->second; //get its parameter(s)
      if(!_pOpIsoM || _stext.empty())
      {
        obErrorLog.ThrowError(__FUNCTION__,
        "No parameter on -s option, or its OBOp version is not loaded", obError);
        pConv->SetOneObjectOnly(); //to finish
        return false;
      }
    }
  }

  // If the output format is a 2D depiction format, then we should align
  // on the 2D coordinates and not the 3D coordinates (if present). This
  //means we need to generate the 2D coordinates at this point.
  if(pmol->GetDimension()==3 && (pConv->GetOutFormat()->Flags() & DEPICTION2D))
  {
    OBOp* pgen = OBOp::FindType("gen2D");
    if(pgen)
      pgen->Do(pmol);
  }

  // All molecules must have coordinates, so add them if 0D
  // They may be added again later when gen2D or gen3D is called, but they will be the same.
  // It would be better if this op was called after them, which would happen
  // if its name was alphabetically after "gen" (and before "s").
  if(pmol->GetDimension()==0)
  {
    //Will the coordinates be 2D or 3D?
    itr = pmap->find("gen3D");
    OBOp* pgen = (itr==pmap->end()) ? OBOp::FindType("gen2D") : OBOp::FindType("gen3D");
    if(pgen)
      pgen->Do(pmol);
  }

  //Do the alignment in 2D if the output format is svg, png etc. and there is no -xn option
  if(pmol->GetDimension()==3 && pConv && !pConv->IsOption("n"))
  {
    OBFormat* pOutFormat = pConv->GetOutFormat();
    if(pOutFormat->Flags() & DEPICTION2D)
    {
      OBOp* pgen = OBOp::FindType("gen2D");
      if(pgen)
        pgen->Do(pmol);
    }
  }

  if(pConv->IsFirstInput() || _refMol.NumAtoms()==0)
  {
    _refvec.clear();
    // Reference molecule is basically the first molecule
    _refMol = *pmol;
    if(!_pOpIsoM)
     //no -s option. Use a molecule reference.
     _align.SetRefMol(_refMol);
    else
    {
      //If there is a -s option, reference molecule has only those atoms that are matched
      //Call the -s option from here
      bool ret = _pOpIsoM->Do(pmol, _stext.c_str(), pmap, pConv);
      // Get the atoms that were matched
      vector<int> ats = _pOpIsoM->GetMatchAtoms();
      if(!ats.empty())
      {
        // Make a vector of the matching atom coordinates...
        for(vector<int>::iterator iter=ats.begin(); iter!=ats.end(); ++iter)
          _refvec.push_back((pmol->GetAtom(*iter))->GetVector());
        // ...and use a vector reference
        _align.SetRef(_refvec);
      }
      // Stop -s option being called normally, although it will still be called once
      //  in the DoOps loop already started for the current (first) molecule.
      pConv->RemoveOption("s",OBConversion::GENOPTIONS);
      if(!ret)
      {
        // the first molecule did not match the -s option so a reference molecule
        // could not be made. Keep trying.
        _refMol.Clear();
        //obErrorLog.ThrowError(__FUNCTION__, "The first molecule did not match the -s option\n"
        //  "so the reference structure was not derived from it", obWarning, onceOnly);
        return false; //not matched
      }
    }
  }

  //All molecules
  if(pmol->GetDimension()!= _refMol.GetDimension())
  {
    stringstream ss;
    ss << "The molecule" << pmol->GetTitle()
       << " does not have the same dimensions as the reference molecule "
       << _refMol.GetTitle() << " and is ignored.";
       obErrorLog.ThrowError(__FUNCTION__, ss.str().c_str(), obError);
    return false;
  }

  if(_pOpIsoM) //Using -s option
  {
    //Ignore mol if it does not pass -s option
    if(!_pOpIsoM->Do(pmol, "", pmap, pConv)) // "" means will use existing parameters
      return false;

    // Get the atoms equivalent to those in ref molecule
    vector<int> ats = _pOpIsoM->GetMatchAtoms();

    // Make a vector of their coordinates and get the centroid
    vector<vector3> vec;
    vector3 centroid;
    for(vector<int>::iterator iter=ats.begin(); iter!=ats.end(); ++iter) {
      vector3 v = pmol->GetAtom(*iter)->GetVector();
      centroid += v;
      vec.push_back(v);
    }
    centroid /= vec.size();

    // Do the alignment
    _align.SetTarget(vec);
    if(!_align.Align())
      return false;

    // Get the centroid of the reference atoms
    vector3 ref_centroid;
    for(vector<vector3>::iterator iter=_refvec.begin(); iter!=_refvec.end(); ++iter)
      ref_centroid += *iter;
    ref_centroid /= _refvec.size();

    //subtract the centroid, rotate the target molecule, then add the centroid
    matrix3x3 rotmatrix = _align.GetRotMatrix();
    for (unsigned int i = 1; i <= pmol->NumAtoms(); ++i)
    {
      vector3 tmpvec = pmol->GetAtom(i)->GetVector();
      tmpvec -= centroid;
      tmpvec *= rotmatrix; //apply the rotation
      tmpvec += ref_centroid;
      pmol->GetAtom(i)->SetVector(tmpvec);
    }
  }
  else //Not using -s option)
  {
    _align.SetTargetMol(*pmol);
    if(!_align.Align())
      return false;
    _align.UpdateCoords(pmol);
  }

  //Save rmsd as a property
  OBPairData* dp = new OBPairData;
  dp->SetAttribute("rmsd");
  double val = _align.GetRMSD();
  if(val<1e-12)
    val = 0.0;
  dp->SetValue(toString(val));
  dp->SetOrigin(local);
  pmol->SetData(dp);

  return true;
}