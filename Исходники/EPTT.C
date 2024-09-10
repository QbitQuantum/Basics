Foam::EPTT::EPTT
(
    const word& name,
    const volScalarField& alpha,
    const volScalarField& rho,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const dictionary& dict
)
:
    viscoelasticLaw(name, alpha, rho, U, phi),
    tau_
    (
        IOobject
        (
            "tau" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        U.mesh()
    ),
    etaS1_(dict.subDict("phase1").lookup("etaS")),
    etaS2_(dict.subDict("phase2").lookup("etaS")),
    etaP1_(dict.subDict("phase1").lookup("etaP")),
    etaP2_(dict.subDict("phase2").lookup("etaP")),
    lambda1_(dict.subDict("phase1").lookup("lambda")),
    lambda2_(dict.subDict("phase2").lookup("lambda")),
    epsilon1_(dict.subDict("phase1").lookup("epsilon")),
    epsilon2_(dict.subDict("phase2").lookup("epsilon")),
    zeta1_(dict.subDict("phase1").lookup("zeta")),
    zeta2_(dict.subDict("phase2").lookup("zeta"))
{}