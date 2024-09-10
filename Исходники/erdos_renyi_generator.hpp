    void next()
    {
      using std::sqrt;
      using std::floor;

      // In order to get the edges from the generator in sorted order, one
      // effective (but slow) procedure would be to use a
      // bernoulli_distribution for each legal (src, tgt) pair.  Because of the
      // O(n^2) cost of that, a geometric distribution is used.  The geometric
      // distribution tells how many times the bernoulli_distribution would
      // need to be run until it returns true.  Thus, this distribution can be
      // used to step through the edges which are actually present.  Everything
      // beyond "tgt += increment" is done to effectively convert linear
      // indexing (the partial sums of the geometric distribution output) into
      // graph edges.
      assert (src != (std::numeric_limits<vertices_size_type>::max)());
      vertices_size_type increment = rand_vertex(*gen);
      tgt += increment;
      if (is_undirected) {
    // Update src and tgt based on position of tgt
    // Basically, we want the greatest src_increment such that (in \bbQ):
    // src_increment * (src + allow_self_loops + src_increment - 1/2) <= tgt
    // The result of the LHS of this, evaluated with the computed
    // src_increment, is then subtracted from tgt
    double src_minus_half = (src + allow_self_loops) - 0.5;
    double disc = src_minus_half * src_minus_half + 2 * tgt;
    double src_increment_fp = floor(sqrt(disc) - src_minus_half);
    vertices_size_type src_increment = vertices_size_type(src_increment_fp);
    if (src + src_increment >= n) {
      src = n;
    } else {
      tgt -= (src + allow_self_loops) * src_increment + 
         src_increment * (src_increment - 1) / 2;
      src += src_increment;
    }
      } else {
    // Number of out edge positions possible from each vertex in this graph
    vertices_size_type possible_out_edges = n - (allow_self_loops ? 0 : 1);
    src += (std::min)(n - src, tgt / possible_out_edges);
    tgt %= possible_out_edges;
      }
      // Set end of graph code so (src, tgt) will be the same as for the end
      // sorted_erdos_renyi_iterator
      if (src >= n) {src = (std::numeric_limits<vertices_size_type>::max)(); tgt = 0;}
      // Copy (src, tgt) into current
      current.first = src;
      current.second = tgt;
      // Adjust for (src, src) edge being forbidden
      if (!allow_self_loops && tgt >= src) ++current.second;
    }