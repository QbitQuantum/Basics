void ModelTriangle2D::transformModel(const Transform &T) {
    Matrix2 R = T.rotation().block<2, 2>(0, 0);
    Vector2 t = T.translation().block<2, 1>(0, 0);
    for (auto &triangle : m_triangles)
        triangle.transform(R, t);

    m_mesh = cad::generateMesh(m_triangles);
    m_mesh.aabb = cad::computeAABB(m_mesh);
}