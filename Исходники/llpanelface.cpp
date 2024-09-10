void LLPanelFace::getState()
{
	LLViewerObject* objectp = LLSelectMgr::getInstance()->getSelection()->getFirstObject();

	LLCalc* calcp = LLCalc::getInstance();
	if( objectp
		&& objectp->getPCode() == LL_PCODE_VOLUME
		&& objectp->permModify())
	{
		BOOL editable = objectp->permModify();

		// only turn on auto-adjust button if there is a media renderer and the media is loaded
		childSetEnabled("textbox autofix",FALSE);
		//mLabelTexAutoFix->setEnabled ( FALSE );
		childSetEnabled("button align",FALSE);
		//mBtnAutoFix->setEnabled ( FALSE );
		
		//if ( LLMediaEngine::getInstance()->getMediaRenderer () )
		//	if ( LLMediaEngine::getInstance()->getMediaRenderer ()->isLoaded () )
		//	{	
		//		
		//		//mLabelTexAutoFix->setEnabled ( editable );
		//		
		//		//mBtnAutoFix->setEnabled ( editable );
		//	}
		S32 selected_count = LLSelectMgr::getInstance()->getSelection()->getObjectCount();
		BOOL single_volume = (LLSelectMgr::getInstance()->selectionAllPCode( LL_PCODE_VOLUME ))
						 && (selected_count == 1);
		
		childSetEnabled("copytextures", single_volume && editable);
		childSetEnabled("pastetextures", single_volume && editable);
		childSetEnabled("textbox params", single_volume && editable);
		childSetEnabled("button apply",editable);

		bool identical;
		LLTextureCtrl*	texture_ctrl = getChild<LLTextureCtrl>("texture control");
		
		// Texture
		{
			LLUUID id;
			struct f1 : public LLSelectedTEGetFunctor<LLUUID>
			{
				LLUUID get(LLViewerObject* object, S32 te)
				{
					LLViewerImage* image = object->getTEImage(te);
					return image ? image->getID() : LLUUID::null;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, id );

			if (identical)
			{
				// All selected have the same texture
				if(texture_ctrl)
				{
					texture_ctrl->setTentative( FALSE );
					texture_ctrl->setEnabled( editable );
					texture_ctrl->setImageAssetID( id );
				}
			}
			else
			{
				if(texture_ctrl)
				{
					if( id.isNull() )
					{
						// None selected
						texture_ctrl->setTentative( FALSE );
						texture_ctrl->setEnabled( FALSE );
						texture_ctrl->setImageAssetID( LLUUID::null );
					}
					else
					{
						// Tentative: multiple selected with different textures
						texture_ctrl->setTentative( TRUE );
						texture_ctrl->setEnabled( editable );
						texture_ctrl->setImageAssetID( id );
					}
				}
			}

			if(LLViewerMedia::textureHasMedia(id))
			{
				childSetEnabled("textbox autofix",editable);
				childSetEnabled("button align",editable);
			}

		}

		
		LLAggregatePermissions texture_perms;
		if(texture_ctrl)
		{
// 			texture_ctrl->setValid( editable );
		
			if (LLSelectMgr::getInstance()->selectGetAggregateTexturePermissions(texture_perms))
			{
				BOOL can_copy = 
					texture_perms.getValue(PERM_COPY) == LLAggregatePermissions::AP_EMPTY || 
					texture_perms.getValue(PERM_COPY) == LLAggregatePermissions::AP_ALL;
				BOOL can_transfer = 
					texture_perms.getValue(PERM_TRANSFER) == LLAggregatePermissions::AP_EMPTY || 
					texture_perms.getValue(PERM_TRANSFER) == LLAggregatePermissions::AP_ALL;
				texture_ctrl->setCanApplyImmediately(can_copy && can_transfer);
			}
			else
			{
				texture_ctrl->setCanApplyImmediately(FALSE);
			}
		}

		// planar align
		bool align_planar = false;
		bool identical_planar_aligned = false;
		{
			LLCheckBoxCtrl*	cb_planar_align = getChild<LLCheckBoxCtrl>("checkbox planar align");
			align_planar = (cb_planar_align && cb_planar_align->get());
			struct f1 : public LLSelectedTEGetFunctor<bool>
			{
				bool get(LLViewerObject* object, S32 face)
				{
					return (object->getTE(face)->getTexGen() == LLTextureEntry::TEX_GEN_PLANAR);
				}
			} func;
			
			bool is_planar;
			bool texgens_identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, is_planar );
			bool enabled = (editable && texgens_identical && is_planar);
			childSetValue("checkbox planar align", align_planar && enabled);
			childSetEnabled("checkbox planar align", enabled);
		
			if (align_planar && enabled)
			{
				struct f2 : public LLSelectedTEGetFunctor<LLFace *>
				{
					LLFace* get(LLViewerObject* object, S32 te)
					{
						return (object->mDrawable) ? object->mDrawable->getFace(te): NULL;
					}
				} get_te_face_func;
				LLFace* last_face;
				LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue(&get_te_face_func, last_face);
				LLPanelFaceGetIsAlignedTEFunctor get_is_aligend_func(last_face);
				// this will determine if the texture param controls are tentative:
				identical_planar_aligned = LLSelectMgr::getInstance()->getSelection()->applyToTEs(&get_is_aligend_func);
			}
		}
		
		// Texture scale
		{
			childSetEnabled("tex scale",editable);
			//mLabelTexScale->setEnabled( editable );
			F32 scale_s = 1.f;
			struct f2 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->mScaleS;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, scale_s );
			identical = align_planar ? identical_planar_aligned : identical;
			childSetValue("TexScaleU",editable ? llabs(scale_s) : 0);
			childSetTentative("TexScaleU",LLSD((BOOL)(!identical)));
			childSetEnabled("TexScaleU",editable);
			childSetValue("checkbox flip s",LLSD((BOOL)(scale_s < 0 ? TRUE : FALSE )));
			childSetTentative("checkbox flip s",LLSD((BOOL)((!identical) ? TRUE : FALSE )));
			childSetEnabled("checkbox flip s",editable);
		}

		{
			F32 scale_t = 1.f;
			struct f3 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->mScaleT;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, scale_t );
			identical = align_planar ? identical_planar_aligned : identical;

			childSetValue("TexScaleV",llabs(editable ? llabs(scale_t) : 0));
			childSetTentative("TexScaleV",LLSD((BOOL)(!identical)));
			childSetEnabled("TexScaleV",editable);
			childSetValue("checkbox flip t",LLSD((BOOL)(scale_t< 0 ? TRUE : FALSE )));
			childSetTentative("checkbox flip t",LLSD((BOOL)((!identical) ? TRUE : FALSE )));
			childSetEnabled("checkbox flip t",editable);
		}

		// Texture offset
		{
			childSetEnabled("tex offset",editable);
			F32 offset_s = 0.f;
			struct f4 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->mOffsetS;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, offset_s );
			identical = align_planar ? identical_planar_aligned : identical;
			childSetValue("TexOffsetU", editable ? offset_s : 0);
			childSetTentative("TexOffsetU",!identical);
			childSetEnabled("TexOffsetU",editable);
		}

		{
			F32 offset_t = 0.f;
			struct f5 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->mOffsetT;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, offset_t );
			identical = align_planar ? identical_planar_aligned : identical;
			childSetValue("TexOffsetV", editable ? offset_t : 0);
			childSetTentative("TexOffsetV",!identical);
			childSetEnabled("TexOffsetV",editable);
		}

		// Texture rotation
		{
			childSetEnabled("tex rotate",editable);
			F32 rotation = 0.f;
			struct f6 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->mRotation;
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, rotation );
			identical = align_planar ? identical_planar_aligned : identical;
			childSetValue("TexRot", editable ? rotation * RAD_TO_DEG : 0);
			childSetTentative("TexRot",!identical);
			childSetEnabled("TexRot",editable);
		}

		// Color swatch
		LLColorSwatchCtrl*	mColorSwatch = getChild<LLColorSwatchCtrl>("colorswatch");
		LLColor4 color = LLColor4::white;
		if(mColorSwatch)
		{
			struct f7 : public LLSelectedTEGetFunctor<LLColor4>
			{
				LLColor4 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->getColor();
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, color );
			
			mColorSwatch->setOriginal(color);
			mColorSwatch->set(color, TRUE);

			mColorSwatch->setValid(editable);
			mColorSwatch->setEnabled( editable );
			mColorSwatch->setCanApplyImmediately( editable );
		}
		// Color transparency
		{
			childSetEnabled("color trans",editable);
		}

		F32 transparency = (1.f - color.mV[VALPHA]) * 100.f;
		{
			childSetValue("ColorTrans", editable ? transparency : 0);
			childSetEnabled("ColorTrans",editable);
		}

		{
			F32 glow = 0.f;
			struct f8 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return object->getTE(face)->getGlow();
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, glow );

			childSetValue("glow",glow);
			childSetEnabled("glow",editable);
			childSetTentative("glow",!identical);
			childSetEnabled("glow label",editable);

		}

		// Bump
		{
			F32 shinyf = 0.f;
			struct f9 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return (F32)(object->getTE(face)->getShiny());
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, shinyf );
			LLCtrlSelectionInterface* combobox_shininess =
			      childGetSelectionInterface("combobox shininess");
			if (combobox_shininess)
			{
				combobox_shininess->selectNthItem((S32)shinyf);
			}
			else
			{
				llwarns << "failed childGetSelectionInterface for 'combobox shininess'" << llendl;
			}
			childSetEnabled("combobox shininess",editable);
			childSetTentative("combobox shininess",!identical);
			childSetEnabled("label shininess",editable);
		}

		{
			F32 bumpf = 0.f;
			struct f10 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return (F32)(object->getTE(face)->getBumpmap());
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, bumpf );
			LLCtrlSelectionInterface* combobox_bumpiness =
			      childGetSelectionInterface("combobox bumpiness");
			if (combobox_bumpiness)
			{
				combobox_bumpiness->selectNthItem((S32)bumpf);
			}
			else
			{
				llwarns << "failed childGetSelectionInterface for 'combobox bumpiness'" << llendl;
			}
			childSetEnabled("combobox bumpiness",editable);
			childSetTentative("combobox bumpiness",!identical);
			childSetEnabled("label bumpiness",editable);
		}

		{
			F32 genf = 0.f;
			struct f11 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return (F32)(object->getTE(face)->getTexGen());
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, genf );
			S32 selected_texgen = ((S32) genf) >> TEM_TEX_GEN_SHIFT;
			LLCtrlSelectionInterface* combobox_texgen =
			      childGetSelectionInterface("combobox texgen");
			if (combobox_texgen)
			{
				combobox_texgen->selectNthItem(selected_texgen);
			}
			else
			{
				llwarns << "failed childGetSelectionInterface for 'combobox texgen'" << llendl;
			}
			childSetEnabled("combobox texgen",editable);
			childSetTentative("combobox texgen",!identical);
			childSetEnabled("tex gen",editable);

			if (selected_texgen == 1)
			{
				childSetText("tex scale",getString("string repeats per meter"));
				childSetValue("TexScaleU", 2.0f * childGetValue("TexScaleU").asReal() );
				childSetValue("TexScaleV", 2.0f * childGetValue("TexScaleV").asReal() );
			}
			else
			{
				childSetText("tex scale",getString("string repeats per face"));
			}

		}

		{
			F32 fullbrightf = 0.f;
			struct f12 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					return (F32)(object->getTE(face)->getFullbright());
				}
			} func;
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, fullbrightf );

			childSetValue("checkbox fullbright",(S32)fullbrightf);
			childSetEnabled("checkbox fullbright",editable);
			childSetTentative("checkbox fullbright",!identical);
		}
		
		// Repeats per meter label
		{
			childSetEnabled("rpt",editable);
		}

		// Repeats per meter
		{
			F32 repeats = 1.f;
			struct f13 : public LLSelectedTEGetFunctor<F32>
			{
				F32 get(LLViewerObject* object, S32 face)
				{
					U32 s_axis = VX;
					U32 t_axis = VY;
					// BUG: Only repeats along S axis
					// BUG: Only works for boxes.
					LLPrimitive::getTESTAxes(face, &s_axis, &t_axis);
					return object->getTE(face)->mScaleS / object->getScale().mV[s_axis];
				}
			} func;			
			identical = LLSelectMgr::getInstance()->getSelection()->getSelectedTEValue( &func, repeats );
			
			childSetValue("rptctrl", editable ? repeats : 0);
			childSetTentative("rptctrl",!identical);
			LLComboBox*	mComboTexGen = getChild<LLComboBox>("combobox texgen");
			if (mComboTexGen)
			{
				BOOL enabled = editable && (!mComboTexGen || mComboTexGen->getCurrentIndex() != 1);
				childSetEnabled("rptctrl",enabled);
				childSetEnabled("button apply",enabled);
			}
		}

		// Set variable values for numeric expressions
		calcp->setVar(LLCalc::TEX_U_SCALE, childGetValue("TexScaleU").asReal());
		calcp->setVar(LLCalc::TEX_V_SCALE, childGetValue("TexScaleV").asReal());
		calcp->setVar(LLCalc::TEX_U_OFFSET, childGetValue("TexOffsetU").asReal());
		calcp->setVar(LLCalc::TEX_V_OFFSET, childGetValue("TexOffsetV").asReal());
		calcp->setVar(LLCalc::TEX_ROTATION, childGetValue("TexRot").asReal());
		calcp->setVar(LLCalc::TEX_TRANSPARENCY, childGetValue("ColorTrans").asReal());
		calcp->setVar(LLCalc::TEX_GLOW, childGetValue("glow").asReal());
	}