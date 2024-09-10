Foam::XiModel::XiModel
(
    const dictionary& XiProperties,
    const hhuCombustionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su,
    const volScalarField& rho,
    const volScalarField& b,
    const surfaceScalarField& phi
)
:
    XiModelCoeffs_
    (
        XiProperties.subDict
        (
            word(XiProperties.lookup("XiModel")) + "Coeffs"
        )
    ),
    thermo_(thermo),
    turbulence_(turbulence),
    Su_(Su),
    rho_(rho),
    b_(b),
    phi_(phi),
    Xi_
    (
        IOobject
        (
            "Xi",
            b.time().timeName(),
            b.db(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        b.mesh()
    )
{}