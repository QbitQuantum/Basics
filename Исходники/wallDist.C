Foam::wallDist::wallDist(const fvMesh& mesh, const bool correctWalls)
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
    cellDistFuncs(mesh),
    correctWalls_(correctWalls),
    nUnset_(0)
{
    wallDist::correct();
}