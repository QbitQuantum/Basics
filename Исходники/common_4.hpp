  // generate a bolt of lightning and add to our mesh
  // modified from Michael Hoffman's
  // (http://gamedevelopment.tutsplus.com/tutorials/how-to-generate-shockingly-good-2d-lightning-effects--gamedev-2681)
  void makeBolt(Vec3f source, Vec3f dest, int maxBranches = 0,
            float branchProb = 0.01, float wid = 0.05, int n = 80) {

    Vec3f tangent = (dest - source);  // direction of lightning
    Vec3f normal =
        tangent.cross(Vec3f(0, 0, -1)).normalize();  // normal to lightning
    float length = tangent.mag();

    // choose n random positions (0,1) along lightning vector and sort them
    vector<float> positions;
    positions.push_back(0);
    for (int i = 0; i < n; i++) positions.push_back(rnd::uniform());
    sort(positions.begin(), positions.end());

    float sway = 1;  // max random walk step of displacement along normal
    float jaggedness = 1 / sway;

    Vec3f prevPoint = source;
    float prevDisplacement = 0;
   
    //float width = 0.06; 
    float width = (wid > 0) ? wid : length / 25.0 + 0.01;
    //color = Color(1, 0.7, 1, 1);
    int branches = 0;

    mesh.primitive(Graphics::TRIANGLES);

    Vec3f point;

    for (int i = 1; i < n; i++) {
      float pos = positions[i];

      // used to prevent sharp angles by ensuring very close positions also have
      // small perpendicular variation.
      float scale = (length * jaggedness) * (pos - positions[i - 1]);

      // defines an envelope. Points near the middle of the bolt can be further
      // from the central line.
      float envelope = pos > 0.95f ? mapRange(pos, 0.95f, 1.0f, 1.0f, 0.0f) : 1;

      // displacement from prevDisplacement (random walk (brownian motion))
      float displacement = rnd::uniformS(sway) * scale + prevDisplacement;
      displacement *= envelope;

      // calculate point, source plus percentage along tangent, and displacement
      // along normal;
      point = source + pos * tangent + displacement * normal;

      // generate triangles (vertices and texture coordinates) from point and
      // prevPoint
//**********
      mesh.vertex(prevPoint + normal * width);
      mesh.vertex(prevPoint - normal * width);
      mesh.vertex(point + normal * width);
      mesh.vertex(point + normal * width);
      mesh.vertex(prevPoint - normal * width);
      mesh.vertex(point - normal * width);
      mesh.texCoord(0, (float)(i - 1) / n);
      mesh.texCoord(1, (float)(i - 1) / n);
      mesh.texCoord(0, (float)(i) / n);
      mesh.texCoord(0, (float)(i) / n);
      mesh.texCoord(1, (float)(i - 1) / n);
      mesh.texCoord(1, (float)(i) / n);
      mesh.color(color);
      mesh.color(color);
      mesh.color(color);
      mesh.color(color);
      mesh.color(color);
      mesh.color(color);
//**********
      if (branches < maxBranches && rnd::prob(branchProb)) {
        branches++;
        Vec3f dir(tangent);
        rotate(dir, Vec3f(0, 0, 1), rnd::uniformS(30) * M_DEG2RAD);
        dir.normalize();
        float len = (dest - point).mag();
        makeBolt(point, point + dir * len * 0.4, maxBranches - 1, branchProb, width * 0.6,
             n * 0.5);
      }
      // remember previous point and displacement for next iteration
      prevPoint = point;
      prevDisplacement = displacement;
    }
    //generate last piece
    mesh.vertex(point + normal * width);
    mesh.vertex(point - normal * width);
    mesh.vertex(dest + normal * width);
    mesh.vertex(dest + normal * width);
    mesh.vertex(point - normal * width);
    mesh.vertex(dest - normal * width);
    mesh.texCoord(0, (float)(n - 1) / n);
    mesh.texCoord(1, (float)(n - 1) / n);
    mesh.texCoord(0, (float)(n) / n); //0
    mesh.texCoord(0, (float)(n) / n); //0
    mesh.texCoord(1, (float)(n - 1) / n);
    mesh.texCoord(1, (float)(n) / n); //1
    mesh.color(color);
    mesh.color(color);
    mesh.color(color);
    mesh.color(color);
    mesh.color(color);
    mesh.color(color);
  }