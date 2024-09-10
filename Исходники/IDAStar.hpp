  void search()
  {
    if (searched)
      return;
    searched = true;

    Node *start_node = new (node_pool.malloc()) Node(domain.get_start_state(),
                                                     0,
                                                     0);
    domain.compute_heuristic(*start_node);
    goal = idastar_search(start_node);
  }