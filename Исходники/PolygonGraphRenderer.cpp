void PolygonGraphRenderer::PreparePolygons()
{
   m_displayListPolygons.Init();

   m_displayListPolygons.Open();

   for (PolygonGraph::CenterPtr p : m_graph.m_centers)
   {
      std::vector<PolygonGraph::CornerPtr> vecCorners = p->corners;

      // order them clockwise
      std::sort(vecCorners.begin(), vecCorners.end(),
         PolygonGraph::CornerSorter(p->point));

      // draw triangle fan
      glBegin(GL_TRIANGLE_FAN);

      Color c = PolygonGraph::ColorByBiomeType(p->enBiomeType);
      //Color c = PolygonGraph::ColorByTerrainType(p->enTerrainType);
      //Color c = PolygonGraph::ColorByElevation(p->elevation);
      //Color c = PolygonGraph::ColorByMoisture(p->moisture);


      glColor3ubv(c.m_color);

      // normal
      ATLASSERT(vecCorners.size() >= 2);
      Vector3d center(p->point.X(), p->elevation * c_dElevationScaleFactor, p->point.Y());
      Vector3d p1(vecCorners[0]->point.X(), vecCorners[0]->elevation * c_dElevationScaleFactor, vecCorners[0]->point.Y());
      Vector3d p2(vecCorners[1]->point.X(), vecCorners[1]->elevation * c_dElevationScaleFactor, vecCorners[1]->point.Y());
      Vector3d normal;
      normal.Cross(center-p1, center-p2);
      normal.Normalize();

      glNormal3dv(normal.Data());

      // center
      glVertex3d(p->point.X(), p->elevation * c_dElevationScaleFactor, p->point.Y());

      for (PolygonGraph::CornerPtr q : vecCorners)
         glVertex3d(q->point.X(), q->elevation * c_dElevationScaleFactor, q->point.Y());

      glVertex3d(vecCorners[0]->point.X(), vecCorners[0]->elevation * c_dElevationScaleFactor,
         vecCorners[0]->point.Y());

      glEnd();
   }

   m_displayListPolygons.Close();
}