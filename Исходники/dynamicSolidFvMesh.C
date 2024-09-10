dynamicSolidFvMesh::dynamicSolidFvMesh(const IOobject& io)
:
    dynamicFvMesh(io),
    fvMesh_(refCast<const fvMesh>(*this)),
    pointDisplacement_
    (
        IOobject
        (
            "pointDisplacement",
            io.time().timeName(),
            meshSubDir,
            *this,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        pointMesh::New(fvMesh_),
        dimensionedVector
        (
            "pointDisplacement",
            pointDisplacement_.dimensions(),
            vector::zero
        )
    ),
    stationaryPoints_
    (
            IOobject
            (
                "points",
                io.time().constant(),
                meshSubDir,
                *this,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            )
    ),
//     pointLocation_(NULL),
    points0_
    (
        pointIOField
        (
            IOobject
            (
                "points",
                io.time().constant(),
                meshSubDir,
                *this,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            )
        )
    )
{

// //     if (io.headerOk())
// //     {
//         pointLocation_.reset
//         (
//             new pointVectorField
//             (
//                 io,
//                 pointMesh::New(fvMesh_)
//             )
//         );
// 
//         if (debug)
//         {
//             Info<< "displacementLaplacianFvMotionSolver :"
//                 << " Read pointVectorField "
//                 << io.name() << " to be used for boundary conditions on points."
//                 << nl
//                 << "Boundary conditions:"
//                 << pointLocation_().boundaryField().types() << endl;
//         }
// //     }

}