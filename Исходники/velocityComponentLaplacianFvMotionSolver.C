Foam::velocityComponentLaplacianFvMotionSolver::
velocityComponentLaplacianFvMotionSolver
(
    const polyMesh& mesh,
    Istream& msData
)
:
    fvMotionSolver(mesh),
    cmptName_(msData),
    cmpt_(0),
    pointMotionU_
    (
        IOobject
        (
            "pointMotionU" + cmptName_,
            fvMesh_.time().timeName(),
            fvMesh_,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        pointMesh_
    ),
    cellMotionU_
    (
        IOobject
        (
            "cellMotionU" + cmptName_,
            mesh.time().timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        fvMesh_,
        dimensionedScalar
        (
            "cellMotionU",
            pointMotionU_.dimensions(),
            0
        ),
        cellMotionBoundaryTypes<scalar>(pointMotionU_.boundaryField())
    ),
    diffusivityPtr_
    (
        motionDiffusivity::New(*this, lookup("diffusivity"))
    )
{
    if (cmptName_ == "x")
    {
        cmpt_ = vector::X;
    }
    else if (cmptName_ == "y")
    {
        cmpt_ = vector::Y;
    }
    else if (cmptName_ == "z")
    {
        cmpt_ = vector::Z;
    }
    else
    {
        FatalErrorIn
        (
            "velocityComponentLaplacianFvMotionSolver::"
            "velocityComponentLaplacianFvMotionSolver"
            "(const polyMesh& mesh, Istream& msData)"
        )   << "Given component name " << cmptName_ << " should be x, y or z"
            << exit(FatalError);
    }
}