  void addBox(Geometry * geom, Matrix4 const& transform, Vector3 const& size, Color const& color)
  {
    Matrix4 normalMat = transform.inverse().transpose();

    for (int i = 0; i < 6; ++i)
    {
      Vector3 normal = dirs[i];

      Vector3 up = std::abs(dot(normal, Vector3(0, 1, 0))) > 0.9f ? Vector3(0, 0, 1) : Vector3(0, 1, 0);
      Vector3 side = cross(normal, up) * size * 0.5f;
      up = up * size * 0.5f;

      Vector3 pos = normal * size * 0.5f;

      uint16_t indexStart = geom->vertices.size();

      geom->vertices.push_back(transform * (pos + side + up));
      geom->vertices.push_back(transform * (pos + side - up));
      geom->vertices.push_back(transform * (pos - side - up));
      geom->vertices.push_back(transform * (pos - side + up));
      geom->normals.push_back(normalMat * normal);
      geom->normals.push_back(normalMat * normal);
      geom->normals.push_back(normalMat * normal);
      geom->normals.push_back(normalMat * normal);
      geom->colors.push_back(color);
      geom->colors.push_back(color);
      geom->colors.push_back(color);
      geom->colors.push_back(color);
      geom->texCoord0.push_back(Vector2(1, 1));
      geom->texCoord0.push_back(Vector2(1, 0));
      geom->texCoord0.push_back(Vector2(0, 0));
      geom->texCoord0.push_back(Vector2(0, 1));
      geom->faces.push_back(Face(indexStart + 0, indexStart + 1, indexStart + 2));
      geom->faces.push_back(Face(indexStart + 2, indexStart + 3, indexStart + 0));
    }
  }