  //
  // Render edges of the box
  //
  static void RenderBoxEdges(VertexTL *verts, const Matrix *m = NULL)
  {
    const U16 faces[12][2] = 
    {
      {0, 1}, {1, 2}, {2, 3}, {3, 0},
      {4, 5}, {5, 6}, {6, 7}, {7, 4},
      {0, 4}, {1, 5}, {2, 6}, {3, 7},
    };

    // Transform
    if (m)
    {
      Matrix transform = *m * Vid::Math::viewMatrix;
      transform.Transform(verts, verts, 8);
    }
    else
    {
      Vid::Math::viewMatrix.Transform(verts, verts, 8);
    }

    for (U32 i = 0; i < 8; i ++)        
    {
      Vid::ProjectFromCamera( verts[i]);
    }

    for (i = 0; i < 12; i ++) 
    {
    VertexTL pt[2];
      pt[0] = verts[faces[i][0]];
      pt[1] = verts[faces[i][1]];

      Vid::DrawPrimitive
      (
        PT_LINELIST, FVF_TLVERTEX, pt, 2, RS_BLEND_DEF | DP_DONOTUPDATEEXTENTS
      );
    }
  }