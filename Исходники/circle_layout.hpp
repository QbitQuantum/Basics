  void 
  circle_graph_layout(const VertexListGraph& g, PositionMap position,
                      Radius radius)
  {
    const double pi = 3.14159;

#ifndef BOOST_NO_STDC_NAMESPACE
    using std::sin;
    using std::cos;
#endif // BOOST_NO_STDC_NAMESPACE

    typedef typename graph_traits<VertexListGraph>::vertices_size_type 
      vertices_size_type;

    vertices_size_type n = num_vertices(g);
    
    typedef typename graph_traits<VertexListGraph>::vertex_iterator 
      vertex_iterator;

    vertices_size_type i = 0;
    for(std::pair<vertex_iterator, vertex_iterator> v = vertices(g); 
        v.first != v.second; ++v.first, ++i) {
      position[*v.first].x = radius * cos(i * 2 * pi / n);
      position[*v.first].y = radius * sin(i * 2 * pi / n);
    }
  }