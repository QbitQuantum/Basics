    virtual void SetParallel (void)     // overload virtual
    {
      Trafo A; 
      float fov, newfov = 1.0;
      GetSelectionView(A,fov);

      // Reduce the field of view angle fov to 1 degree 
      // scaling the z-coordinate of the translation part of the 
      // transformation matrix A(2,3) to make the image appear the
      // same size.
      A(2,3) *= tan(DegToRad(fov)) / tan(DegToRad(newfov));

      SetSelectionView(A,newfov,
                       view->GetActiveGraphPtr()->vbx,
                       view->GetActiveGraphPtr()->vby,
                       view->GetActiveGraphPtr()->vbz);
      Accept();

      // finally always call method of base class of view panel for update
      view->display->Viewport3DPanel->MpViewPanel::Accept();
    }