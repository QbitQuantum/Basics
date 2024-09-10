  bool RMOSM::RenderView (iView* view, bool recursePortals)
  {
    // Setup a rendering view
    view->UpdateClipper ();

    csRef<CS::RenderManager::RenderView> rview;
    rview = treePersistent.renderViews.GetRenderView (view);
    iGraphics3D* G3D = rview->GetGraphics3D ();
    int frameWidth = G3D->GetWidth ();
    int frameHeight = G3D->GetHeight ();
    view->GetCamera () ->SetViewportSize (frameWidth, frameHeight);
    view->GetEngine ()->UpdateNewFrame ();  
    view->GetEngine ()->FireStartFrame (rview);

    // Computes the left, right, top, and bottom of the view frustum.
    iPerspectiveCamera *camera = view->GetPerspectiveCamera ();
    float invFov = camera->GetInvFOV ();
    float l = -invFov * camera->GetShiftX ();
    float r =  invFov * (frameWidth - camera->GetShiftX ());
    float t = -invFov * camera->GetShiftY ();
    float b =  invFov * (frameHeight - camera->GetShiftY ());
    rview->SetFrustum (l, r, t, b);

    lightPersistent.UpdateNewFrame ();

    iSector* startSector = rview->GetThisSector ();

    if (!startSector)
      return false;

    // Pre-setup culling graph
    RenderTreeType renderTree (treePersistent);

    RenderTreeType::ContextNode* startContext = 
      renderTree.CreateContext (rview);
    startContext->drawFlags |= (CSDRAW_CLEARSCREEN | CSDRAW_CLEARZBUFFER);

    // Setup the main context
    {
      ContextSetupType contextSetup (this, renderLayer);
      ContextSetupType::PortalSetupType::ContextSetupData 
        portalData (startContext);

      contextSetup (*startContext, portalData, recursePortals);
    }

    // Render all contexts, back to front
    {
      view->GetContext()->SetZMode (CS_ZBUF_MESH);

      SimpleTreeRenderer<RenderTreeType> render (rview->GetGraphics3D (),
        shaderManager);
      ForEachContextReverse (renderTree, render);
    }

    // Output the final result to the backbuffer.
//     DebugFrameRender (rview, renderTree);

    return true;
  }