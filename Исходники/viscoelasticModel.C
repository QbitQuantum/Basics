viscoelasticModel::viscoelasticModel
(
    const volScalarField& alpha,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    IOdictionary
    (
        IOobject
        (
            "viscoelasticProperties",
            U.time().constant(),
            U.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),
    lawPtr_(viscoelasticLaw::New(word::null, alpha, U, phi, subDict("rheology")))
{}