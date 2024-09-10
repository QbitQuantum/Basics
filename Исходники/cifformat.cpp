  void CIFData::ExtractSpacegroup(const bool verbose)
  {
    map<ci_string,string>::const_iterator positem;
    bool found = false;
    positem=mvItem.find("_space_group_IT_number");
    if(positem!=mvItem.end())
      {
        mSpacegroupNumberIT=CIFNumeric2Int(positem->second);
        found = true;
        if(verbose) cout<<"Found spacegroup IT number:"<<mSpacegroupNumberIT<<endl;
      }
    else
      {
        positem=mvItem.find("_symmetry_Int_Tables_number");
        if(positem!=mvItem.end())
          {
            mSpacegroupNumberIT=CIFNumeric2Int(positem->second);
            found = true;
            if(verbose) cout<<"Found spacegroup IT number (with OBSOLETE CIF #1.0 TAG):"<<mSpacegroupNumberIT<<endl;
          }
        else {
          positem=mvItem.find("_symmetry_group_IT_number");
          if(positem!=mvItem.end())
          {
            mSpacegroupNumberIT=CIFNumeric2Int(positem->second);
            found = true;
            if(verbose) cout<<"Found spacegroup IT number (with NON-STANDARD CIF TAG):"<<mSpacegroupNumberIT<<endl;
          }
          else
            mSpacegroupNumberIT=0;
        }
      }

    positem=mvItem.find("_space_group_name_Hall");
    if(positem!=mvItem.end())
      {
        mSpacegroupSymbolHall=positem->second;
        found = true;
        if(verbose) cout<<"Found spacegroup Hall symbol:"<<mSpacegroupSymbolHall<<endl;
      }
    else
      {
        positem=mvItem.find("_symmetry_space_group_name_Hall");
        if(positem!=mvItem.end())
          {
            mSpacegroupSymbolHall=positem->second;
            found = true;
            if(verbose) cout<<"Found spacegroup Hall symbol (with OBSOLETE CIF #1.0 TAG):"<<mSpacegroupSymbolHall<<endl;
          }
      }

    positem=mvItem.find("_space_group_name_H-M_alt");
    if(positem!=mvItem.end())
      {
        mSpacegroupHermannMauguin=positem->second;
        found = true;
        if(verbose) cout<<"Found spacegroup Hermann-Mauguin symbol:"<<mSpacegroupHermannMauguin<<endl;
      }
    else
      {
        positem=mvItem.find("_symmetry_space_group_name_H-M");
        if(positem!=mvItem.end())
          {
            mSpacegroupHermannMauguin=positem->second;
            found = true;
            if(verbose) cout<<"Found spacegroup Hermann-Mauguin symbol (with OBSOLETE CIF #1.0 TAG):"<<mSpacegroupHermannMauguin<<endl;
          }
      }
    mSpaceGroup=NULL;
    if (mSpacegroupNumberIT != 0) {
      mSpaceGroup = SpaceGroup::GetSpaceGroup(mSpacegroupNumberIT);
    }
    else if (mSpacegroupSymbolHall.length() > 0) {
      mSpaceGroup = SpaceGroup::GetSpaceGroup(mSpacegroupSymbolHall);
    }
    else if (mSpacegroupHermannMauguin.length() > 0) {
      mSpaceGroup = SpaceGroup::GetSpaceGroup(mSpacegroupHermannMauguin);
    }
    else {
      SpaceGroup *sg = new SpaceGroup();
      positem=mvItem.find("_symmetry_equiv_pos_as_xyz");
      if(positem!=mvItem.end())
        {
          sg->AddTransform (positem->second);
          found = true;
        }
      else {
        for(map<set<ci_string>,map<ci_string,vector<string> > >::const_iterator loop=mvLoop.begin();
            loop!=mvLoop.end();++loop)
          {
            map<ci_string,vector<string> >::const_iterator pos;
            unsigned i, nb;
            pos=loop->second.find("_symmetry_equiv_pos_as_xyz");
            if (pos!=loop->second.end())
              {
                nb=pos->second.size();
                found = true;
                for (i = 0; i < nb; i++)
                  sg->AddTransform(pos->second[i]);
                break; // found the transforms, so we have done with them
              }
          }
        if (found)
          mSpaceGroup = SpaceGroup::Find(sg);
        delete sg;
      }
    }
    if (mSpaceGroup != NULL)
      // set the space group name to Hall symbol
      mSpacegroupSymbolHall = mSpaceGroup->GetHallName();
  }