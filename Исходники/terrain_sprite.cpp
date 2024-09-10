  // draw a water-hugging sprite; rotate the texture first
  //
  Bucket * RenderWaterSprite( const Vector & origin, F32 radius, const Vector &front, const Bitmap *texture, Color color, U32 blend, UVPair uv0, UVPair uv1, UVPair uv2, U16 sorting) // UVPair(0.0f,1.0f), UVPair(1.0f,1.0f), UVPair(1.0f,0.0f)
  {
    Vector f = front;
    f.y =0.0f;
    f.Normalize();
    Matrix m;
    m.ClearData();
    m.SetFromFront( f);

    F32 du = (F32) fabs(uv2.u + uv0.u) * 0.5f;
    F32 dv = (F32) fabs(uv2.v + uv0.v) * 0.5f;
    uv0.u -= du;
    uv0.v -= dv;
    uv1.u -= du;
    uv1.v -= dv;
    uv2.u -= du;
    uv2.v -= dv;

    m.Rotate( uv0);
    m.Rotate( uv1);
    m.Rotate( uv2);

    uv0.u += du;
    uv0.v += dv;
    uv1.u += du;
    uv1.v += dv;
    uv2.u += du;
    uv2.v += dv;

    return RenderWaterSprite( origin, radius, texture, color, blend, uv0, uv1, uv2, sorting);
  }