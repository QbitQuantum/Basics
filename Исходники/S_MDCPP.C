Foam::S_MDCPP::S_MDCPP
(
    const word& name,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const dictionary& dict
)
    :
    viscoelasticLaw(name, U, phi),
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
    rho_(dict.lookup("rho")),
    etaS_(dict.lookup("etaS")),
    etaP_(dict.lookup("etaP")),
    zeta_(dict.lookup("zeta")),
    lambdaOb_(dict.lookup("lambdaOb")),
    lambdaOs_(dict.lookup("lambdaOs")),
    q_(dict.lookup("q"))
{}