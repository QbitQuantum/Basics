void SlamGraph<Sim3, LinearCamera, Sim3XYZ, 2>
::addConstraintToG2o(const Sim3 & T_2_from_1,
                     const Matrix6d & Lambda_2_from_1,
                     int pose_id_1,
                     int pose_id_2,
                     g2o::SparseOptimizer * optimizer)
{
  G2oEdgeSim3 * e = new G2oEdgeSim3();

  g2o::HyperGraph::Vertex * pose1_vertex
      = GET_MAP_ELEM(pose_id_1, optimizer->vertices());
  e->vertices()[0]
      = dynamic_cast<g2o::OptimizableGraph::Vertex*>(pose1_vertex);

  g2o::HyperGraph::Vertex * pose2_vertex
      = GET_MAP_ELEM(pose_id_2, optimizer->vertices());
  e->vertices()[1]
      = dynamic_cast<g2o::OptimizableGraph::Vertex*>(pose2_vertex);

  e->measurement() = T_2_from_1;
  e->inverseMeasurement() = T_2_from_1.inverse();
  e->information() = Lambda_2_from_1;

  optimizer->addEdge(e);
}