void
TestSourceNode() {
    tbb::flow::graph g;
    tbb::flow::source_node<int> sn(g, snode_body(4), false);
    REMARK("Testing source_node:");
    tbb::flow::queue_node<int> qin(g);
    tbb::flow::join_node<tbb::flow::tuple<int,int>, tbb::flow::reserving> jn(g);
    tbb::flow::queue_node<tbb::flow::tuple<int,int> > qout(g);
    
    REMARK(" make_edges");
    tbb::flow::make_edge(sn, tbb::flow::input_port<0>(jn));
    tbb::flow::make_edge(qin, tbb::flow::input_port<1>(jn));
    tbb::flow::make_edge(jn,qout);
    ASSERT(!sn.my_successors.empty(), "source node has no successor after make_edge");
    g.wait_for_all();
    g.reset();
    ASSERT(!sn.my_successors.empty(), "source node has no successor after reset");
#if TBB_PREVIEW_FLOW_GRAPH_FEATURES
    g.wait_for_all();
    g.reset(tbb::flow::rf_extract);
    ASSERT(sn.my_successors.empty(), "source node has successor after reset(rf_extract)");
    tbb::flow::make_edge(sn, tbb::flow::input_port<0>(jn));
    tbb::flow::make_edge(qin, tbb::flow::input_port<1>(jn));
    tbb::flow::make_edge(jn,qout);
    g.wait_for_all();
#endif
    REMARK(" activate");
    sn.activate();  // will forward to the fnode
    REMARK(" wait1");
    BACKOFF_WAIT( !sn.my_successors.empty(), "Timed out waiting for edge to reverse");
    ASSERT(sn.my_successors.empty(), "source node has no successor after forwarding message");

    g.wait_for_all();
    g.reset();
    ASSERT(!sn.my_successors.empty(), "source_node has no successors after reset");
    ASSERT(tbb::flow::input_port<0>(jn).my_predecessors.empty(), "successor if source_node has pred after reset.");
    REMARK(" done\n");
}