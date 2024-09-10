// from components
Feta_PTT::Feta_PTT
(
    const word& name,
    const volScalarField& alpha,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const dictionary& dict
)
:
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
    epsilon1_(dict.subDict("phase1").lookup("epsilon")),
    epsilon2_(dict.subDict("phase2").lookup("epsilon")),
    zeta1_(dict.subDict("phase1").lookup("zeta")),
    zeta2_(dict.subDict("phase2").lookup("zeta")),
    A1_(dict.subDict("phase1").lookup("A")),
    A2_(dict.subDict("phase2").lookup("A")),
    a1_(dict.subDict("phase1").lookup("a")),
    a2_(dict.subDict("phase2").lookup("a")),
    b1_(dict.subDict("phase1").lookup("b")),
    b2_(dict.subDict("phase2").lookup("b")),
    alpha1f_
    (
        IOobject
        (
            "alpha1f" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        min(max(alpha, scalar(0)), scalar(1))
    ),
    etaPEff_
    (
        IOobject
        (
            "etaPEff" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        (etaP1_/( Foam::pow(scalar(1) + A1_*Foam::pow(0.5*( Foam::sqr(tr(tau_)) - tr(tau_ & tau_) ) * Foam::sqr(lambda1_) / Foam::sqr(etaP1_), a1_), b1_) ) )*alpha1f_ + (etaP2_/( Foam::pow(scalar(1) + A2_*Foam::pow(0.5*( Foam::sqr(tr(tau_)) - tr(tau_ & tau_) ) * Foam::sqr(lambda2_) / Foam::sqr(etaP2_), a2_), b2_) ) )*(scalar(1) - alpha1f_)
    ),
    lambdaEff_
    (
        IOobject
        (
            "lambdaEff" + name,
            U.time().timeName(),
            U.mesh(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        (lambda1_ / (scalar(1)  + epsilon1_*lambda1_*tr(tau_) / etaP1_) )*alpha1f_ + (lambda2_ / (scalar(1)  + epsilon2_*lambda2_*tr(tau_) / etaP2_) )*(scalar(1) - alpha1f_)
    )
{}