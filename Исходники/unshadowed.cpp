bool RMUnshadowed::RenderView (iView* view, bool recursePortals)
{
  // Setup a rendering view
  view->UpdateClipper ();

  csRef<CS::RenderManager::RenderView> rview;
  rview = treePersistent.renderViews.GetRenderView (view);
  iCamera* c = view->GetCamera ();
  iGraphics3D* G3D = rview->GetGraphics3D ();
  int frameWidth = G3D->GetWidth ();
  int frameHeight = G3D->GetHeight ();
  c->SetViewportSize (frameWidth, frameHeight);
  view->GetEngine ()->UpdateNewFrame ();  
  view->GetEngine ()->FireStartFrame (rview);

  float ifov, sx, sy;
  iPerspectiveCamera* pcam = view->GetPerspectiveCamera ();
  if (pcam)
  {
    ifov = pcam->GetInvFOV ();
    sx = pcam->GetShiftX ();
    sy = pcam->GetShiftY ();
  }
  else
  {
    ifov = 1.0f;
    sx = 0.0f;
    sy = 0.0f;
  }

  float leftx = -sx * ifov;
  float rightx = (frameWidth - sx) * ifov;
  float topy = -sy * ifov;
  float boty = (frameHeight - sy) * ifov;
  rview->SetFrustum (leftx, rightx, topy, boty);

  contextsScannedForTargets.Empty ();
  portalPersistent.UpdateNewFrame ();
  lightPersistent.UpdateNewFrame ();
  reflectRefractPersistent.UpdateNewFrame ();
  framebufferTexPersistent.UpdateNewFrame ();

  iSector* startSector = rview->GetThisSector ();

  if (!startSector)
    return false;

  CS::Math::Matrix4 perspectiveFixup;
  postEffects.SetupView (view, perspectiveFixup);

  // Pre-setup culling graph
  RenderTreeType renderTree (treePersistent);

  RenderTreeType::ContextNode* startContext = renderTree.CreateContext (rview);
  startContext->drawFlags |= (CSDRAW_CLEARSCREEN | CSDRAW_CLEARZBUFFER);
  startContext->renderTargets[rtaColor0].texHandle = postEffects.GetScreenTarget ();
  startContext->perspectiveFixup = perspectiveFixup;

  // Setup the main context
  {
    ContextSetupType contextSetup (this, renderLayer);
    ContextSetupType::PortalSetupType::ContextSetupData portalData (startContext);

    contextSetup (*startContext, portalData, recursePortals);
  
    targets.StartRendering (shaderManager);
    targets.EnqueueTargets (renderTree, shaderManager, renderLayer, contextsScannedForTargets);
  }

  // Setup all dependent targets
  while (targets.HaveMoreTargets ())
  {
    TargetManagerType::TargetSettings ts;
    targets.GetNextTarget (ts);

    HandleTarget (renderTree, ts, recursePortals);
  }

  targets.FinishRendering ();

  // Render all contexts, back to front
  {
    view->GetContext()->SetZMode (CS_ZBUF_MESH);

    SimpleTreeRenderer<RenderTreeType> render (rview->GetGraphics3D (),
      shaderManager);
    ForEachContextReverse (renderTree, render);
  }

  postEffects.DrawPostEffects (renderTree);
  
  if (doHDRExposure) hdrExposure.ApplyExposure (renderTree, view);
  
  DebugFrameRender (rview, renderTree);

  return true;
}