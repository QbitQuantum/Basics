  /// transforms face coordinates to regular system, face normal will be z'
  /// will try to align y' with z, but if that fails will align y' with y
  /// face origin will be minimum point in x', y' and z'=0
  /// will return identity transformation if cannot compute plane for vertices
  Transformation Transformation::alignFace(const std::vector<Point3d>& vertices)
  {
    OptionalVector3d zPrime = getOutwardNormal(vertices);
    if (!zPrime){
      LOG(Error, "Cannot compute outward normal for vertices");
      return Transformation();
    }

    // align z' with outward normal
    Transformation align = alignZPrime(*zPrime);
    Point3dVector alignedVertices = align.inverse()*vertices;

    // compute translation to minimum in aligned system
    double minX = alignedVertices[0].x();
    double minY = alignedVertices[0].y();
    double minZ = alignedVertices[0].z();

    for (const Point3d& vertex : alignedVertices){
      minX = min(minX, vertex.x());
      minY = min(minY, vertex.y());
      minZ = min(minZ, vertex.z());
    }
    Transformation translate = translation(Vector3d(minX, minY, minZ));

    return align*translate;
  }