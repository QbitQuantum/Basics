int StringFragmentation::decayStringIntoParticles( TLorentzVector *vArr, double fictionRhoPt )
{
    if ( !fRand )
    {
        printf("StringFragmentation: fRand is not set!!!\n" );
        return 0;
    }
    //    double yStringSize = fabs( fRand->Gaus(1,0.2) ) + fabs( fRand->Gaus(0,fYmax-fYmin) );
    //    double yStringShift = fRand->Gaus(0,fStringShiftSigma);

    //    double yStringSize = fabs( fRand->Gaus(4,0.4) ) + 2*fabs( fRand->Gaus(0,2) );
    //    double yStringSize = fabs( fRand->Gaus(4,0.2) ) + 2*fabs( fRand->Gaus(0,4) );
    //WAS USED FOR PROCEEDING...    double yStringSize = 10;//fRand->Uniform(2,10);
    double yStringSize = fYmax-fYmin;//fRand->Uniform(2,10);
    //    double yStringSize = fabs( fRand->Gaus(fYmax-fYmin,0.2) ) + 2*fabs( fRand->Gaus(0,0.5) );
    //    double yStringSize = fYmax-fYmin;//fabs( fRand->Gaus(3.6,0.2) ) + 2*fabs( fRand->Gaus(0,5) );
    //    double yStringShift = fRand->Uniform(-fStringShiftSigma,fStringShiftSigma) + fRand->Gaus(0,fStringShiftSigma);
    double yStringShift = (fYmax+fYmin)/2;//fRand->Gaus(0,fStringShiftSigma);
    //    double yStringShift = fRand->Gaus(0,2);
    //    double yStringSize = fabs( fRand->Gaus(3.6,0.2) ) + 2*fabs( fRand->Gaus(0,5) );
    //    double yStringSize = fabs( fRand->Gaus(3.6,0.2) ) + 2*fabs( fRand->Gaus(0,5) );
    //        double yStringSize = fabs( fRand->Gaus(3.6,0.2) ) + 2*fabs( fRand->Gaus(0,5) );
    //    double yStringSize = fRand->Uniform(0., fYmax-fYmin);
    //        double yStringSize = fabs( fRand->Gaus(2.,0.001) ) + 2*fabs( fRand->Gaus(0,0.2) );



    //    funcStringDecay->SetParameter( 0, yStringSize );
    //    funcStringDecay->SetParameter( 1, 1 );

    //    cout << nParticlesInString << endl;
    if(0)if ( fRand->Uniform() > 0.25) //ministrings
    {
        //        yStringSize = TMath::Max(4., fabs(fRand->Gaus(0,2)) );
        yStringSize = fabs( fRand->Gaus(2,0.2) ) + 2*fabs( fRand->Gaus(0,1) );
        //        yStringSize = TMath::Max(0.5, fabs(fRand->Gaus(0,1)) );
        //TMath::Max( 0.5, fabs( fRand->Gaus(1.5,0.3) ) + 2*fabs( fRand->Gaus(0,0.2) ) );
    }

    //    int nParticlesInString = 0.72 /*coeffToTuneMult*/ * TMath::Max(1,TMath::Nint( fRand->Gaus(yStringSize,yStringSize/10) )); // /2270*1550;
    //    nParticlesInString *= 1.14; //for energy-dependence! (30.01.2015, tuning basing on STAR)

    int nParticlesInString = TMath::Max(1,TMath::Nint( fRand->Gaus(yStringSize,yStringSize/10) )); // /2270*1550;
    //    nParticlesInString *= 1.25; //arbitrary factor to increase multiplicity
    nParticlesInString *= 1.25*0.7; //arbitrary factor to tune multiplicity IN CASE OF ALL PARTICLES - RHOS

    //nParticlesInString; // to take into account two pions from single rho!!!!!!!
    //    int nParticlesInString = TMath::Max(1,TMath::Nint( fRand->Gaus(yStringSize,yStringSize/5) ));
    //WAS USED FOR PROCEEDING...    int nParticlesInString = TMath::Max(2,TMath::Nint( fRand->Gaus(1.2,0.5) ));

    int nCutPoints = nParticlesInString + 1;
    for ( int iBreak = 0; iBreak < nCutPoints; iBreak++ )
    {
        //        double y = fRand->Uniform( fRand->Gaus(fYmin,0.2)+yStringShift, fRand->Gaus(fYmax,0.2)+yStringShift );
        //        double y = fRand->Uniform( fYmin+yStringShift, fYmax+yStringShift );
        //        double y = funcStringDecay->GetRandom();
        double y = fRand->Uniform( -yStringSize/2 + yStringShift, yStringSize/2+yStringShift );
        //        double y = fRand->Gaus( 0, fRand->Gaus(fYmin,0.2) ) + yStringShift;
        //y += yStringShift; //fRand->Gaus(0,2);
        yBreakPoints[iBreak] = y;
    }

    //sort cut points
    TMath::Sort<double, int>( nCutPoints, yBreakPoints, indecesCutsSorted, kFALSE );

    //fill array with sorted y of the string cuts
    for ( int iBreak = 0; iBreak < nCutPoints; iBreak++ )
        yBreakPointsSorted[iBreak] = yBreakPoints[ indecesCutsSorted[iBreak] ];

    //    double particleMass = mRho;
    //        double particleMass = mPion;
    // possible LOGICAL ERROR HERE!!! (if use the mass in cut point calculations)



    //double factorToPtExp = ( particleMass == mPion ? 2.5 : 1.57 );
    //make pTs at string cuts
    for ( int iBreak = 0; iBreak < nCutPoints; iBreak++ )
    {

        /*
            https://arxiv.org/pdf/1101.2599v1.pdf :

            page 86:
            The transverse dimensions of the tube are of typical hadronic sizes, roughly 1 fm.

            From hadron mass spectroscopy the string constant k, i.e. the amount of energy per unit length, is known to
            be k ≈ 1 GeV/fm ≈ 0.2 GeV2.

            page 87:
            ...The expression “massless” relativistic string is somewhat of a misnomer:
            k effectively corresponds to a “mass density” along the string.

            Typically, a break occurs when the q and the qbar
            ends of a colour singlet system are 1–5 fm apart in the qqbar rest frame,
            but note that the higher-momentum particles at the outskirts of the system are
            appreciably Lorentz contracted.

            At the end of the process, the string has broken by the creation of a set
            of new qiqbari pairs, with i running from 1 to n − 1 for a system that fragments
            into n primary hadrons (i.e. hadrons before secondary decays). Each hadron
            is formed by the quark from one break (or an endpoint) and the antiquark
            from an adjacent break: qqbar1, q1qbar2, q2qbar3, . . . , qn−1qbar.

            page 90:
            The factorization of the transverse-momentum and the mass terms leads
            to a flavour-independent Gaussian spectrum for the q'qbar' pairs.
             Since the
            string is assumed to have no transverse excitations, this p⊥ is locally compensated
            between the quark and the antiquark of the pair, and <pT_q^2> = sigma^2 = κ/π ≈ (250 MeV)2.

             Experimentally a number closer to σ2 ≈ (350 MeV)2 is required,
             which could be explained as the additional effect of soft-gluon
            radiation below the shower cutoff scale. That radiation would have a nonGaussian
            shape but, when combined with the ordinary fragmentation p⊥, the
            overall shape is close to Gaussian, and is parameterized correspondingly in
            the program. Hadrons receive p⊥ contributions from two q'qbar' pairs and have
            <pT_hadron^2> = sigma^2 2σ^2.

            The formula also implies a suppression of heavy quark production,
            u : d : s : c ≈ 1 : 1 : 0.3 : 10−11.

            The simplest scheme for baryon production is that, in addition to quark–
            antiquark pairs, also antidiquark–diquark pairs are occasionally produced in
            the field, in a triplet–antitriplet representation.

             */


        // !!! use some numerical factor to MATCH MEAN PT when later merge two quarks of string fragments
        //        if ( particleMass == mPion )
        //            breakPointPt[iBreak] = fRand->Exp( 0.25 ); //0.3); //funcPt->GetRandom();//fRand->Exp(pTtau);
        //        else //rho
        //        breakPointPt[iBreak] = fRand->Exp( 0.25 ); //0.75 );//fictionRhoPt ); //0.3); //funcPt->GetRandom();//fRand->Exp(pTtau);
        //            breakPointPt[iBreak] = fRand->Exp( 0.25 ); //0.75 );//fictionRhoPt ); //0.3); //funcPt->GetRandom();//fRand->Exp(pTtau);
        // GOOD: breakPointPt[iBreak] = fabs(fRand->Gaus( 0, 0.35 )); //0.75 );//fictionRhoPt ); //0.3); //funcPt->GetRandom();//fRand->Exp(pTtau);
        //        breakPointPt[iBreak] = funcPt->GetRandom( /*fictionRhoPt*/ ); //0.3); //funcPt->GetRandom();//fRand->Exp(pTtau);



        //        const double kPtFor_u_d_quarks = 0.35;

        // ##### July 2016: NEW STRING DECAY INTO QUARKS:
        bool flagFineQuarkConfig = false;

        while ( !flagFineQuarkConfig )
        {
            double probQuarkType = fRand->Uniform( 0, 2.3); // u:d:s = 1:1:0.3 from Generators overview paper
            if ( probQuarkType < 0.01 ) // Sept 2017: ASSUME SOME PROBABILITY TO DECAY INTO C-QUARK!
            {
                breakPointType[iBreak] = 3; // c - quark
                breakPointPt[iBreak] = fabs(fRand->Exp( 0.35 ));

            }
            else if ( probQuarkType < 0.2 )
            {
                breakPointType[iBreak] = 1; // s - quark
//                breakPointPt[iBreak] = fabs(fRand->Gaus( 0, 0.47 )); //0.45 ));
//                breakPointPt[iBreak] = fabs(fRand->Gaus( 0.1, 0.35 )); //0.45 ));
                breakPointPt[iBreak] = fabs(fRand->Exp( 0.35 )); //0.45 ));
            }
            else //if ( probQuarkType < 0.05 )
            {
                double probQuarkDiquark = fRand->Uniform( 0, 1 );
                if ( probQuarkDiquark < 0.04 )
                {
                    breakPointType[iBreak] = 2; // diquark
//                    breakPointPt[iBreak] = fabs(fRand->Gaus( 0, 0.56 )); //0.55 ));
//                    breakPointPt[iBreak] = fabs(fRand->Gaus( 0.3, 0.35 )); //0.55 ));
                    breakPointPt[iBreak] = fabs(fRand->Exp( 0.48 ));
                }
                else
                {
                    breakPointType[iBreak] = 0; // u and d quarks
//                    breakPointPt[iBreak] = fabs(fRand->Gaus( 0, 0.28 ) ); //0.28 ));// 0.35 ));
                    breakPointPt[iBreak] = fabs(fRand->Exp( 0.2 )); //0.45 ));
                }
            }
            if ( iBreak == 0 ) // first break: always allowed
                flagFineQuarkConfig = true;
            else
            {
                if ( breakPointType[iBreak-1] == 2 && breakPointType[iBreak] == 2 ) // NOT ALLOWED CONFIG! ("pentaquark? :) )
                    continue;
                else
                    flagFineQuarkConfig = true;
            }
        }

        //                ...

        //        if ( fictionRhoPt == 0 )
        //            breakPointPt[iBreak] = 0;
        //        else
        //            breakPointPt[iBreak] = fRand->Gaus(fictionRhoPt,0.01); //funcPt->GetRandom();//fRand->Exp(pTtau);

        //        breakPointPt[iBreak] = fRand->Uniform( 0.1, 0.5 );
        breakPointPhi[iBreak] = fRand->Uniform( 0, 2*TMath::Pi() );
    }

    //calc kinematic params of "particles"=string fragments
    for ( int iBreak = 0; iBreak < nParticlesInString; iBreak++ )
    {
        double pT1 = breakPointPt[iBreak];
        double pT2 = breakPointPt[iBreak+1];
        double phi1 = breakPointPhi[iBreak];
        double phi2 = breakPointPhi[iBreak+1];
        phi2 += TMath::Pi();
        FixAngleInTwoPi(phi2);

        double ptX = pT1*cos( phi1 ) + pT2*cos( phi2 );
        double ptY = pT1*sin( phi1 ) + pT2*sin( phi2 );
        double ptParticle = sqrt( ptX*ptX+ptY*ptY );
        //        double ptParticle = fRand->Exp(0.9);
        if ( ptParticle < 0.01 )
            ptParticle = 0.01;


        // FOR TESTS!!!
        if(0)
        {
            if ( fictionRhoPt == 0 )
                ptParticle = 0.01;
            else
                ptParticle = fRand->Exp(fictionRhoPt);
            //            ptParticle = fRand->Gaus(fictionRhoPt,0.01); //funcPt->GetRandom();//fRand->Exp(pTtau);
        }
        // FOR TESTS!!!
        if(0)
            ptParticle = fRand->Exp(0.75);


        // !!! RANDOMIZE PT for generated particles:
        //        fParticles[iBreak].pt  = funcPt->GetRandom();
        //        cout << fParticles[iP].pt << endl;

        double phiVectorSum = asin( ptY/ptParticle );
        if ( ptX < 0 )
            phiVectorSum = TMath::Pi()-phiVectorSum;
        FixAngleInTwoPi(phiVectorSum);
        FixAngleInTwoPi(phiVectorSum);

        //        histPhi->Fill(phiVectorSum);
        //        histPtRho->Fill(ptParticle );
        //        histPtRhoWithWeight->Fill(ptParticle, 1./2/TMath::Pi()/ptParticle );

        double phiParticle = phiVectorSum;
        if(0)
            phiParticle = fRand->Uniform( 0, 2*TMath::Pi() );//phiVectorSum;

        double yParticle = (yBreakPointsSorted[iBreak] + yBreakPointsSorted[iBreak+1])/2;

        if(0)
            yParticle = fRand->Uniform( -yStringSize/2, yStringSize/2 );
        //            yParticle = fRand->Uniform( fYmin+yStringShift, fYmax+yStringShift ); //use it to "shuffle" particles in y!
        //        yParticle += fRand->Gaus(0,1);
        //        yParticle = fRand->Uniform( -yStringSize/2, yStringSize/2 );
        yParticle = fRand->Uniform( -yStringSize/2+yStringShift, yStringSize/2+yStringShift );



        // to get pions = 0.8 when half of them goes from rho decays:
        // probabilities for rho, pions, kaons+protons should be 0.25, 0.5, 0.25
        //        k=1 //ratio of pions from rho-s to pions from string
        //        a=0.8 //ratio of final state pions to all charged
        //        x=(a*k)/(2*k+2-a*k)
        //        y=(a*k)/(2*k+2-a*k)*2/k
        //        z=1-x-y
        //        check: (2*x+y)/(2*x+y+z)

        // TMP: just assign mass for particle. Todo?: separate mechanisms for mesons and proton (?)
        double particleMass = mPion;
        // ##### tune particle ratios!
        if (0) // only rho mesons!!!
        {
            while ( fabs(particleMass-mRho) > mRhoWidth/2 )
                particleMass = fRand->Gaus(mRho,mRhoWidth/2);//( fRand->Uniform(0,1) > 0.5 ? fRand->Gaus(mRho,mRhoWidth/2) : mPion );
        }
        //        else //if (0)
        //        {
        //            double probPID = fRand->Uniform(0,1);
        //            if ( probPID < 0.0 )
        //                particleMass = fRand->Gaus(mRho,mRhoWidth/2);//( fRand->Uniform(0,1) > 0.5 ? fRand->Gaus(mRho,mRhoWidth/2) : mPion );
        //            else if ( probPID < 0.75 )
        //                particleMass = mPion;
        //            else //kaon or proton (13% and 4%)
        //            {
        //                if ( fRand->Uniform(0,1) < 13./(13+4) )
        //                    particleMass = mKaon;
        //                else
        //                    particleMass = mProton;
        //            }
        //        }
        else
        {
            short q1 = breakPointType[iBreak];
            short q2 = breakPointType[iBreak+1];
            if ( q1 == 0 && q2 == 0 ) // u/d quarks => pions
                particleMass = mPion;
            else if ( (q1 == 0 && q2 == 1)
                      || (q1 == 1 && q2 == 0) ) // u/d and s quarks => kaons
                particleMass = mKaon;
            else if ( q1 == 1 && q2 == 1 ) // two s quarks => phi
                particleMass = mPhi;
            else if ( (q1 == 0 && q2 == 2)
                      || (q1 == 2 && q2 == 0) ) // u/d quarks and diquark  => protons/neutrons (!!! also neutrons!)
                particleMass = mProton;
            else if ( (q1 == 1 && q2 == 2)
                      || (q1 == 2 && q2 == 1) ) // s quark and diquark  => Lambda
                particleMass = mLambda;
            else if ( q1 == 3 || q2 == 3 ) // KOSTYL': if at least one of the two string ends is a c-quark
                //(q1 == 0 && q2 == 3)
//                      || (q1 == 3 && q2 == 0) ) // u/d quarks and c quark  => D-meson
                particleMass = mD0;
            else
            {
                cout << "breakPointTypes: impossible configuration! "
                     << q1 << " and " <<  q2 << endl;
                particleMass = mLambda;
            }
        }



        //        cout << particleMass << endl;

        //        ptParticle = fRand->Exp(0.45);

        // prepare lorentz vector
        if (1) //use direct sampling of pt "boltzman" distr
        {
            if ( fabs( particleMass-mPion) < 0.001 )
                ptParticle = funcPtBoltzmanLikePion->GetRandom();
            else if ( fabs( particleMass-mKaon) < 0.001 )
                ptParticle = funcPtBoltzmanLikeKaon->GetRandom();
            else if ( fabs( particleMass-mProton) < 0.001 )
                ptParticle = funcPtBoltzmanLikeProton->GetRandom();
            else if ( fabs( particleMass-mD0) < 0.001 )
                ptParticle = funcPtBoltzmanLikeDmeson->GetRandom();
        }
        if (0)
            phiParticle = fRand->Uniform( 0, TMath::TwoPi() );

        double mT = sqrt( ptParticle*ptParticle + particleMass*particleMass );
        double pX = ptParticle * cos(phiParticle);
        double pY = ptParticle * sin(phiParticle);
        double pZ = mT*sinh(yParticle);
        vArr[iBreak].SetXYZM( pX, pY, pZ, particleMass );

    }

    return nParticlesInString;

}