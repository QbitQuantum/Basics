Foam::hReactionThermo::hReactionThermo
(
    const fvMesh& mesh,
    const objectRegistry& obj
)
:
    basicRhoThermo(mesh, obj),

    h_
    (
        IOobject
        (
            "h",
            mesh.time().timeName(),
            obj,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 2, -2, 0, 0),
        this->hBoundaryTypes()
    )
{}