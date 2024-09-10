void CopyFromRoot( const DistGraph& distGraph, Graph& graph )
{
    EL_DEBUG_CSE
    const Grid& grid = distGraph.Grid();
    const int commSize = grid.Size();
    const int commRank = grid.Rank();

    const int numLocalEdges = distGraph.NumLocalEdges();
    vector<int> edgeSizes(commSize);
    mpi::AllGather( &numLocalEdges, 1, edgeSizes.data(), 1, grid.Comm() );
    vector<int> edgeOffsets;
    const int numEdges = Scan( edgeSizes, edgeOffsets );

    graph.Resize( distGraph.NumSources(), distGraph.NumTargets() );
    graph.Reserve( numEdges );
    graph.sources_.resize( numEdges );
    graph.targets_.resize( numEdges );
    mpi::Gather
    ( distGraph.LockedSourceBuffer(), numLocalEdges,
      graph.SourceBuffer(), edgeSizes.data(), edgeOffsets.data(),
      commRank, grid.Comm() );
    mpi::Gather
    ( distGraph.LockedTargetBuffer(), numLocalEdges,
      graph.TargetBuffer(), edgeSizes.data(), edgeOffsets.data(),
      commRank, grid.Comm() );
    graph.ProcessQueues();
}