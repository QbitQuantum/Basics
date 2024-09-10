// Construct from components
Foam::enginePiston::enginePiston
(
    const polyMesh& mesh,
    const word& pistonPatchName,
    const autoPtr<coordinateSystem>& pistonCS,
    const scalar minLayer,
    const scalar maxLayer
)
:
    mesh_(mesh),
    engineDB_(refCast<const engineTime>(mesh.time())),
    patchID_(pistonPatchName, mesh.boundaryMesh()),
    csPtr_(pistonCS),
    minLayer_(minLayer),
    maxLayer_(maxLayer)
{}