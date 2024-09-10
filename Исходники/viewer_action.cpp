    //
    // Simulation
    //
    void Mesh::Notify(U32 crc)
    {
      switch (crc)
      {
        case 0xEF30A860: // "Render::PostObject"
        {
          Simulate();

          if (root && !done)
          {
            Matrix mat = Vid::CurCamera().WorldMatrix();
            Vector vect;
            mat.Transform( vect, offset);
            mat.posit = vect;
            root->Render( mat);
          }
          return;
        }
      }
    }