void
RCM2Material ::  giveRealPrincipalStressVector3d(FloatArray &answer, GaussPoint *gp,
                                                 FloatArray &principalStrain,
                                                 FloatMatrix &tempCrackDirs,
                                                 TimeStep *atTime)
//
// returns real principal stress vector in 3d stress space of receiver according to
// previous level of stress and current
// strain increment, the only way, how to correctly update gp records
// updates principal strain and stress of the receiver's status.
//
{
    int i, iter, ind;
    double maxErr;
    FloatArray crackStrainVector, reducedTotalStrainVector;
    FloatArray strainIncrement, crackStrainIterativeIncrement;
    FloatArray prevPrincipalStrain;
    FloatArray dSigma;
    FloatArray elastStrain, sigmaEl, sigmaCr(3);
    FloatArray fullDSigma;
    IntArray activatedCracks, crackMapping;
    FloatMatrix dcr, de, decr, fullDecr, crackDirs;
    RCM2MaterialStatus *status = ( RCM2MaterialStatus * ) this->giveStatus(gp);

    /*
     * if (status -> giveStressVector() == NULL) status->letStressVectorBe(new FloatArray(this->giveSizeOfReducedStressStrainVector(gp->giveMaterialMode())));
     * if (status -> giveStrainVector() == NULL) status->letStrainVectorBe(new FloatArray(this->giveSizeOfReducedStressStrainVector(gp->giveMaterialMode())));
     * // if (status -> givePlasticStrainVector() == NULL) status->letPlasticStrainVectorBe(new FloatArray(6));
     * if (status -> giveStressIncrementVector() == NULL) status->letStressIncrementVectorBe(new FloatArray(this->giveSizeOfReducedStressStrainVector(gp->giveMaterialMode())));
     * if (status -> giveStrainIncrementVector() == NULL) status->letStrainIncrementVectorBe(new FloatArray(this->giveSizeOfReducedStressStrainVector(gp->giveMaterialMode())));
     * // if (status -> givePlasticStrainIncrementVector() == NULL) status->letPlasticStrainIncrementVectorBe(new FloatArray(6));
     */

    /*
     * // totalStressVector = gp -> giveStressVector()->GiveCopy();
     * reducedTotalStrainVector = status -> giveStrainVector();
     * reducedTotalStrainVector.add(fullStrainIncrement);
     * crossSection->giveFullCharacteristicVector(totalStrainVector, gp, reducedTotalStrainVector);
     * //delete reducedTotalStrainVector;
     * // plasticStrainVector = status -> givePlasticStrainVector()->GiveCopy();
     *
     *
     * // already cracked - next directions are determined
     * // according to principal strain directions
     * status->giveTempCrackDirs(tempCrackDirs);
     * this->computePrincipalValDir (principalStrain, tempCrackDirs,
     *              totalStrainVector,
     *              principal_strain);
     * status->letTempCrackDirsBe (tempCrackDirs);
     */
    status->giveCrackStrainVector(crackStrainVector); // local one
    status->giveCrackDirs(crackDirs);
    if ( principalStrain.containsOnlyZeroes() ) {
        // keep old principal values
        status->letTempCrackDirsBe(crackDirs);
    } else {
        this->sortPrincDirAndValCloseTo(& principalStrain,
                                        & tempCrackDirs, & crackDirs);
        status->letTempCrackDirsBe(tempCrackDirs);
    }

    // compute de in local system
    // for iso materials no transformation if stiffness required
    //
    // local strain increment
    status->givePrevPrincStrainVector(prevPrincipalStrain);
    strainIncrement.beDifferenceOf(principalStrain, prevPrincipalStrain);
    status->letPrincipalStrainVectorBe(principalStrain);

    this->giveNormalElasticStiffnessMatrix(de, FullForm, TangentStiffness,
                                           gp, atTime, tempCrackDirs);
    //
    // construct mapping matrix of active cracks
    // this mapping will dynamically change as
    // some crack can unlo or reload
    //
    this->updateActiveCrackMap(gp);
    status->giveCrackMap(crackMapping);
    // start iteration until stress computed from elastic increment
    // is equal to stress computed from cracking strain increment
    // we do this computation in reduced stress strain space
    dSigma.resize(0);
    for ( iter = 1; iter <= 20; iter++ ) {
        //
        // first check if already cracked
        //
        if ( status->giveNumberOfTempActiveCracks() ) {
            // active crack exist
            this->giveCrackedStiffnessMatrix(dcr, TangentStiffness, gp, atTime);
            fullDecr = de;
            fullDecr.add(dcr);
            decr.beSubMatrixOf(fullDecr, crackMapping);

            if ( dSigma.giveSize() == 0 ) {
                fullDSigma.beProductOf(de, strainIncrement);
                dSigma.beSubArrayOf(fullDSigma, crackMapping);
            }

            decr.solveForRhs(dSigma, crackStrainIterativeIncrement);
            for ( i = 1; i <= 3; i++ ) {
                if ( ( ind = crackMapping.at(i) ) ) {
                    crackStrainVector.at(i) += crackStrainIterativeIncrement.at(ind);
                }
            }

            // check for crack closing, updates also cracking map
            this->checkIfClosedCracks(gp, crackStrainVector, crackMapping);

            // elastic strain component
            elastStrain.beDifferenceOf(principalStrain, crackStrainVector);
            sigmaEl.beProductOf(de, elastStrain);

            // Stress in cracks
            for ( i = 1; i <= 3; i++ ) {
                if ( crackMapping.at(i) ) {
                    sigmaCr.at(i) = giveNormalCrackingStress(gp, crackStrainVector.at(i), i);
                }
            }

            // update status
            status->letCrackStrainVectorBe(crackStrainVector);
        } else {
            //
            // no active crack exist - elastic behaviour
            //
            elastStrain.beDifferenceOf(principalStrain, crackStrainVector);
            sigmaEl.beProductOf(de, elastStrain);
            sigmaCr.zero();
        }

        // check for new cracks
        // and update crack map if necessary
        // when we update map, we need to add new crack at end
        // because sigmaCr is build
        this->checkForNewActiveCracks(activatedCracks, gp, crackStrainVector,
                                      sigmaEl, sigmaCr, principalStrain);
        if ( activatedCracks.giveSize() ) {
            // update crack map also
            this->updateActiveCrackMap(gp, & activatedCracks);
            status->giveCrackMap(crackMapping); // update crackMap
        }

        //

        // compute unbalanced stress
        // dSigma = sigmaEl - sigmaCr for active cracks
        fullDSigma = sigmaEl;
        fullDSigma.subtract(sigmaCr);
        dSigma.beSubArrayOf(fullDSigma, crackMapping);
        // find max error in dSigma
        // if max err < allovedErr -> stop iteration
        // allowed Err is computed relative to Ft;

        // check only for active cracks
        maxErr = 0.;
        for ( i = 1; i <= dSigma.giveSize(); i++ ) {
            if ( fabs( dSigma.at(i) ) > maxErr ) {
                maxErr = fabs( dSigma.at(i) );
            }
        }

        if ( maxErr < rcm_STRESSRELERROR * this->give(pscm_Ft, gp) ) {
            status->letPrincipalStressVectorBe(sigmaEl);
            answer = sigmaEl;
            return;
        }
    } // loop

    // convergence not reached
    _error("GiveRealStressVector3d - convergence not reached");
}