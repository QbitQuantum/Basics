void peano::applications::poisson::multigrid::mappings::SpacetreeGrid2PlotSolution::plotVertex(
  peano::applications::poisson::multigrid::SpacetreeGridVertex&  fineGridVertex,
  const tarch::la::Vector<DIMENSIONS,double>&                    fineGridX
) {
  if ( fineGridVertex.getRefinementControl() == SpacetreeGridVertex::Records::Unrefined ) {
    #ifdef SharedTBB
    Vertex2IndexMapSemaphore::scoped_lock localLock(_vertex2IndexMapSemaphore);
    #elif SharedOMP
    assertionMsg( false, "here should be a critical section, but I don't know how to implement this. If you implement it, please add it to the templates, too." );
    #endif
    if ( _vertex2IndexMap.find(fineGridX) == _vertex2IndexMap.end() ) {
      #if defined(Dim2) || defined(Dim3)
      _vertex2IndexMap[fineGridX] = _vertexWriter->plotVertex(fineGridX);
      #else
      _vertex2IndexMap[fineGridX] = _vertexWriter->plotVertex(tarch::la::Vector<3,double>(fineGridX.data()));
      #endif

      if (fineGridVertex.isHangingNode()) {
        _vertexResidualWriter->plotVertex(_vertex2IndexMap[fineGridX],0.0);
        _vertexValueWriter->plotVertex(_vertex2IndexMap[fineGridX],0.0);
        // @todo For a smooth plot, it might make sense to set the 'right' rhs, i.e.
        //       the rhs belonging to a persistent vertex at this very position.
        _vertexRhsWriter->plotVertex(_vertex2IndexMap[fineGridX],0.0);
      }
      else {
        _vertexResidualWriter->plotVertex(_vertex2IndexMap[fineGridX],fineGridVertex.getResidual());
        _vertexValueWriter->plotVertex(_vertex2IndexMap[fineGridX],fineGridVertex.getU());
        _vertexRhsWriter->plotVertex(_vertex2IndexMap[fineGridX],fineGridVertex.getRhs());
      }
    }
  }
}