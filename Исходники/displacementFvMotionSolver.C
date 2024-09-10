Foam::displacementFvMotionSolver::displacementFvMotionSolver
(
    const polyMesh& mesh,
    Istream&
)
:
    fvMotionSolver(mesh),
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
        )
    )
{
    if (points0_.size() != mesh.nPoints())
    {
        FatalErrorIn
        (
            "displacementFvMotionSolver::displacementFvMotionSolver\n"
            "(\n"
            "    const polyMesh&,\n"
            "    Istream&\n"
            ")"
        )   << "Number of points in mesh " << mesh.nPoints()
            << " differs from number of points " << points0_.size()
            << " read from file "
            <<
                IOobject
                (
                    "points",
                    mesh.time().constant(),
                    polyMesh::meshSubDir,
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE,
                    false
                ).filePath()
            << exit(FatalError);
    }
}