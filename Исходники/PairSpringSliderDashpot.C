void Foam::PairSpringSliderDashpot<CloudType>::evaluatePair
(
    typename CloudType::parcelType& pA,
    typename CloudType::parcelType& pB
) const
{
    vector r_AB = (pA.position() - pB.position());

    scalar dAEff = pA.d();

    if (useEquivalentSize_)
    {
        dAEff *= cbrt(pA.nParticle()*volumeFactor_);
    }

    scalar dBEff = pB.d();

    if (useEquivalentSize_)
    {
        dBEff *= cbrt(pB.nParticle()*volumeFactor_);
    }

    scalar r_AB_mag = mag(r_AB);

    scalar normalOverlapMag = 0.5*(dAEff + dBEff) - r_AB_mag;

    if (normalOverlapMag > 0)
    {
        //Particles in collision

        vector rHat_AB = r_AB/(r_AB_mag + VSMALL);

        vector U_AB = pA.U() - pB.U();

        // Effective radius
        scalar R = 0.5*dAEff*dBEff/(dAEff + dBEff);

        // Effective mass
        scalar M = pA.mass()*pB.mass()/(pA.mass() + pB.mass());

        scalar kN = (4.0/3.0)*sqrt(R)*Estar_;

        scalar etaN = alpha_*sqrt(M*kN)*pow025(normalOverlapMag);

        // Normal force
        vector fN_AB =
            rHat_AB
           *(kN*pow(normalOverlapMag, b_) - etaN*(U_AB & rHat_AB));

        // Cohesion force
        if (cohesion_)
        {
            fN_AB +=
                -cohesionEnergyDensity_
                *overlapArea(dAEff/2.0, dBEff/2.0, r_AB_mag)
                *rHat_AB;
        }

        pA.f() += fN_AB;
        pB.f() += -fN_AB;

        vector USlip_AB =
            U_AB - (U_AB & rHat_AB)*rHat_AB
          + (pA.omega() ^ (dAEff/2*-rHat_AB))
          - (pB.omega() ^ (dBEff/2*rHat_AB));

        scalar deltaT = this->owner().mesh().time().deltaTValue();

        vector& tangentialOverlap_AB =
            pA.collisionRecords().matchPairRecord
            (
                pB.origProc(),
                pB.origId()
            ).collisionData();

        vector& tangentialOverlap_BA =
            pB.collisionRecords().matchPairRecord
            (
                pA.origProc(),
                pA.origId()
            ).collisionData();

        vector deltaTangentialOverlap_AB = USlip_AB*deltaT;

        tangentialOverlap_AB += deltaTangentialOverlap_AB;
        tangentialOverlap_BA += -deltaTangentialOverlap_AB;

        scalar tangentialOverlapMag = mag(tangentialOverlap_AB);

        if (tangentialOverlapMag > VSMALL)
        {
            scalar kT = 8.0*sqrt(R*normalOverlapMag)*Gstar_;

            scalar etaT = etaN;

            // Tangential force
            vector fT_AB;

            if (kT*tangentialOverlapMag > mu_*mag(fN_AB))
            {
                // Tangential force greater than sliding friction,
                // particle slips

                fT_AB = -mu_*mag(fN_AB)*USlip_AB/mag(USlip_AB);

                tangentialOverlap_AB = vector::zero;
                tangentialOverlap_BA = vector::zero;
            }
            else
            {
                fT_AB =
                    -kT*tangentialOverlapMag
                   *tangentialOverlap_AB/tangentialOverlapMag
                  - etaT*USlip_AB;
            }

            pA.f() += fT_AB;
            pB.f() += -fT_AB;

            pA.torque() += (dAEff/2*-rHat_AB) ^ fT_AB;
            pB.torque() += (dBEff/2*rHat_AB) ^ -fT_AB;
        }
    }
}