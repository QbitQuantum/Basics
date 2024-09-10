Foam::Leonov::Leonov
(
    const word& name,
    const volScalarField& alpha,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const dictionary& dict
)
:
    viscoelasticLaw(name, alpha, U, phi),
    sigma_
    (
        IOobject
        (
            "sigma" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        U.mesh()
    ),
    tau_
    (
        IOobject
        (
            "tau" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        U.mesh(),
        dimensionedSymmTensor
        (
            "zero",
            dimensionSet(1, -1, -2, 0, 0, 0, 0),
            symmTensor::zero
        )
    ),
    I_
    (
        dimensionedSymmTensor
        (
            "I",
            dimensionSet(0, 0, 0, 0, 0, 0, 0),
            symmTensor
            (
                1, 0, 0,
                   1, 0,
                      1
            )
        )
    ),
    rho1_(dict.subDict("phase1").lookup("rho")),
    rho2_(dict.subDict("phase2").lookup("rho")),
    etaS1_(dict.subDict("phase1").lookup("etaS")),
    etaS2_(dict.subDict("phase2").lookup("etaS")),
    etaP1_(dict.subDict("phase1").lookup("etaP")),
    etaP2_(dict.subDict("phase2").lookup("etaP")),
    lambda1_(dict.subDict("phase1").lookup("lambda")),
    lambda2_(dict.subDict("phase2").lookup("lambda"))
{}