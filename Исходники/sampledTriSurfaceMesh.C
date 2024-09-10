Foam::sampledTriSurfaceMesh::sampledTriSurfaceMesh
(
    const word& name,
    const polyMesh& mesh,
    const dictionary& dict
)
:
    sampledSurface(name, mesh, dict),
    surface_
    (
        IOobject
        (
            dict.lookup("surface"),
            mesh.time().constant(), // instance
            "triSurface",           // local
            mesh,                   // registry
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    ),
    needsUpdate_(true),
    cellLabels_(0),
    pointToFace_(0)
{}