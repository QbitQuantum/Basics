// Handle keyboard events
//-----------------------------------------------------------------------------
CPUTEventHandledCode MySample::HandleKeyboardEvent(CPUTKey key)
{
    static bool panelToggle = false;
    CPUTEventHandledCode    handled = CPUT_EVENT_UNHANDLED;
    cString fileName;
    CPUTGuiControllerDX11*  pGUI = CPUTGetGuiController();

    switch(key)
    {
    case KEY_F1:
        panelToggle = !panelToggle;
        if(panelToggle)
        {
            pGUI->SetActivePanel(ID_SECONDARY_PANEL);
        }
        else
        {
            pGUI->SetActivePanel(ID_MAIN_PANEL);
        }
        handled = CPUT_EVENT_HANDLED;
        break;
    case KEY_L:
        {
            static int cameraObjectIndex = 0;
            CPUTRenderNode *pCameraList[] = { mpCamera, mpShadowCamera };
            cameraObjectIndex = (++cameraObjectIndex) % (sizeof(pCameraList)/sizeof(*pCameraList));
            CPUTRenderNode *pCamera = pCameraList[cameraObjectIndex];
            mpCameraController->SetCamera( pCamera );
        }
        handled = CPUT_EVENT_HANDLED;
        break;
    case KEY_ESCAPE:
        handled = CPUT_EVENT_HANDLED;
        Shutdown();
        break;

	case KEY_1:
		{
			CPUTToggleFullScreenMode();
			break;
		}
	case KEY_2:
		{
			mEnableCulling = !mEnableCulling;
			CPUTCheckboxState state;
			if(mEnableCulling)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else 
			{
				state = CPUT_CHECKBOX_UNCHECKED;
				memset(mpCPUDepthBuf[mCurrId], 0, SCREENW * SCREENH *4);

				mpOccludersR2DBText->SetText(         _L("\tDepth rasterized models: 0"));
				mpOccluderRasterizedTrisText->SetText(_L("\tDepth rasterized tris: \t0"));
				mpRasterizeTimeText->SetText(         _L("\tDepth rasterizer time: \t0 ms"));

				mpCulledText->SetText(       _L("\tModels culled: \t\t0"));
				mpVisibleText->SetText(      _L("\tModels visible: \t\t0"));
				mpCulledTrisText->SetText(   _L("\tCulled tris: \t\t0"));
				mpVisibleTrisText->SetText(   _L("\tVisible tris: \t\t0"));
				mpDepthTestTimeText->SetText(_L("\tDepth test time: \t0 ms"));
			}
			mpCullingCheckBox->SetCheckboxState(state);
			break;
		}
	case KEY_3:
		{
			mEnableFCulling = !mEnableFCulling;
			CPUTCheckboxState state;
			if(mEnableFCulling)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else
			{
				state = CPUT_CHECKBOX_UNCHECKED;
				mpDBR->ResetInsideFrustum();
				mpAABB->ResetInsideFrustum();
			}
			mpFCullingCheckBox->SetCheckboxState(state);
			break;			
		}
	case KEY_4:
		{
			mViewDepthBuffer = !mViewDepthBuffer;
			CPUTCheckboxState state;
			if(mViewDepthBuffer)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else 
			{
				state = CPUT_CHECKBOX_UNCHECKED;
			}
			mpDBCheckBox->SetCheckboxState(state);
			break;
		}
	case KEY_5:
		{
			mViewBoundingBox = !mViewBoundingBox;
			CPUTCheckboxState state;
			if(mViewBoundingBox)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else
			{
				state = CPUT_CHECKBOX_UNCHECKED;
			}
			mpBBCheckBox->SetCheckboxState(state);
			break;
		}
	case KEY_6:
		{
			TaskCleanUp();
			mEnableTasks = !mEnableTasks;
			CPUTCheckboxState state;
			
			SAFE_DELETE_ARRAY(mpDBR);
			SAFE_DELETE_ARRAY(mpAABB);

			if(mEnableTasks)
			{
				state = CPUT_CHECKBOX_CHECKED;
				mpPipelineCheckBox->SetVisibility(true);
				mpDepthTestTaskSlider->SetVisibility(true);

				wchar_t string[CPUT_MAX_STRING_LENGTH];
				swprintf_s(&string[0], CPUT_MAX_STRING_LENGTH, _L("Depth Test Task: \t%d"), mNumDepthTestTasks);
				mpDepthTestTaskSlider->SetText(string);
			
				if(mSOCType == SCALAR_TYPE)
				{
					mpDBRScalarMT = new DepthBufferRasterizerScalarMT;
					mpDBR = mpDBRScalarMT;

					mpAABBScalarMT = new AABBoxRasterizerScalarMT;
					mpAABB = mpAABBScalarMT;
				}
				else if(mSOCType == SSE_TYPE)
				{
					mpDBRSSEMT = new DepthBufferRasterizerSSEMT;
					mpDBR = mpDBRSSEMT;
					
					mpAABBSSEMT = new AABBoxRasterizerSSEMT;
					mpAABB = mpAABBSSEMT;
				}
				mpAABB->SetDepthTestTasks(mNumDepthTestTasks);
			}
			else
			{
				state = CPUT_CHECKBOX_UNCHECKED;
				mpPipelineCheckBox->SetVisibility(false);
				mpDepthTestTaskSlider->SetVisibility(false);
				if(mSOCType == SCALAR_TYPE)
				{
					mpDBRScalarST = new DepthBufferRasterizerScalarST;
					mpDBR = mpDBRScalarST;
	
					mpAABBScalarST = new AABBoxRasterizerScalarST;
					mpAABB = mpAABBScalarST;
				}
				else if(mSOCType == SSE_TYPE)
				{
					mpDBRSSEST = new DepthBufferRasterizerSSEST;
					mpDBR = mpDBRSSEST;
					
					mpAABBSSEST = new AABBoxRasterizerSSEST;
					mpAABB = mpAABBSSEST;
				}	
			}
			mpDBR->CreateTransformedModels(mpAssetSetDBR, OCCLUDER_SETS);		
			mpDBR->SetOccluderSizeThreshold(mOccluderSizeThreshold);
			mpAABB->CreateTransformedAABBoxes(mpAssetSetAABB, OCCLUDEE_SETS);
			mpAABB->SetOccludeeSizeThreshold(mOccludeeSizeThreshold);
			mpTasksCheckBox->SetCheckboxState(state);
			break;
		}
	case KEY_7:
		{
			if(mSyncInterval == 1)
			{
				mSyncInterval = 0;
			}
			else 
			{
				mSyncInterval = 1;
			}
			CPUTCheckboxState state;
			if(mSyncInterval == 1)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else
			{
				state = CPUT_CHECKBOX_UNCHECKED;
			}
			mpVsyncCheckBox->SetCheckboxState(state);
			break;
		}
	case KEY_8:
		{
			TaskCleanUp();
			mPipeline = !mPipeline;
			CPUTCheckboxState state;
			if(mPipeline)
			{
				state = CPUT_CHECKBOX_CHECKED;
			}
			else
			{
				state = CPUT_CHECKBOX_UNCHECKED;
			}
			mpPipelineCheckBox->SetCheckboxState(state);
			break;
		}
    }
	

    // pass it to the camera controller
    if(handled == CPUT_EVENT_UNHANDLED)
    {
        handled = mpCameraController->HandleKeyboardEvent(key);
    }
    return handled;
}