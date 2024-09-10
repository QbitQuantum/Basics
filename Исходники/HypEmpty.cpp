 bool inputTransformInPlace(IHypergraph<Arc> const& hg, int) {
   if (empty.empty)
     outProperty("EMPTY", Hypergraph::empty(hg));
   if (empty.fsm)
     outProperty("FSM", hg.isFsm());
   if (empty.graph)
     outProperty("GRAPH", hg.isGraph());
   return true;
 }