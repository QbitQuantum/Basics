Foam::patchDist::patchDist
(
    const fvMesh& mesh,
    const labelHashSet& patchIDs,
    const bool correctWalls
)
:
    volScalarField
    (
        IOobject
        (
            "y",
            mesh.time().timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar("y", dimLength, GREAT)
    ),
    patchIDs_(patchIDs),
    correctWalls_(correctWalls),
    nUnset_(0)
{
    patchDist::correct();
}