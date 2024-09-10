Foam::labelList Foam::metisDecomp::decompose
(
    const polyMesh& mesh,
    const pointField& points,
    const scalarField& pointWeights
)
{
    if (points.size() != mesh.nCells())
    {
        FatalErrorIn
        (
            "metisDecomp::decompose(const pointField&,const scalarField&)"
        )   << "Can use this decomposition method only for the whole mesh"
            << endl
            << "and supply one coordinate (cellCentre) for every cell." << endl
            << "The number of coordinates " << points.size() << endl
            << "The number of cells in the mesh " << mesh.nCells()
            << exit(FatalError);
    }

    CompactListList<label> cellCells;
    calcCellCells(mesh, identity(mesh.nCells()), mesh.nCells(), cellCells);

    // Decompose using default weights
    labelList decomp;
    decompose(cellCells.m(), cellCells.offsets(), pointWeights, decomp);

    return decomp;
}