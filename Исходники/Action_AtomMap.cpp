// Action_AtomMap::Init()
Action::RetType Action_AtomMap::Init(ArgList& actionArgs, ActionInit& init, int debugIn)
{
    DataFile* rmsout = 0;
    int refatom,targetatom;
    debug_ = debugIn;
    RefMap_.SetDebug(debug_);
    TgtMap_.SetDebug(debug_);

    // Get Args
    CpptrajFile* outputfile = init.DFL().AddCpptrajFile(actionArgs.GetStringKey("mapout"), "Atom Map");
    maponly_ = actionArgs.hasKey("maponly");
    rmsfit_ = actionArgs.hasKey("rmsfit");
    if (rmsfit_)
        rmsout = init.DFL().AddDataFile( actionArgs.GetStringKey("rmsout"), actionArgs );
    std::string targetName = actionArgs.GetStringNext();
    std::string refName = actionArgs.GetStringNext();
    if (targetName.empty()) {
        mprinterr("Error: No target specified.\n");
        return Action::ERR;
    }
    if (refName.empty()) {
        mprinterr("Error: No reference specified.\n");
        return Action::ERR;
    }
    // Get Reference
    RefFrame_ = (DataSet_Coords_REF*)init.DSL().FindSetOfType( refName, DataSet::REF_FRAME );
    if (RefFrame_ == 0) {
        mprinterr("Error: Could not get reference frame %s\n",refName.c_str());
        return Action::ERR;
    }
    // Get Target
    TgtFrame_ = (DataSet_Coords_REF*)init.DSL().FindSetOfType( targetName, DataSet::REF_FRAME );
    if (TgtFrame_ == 0) {
        mprinterr("Error: Could not get target frame %s\n",targetName.c_str());
        return Action::ERR;
    }

    mprintf("    ATOMMAP: Atoms in trajectories associated with parm %s will be\n",
            TgtFrame_->Top().c_str());
    mprintf("             mapped according to parm %s.\n",RefFrame_->Top().c_str());
    if (outputfile != 0)
        mprintf("             Map will be written to %s\n",outputfile->Filename().full());
    if (maponly_)
        mprintf("             maponly: Map will only be written, not used in trajectory read.\n");
    if (!maponly_ && rmsfit_) {
        mprintf("             rmsfit: Will rms fit mapped atoms in tgt to reference.\n");
        if (rmsout != 0) {
            rmsdata_ = init.DSL().AddSet(DataSet::DOUBLE, actionArgs.GetStringNext(), "RMSD");
            if (rmsdata_==0) return Action::ERR;
            rmsout->AddDataSet(rmsdata_);
        }
    }

    // For each map, set up (get element for each atom, initialize map mem),
    // determine what atoms are bonded to each other via simple distance
    // cutoffs, the give each atom an ID based on what atoms are bonded to
    // it, noting which IDs are unique for that map.

    if (RefMap_.Setup(RefFrame_->Top())!=0) return Action::ERR;
    //RefMap_.WriteMol2((char*)"RefMap.mol2\0"); // DEBUG
    RefMap_.DetermineAtomIDs();

    if (TgtMap_.Setup(TgtFrame_->Top())!=0) return Action::ERR;
    //TgtMap_.WriteMol2((char*)"TgtMap.mol2\0"); // DEBUG
    TgtMap_.DetermineAtomIDs();

    // Check if number of atoms in each map is equal
    if (RefMap_.Natom() != TgtMap_.Natom()) {
        mprintf("Warning: # atoms in reference (%i) not equal\n",
                RefMap_.Natom());
        mprintf("Warning:\tto # atoms in target (%i).\n",TgtMap_.Natom());
    }

    // Set up RMS frames to be able to hold max # of possible atoms
    rmsRefFrame_.SetupFrame(RefMap_.Natom());
    rmsTgtFrame_.SetupFrame(RefMap_.Natom());

    // Allocate memory for atom map
    //   AMap_[reference]=target
    AMap_.resize( RefMap_.Natom(), -1);
    // Map unique atoms
    int numMappedAtoms = MapUniqueAtoms(RefMap_, TgtMap_);
    if (debug_>0)
        mprintf("*         MapUniqueAtoms: %i atoms mapped.\n",numMappedAtoms);
    // If no unique atoms mapped system is highly symmetric and needs to be
    // iteratively mapped. Otherwise just map remaining atoms.
    if (numMappedAtoms==0) {
        if (MapWithNoUniqueAtoms(RefMap_,TgtMap_)) return Action::ERR;
    } else {
        if (MapAtoms(RefMap_,TgtMap_)) return Action::ERR;
    }

    // Print atom map and count # mapped atoms
    numMappedAtoms = 0;
    outputfile->Printf("%-6s %4s %6s %4s\n","#TgtAt","Tgt","RefAt","Ref");
    for (refatom=0; refatom < RefMap_.Natom(); refatom++) {
        targetatom = AMap_[refatom];
        if (targetatom < 0)
            outputfile->Printf("%6s %4s %6i %4s\n","---","---",refatom+1,RefMap_[refatom].c_str());
        else
            outputfile->Printf("%6i %4s %6i %4s\n",targetatom+1,TgtMap_[targetatom].c_str(),
                               refatom+1, RefMap_[refatom].c_str());
        if (targetatom>=0) {
            //mprintf("* TargetAtom %6i(%4s) maps to RefAtom %6i(%4s)\n",
            //                targetatom,TgtMap_.P->names[targetatom],
            //                refatom,RefMap_.P->names[refatom]);
            ++numMappedAtoms;
        } //else {
        //  mprintf("* Could not map any TargetAtom to RefAtom %6i(%4s)\n",
        //                  refatom,RefMap_.P->names[refatom]);
        //}
    }
    mprintf("      %i total atoms were mapped.\n",numMappedAtoms);
    if (maponly_) return Action::OK;

    // If rmsfit is specified, an rms fit of target to reference will be
    // performed using all atoms that were successfully mapped from
    // target to reference.
    if (rmsfit_) {
        // Set up a reference frame containing only mapped reference atoms
        rmsRefFrame_.StripUnmappedAtoms(RefFrame_->RefFrame(), AMap_);
        mprintf("      rmsfit: Will rms fit %i atoms from target to reference.\n",numMappedAtoms);
        return Action::OK;
    }

    // Check if not all atoms could be mapped
    if (numMappedAtoms != RefMap_.Natom()) {
        // If the number of mapped atoms is less than the number of reference
        // atoms but equal to the number of target atoms, can modify the reference
        // frame to only include mapped atoms
        if (numMappedAtoms<RefMap_.Natom() && numMappedAtoms==TgtMap_.Natom()) {
            // Create mask that includes only reference atoms that could be mapped
            AtomMask M1;
            for (refatom = 0; refatom < RefMap_.Natom(); refatom++) {
                if (AMap_[refatom] != -1) M1.AddAtom(refatom);
            }
            // Strip reference parm
            mprintf("    Modifying reference '%s' topology and frame to match mapped atoms.\n",
                    RefFrame_->legend());
            if (RefFrame_->StripRef( M1 )) return Action::ERR;
            // Since AMap[ ref ] = tgt but ref is now missing any stripped atoms,
            // the indices of AMap must be shifted to match
            int refIndex = 0; // The new index
            for (refatom = 0; refatom < RefMap_.Natom(); refatom++) {
                targetatom = AMap_[refatom];
                if (targetatom<0)
                    continue;
                else
                    AMap_[refIndex++]=targetatom;
            }
        } else {
            mprintf("Warning: AtomMap: Not all atoms were mapped. Frames will not be modified.\n");
            maponly_=true;
        }
    }

    if (!maponly_) {
        // Set up new Frame
        newFrame_ = new Frame();
        newFrame_->SetupFrameM( TgtFrame_->Top().Atoms() );

        // Set up new Parm
        newParm_ = TgtFrame_->Top().ModifyByMap(AMap_);
    }

    return Action::OK;
}