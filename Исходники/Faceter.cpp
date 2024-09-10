void Faceter::max_min_edge_ratio( DLIList <DLIList <CubitPoint*>*> &boundary_point_loops,
                                  double &ratio,
                                  double &cell_size)
{
  double max_edge_length = CUBIT_DBL_MIN;
  double min_edge_length = CUBIT_DBL_MAX;
  double sum = 0.0;
  int total_count = 0;
  DLIList<CubitPoint*> *loopPtr;
  CubitPoint *node1, *node2;
  CubitVector edge;
  for (int i = boundary_point_loops.size(); i > 0; i--) {
    loopPtr = boundary_point_loops.get_and_step();
    node2 = loopPtr->prev();
    for (int j = loopPtr->size(); j > 0; j--) {
      node1 = node2;
      node2 = loopPtr->get_and_step();
      CubitVector p1 = node1->coordinates();
      CubitVector p2 = node2->coordinates();
      edge = p2-p1;
      double edge_length = edge.length_squared();
      if (edge_length > max_edge_length) max_edge_length = edge_length;
      if (edge_length < min_edge_length) min_edge_length = edge_length;
      total_count++;
      sum += edge_length;
    }
  }

  if (min_edge_length > CUBIT_RESABS) {
    ratio = sqrt(max_edge_length/min_edge_length);
  }
  else {
    ratio = sqrt(max_edge_length);
  }
  if ( total_count > 0 && sum > 0 )
    cell_size = sqrt(sum/total_count);
  else
    cell_size = 0.0;
}