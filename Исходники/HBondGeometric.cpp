  void HBondGeometric::process() {
    Molecule* mol1;
    Molecule* mol2;
    RigidBody* rb1;
    Molecule::HBondDonor* hbd1;
    Molecule::HBondDonor* hbd2;
    std::vector<Molecule::HBondDonor*>::iterator hbdi;
    std::vector<Molecule::HBondDonor*>::iterator hbdj;
    std::vector<Atom*>::iterator hbai;
    std::vector<Atom*>::iterator hbaj;
    Atom* hba1;
    Atom* hba2;
    SimInfo::MoleculeIterator mi;
    Molecule::RigidBodyIterator rbIter;
    Vector3d dPos;
    Vector3d aPos;
    Vector3d hPos;
    Vector3d DH;
    Vector3d DA;
    RealType DAdist, DHdist, theta, ctheta;
    int ii, jj;
    int nHB, nA, nD;

    DumpReader reader(info_, dumpFilename_);    
    int nFrames = reader.getNFrames();
    frameCounter_ = 0;

    for (int istep = 0; istep < nFrames; istep += step_) {
      reader.readFrame(istep);
      frameCounter_++;
      currentSnapshot_ = info_->getSnapshotManager()->getCurrentSnapshot();
     
      // update the positions of atoms which belong to the rigidbodies
      
      for (mol1 = info_->beginMolecule(mi); mol1 != NULL; 
           mol1 = info_->nextMolecule(mi)) {
        for (rb1 = mol1->beginRigidBody(rbIter); rb1 != NULL; 
             rb1 = mol1->nextRigidBody(rbIter)) {
          rb1->updateAtoms();
        }        
      }           
      
      if  (evaluator1_.isDynamic()) {
        seleMan1_.setSelectionSet(evaluator1_.evaluate());
      }
      if  (evaluator2_.isDynamic()) {
        seleMan2_.setSelectionSet(evaluator2_.evaluate());
      }
      
      for (mol1 = seleMan1_.beginSelectedMolecule(ii);
           mol1 != NULL; mol1 = seleMan1_.nextSelectedMolecule(ii)) {

        // We're collecting statistics on the molecules in selection 1:
        nHB = 0;
        nA = 0;
        nD = 0;
        
        for (mol2 = seleMan2_.beginSelectedMolecule(jj);
             mol2 != NULL; mol2 = seleMan2_.nextSelectedMolecule(jj)) {
          
          // loop over the possible donors in molecule 1:
          for (hbd1 = mol1->beginHBondDonor(hbdi); hbd1 != NULL;
               hbd1 = mol1->nextHBondDonor(hbdi)) {
            dPos = hbd1->donorAtom->getPos();
            hPos = hbd1->donatedHydrogen->getPos();
            DH = hPos - dPos; 
            currentSnapshot_->wrapVector(DH);
            DHdist = DH.length();

            // loop over the possible acceptors in molecule 2:
            for (hba2 = mol2->beginHBondAcceptor(hbaj); hba2 != NULL;
                 hba2 = mol2->nextHBondAcceptor(hbaj)) {
              aPos = hba2->getPos();
              DA = aPos - dPos;              
              currentSnapshot_->wrapVector(DA);
              DAdist = DA.length();

              // Distance criteria: are the donor and acceptor atoms
              // close enough?
              if (DAdist < rCut_) {

                ctheta = dot(DH, DA) / (DHdist * DAdist);
                theta = acos(ctheta) * 180.0 / M_PI;

                // Angle criteria: are the D-H and D-A and vectors close?
                if (theta < thetaCut_) {
                  // molecule 1 is a Hbond donor:
                  nHB++;
                  nD++;
                }
              }            
            }            
          }

          // now loop over the possible acceptors in molecule 1:
          for (hba1 = mol1->beginHBondAcceptor(hbai); hba1 != NULL;
               hba1 = mol1->nextHBondAcceptor(hbai)) {
            aPos = hba1->getPos();
            
            // loop over the possible donors in molecule 2:
            for (hbd2 = mol2->beginHBondDonor(hbdj); hbd2 != NULL;
               hbd2 = mol2->nextHBondDonor(hbdj)) {
              dPos = hbd2->donorAtom->getPos();

              DA = aPos - dPos;
              currentSnapshot_->wrapVector(DA);
              DAdist = DA.length();
              
              // Distance criteria: are the donor and acceptor atoms
              // close enough?
              if (DAdist < rCut_) {
                hPos = hbd2->donatedHydrogen->getPos();
                DH = hPos - dPos; 
                currentSnapshot_->wrapVector(DH);
                DHdist = DH.length();
                ctheta = dot(DH, DA) / (DHdist * DAdist);
                theta = acos(ctheta) * 180.0 / M_PI;
                // Angle criteria: are the D-H and D-A and vectors close?
                if (theta < thetaCut_) {
                  // molecule 1 is a Hbond acceptor:
                  nHB++;
                  nA++;
                }                
              }
            }
          }
        }                 
        collectHistogram(nHB, nA, nD);
      }
    }
    writeHistogram();
  }