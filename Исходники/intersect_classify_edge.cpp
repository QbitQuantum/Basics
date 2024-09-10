      static void traceIntersectionGraph(const V2Set &shared_edges,
                                         const FLGroupList & /* a_loops_grouped */,
                                         const FLGroupList & /* b_loops_grouped */,
                                         const carve::csg::detail::LoopEdges &a_edge_map,
                                         const carve::csg::detail::LoopEdges &b_edge_map) {

        carve::csg::detail::VVSMap shared_edge_graph;
        carve::csg::detail::VSet branch_points;

        // first, make the intersection graph.
        for (V2Set::const_iterator i = shared_edges.begin(); i != shared_edges.end(); ++i) {
          const V2Set::key_type &edge = (*i);
          carve::csg::detail::VVSMap::mapped_type &out = (shared_edge_graph[edge.first]);
          out.insert(edge.second);
          if (out.size() == 3) branch_points.insert(edge.first);

#if defined(CARVE_DEBUG) && defined(DEBUG_DRAW_INTERSECTION_LINE)
          HOOK(drawEdge(edge.first, edge.second, 1, 1, 1, 1, 1, 1, 1, 1, 1.0););
#endif
        }