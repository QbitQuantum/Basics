void GLSBVR::Render3DInLoop(const RenderRegion3D& renderRegion,
                            size_t iCurrentBrick, EStereoID eStereoID) {

  m_pContext->GetStateManager()->Apply(m_BaseState);

  const Brick& b = (eStereoID == SI_LEFT_OR_MONO) ? m_vCurrentBrickList[iCurrentBrick] : m_vLeftEyeBrickList[iCurrentBrick];
  
  if (m_iBricksRenderedInThisSubFrame == 0 && m_eRenderMode == RM_ISOSURFACE){
    m_TargetBinder.Bind(m_pFBOIsoHit[size_t(eStereoID)], 0, m_pFBOIsoHit[size_t(eStereoID)], 1);
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    if (m_bDoClearView) {
      m_TargetBinder.Bind(m_pFBOCVHit[size_t(eStereoID)], 0, m_pFBOCVHit[size_t(eStereoID)], 1);
      GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
  }

  if (!m_bSupportsMeshes && b.bIsEmpty) return;

  // setup the slice generator
  m_SBVRGeogen.SetBrickData(b.vExtension, b.vVoxelCount,
                            b.vTexcoordsMin, b.vTexcoordsMax);
  FLOATMATRIX4 maBricktTrans;
  maBricktTrans.Translation(b.vCenter.x, b.vCenter.y, b.vCenter.z);
  m_mProjection[size_t(eStereoID)].setProjection();
  renderRegion.modelView[size_t(eStereoID)].setModelview();

  m_SBVRGeogen.SetBrickTrans(b.vCenter);
  m_SBVRGeogen.SetWorld(renderRegion.rotation*renderRegion.translation);
  m_SBVRGeogen.SetView(m_mView[size_t(eStereoID)]);

  if (m_bSupportsMeshes) {
    m_SBVRGeogen.ResetMesh();
    if (m_eRenderMode != RM_ISOSURFACE) {
      for (vector<shared_ptr<RenderMesh>>::iterator mesh = m_Meshes.begin();
           mesh != m_Meshes.end(); mesh++) {
        if ((*mesh)->GetActive()) {
          m_SBVRGeogen.AddMesh((*mesh)->GetInPointList(false));
        }
      }
    }
  }

  m_SBVRGeogen.ComputeGeometry(b.bIsEmpty);

  if (m_eRenderMode == RM_ISOSURFACE) {
    m_pContext->GetStateManager()->SetEnableBlend(false);

    m_TargetBinder.Bind(m_pFBOIsoHit[size_t(eStereoID)], 0, m_pFBOIsoHit[size_t(eStereoID)], 1);
    SetBrickDepShaderVars(b);
    
    GLSLProgram* shader = this->ColorData() ? m_pProgramColor : m_pProgramIso;
    shader->Set("fIsoval", static_cast<float>
                                        (this->GetNormalizedIsovalue()));    
    RenderProxyGeometry();

    if (m_bDoClearView) {
      m_TargetBinder.Bind(m_pFBOCVHit[size_t(eStereoID)], 0, m_pFBOCVHit[size_t(eStereoID)], 1);

      m_pProgramIso->Enable();
      m_pProgramIso->Set("fIsoval", static_cast<float>
                                                 (GetNormalizedCVIsovalue()));
      RenderProxyGeometry();
    }
  } else {
    m_pContext->GetStateManager()->SetDepthMask(false);

    m_TargetBinder.Bind(m_pFBO3DImageNext[size_t(eStereoID)]);
    SetBrickDepShaderVars(b);
    RenderProxyGeometry();
  }
  m_TargetBinder.Unbind();
}