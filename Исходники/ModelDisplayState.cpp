void ModelDisplayState::RenderModelNormals(const Group& group) const
{
   AnimatedModel3d& model = *m_spModel->GetAnimated();
   const Data& data = model.GetData();

   OpenGL::PushedAttributes attrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);

   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_TEXTURE_2D);

   glLineWidth(2.0f);

   glBegin(GL_LINES);

   for (size_t uiTriangleIndex : group.m_vecTriangleIndices)
   {
      ATLASSERT(uiTriangleIndex < data.m_vecTriangles.size());

      const Triangle& t = data.m_vecTriangles[uiTriangleIndex];
      for (unsigned int v=0; v<3; v++)
      {
         size_t vertexIndex = t.auiVertexIndices[v];
         const Vertex& vert = data.m_vecVertices[vertexIndex];

         Vector3d vVertex = vert.m_vPos;
         model.TransformVertex(vert, m_vecJointRenderData, vVertex);

         Vector3d vNormal = t.aNormals[v];
         model.TransformNormal(vert, m_vecJointRenderData, vNormal);

         vNormal.Normalize();
         vNormal *= 0.1;
         vNormal += vVertex;

         glVertex3dv(vVertex.Data());
         glVertex3dv(vNormal.Data());
      }
   }

   glEnd();
}