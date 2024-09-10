Vector3F NormalsUtils::calculateNormal(const IFloatBuffer* vertices,
                                       short index0,
                                       short index1,
                                       short index2) {
  const Vector3F vertex0 = getVertex(vertices, index0);
  const Vector3F vertex1 = getVertex(vertices, index1);
  const Vector3F vertex2 = getVertex(vertices, index2);

  const Vector3F p10 = vertex1.sub(vertex0);
  const Vector3F p20 = vertex2.sub(vertex0);

  return p10.cross(p20);
}