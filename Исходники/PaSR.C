Foam::combustionModels::PaSR<Type>::PaSR
(
    const word& modelType,
    const fvMesh& mesh,
    const word& phaseName
)
:
    laminar<Type>(modelType, mesh, phaseName),
    Cmix_(readScalar(this->coeffs().lookup("Cmix"))),
    turbulentReaction_(this->coeffs().lookup("turbulentReaction")),
    kappa_
    (
        IOobject
        (
            IOobject::groupName("PaSR:kappa", phaseName),
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("kappa", dimless, 0.0)
    )
{}