void test_extract() {
    int counts = 0;
    tbb::flow::tuple<int,int> dont_care;
    tbb::flow::graph g;
    typedef tbb::flow::source_node<int> snode_type;
    tbb::flow::source_node<int> s0(g, source_body<int>(counts), /*is_active*/false ); 
    tbb::flow::join_node< tbb::flow::tuple<int,int>, tbb::flow::reserving > j0(g);
    tbb::flow::join_node< tbb::flow::tuple<int,int>, tbb::flow::reserving > j1(g);
    tbb::flow::join_node< tbb::flow::tuple<int,int>, tbb::flow::reserving > j2(g);
    tbb::flow::queue_node<int> q0(g);
    tbb::flow::queue_node<tbb::flow::tuple<int,int> > q1(g);
    tbb::flow::make_edge(s0, tbb::flow::get<0>(j0.input_ports()));
    /*  s0 ----+    */
    /*         | j0 */
    /*         +    */
    ASSERT(!counts, "source_node activated too soon");
    s0.activate();
    g.wait_for_all();  // should produce one value, buffer it.
    ASSERT(counts == 1, "source_node did not react to activation");

    g.reset(tbb::flow::rf_reset_bodies);
    counts = 0;
    s0.extract();
    /*  s0     +    */
    /*         | j0 */
    /*         +    */
    s0.activate();
    g.wait_for_all();  // no successors, so the body will not execute
    ASSERT(counts == 0, "source_node shouldn't forward (no successors)");
    s0.extract(tbb::flow::rf_reset_bodies);

    tbb::flow::make_edge(s0, tbb::flow::get<0>(j0.input_ports()));
    tbb::flow::make_edge(s0, tbb::flow::get<0>(j1.input_ports()));
    tbb::flow::make_edge(s0, tbb::flow::get<0>(j2.input_ports()));

    /*        /+    */
    /*       / | j0 */
    /*      /  +    */
    /*     /        */
    /*    / /--+    */
    /*  s0-/   | j1 */
    /*    \    +    */
    /*     \        */
    /*      \--+    */
    /*         | j2 */
    /*         +    */

    // do all joins appear in successor list?
    std::vector<tbb::flow::receiver<int>*> jv1;
    jv1.push_back(&(tbb::flow::get<0>(j0.input_ports())));
    jv1.push_back(&(tbb::flow::get<0>(j1.input_ports())));
    jv1.push_back(&(tbb::flow::get<0>(j2.input_ports())));
    tbb::flow::source_node<int>::successor_vector_type sv;
    s0.copy_successors(sv);
    ASSERT(lists_match(sv, jv1), "mismatch in successor list");

    tbb::flow::make_edge(q0, tbb::flow::get<1>(j2.input_ports()));
    tbb::flow::make_edge(j2, q1);
    s0.activate();

    /*        /+           */
    /*       / | j0        */
    /*      /  +           */
    /*     /               */
    /*    / /--+           */
    /*  s0-/   | j1        */
    /*    \    +           */
    /*     \               */
    /*      \--+           */
    /*         | j2----q1  */
    /*  q0-----+           */

    q0.try_put(1);
    g.wait_for_all();
    ASSERT(q1.try_get(dont_care), "join did not emit result");
    j2.extract();
    tbb::flow::make_edge(q0, tbb::flow::get<1>(j2.input_ports()));
    tbb::flow::make_edge(j2, q1);

    /*        /+           */
    /*       / | j0        */
    /*      /  +           */
    /*     /               */
    /*    / /--+           */
    /*  s0-/   | j1        */
    /*         +           */
    /*                     */
    /*         +           */
    /*         | j2----q1  */
    /*  q0-----+           */

    jv1.clear();
    jv1.push_back(&(tbb::flow::get<0>(j0.input_ports())));
    jv1.push_back(&(tbb::flow::get<0>(j1.input_ports())));
    s0.copy_successors(sv);
    ASSERT(lists_match(sv, jv1), "mismatch in successor list");

    q0.try_put(1);
    g.wait_for_all();
    ASSERT(!q1.try_get(dont_care), "extract of successor did not remove pred link");

    s0.extract();

    /*         +           */
    /*         | j0        */
    /*         +           */
    /*                     */
    /*         +           */
    /*  s0     | j1        */
    /*         +           */
    /*                     */
    /*         +           */
    /*         | j2----q1  */
    /*  q0-----+           */

    ASSERT(s0.successor_count() == 0, "successor list not cleared");
    s0.copy_successors(sv);
    ASSERT(sv.size() == 0, "non-empty successor list");

    tbb::flow::make_edge(s0, tbb::flow::get<0>(j2.input_ports()));

    /*         +           */
    /*         | j0        */
    /*         +           */
    /*                     */
    /*         +           */
    /*  s0     | j1        */
    /*    \    +           */
    /*     \               */
    /*      \--+           */
    /*         | j2----q1  */
    /*  q0-----+           */

    jv1.clear();
    jv1.push_back(&(tbb::flow::get<0>(j2.input_ports())));
    s0.copy_successors(sv);
    ASSERT(lists_match(sv, jv1), "mismatch in successor list");

    q0.try_put(1);
    g.wait_for_all();
    ASSERT(!q1.try_get(dont_care), "extract of successor did not remove pred link");
}