void Foam::kineticTheoryModel::solve(const volTensorField& gradUat)
{
    if (!kineticTheory_)
    {
        return;
    }

    const scalar sqrtPi = sqrt(constant::mathematical::pi);

    surfaceScalarField phi(1.5*rhoa_*phia_*fvc::interpolate(alpha_));

    volTensorField dU(gradUat.T());    //fvc::grad(Ua_);
    volSymmTensorField D(symm(dU));

    // NB, drag = K*alpha*beta,
    // (the alpha and beta has been extracted from the drag function for
    // numerical reasons)
    volScalarField Ur(mag(Ua_ - Ub_));
    volScalarField betaPrim(alpha_*(1.0 - alpha_)*draga_.K(Ur));

    // Calculating the radial distribution function (solid volume fraction is
    //  limited close to the packing limit, but this needs improvements)
    //  The solution is higly unstable close to the packing limit.
    gs0_ = radialModel_->g0
    (
        min(max(alpha_, scalar(1e-6)), alphaMax_ - 0.01),
        alphaMax_
    );

    // particle pressure - coefficient in front of Theta (Eq. 3.22, p. 45)
    volScalarField PsCoeff
    (
        granularPressureModel_->granularPressureCoeff
        (
            alpha_,
            gs0_,
            rhoa_,
            e_
        )
    );

    // 'thermal' conductivity (Table 3.3, p. 49)
    kappa_ = conductivityModel_->kappa(alpha_, Theta_, gs0_, rhoa_, da_, e_);

    // particle viscosity (Table 3.2, p.47)
    mua_ = viscosityModel_->mua(alpha_, Theta_, gs0_, rhoa_, da_, e_);

    dimensionedScalar Tsmall
    (
        "small",
        dimensionSet(0 , 2 ,-2 ,0 , 0, 0, 0),
        1.0e-6
    );

    dimensionedScalar TsmallSqrt = sqrt(Tsmall);
    volScalarField ThetaSqrt(sqrt(Theta_));

    // dissipation (Eq. 3.24, p.50)
    volScalarField gammaCoeff
    (
        12.0*(1.0 - sqr(e_))*sqr(alpha_)*rhoa_*gs0_*(1.0/da_)*ThetaSqrt/sqrtPi
    );

    // Eq. 3.25, p. 50 Js = J1 - J2
    volScalarField J1(3.0*betaPrim);
    volScalarField J2
    (
        0.25*sqr(betaPrim)*da_*sqr(Ur)
       /(max(alpha_, scalar(1e-6))*rhoa_*sqrtPi*(ThetaSqrt + TsmallSqrt))
    );

    // bulk viscosity  p. 45 (Lun et al. 1984).
    lambda_ = (4.0/3.0)*sqr(alpha_)*rhoa_*da_*gs0_*(1.0+e_)*ThetaSqrt/sqrtPi;

    // stress tensor, Definitions, Table 3.1, p. 43
    volSymmTensorField tau(2.0*mua_*D + (lambda_ - (2.0/3.0)*mua_)*tr(D)*I);

    if (!equilibrium_)
    {
        // construct the granular temperature equation (Eq. 3.20, p. 44)
        // NB. note that there are two typos in Eq. 3.20
        // no grad infront of Ps
        // wrong sign infront of laplacian
        fvScalarMatrix ThetaEqn
        (
            fvm::ddt(1.5*alpha_*rhoa_, Theta_)
          + fvm::div(phi, Theta_, "div(phi,Theta)")
         ==
            fvm::SuSp(-((PsCoeff*I) && dU), Theta_)
          + (tau && dU)
          + fvm::laplacian(kappa_, Theta_, "laplacian(kappa,Theta)")
          + fvm::Sp(-gammaCoeff, Theta_)
          + fvm::Sp(-J1, Theta_)
          + fvm::Sp(J2/(Theta_ + Tsmall), Theta_)
        );

        ThetaEqn.relax();
        ThetaEqn.solve();
    }
    else
    {
        // equilibrium => dissipation == production
        // Eq. 4.14, p.82
        volScalarField K1(2.0*(1.0 + e_)*rhoa_*gs0_);
        volScalarField K3
        (
            0.5*da_*rhoa_*
            (
                (sqrtPi/(3.0*(3.0-e_)))
               *(1.0 + 0.4*(1.0 + e_)*(3.0*e_ - 1.0)*alpha_*gs0_)
               +1.6*alpha_*gs0_*(1.0 + e_)/sqrtPi
            )
        );

        volScalarField K2
        (
            4.0*da_*rhoa_*(1.0 + e_)*alpha_*gs0_/(3.0*sqrtPi) - 2.0*K3/3.0
        );

        volScalarField K4(12.0*(1.0 - sqr(e_))*rhoa_*gs0_/(da_*sqrtPi));

        volScalarField trD(tr(D));
        volScalarField tr2D(sqr(trD));
        volScalarField trD2(tr(D & D));

        volScalarField t1(K1*alpha_ + rhoa_);
        volScalarField l1(-t1*trD);
        volScalarField l2(sqr(t1)*tr2D);
        volScalarField l3
        (
            4.0
           *K4
           *max(alpha_, scalar(1e-6))
           *(2.0*K3*trD2 + K2*tr2D)
        );

        Theta_ = sqr((l1 + sqrt(l2 + l3))/(2.0*(alpha_ + 1.0e-4)*K4));
    }

    Theta_.max(1.0e-15);
    Theta_.min(1.0e+3);

    volScalarField pf
    (
        frictionalStressModel_->frictionalPressure
        (
            alpha_,
            alphaMinFriction_,
            alphaMax_,
            Fr_,
            eta_,
            p_
        )
    );

    PsCoeff += pf/(Theta_+Tsmall);

    PsCoeff.min(1.0e+10);
    PsCoeff.max(-1.0e+10);

    // update particle pressure
    pa_ = PsCoeff*Theta_;

    // frictional shear stress, Eq. 3.30, p. 52
    volScalarField muf
    (
        frictionalStressModel_->muf
        (
            alpha_,
            alphaMax_,
            pf,
            D,
            phi_
        )
    );

    // add frictional stress
    mua_ += muf;
    mua_.min(1.0e+2);
    mua_.max(0.0);

    Info<< "kinTheory: max(Theta) = " << max(Theta_).value() << endl;

    volScalarField ktn(mua_/rhoa_);

    Info<< "kinTheory: min(nua) = " << min(ktn).value()
        << ", max(nua) = " << max(ktn).value() << endl;

    Info<< "kinTheory: min(pa) = " << min(pa_).value()
        << ", max(pa) = " << max(pa_).value() << endl;
}