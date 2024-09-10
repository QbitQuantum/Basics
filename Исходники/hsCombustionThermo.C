Foam::hsCombustionThermo::hsCombustionThermo(const fvMesh& mesh)
:
    basicPsiThermo(mesh),

    hs_
    (
        IOobject
        (
            "hs",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimEnergy/dimMass,
        this->hBoundaryTypes()
    )
{}