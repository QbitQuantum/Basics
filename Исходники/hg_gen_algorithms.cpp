inline double hg_hyperbolic_distance_hyperbolic_rgg_standard(const hg_graph_t * graph,
							     const hg_coordinate_t & node1, 
							     const hg_coordinate_t & node2,
							     r_precomputedsinhcosh * r_psc = NULL) {
  // check if it is the same node
  if(node1.r == node2.r && node1.theta == node2.theta) {
    return 0;
  }
  // if the nodes have the same angular coordinates
  // then we return the euclidean distance
  if(node1.theta == node2.theta) {
    return abs(node1.r-node2.r);
  }
  // equation 13
  double zeta = (*graph)[boost::graph_bundle].zeta_eta;
  double delta_theta = HG_PI - abs(HG_PI - abs(node1.theta - node2.theta));
  double part1, part2;
  if(r_psc != NULL) {
    part1 = (*r_psc)[node1.r].second * (*r_psc)[node2.r].second;
    part2 = (*r_psc)[node1.r].first  * (*r_psc)[node2.r].first  * cos(delta_theta);
  }
  else {    
    part1 = cosh(zeta * node1.r) * cosh(zeta * node2.r);
    part2 = sinh(zeta * node1.r) * sinh(zeta * node2.r) * cos(delta_theta);
  }
  return  acosh(part1 - part2) / zeta;
}