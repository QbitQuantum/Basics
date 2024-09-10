  void
  FrameStoreInit::aTransToTransform3D(Transform3D& trans3d, ATrans3 const& atrans) throw()
  {
#ifdef RTIDDS_FOUND
    for (unsigned int i = 0; i < 3; ++i) {
      trans3d.xyz[i] = atrans.translation()[i];
      for (unsigned int j = 0; j < 3; ++j) {
        trans3d.rot[(i * 3 + j)] = atrans.rotation()(i, j);
      }
    }
#endif
  }