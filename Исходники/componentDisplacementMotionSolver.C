Foam::componentDisplacementMotionSolver::componentDisplacementMotionSolver
(
    const polyMesh& mesh,
    const dictionary& dict,
    const word& type
)
:
    motionSolver(mesh, dict, type),
    cmptName_(coeffDict().lookup("component")),
    cmpt_(cmpt(cmptName_)),
    points0_
    (
        pointIOField
        (
            IOobject
            (
                "points",
                mesh.time().constant(),
                polyMesh::meshSubDir,
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        ).component(cmpt_)
    ),
    pointDisplacement_
    (
        IOobject
        (
            "pointDisplacement" + cmptName_,
            mesh.time().timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        pointMesh::New(mesh)
    )
{
    if (points0_.size() != mesh.nPoints())
    {
        FatalErrorInFunction
            << "Number of points in mesh " << mesh.nPoints()
            << " differs from number of points " << points0_.size()
            << " read from file "
            <<  typeFilePath<pointIOField>
                (
                    IOobject
                    (
                        "points",
                        mesh.time().constant(),
                        polyMesh::meshSubDir,
                        mesh,
                        IOobject::MUST_READ,
                        IOobject::NO_WRITE,
                        false
                    )
                )
            << exit(FatalError);
    }
}