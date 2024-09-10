Foam::dynamicBodyFvMesh::dynamicBodyFvMesh(const IOobject& io)
:
    dynamicFvMesh(io),
    dynamicMeshCoeffs_
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
    motionPtr_(motionSolver::New(*this)),
    bodyPatchName_
    (
        dynamicMeshCoeffs_.lookup("bodyPatchName")
    ),
    bodyPatchID_(-1),
    translationDirection_
    (
        dynamicMeshCoeffs_.lookup("translationDirection")
    ),
    translationAmplitude_
    (
        readScalar(dynamicMeshCoeffs_.lookup("translationAmplitude"))
    ),
    translationFrequency_
    (
        readScalar(dynamicMeshCoeffs_.lookup("translationFrequency"))
    ),
    initialRotationOrigin_
    (
        dynamicMeshCoeffs_.lookup("initialRotationOrigin")
    ),
    rotationAxis_
    (
        dynamicMeshCoeffs_.lookup("rotationAxis")
    ),
    rotationAmplitude_
    (
        readScalar(dynamicMeshCoeffs_.lookup("rotationAmplitude"))
    ),
    rotationFrequency_
    (
        readScalar(dynamicMeshCoeffs_.lookup("rotationFrequency"))
    )
{
    bodyPatchID_ = boundaryMesh().findPatchID(bodyPatchName_);

    if (bodyPatchID_<0)
    {
        FatalErrorIn
        (
            "dynamicBodyFvMesh::dynamicBodyFvMesh(const IOobject& io)"
        )
            << "Can't find patch: " << bodyPatchName_
                << exit(FatalError);
    }

    translationDirection_ /= mag(translationDirection_) + SMALL;

    rotationAxis_ /= mag(rotationAxis_) + SMALL;
}