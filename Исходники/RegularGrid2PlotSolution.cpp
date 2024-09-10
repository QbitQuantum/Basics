void peano::applications::poisson::jacobitutorial::mappings::RegularGrid2PlotSolution::touchVertexFirstTime(
  peano::applications::poisson::jacobitutorial::RegularGridVertex&  vertex,
  const tarch::la::Vector<DIMENSIONS,double>&  x
) {
  logTraceInWith2Arguments( "touchVertexFirstTime()", x, vertex );

  /**
   * --- inserted manually ---
   *
   * This is now the interesting part. The first few lines in the block resemble
   * the one inserted by the generated grid plotter. It brings the vertex to
   * your screen (or vtk file respectively. The lines afterwards then set
   */
  tarch::multicore::Lock localLock( _outputStreamSemaphore );

  if ( _vertex2IndexMap.find(x) == _vertex2IndexMap.end() ) {
    #if defined(Dim2) || defined(Dim3)
    _vertex2IndexMap[x] = _vertexWriter->plotVertex(x);
    #else
    _vertex2IndexMap[x] = _vertexWriter->plotVertex(tarch::la::Vector<3,double>(x.data()));
    #endif

    _vertexResidualWriter->plotVertex(_vertex2IndexMap[x],vertex.getResidual());
    _vertexValueWriter->plotVertex(_vertex2IndexMap[x],vertex.getU());
    _vertexRhsWriter->plotVertex(_vertex2IndexMap[x],vertex.getRhs());
  }

  logTraceOutWith1Argument( "touchVertexFirstTime()", vertex );
}