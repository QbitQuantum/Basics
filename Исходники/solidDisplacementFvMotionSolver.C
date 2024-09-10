Foam::solidDisplacementFvMotionSolver::solidDisplacementFvMotionSolver
(
    const polyMesh& mesh,
    Istream& is
)
:
    displacementFvMotionSolver(mesh, is),
    pointDisplacement_
    (
        IOobject
        (
            "pointDisplacement",
            fvMesh_.time().timeName(),
            fvMesh_,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        pointMesh::New(fvMesh_),
        dimensionedVector
        (
            "pointDisplacement",
            dimLength,
            vector::zero
        )
    ),
    cellDisplacement_
    (
        IOobject
        (
            "cellDisplacement",
            mesh.time().timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        fvMesh_,
        dimensionedVector
        (
            "cellDisplacement",
            dimLength,
            vector::zero
        ) //,
//         cellMotionBoundaryTypes<vector>(pointDisplacement_.boundaryField())
    ),
    pointLocation_(NULL),
//     diffusivityPtr_
//     (
//         motionDiffusivity::New(*this, lookup("diffusivity"))
//     ),
    frozenPointsZone_
    (
        found("frozenPointsZone")
      ? fvMesh_.pointZones().findZoneID(lookup("frozenPointsZone"))
      : -1
    )
{
    IOobject io
    (
        "pointLocation",
        fvMesh_.time().timeName(),
        fvMesh_,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    );

    if (debug)
    {
        Info<< "solidDisplacementFvMotionSolver:" << nl
//             << "    diffusivity       : " << diffusivityPtr_().type() << nl
            << "    frozenPoints zone : " << frozenPointsZone_ << endl;
    }


    if (io.headerOk())
    {
        pointLocation_.reset
        (
            new pointVectorField
            (
                io,
                pointMesh::New(fvMesh_)
            )
        );

        if (debug)
        {
            Info<< "solidDisplacementFvMotionSolver :"
                << " Read pointVectorField "
                << io.name() << " to be used for boundary conditions on points."
                << nl
                << "Boundary conditions:"
                << pointLocation_().boundaryField().types() << endl;
        }
    }
}