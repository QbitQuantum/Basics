void Mist::createRing(float x, float y, float radius, float width) {
  offsets.push_back(vertices.size());

  float resolution = 60.0;
  float angle = TWO_PI/resolution;
  float outer_radius = radius + width;

  for(int i = 0; i < resolution; ++i) {
    float c0 = cos( (i + 0) * angle);
    float s0 = sin( (i + 0) * angle);
    float c1 = cos( (i + 1) * angle);
    float s1 = sin( (i + 1) * angle);
    
    // positions
    vec3 pa(c0 * radius, s0 * radius, 0.0f);
    vec3 pb(c1 * radius, s1 * radius, 0.0f);
    vec3 pc(c1 * outer_radius, s1 * outer_radius, 0.0f);
    vec3 pd(c0 * outer_radius, s0 * outer_radius, 0.0f);

    // texcoords
    float u0 = float(i+0)/resolution;
    float u1 = float(i+1)/resolution;
    vec3 ta(u0, 0.0f, 1.0f);
    vec3 tb(u1, 0.0f, 1.0f);
    vec3 tc(u1, 1.0f, 1.0f);
    vec3 td(u0, 1.0f, 1.0f);

    // calculate distances from the corners to the centers
    vec3 intersection;
    if(!intersect(pa, pc, pb, pd, intersection)) {
      printf("The vertices of the dist do not intersect. Error.\n");
      ::exit(EXIT_FAILURE);
    }

    float d0 = length(pa - intersection);
    float d1 = length(pb - intersection);
    float d2 = length(pc - intersection);
    float d3 = length(pd - intersection);

    ta = ta * ((d0 + d2)/d2);
    tb = tb * ((d1 + d3)/d3);
    tc = tc * ((d2 + d0)/d0);
    td = td * ((d3 + d1)/d1);

    // store the vertices
    VertexPT3 a(pa,ta);
    VertexPT3 b(pb,tb);
    VertexPT3 c(pc,tc);
    VertexPT3 d(pd,td);

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);

    vertices.push_back(a);
    vertices.push_back(c);
    vertices.push_back(d);
  }

  counts.push_back(vertices.size()-offsets.back());
  needs_update = true;
}