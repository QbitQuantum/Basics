// from components
Giesekus_Cross::Giesekus_Cross
(
    const word& name,
    const volScalarField& alpha,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const dictionary& dict
)
:
    twoPhaseMixture(U, phi, "alpha"),
    viscoelasticLaw(name, alpha, U, phi),
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
    alpha1_(dict.subDict("phase1").lookup("alpha")),
    alpha2_(dict.subDict("phase2").lookup("alpha"))
{}