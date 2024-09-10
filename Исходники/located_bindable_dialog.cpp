//***********************************************************************************
void CLocatedBindableDialog::init(CParticleDlg* pParent)
{
	Create(IDD_LOCATED_BINDABLE, pParent);
	ShowWindow(SW_SHOW);
	_ParticleDlg = pParent;

	NL3D::CParticleSystem *ps = _Bindable->getOwner()->getOwner();
	if (ps->isSharingEnabled())
	{	
		GetDlgItem(IDC_NO_AUTO_LOD)->ShowWindow(TRUE);
		if (ps->isAutoLODEnabled() == false)
		{
			GetDlgItem(IDC_NO_AUTO_LOD)->EnableWindow(FALSE);
		}
		else
		{
			((CButton *) GetDlgItem(IDC_NO_AUTO_LOD))->SetCheck(NLMISC::safe_cast<NL3D::CPSParticle *>(_Bindable)->isAutoLODDisabled());
		}
	}
	else
	{
		GetDlgItem(IDC_NO_AUTO_LOD)->ShowWindow(FALSE);
	}

	uint yPos = 60;
	const uint xPos = 5;
	RECT rect;


	// control at the top of the sheet are not available for meshs & constraint meshes, so use that extra space
	if (dynamic_cast<NL3D::CPSMesh *>(_Bindable) || dynamic_cast<NL3D::CPSConstraintMesh *>(_Bindable))
	{
		yPos = 0;
	}

	// has the particle a material ?
	if (dynamic_cast<NL3D::CPSMaterial *>(_Bindable))
	{
		NL3D::CPSMaterial *material = dynamic_cast<NL3D::CPSMaterial *>(_Bindable);
		// blending mode
		m_BlendingMode.SetCurSel((uint) material->getBlendingMode() );
		// z-test		
		((CButton *) GetDlgItem(IDC_ZTEST))->SetCheck(material->isZTestEnabled() ? BST_CHECKED : BST_UNCHECKED);
		// z-bias
		GetDlgItem(IDC_ZBIAS)->SetWindowText(NLMISC::toString("%.2f", -material->getZBias()).c_str());						
	}
	else
	{
		m_BlendingMode.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BLENDING_MODE_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ZTEST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ZBIAS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ZBIAS_TEXT)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_ALIGN_ON_MOTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZALIGN)->ShowWindow(SW_HIDE);
	// enable disable z-test	
	//
	if (dynamic_cast<NL3D::CPSParticle *>(_Bindable))
	{
		NL3D::CPSParticle *p = (NL3D::CPSParticle *) _Bindable;

		// check support for lighting
		if (p->supportGlobalColorLighting())
		{
			GetDlgItem(ID_GLOBAL_COLOR_LIGHTING)->ShowWindow(SW_SHOW);
			// if global color lighting is forced for all objects, don't allow to modify
			GetDlgItem(ID_GLOBAL_COLOR_LIGHTING)->EnableWindow(ps->getForceGlobalColorLightingFlag() ? FALSE : TRUE);
			((CButton *) GetDlgItem(ID_GLOBAL_COLOR_LIGHTING))->SetCheck(p->usesGlobalColorLighting() ? 1 : 0);
		}
		else
		{
			GetDlgItem(ID_GLOBAL_COLOR_LIGHTING)->ShowWindow(SW_HIDE);
		}
		// check support for color
		if (dynamic_cast<NL3D::CPSColoredParticle *>(_Bindable))
		{
			
			CAttribDlgRGBA *ad = new CAttribDlgRGBA("PARTICLE_COLOR", _Node);
			pushWnd(ad);

			_ColorWrapper.S = dynamic_cast<NL3D::CPSColoredParticle *>(_Bindable);		
			ad->setWrapper(&_ColorWrapper);			
			ad->setSchemeWrapper(&_ColorWrapper);

			HBITMAP bmh = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PARTICLE_COLOR));
			ad->init(bmh, xPos, yPos, this);
			ad->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}

		// init size ctrl
		_SizeCtrlX = xPos;
		_SizeCtrlY = yPos;
		yPos += updateSizeControl();

		// check support for angle 2D
		if (dynamic_cast<NL3D::CPSRotated2DParticle *>(_Bindable))
		{
			
			CAttribDlgFloat *ad = new CAttribDlgFloat("PARTICLE_ANGLE2D", _Node, 0.f, 256.f);
			pushWnd(ad);

			_Angle2DWrapper.S = dynamic_cast<NL3D::CPSRotated2DParticle *>(_Bindable);
			ad->setWrapper(&_Angle2DWrapper);						
			ad->setSchemeWrapper(&_Angle2DWrapper);	

			HBITMAP bmh = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PARTICLE_ANGLE));
			ad->init(bmh, xPos, yPos, this);
			ad->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}

		

		CAttribDlgPlaneBasis *pb = NULL;

		// check support for plane basis
		if (dynamic_cast<NL3D::CPSRotated3DPlaneParticle *>(_Bindable))
		{
			pb = new CAttribDlgPlaneBasis("PARTICLE_PLANE_BASIS", _Node);
			pushWnd(pb);
			_PlaneBasisWrapper.S = dynamic_cast<NL3D::CPSRotated3DPlaneParticle *>(_Bindable);
			pb->setWrapper(&_PlaneBasisWrapper);
			pb->setSchemeWrapper(&_PlaneBasisWrapper);
			HBITMAP bmh = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BASIS));
			pb->init(bmh, xPos, yPos, this);
			pb->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		
		}

		// check support for precomputed rotations
		if (dynamic_cast<NL3D::CPSHintParticleRotateTheSame *>(_Bindable))
		{
			CPrecomputedRotationsDlg *pr = new CPrecomputedRotationsDlg(_Node, dynamic_cast<NL3D::CPSHintParticleRotateTheSame *>(_Bindable), pb);
			pushWnd(pr);
			pr->init(this, xPos, yPos);
			pr->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}

		// if we're dealing with a face look at, motion blur can be tuned
		if (dynamic_cast<NL3D::CPSFaceLookAt *>(_Bindable))
		{
			NL3D::CPSFaceLookAt *fla = static_cast<NL3D::CPSFaceLookAt *>(_Bindable);
			CEditableRangeFloat *mbc = new CEditableRangeFloat(std::string("MOTION_BLUR_COEFF"), _Node, 0, 5);
			pushWnd(mbc);
			_MotionBlurWnd.push_back(mbc);
			_MotionBlurCoeffWrapper.P = fla;
			mbc->setWrapper(&_MotionBlurCoeffWrapper);
			mbc->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			_MotionBlurWnd.push_back(s);
			s->Create("Fake motion blur coeff.", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);
			mbc->GetClientRect(&rect);
			yPos += rect.bottom + 3;
			mbc = new CEditableRangeFloat(std::string("MOTION_BLUR_THRESHOLD"), _Node, 0, 5);
			pushWnd(mbc);
			_MotionBlurWnd.push_back(mbc);
			_MotionBlurThresholdWrapper.P = fla;
			mbc->setWrapper(&_MotionBlurThresholdWrapper);
			mbc->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			_MotionBlurWnd.push_back(s);
			s->Create("Fake motion blur threshold.", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
			s->ShowWindow(SW_SHOW);
			mbc->GetClientRect(&rect);
			yPos += rect.bottom + 3;				
			GetDlgItem(IDC_ALIGN_ON_MOTION)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ZALIGN)->ShowWindow(SW_SHOW);
			((CButton *) GetDlgItem(IDC_ALIGN_ON_MOTION))->SetCheck(fla->getAlignOnMotion());
			((CButton *) GetDlgItem(IDC_ZALIGN))->SetCheck(fla->getAlignOnZAxis());
			updateValidWndForAlignOnMotion(fla->getAlignOnMotion());
		}

		// if we're dealing with a shockwave, we add dlg for the radius cut, and the number of segments
		if (dynamic_cast<NL3D::CPSShockWave *>(_Bindable))
		{
			NL3D::CPSShockWave *sw = static_cast<NL3D::CPSShockWave *>(_Bindable);
			CEditableRangeFloat *rc = new CEditableRangeFloat(std::string("RADIUS CUT"), _Node, 0, 1);
			pushWnd(rc);			
			_RadiusCutWrapper.S = sw;
			rc->setWrapper(&_RadiusCutWrapper);
			rc->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			s->Create("Radius cut.", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);


			rc->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			CEditableRangeUInt *snbs = new CEditableRangeUInt(std::string("SHOCK WAVE NB SEG"), _Node, 3, 24);
			pushWnd(snbs);
			_ShockWaveNbSegWrapper.S = sw;
			snbs->enableLowerBound(3, false);
			snbs->setWrapper(&_ShockWaveNbSegWrapper);
			snbs->init(xPos + 140, yPos, this);

			s = new CStatic;			
			pushWnd(s);
			s->Create("Nb segs", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->ShowWindow(SW_SHOW);

			snbs->GetClientRect(&rect);
			yPos += rect.bottom + 3;


			CEditableRangeFloat *uvd = new CEditableRangeFloat(std::string("TEX UFACTOR"), _Node, 0, 5);
			pushWnd(uvd);
			_ShockWaveUFactorWrapper.S = sw;
			uvd->setWrapper(&_ShockWaveUFactorWrapper);
			uvd->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			s->Create("Texture U factor :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->ShowWindow(SW_SHOW);
			uvd->GetClientRect(&rect);
			yPos += rect.bottom + 3;	
			
		}

		// fanlight
		if (dynamic_cast<NL3D::CPSFanLight *>(_Bindable))
		{
			CEditableRangeUInt *nbf = new CEditableRangeUInt(std::string("NB_FANS"), _Node, 3, 127);
			pushWnd(nbf);
			nbf->enableLowerBound(3, false);
			nbf->enableUpperBound(128, true);
			_FanLightWrapper.P = dynamic_cast<NL3D::CPSFanLight *>(_Bindable);
			nbf->setWrapper(&_FanLightWrapper);
			nbf->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			s->Create("Nb fan lights :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);

			nbf->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			nbf = new CEditableRangeUInt(std::string("PHASE_SMOOTHNESS"), _Node, 0, 31);
			pushWnd(nbf);
			nbf->enableUpperBound(32, true);
			_FanLightSmoothnessWrapper.P = static_cast<NL3D::CPSFanLight *>(_Bindable);
			nbf->setWrapper(&_FanLightSmoothnessWrapper);
			nbf->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			s->Create("Phase smoothnes:", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->ShowWindow(SW_SHOW);

			nbf->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			CEditableRangeFloat *nbfp = new CEditableRangeFloat(std::string("FAN_LIGHT_PHASE"), _Node, 0, 4.f);
			pushWnd(nbfp);			
			_FanLightPhaseWrapper.P = static_cast<NL3D::CPSFanLight *>(_Bindable);
			nbfp->setWrapper(&_FanLightPhaseWrapper);
			nbfp->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			s->Create("Fan light speed :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->ShowWindow(SW_SHOW);

			nbf->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			nbfp = new CEditableRangeFloat(std::string("FAN_LIGHT_INTENSITY"), _Node, 0, 4.f);
			pushWnd(nbfp);			
			_FanLightIntensityWrapper.P = static_cast<NL3D::CPSFanLight *>(_Bindable);
			nbfp->setWrapper(&_FanLightIntensityWrapper);
			nbfp->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			s->Create("Fan light intensity:", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->ShowWindow(SW_SHOW);

			nbf->GetClientRect(&rect);
			yPos += rect.bottom + 3;

		}


		// tail particle
		if (dynamic_cast<NL3D::CPSTailParticle *>(_Bindable))
		{
			CEditableRangeUInt *nbs;
			if (!dynamic_cast<NL3D::CPSRibbonLookAt *>(_Bindable))
			{
				nbs = new CEditableRangeUInt(std::string("TAIL_NB_SEGS_"), _Node, 2, 16);
				nbs->enableLowerBound(1, true);
			}
			else
			{
				nbs = new CEditableRangeUInt(std::string("LOOKAT_RIBBON_TAIL_NB_SEGS_"), _Node, 2, 16);
				nbs->enableLowerBound(1, true);
			}

			pushWnd(nbs);

			if (dynamic_cast<NL3D::CPSTailDot *>(_Bindable))
			{
				nbs->enableUpperBound(256, true);
			}
			
			
			_TailParticleWrapper.P = dynamic_cast<NL3D::CPSTailParticle *>(_Bindable);
			nbs->setWrapper(&_TailParticleWrapper);
			nbs->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			s->Create("Nb segs :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);	
			
			nbs->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			CTailParticleDlg *tpd = new CTailParticleDlg(_Node, dynamic_cast<NL3D::CPSTailParticle *>(_Bindable));
			pushWnd(tpd);
			tpd->init(this, xPos, yPos);
				
			tpd->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}


		// shape particle
		if (dynamic_cast<NL3D::CPSShapeParticle *>(_Bindable))
		{
			CMeshDlg *md = new CMeshDlg(_Node, dynamic_cast<NL3D::CPSShapeParticle *>(_Bindable), _ParticleDlg);
			md->init(this, xPos, yPos);
			md->GetClientRect(&rect);
			yPos += rect.bottom + 3;
			pushWnd(md);
		}

		// constraint mesh particle
		if (dynamic_cast<NL3D::CPSConstraintMesh *>(_Bindable))
		{
			CConstraintMeshDlg *cmd = new CConstraintMeshDlg(static_cast<NL3D::CPSConstraintMesh *>(_Bindable));
			cmd->init(xPos, yPos, this);
			cmd->GetClientRect(&rect);
			yPos += rect.bottom + 3;
			CConstraintMeshTexDlg *cmtd = new CConstraintMeshTexDlg(static_cast<NL3D::CPSConstraintMesh *>(_Bindable),
																	this);
			cmtd->init(xPos, yPos, this);
			cmtd->GetClientRect(&rect);
			yPos += rect.bottom + 3;
			pushWnd(cmd);
			pushWnd(cmtd);			
		}



		// check support for animated texture
		if (dynamic_cast<NL3D::CPSTexturedParticle *>(_Bindable))
		{
			CTextureAnimDlg *td = new CTextureAnimDlg(_Node,
													  dynamic_cast<NL3D::CPSTexturedParticle *>(_Bindable),
													  dynamic_cast<NL3D::CPSMultiTexturedParticle *>(_Bindable)
													 );			
			pushWnd(td);
						
			td->init(xPos, yPos, this);
			td->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}

		// unanimated texture
		if (dynamic_cast<NL3D::CPSTexturedParticleNoAnim *>(_Bindable))
		{
			NL3D::CPSTexturedParticleNoAnim *tp = dynamic_cast<NL3D::CPSTexturedParticleNoAnim *>(_Bindable);
			_TextureNoAnimWrapper.TP = tp;
			CTextureChooser *tc = new CTextureChooser(dynamic_cast<NL3D::CPSMultiTexturedParticle *>(_Bindable), _Node);			
			tc->enableRemoveButton();
			tc->setWrapper(&_TextureNoAnimWrapper);
			pushWnd(tc);

			tc->init(xPos, yPos, this);
			tc->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}

		// ribbon texture (doesn't support texture animation for now)
		if (dynamic_cast<NL3D::CPSRibbon *>(_Bindable))
		{									
		
			// add dialog for uv tuning with ribbon
			CEditableRangeFloat *uvd = new CEditableRangeFloat(std::string("RIBBON UFACTOR"), _Node, 0, 5);
			pushWnd(uvd);
			_RibbonUFactorWrapper.R = static_cast<NL3D::CPSRibbon *>(_Bindable);
			uvd->setWrapper(&_RibbonUFactorWrapper);
			uvd->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			s->Create("Texture U factor :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);
			uvd->GetClientRect(&rect);
			yPos += rect.bottom + 3;

			uvd = new CEditableRangeFloat(std::string("RIBBON VFACTOR"), _Node, 0, 5);
			pushWnd(uvd);
			_RibbonVFactorWrapper.R = static_cast<NL3D::CPSRibbon *>(_Bindable);
			uvd->setWrapper(&_RibbonVFactorWrapper);
			uvd->init(xPos + 140, yPos, this);
			s = new CStatic;			
			pushWnd(s);
			s->Create("Texture V factor :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
			s->ShowWindow(SW_SHOW);
			uvd->GetClientRect(&rect);
			yPos += rect.bottom + 3;

		}		

		if (dynamic_cast<NL3D::CPSRibbonBase *>(_Bindable))
		{									
		
			// add dialog for uv tuning with ribbon
			CEditableRangeFloat *sd = new CEditableRangeFloat(std::string("SEGMENT DURATION"), _Node, 0.05f, 0.5f);
			sd->enableLowerBound(0, true);
			pushWnd(sd);
			_SegDurationWrapper.R = static_cast<NL3D::CPSRibbonLookAt *>(_Bindable);
			sd->setWrapper(&_SegDurationWrapper);
			sd->init(xPos + 140, yPos, this);
			CStatic *s = new CStatic;
			pushWnd(s);
			s->Create("Seg Duration :", SS_LEFT, CRect(xPos, yPos + 16, xPos + 139, yPos + 48), this);
			s->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));			
			s->ShowWindow(SW_SHOW);
			sd->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}
	
		// 'look at' independant sizes
		bool isLookAt = dynamic_cast<NL3D::CPSFaceLookAt *>(_Bindable) != NULL;		
		GetDlgItem(IDC_INDE_SIZES)->ShowWindow(isLookAt ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_SIZE_WIDTH)->ShowWindow(isLookAt ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_SIZE_HEIGHT)->ShowWindow(isLookAt ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_WIDTH_HEIGHT_BOX)->ShowWindow(isLookAt ? SW_SHOW : SW_HIDE);		
		((CButton *) GetDlgItem(IDC_SIZE_WIDTH))->SetCheck(1);
		if (isLookAt)
		{
			NL3D::CPSFaceLookAt *la = static_cast<NL3D::CPSFaceLookAt *>(_Bindable);
			m_IndependantSizes = la->hasIndependantSizes();
			((CButton *) GetDlgItem(IDC_INDE_SIZES))->SetCheck(m_IndependantSizes);
			updateIndependantSizes();
		}

		/// new ribbon base class
		if (dynamic_cast<NL3D::CPSRibbonBase *>(_Bindable))
		{
			CRibbonDlg *rd = new CRibbonDlg(_Node, static_cast<NL3D::CPSRibbonBase *>(_Bindable),
											this);
			rd->init(this, xPos, yPos);
			pushWnd(rd);
			rd->GetClientRect(&rect);
			yPos += rect.bottom + 3;
		}		
	}	
	UpdateData();
}