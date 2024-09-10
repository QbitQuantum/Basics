// Draw - must be positioned after all the controls are defined
//--------------------------------------------------------------------------------
void CPUTGuiControllerDX11::Draw(ID3D11DeviceContext *pImmediateContext)
{
    HEAPCHECK;

    if( 0 != GetNumberOfControlsInPanel())
    {
        SetGUIDrawingState(pImmediateContext);
    }
    else
    {
        return;
    }

    ID3D11VertexShader *pVertexShader = mpGUIVertexShader->GetNativeVertexShader();
    ID3D11PixelShader  *pPixelShader  = mpGUIPixelShader->GetNativePixelShader();

    // check and see if any of the controls resized themselves
    int ControlCount=GetNumberOfControlsInPanel();
    bool ResizingNeeded = false;
    for(int ii=0; ii<ControlCount; ii++)
    {
        CPUTControl *pControl = mControlPanelIDList[mActiveControlPanelSlotID]->mControlList[ii];
        if(true == pControl->ControlResizedItself())
        {
            ResizingNeeded = true;
            pControl->ControlResizingHandled();
        }
    }

    // if any of the controls resized, then re-do the autoarrangment
    if(true == ResizingNeeded)
    {
        this->Resize();
    }

    // Now check to see if any controls' graphics are dirty
    for(int ii=0; ii<ControlCount; ii++)
    {
        CPUTControl *pControl = mControlPanelIDList[mActiveControlPanelSlotID]->mControlList[ii];
        if(true == pControl->ControlGraphicsDirty())
        {
            mUberBufferDirty = true;
            break;
        }
    }

    // if any of the controls have announced they are dirty, then rebuild the mirror buffer and update the GFX buffer
    if(mUberBufferDirty)
    {
        
        // if a resize was flagged, do it now.  
        if(mRecalculateLayout)
        {
            RecalculateLayout();
        }


        // 'clear' the buffer by resetting the pointer to the head
        mUberBufferIndex = 0;
        mTextUberBufferIndex = 0;
        mFocusedControlBufferIndex = 0;
        mFocusedControlTextBufferIndex = 0;

        int ii=0;
        while(ii<GetNumberOfControlsInPanel())
        {
            CPUTControl *pControl = mControlPanelIDList[mActiveControlPanelSlotID]->mControlList[ii];

            // don't draw the focus control - draw it last so it stays on 'top'
            if(mpFocusControl != pControl)
            {
                switch(pControl->GetType())
                {
                case CPUT_BUTTON:
                    ((CPUTButton*)pControl)->DrawIntoBuffer(mpMirrorBuffer, &mUberBufferIndex, mUberBufferMax, mpTextMirrorBuffer, &mTextUberBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);                    
                    break;
                case CPUT_CHECKBOX:
                    ((CPUTCheckbox*)pControl)->DrawIntoBuffer(mpMirrorBuffer, &mUberBufferIndex, mUberBufferMax, mpTextMirrorBuffer, &mTextUberBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                    break;
                case CPUT_SLIDER:
                    ((CPUTSlider*)pControl)->DrawIntoBuffer(mpMirrorBuffer, &mUberBufferIndex, mUberBufferMax, mpTextMirrorBuffer, &mTextUberBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                    break;
                case CPUT_DROPDOWN:
                    ((CPUTDropdown*)pControl)->DrawIntoBuffer(mpMirrorBuffer, &mUberBufferIndex, mUberBufferMax, mpTextMirrorBuffer, &mTextUberBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                    break;

                case CPUT_STATIC:
                    ((CPUTText*)pControl)->DrawIntoBuffer(mpTextMirrorBuffer, &mTextUberBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                    break;
                }
            }
            ii++;
            HEAPCHECK
        }

        // do the 'focused' control last so it stays on top (i.e. dropdowns)
        if(mpFocusControl)
        {
            switch(mpFocusControl->GetType())
            {
            case CPUT_BUTTON:
                ((CPUTButton*)mpFocusControl)->DrawIntoBuffer(mpFocusedControlMirrorBuffer, &mFocusedControlBufferIndex, mUberBufferMax, mpFocusedControlTextMirrorBuffer, &mFocusedControlTextBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);                    
                break;
            case CPUT_CHECKBOX:
                ((CPUTCheckbox*)mpFocusControl)->DrawIntoBuffer(mpFocusedControlMirrorBuffer, &mFocusedControlBufferIndex, mUberBufferMax, mpFocusedControlTextMirrorBuffer, &mFocusedControlTextBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                break;
            case CPUT_SLIDER:
                ((CPUTSlider*)mpFocusControl)->DrawIntoBuffer(mpFocusedControlMirrorBuffer, &mFocusedControlBufferIndex, mUberBufferMax, mpFocusedControlTextMirrorBuffer, &mFocusedControlTextBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                break;
            case CPUT_DROPDOWN:
                ((CPUTDropdown*)mpFocusControl)->DrawIntoBuffer(mpFocusedControlMirrorBuffer, &mFocusedControlBufferIndex, mUberBufferMax, mpFocusedControlTextMirrorBuffer, &mFocusedControlTextBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                break;
            case CPUT_STATIC:
                ((CPUTText*)mpFocusControl)->DrawIntoBuffer(mpFocusedControlMirrorBuffer, &mFocusedControlTextBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);
                break;
            }
        }
        
                
        // update the uber-buffers with the control graphics
        UpdateUberBuffers(pImmediateContext);

        // Clear dirty flag on uberbuffer
        mUberBufferDirty = false;

    }
    HEAPCHECK



    // calculate the fps
    double elapsed = mpFPSTimer->GetElapsedTime();
    double fps = 1.0 / elapsed;
    mLastFPS = (float) fps;

    // if we're drawing the FPS counter - update that
    // We do this independently of uber-buffer updates since we'll have FPS updates every frame,
    // but likely not have control updates every frame
    if(mbDrawFPS)
    {
        // calculate the time elapsed since last frame
        bool UberBufferWasDirty = mUberBufferDirty;

        cString Data;
        {
            wchar_t wcstring[CPUT_MAX_STRING_LENGTH];
            swprintf_s(&wcstring[0], CPUT_MAX_STRING_LENGTH, _L("%.2f"), fps);
            Data=wcstring;
        }
        // build the FPS string
        cString FPS = _L("FPS: ")+Data;
        mpFPSCounter->SetText(FPS);        

        // 'draw' the string into the buffer
        mFPSBufferIndex = 0;
        mpFPSCounter->DrawIntoBuffer(mpFPSMirrorBuffer, &mFPSBufferIndex, CPUT_GUI_BUFFER_STRING_SIZE);

        // update the DirectX vertex buffer
        ASSERT(CPUT_GUI_BUFFER_STRING_SIZE > mFocusedControlTextBufferIndex, _L("CPUT GUI: Too many strings for default-sized uber-buffer.  Increase CPUT_GUI_BUFFER_STRING_SIZE"));
        pImmediateContext->UpdateSubresource(mpFPSDirectXBuffer, 0, NULL, mpFPSMirrorBuffer, mFPSBufferIndex*sizeof(CPUTGUIVertex), 0);
        
        // start next frame timer
        mpFPSTimer->StartTimer();
        if(false == UberBufferWasDirty)
        {
            mUberBufferDirty = false;
        }
    }


    // set up orthographic display
    int windowWidth, windowHeight;
    GUIConstantBufferVS ConstantBufferMatrices;
    float znear = 0.1f;
    float zfar = 100.0f;
    XMMATRIX m;

    CPUTOSServices *pServices = CPUTOSServices::GetOSServices();
    pServices->GetClientDimensions( &windowWidth, &windowHeight );
    m = XMMatrixOrthographicOffCenterLH(0, (float)windowWidth, (float)windowHeight, 0, znear, zfar);
    ConstantBufferMatrices.Projection = XMMatrixTranspose( m );

    // set the vertex shader
    pImmediateContext->VSSetShader( pVertexShader, NULL, 0 );
    UINT VertexStride = sizeof(CPUTGUIVertex);
    UINT VertexOffset = 0;
    pImmediateContext->IASetVertexBuffers( 0, 1, &mpUberBuffer, &VertexStride, &VertexOffset );

    m = XMMatrixIdentity();
    ConstantBufferMatrices.Model = XMMatrixTranspose( m );
    pImmediateContext->UpdateSubresource( mpConstantBufferVS, 0, NULL, &ConstantBufferMatrices, 0, 0 );
    pImmediateContext->VSSetConstantBuffers( 0, 1, &mpConstantBufferVS );

    // -- draw the normal controls --    
    // draw the control graphics
    pImmediateContext->PSSetShader( pPixelShader, NULL, 0 );
    pImmediateContext->PSSetShaderResources( 0, 1, &mpControlTextureAtlasView );    
    pImmediateContext->Draw(mUberBufferIndex,0);

    // draw the control's text
    pImmediateContext->PSSetShaderResources( 0, 1, &mpTextTextureAtlasView );
    pImmediateContext->IASetVertexBuffers( 0, 1, &mpTextUberBuffer, &VertexStride, &VertexOffset );
    // draw the text uber-buffer
    pImmediateContext->Draw(mTextUberBufferIndex,0);

    // draw the FPS counter
    if(mbDrawFPS)
    {
        pImmediateContext->IASetVertexBuffers( 0, 1, &mpFPSDirectXBuffer, &VertexStride, &VertexOffset );
        pImmediateContext->Draw(mFPSBufferIndex, 0);
    }
    
    // -- draw the focused control --
    // Draw the focused control's graphics
    pImmediateContext->PSSetShader( pPixelShader, NULL, 0 );
    pImmediateContext->PSSetShaderResources( 0, 1, &mpControlTextureAtlasView );
    pImmediateContext->IASetVertexBuffers( 0, 1, &mpFocusedControlBuffer, &VertexStride, &VertexOffset );
    // draw the uber-buffer
    pImmediateContext->Draw(mFocusedControlBufferIndex,0);


    // Draw the focused control's text
    pImmediateContext->PSSetShaderResources( 0, 1, &mpTextTextureAtlasView );
    pImmediateContext->IASetVertexBuffers( 0, 1, &mpFocusedControlTextBuffer, &VertexStride, &VertexOffset );
    // draw the text uber-buffer
    pImmediateContext->Draw(mFocusedControlTextBufferIndex,0);


    // restore the drawing state
    ClearGUIDrawingState(pImmediateContext);
    HEAPCHECK;
}