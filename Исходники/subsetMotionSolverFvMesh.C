Foam::subsetMotionSolverFvMesh::subsetMotionSolverFvMesh(const IOobject& io)
:
    dynamicFvMesh(io),
    movingMeshCoeffs_
    (
        IOdictionary
        (
            IOobject
            (
                "dynamicMeshDict",
                io.time().constant(),
                *this,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        ).subDict(typeName + "Coeffs")
    ),
    subsetMesh_
    (
        IOobject
        (
            "motion",
            io.time().constant(),
            *this,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        *this
    ),
    motionPtr_(NULL),
    alpha_(readScalar(movingMeshCoeffs_.lookup("alpha")))
{
    // Create subset
    word setName = movingMeshCoeffs_.lookup("set");

    cellSet currentSet
    (
        IOobject
        (
            setName,
            io.time().constant(),
            polyMesh::meshSubDir/"sets",
            *this,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    subsetMesh_.setLargeCellSubset(currentSet, -1);

    // Create motion solver on the subset
    motionPtr_ = motionSolver::New(subsetMesh_.subMesh());

    // Read motion under-relaxation
    if (alpha_ < 0 || alpha_ > 1.0)
    {
        FatalErrorIn
        (
            "subsetMotionSolverFvMesh::subsetMotionSolverFvMesh"
            "(const IOobject& io)"
        )   << "Ill-defined motion under-relaxation: "
            << "should be between 0 and 1."
            << "  Alpha = " << alpha_ << abort(FatalError);
    }
}