  bool FastSearchFormat::ObtainTarget(OBConversion* pConv, vector<OBMol>& patternMols, const string& indexname)
  {
    //Obtains an OBMol from:
    // the filename in the -s option or
    // the SMARTS string in the -s option or
    // by converting the file in the -S or -aS options (deprecated).
    // If there is no -s -S or -aS option, information on the index file is displayed.

    OBMol patternMol;
    patternMol.SetIsPatternStructure();

    const char* p = pConv->IsOption("s",OBConversion::GENOPTIONS);

    bool OldSOption=false;
    //If no -s option, make OBMol from file in -S option or -aS option (both deprecated)
    if(!p)
    {
      p = pConv->IsOption("S",OBConversion::GENOPTIONS);
      if(!p)
        p = pConv->IsOption("S",OBConversion::INOPTIONS);//for GUI mainly
      OldSOption = true;
    }
    if(p)
    {
      vector<string> vec;
      tokenize(vec, p);

      //ignore leading ~ (not relevant to fastsearch)
      if(vec[0][0]=='~')
        vec[0].erase(0,1);

      if(vec.size()>1 && vec[1]=="exact")
        pConv->AddOption("e", OBConversion::INOPTIONS);

      OBConversion patternConv;
      OBFormat* pFormat;
      //Interpret as a filename if possible
      string& txt =vec [0];
      if( txt.empty() ||
          txt.find('.')==string::npos ||
          !(pFormat = patternConv.FormatFromExt(txt.c_str())) ||
          !patternConv.SetInFormat(pFormat) ||
          !patternConv.ReadFile(&patternMol, txt) ||
          patternMol.NumAtoms()==0)
        //if false, have a valid patternMol from a file
      {
        //is SMARTS/SMILES
        //Replace e.g. [#6] in SMARTS by C so that it can be converted as SMILES
        //for the fingerprint phase, but allow more generality in the SMARTS phase.
        for(;;)
        {
          string::size_type pos1, pos2;
          pos1 = txt.find("[#");
          if(pos1==string::npos)
            break;
          pos2 = txt.find(']');
          int atno;
          if(pos2!=string::npos &&  (atno = atoi(txt.substr(pos1+2, pos2-pos1-2).c_str())) && atno>0)
            txt.replace(pos1, pos2-pos1+1, etab.GetSymbol(atno));
          else
          {
            obErrorLog.ThrowError(__FUNCTION__,"Ill-formed [#n] atom in SMARTS", obError);
            return false;
          }
        }

        bool hasTildeBond;
        if( (hasTildeBond = (txt.find('~')!=string::npos)) ) // extra parens to indicate truth value
        {
          //Find ~ bonds and make versions of query molecule with a single and aromatic bonds
          //To avoid having to parse the SMILES here, replace ~ by $ (quadruple bond)
          //and then replace this in patternMol. Check first that there are no $ already
          //Sadly, isocynanides may have $ bonds.
          if(txt.find('$')!=string::npos)
          {
            obErrorLog.ThrowError(__FUNCTION__,
              "Cannot use ~ bonds in patterns with $ (quadruple) bonds.)", obError);
            return false;
          }
          replace(txt.begin(),txt.end(), '~' , '$');
        }

        //read as standard SMILES
        patternConv.SetInFormat("smi");
        if(!patternConv.ReadString(&patternMol, vec[0]))
        {
          obErrorLog.ThrowError(__FUNCTION__,"Cannot read the SMILES string",obError);
          return false;
        }
        if(hasTildeBond)
        {
          AddPattern(patternMols, patternMol, 0); //recursively add all combinations of tilde bond values
          return true;
        }
      }
      else
      {
        // target(s) are in a file
        patternMols.push_back(patternMol);
        while(patternConv.Read(&patternMol))
          patternMols.push_back(patternMol);
        return true;
      }
    }

    if(OldSOption) //only when using deprecated -S and -aS options
    {
      //make -s option for later SMARTS test
      OBConversion conv;
      if(conv.SetOutFormat("smi"))
      {
        string optiontext = conv.WriteString(&patternMol, true);
        pConv->AddOption("s", OBConversion::GENOPTIONS, optiontext.c_str());
      }
    }

    if(!p)
    {
      //neither -s or -S options provided. Output info rather than doing search
      const FptIndexHeader& header = fs.GetIndexHeader();
      string id(header.fpid);
      if(id.empty())
        id = "default";
      clog << indexname << " is an index of\n " << header.datafilename
           << ".\n It contains " << header.nEntries
           << " molecules. The fingerprint type is " << id << " with "
           << OBFingerprint::Getbitsperint() * header.words << " bits.\n"
           << "Typical usage for a substructure search:\n"
           << "obabel indexfile.fs -osmi -sSMILES\n"
           << "(-s option in GUI is 'Convert only if match SMARTS or mols in file')" << endl;
      return false;
    }

    patternMols.push_back(patternMol);
    return true;
  }