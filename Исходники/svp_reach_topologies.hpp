 static 
 double get_proper_norm(const BaseTopology& b_space, const rt_metric_type& rt_dist, const point_difference_type& dp) {
   using std::fabs;
   svp_reach_time_metric< base_time_topo, true > p_rt_dist(rt_dist);
   double reach_time = p_rt_dist(dp.pt, b_space.get_space_topology());
   return fabs(dp.time) + reach_time;
 };