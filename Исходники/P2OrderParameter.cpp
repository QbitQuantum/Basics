void P2OrderParameter::process() {
    Molecule* mol;
    RigidBody* rb;
    SimInfo::MoleculeIterator mi;
    Molecule::RigidBodyIterator rbIter;
    StuntDouble* sd1;
    StuntDouble* sd2;
    int ii;
    int jj;
    int vecCount;
    bool usePeriodicBoundaryConditions_ = info_->getSimParams()->getUsePeriodicBoundaryConditions();

    DumpReader reader(info_, dumpFilename_);
    int nFrames = reader.getNFrames();

    for (int i = 0; i < nFrames; i += step_) {
        reader.readFrame(i);
        currentSnapshot_ = info_->getSnapshotManager()->getCurrentSnapshot();

        for (mol = info_->beginMolecule(mi); mol != NULL;
                mol = info_->nextMolecule(mi)) {
            //change the positions of atoms which belong to the rigidbodies
            for (rb = mol->beginRigidBody(rbIter); rb != NULL;
                    rb = mol->nextRigidBody(rbIter)) {
                rb->updateAtoms();
            }
        }

        Mat3x3d orderTensor(0.0);
        vecCount = 0;

        seleMan1_.setSelectionSet(evaluator1_.evaluate());

        if (doVect_) {

            for (sd1 = seleMan1_.beginSelected(ii); sd1 != NULL;
                    sd1 = seleMan1_.nextSelected(ii)) {
                if (sd1->isDirectional()) {
                    Vector3d vec = sd1->getA().transpose()*V3Z;

                    vec.normalize();
                    orderTensor += outProduct(vec, vec);
                    vecCount++;
                }
            }

            orderTensor /= vecCount;

        } else {

            if (doOffset_) {

                for (sd1 = seleMan1_.beginSelected(ii); sd1 != NULL;
                        sd1 = seleMan1_.nextSelected(ii)) {

                    // This will require careful rewriting if StaticProps is
                    // ever parallelized.  For an example, see
                    // Thermo::getTaggedAtomPairDistance

                    int sd2Index = sd1->getGlobalIndex() + seleOffset_;
                    sd2 = info_->getIOIndexToIntegrableObject(sd2Index);

                    Vector3d vec = sd1->getPos() - sd2->getPos();

                    if (usePeriodicBoundaryConditions_)
                        currentSnapshot_->wrapVector(vec);

                    vec.normalize();

                    orderTensor +=outProduct(vec, vec);
                    vecCount++;
                }

                orderTensor /= vecCount;
            } else {

                seleMan2_.setSelectionSet(evaluator2_.evaluate());

                if (seleMan1_.getSelectionCount() != seleMan2_.getSelectionCount() ) {
                    sprintf( painCave.errMsg,
                             "In frame %d, the number of selected StuntDoubles are\n"
                             "\tnot the same in --sele1 and sele2\n", i);
                    painCave.severity = OPENMD_INFO;
                    painCave.isFatal = 0;
                    simError();
                }

                for (sd1 = seleMan1_.beginSelected(ii),
                        sd2 = seleMan2_.beginSelected(jj);
                        sd1 != NULL && sd2 != NULL;
                        sd1 = seleMan1_.nextSelected(ii),
                        sd2 = seleMan2_.nextSelected(jj)) {

                    Vector3d vec = sd1->getPos() - sd2->getPos();

                    if (usePeriodicBoundaryConditions_)
                        currentSnapshot_->wrapVector(vec);

                    vec.normalize();

                    orderTensor +=outProduct(vec, vec);
                    vecCount++;
                }

                orderTensor /= vecCount;
            }
        }

        if (vecCount == 0) {
            sprintf( painCave.errMsg,
                     "In frame %d, the number of selected vectors was zero.\n"
                     "\tThis will not give a meaningful order parameter.", i);
            painCave.severity = OPENMD_ERROR;
            painCave.isFatal = 1;
            simError();
        }

        orderTensor -= (RealType)(1.0/3.0) * Mat3x3d::identity();

        Vector3d eigenvalues;
        Mat3x3d eigenvectors;

        Mat3x3d::diagonalize(orderTensor, eigenvalues, eigenvectors);

        int which(-1);
        RealType maxEval = 0.0;
        for(int k = 0; k< 3; k++) {
            if(fabs(eigenvalues[k]) > maxEval) {
                which = k;
                maxEval = fabs(eigenvalues[k]);
            }
        }
        RealType p2 = 1.5 * maxEval;

        //the eigen vector is already normalized in SquareMatrix3::diagonalize
        Vector3d director = eigenvectors.getColumn(which);
        if (director[0] < 0) {
            director.negate();
        }

        RealType angle = 0.0;
        vecCount = 0;

        if (doVect_) {
            for (sd1 = seleMan1_.beginSelected(ii); sd1 != NULL;
                    sd1 = seleMan1_.nextSelected(ii)) {
                if (sd1->isDirectional()) {
                    Vector3d vec = sd1->getA().transpose()*V3Z;
                    vec.normalize();
                    angle += acos(dot(vec, director));
                    vecCount++;
                }
            }
            angle = angle/(vecCount*NumericConstant::PI)*180.0;

        } else {
            if (doOffset_) {

                for (sd1 = seleMan1_.beginSelected(ii); sd1 != NULL;
                        sd1 = seleMan1_.nextSelected(ii)) {

                    // This will require careful rewriting if StaticProps is
                    // ever parallelized.  For an example, see
                    // Thermo::getTaggedAtomPairDistance

                    int sd2Index = sd1->getGlobalIndex() + seleOffset_;
                    sd2 = info_->getIOIndexToIntegrableObject(sd2Index);

                    Vector3d vec = sd1->getPos() - sd2->getPos();
                    if (usePeriodicBoundaryConditions_)
                        currentSnapshot_->wrapVector(vec);
                    vec.normalize();
                    angle += acos(dot(vec, director)) ;
                    vecCount++;
                }
                angle = angle / (vecCount * NumericConstant::PI) * 180.0;

            } else {

                for (sd1 = seleMan1_.beginSelected(ii),
                        sd2 = seleMan2_.beginSelected(jj);
                        sd1 != NULL && sd2 != NULL;
                        sd1 = seleMan1_.nextSelected(ii),
                        sd2 = seleMan2_.nextSelected(jj)) {

                    Vector3d vec = sd1->getPos() - sd2->getPos();
                    if (usePeriodicBoundaryConditions_)
                        currentSnapshot_->wrapVector(vec);
                    vec.normalize();
                    angle += acos(dot(vec, director)) ;
                    vecCount++;
                }
                angle = angle / (vecCount * NumericConstant::PI) * 180.0;
            }
        }

        OrderParam param;
        param.p2 = p2;
        param.director = director;
        param.angle = angle;

        orderParams_.push_back(param);

    }

    writeP2();

}