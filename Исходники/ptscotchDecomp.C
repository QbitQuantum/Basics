Foam::labelList Foam::ptscotchDecomp::decompose
(
    const polyMesh& mesh,
    const labelList& agglom,
    const pointField& agglomPoints,
    const scalarField& pointWeights
)
{
    if (agglom.size() != mesh.nCells())
    {
        FatalErrorIn
        (
            "ptscotchDecomp::decompose(const labelList&, const pointField&)"
        )   << "Size of cell-to-coarse map " << agglom.size()
            << " differs from number of cells in mesh " << mesh.nCells()
            << exit(FatalError);
    }

//    // For running sequential ...
//    if (Pstream::nProcs() <= 1)
//    {
//        return scotchDecomp(decompositionDict_, mesh)
//            .decompose(agglom, agglomPoints, pointWeights);
//    }

    // Make Metis CSR (Compressed Storage Format) storage
    //   adjncy      : contains neighbours (= edges in graph)
    //   xadj(celli) : start of information in adjncy for celli
    CompactListList<label> cellCells;
    calcCellCells(mesh, agglom, agglomPoints.size(), cellCells);

    // Decompose using weights
    List<int> finalDecomp;
    decomposeZeroDomains
    (
        mesh.time().path()/mesh.name(),
        cellCells.m(),
        cellCells.offsets(),
        pointWeights,
        finalDecomp
    );

    // Rework back into decomposition for original mesh
    labelList fineDistribution(agglom.size());

    forAll(fineDistribution, i)
    {
        fineDistribution[i] = finalDecomp[agglom[i]];
    }

    return fineDistribution;
}