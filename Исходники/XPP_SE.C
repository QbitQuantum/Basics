XPP_SE::XPP_SE
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
    etaS1_(dict.subDict("phase1").lookup("etaS")),
    etaS2_(dict.subDict("phase2").lookup("etaS")),
    etaP1_(dict.subDict("phase1").lookup("etaP")),
    etaP2_(dict.subDict("phase2").lookup("etaP")),
    alpha1_(dict.subDict("phase1").lookup("alpha")),
    alpha2_(dict.subDict("phase2").lookup("alpha")),
    lambdaOb1_(dict.subDict("phase1").lookup("lambdaOb")),
    lambdaOb2_(dict.subDict("phase2").lookup("lambdaOb")),
    lambdaOs1_(dict.subDict("phase1").lookup("lambdaOs")),
    lambdaOs2_(dict.subDict("phase2").lookup("lambdaOs")),
    q1_(dict.subDict("phase1").lookup("q")),
    q2_(dict.subDict("phase2").lookup("q")),
    pt_
    (
        dimensionedScalar
        (
            "zero",
            lambdaOb1_.dimensions(),
            scalar( SMALL )
        )
    )
{}