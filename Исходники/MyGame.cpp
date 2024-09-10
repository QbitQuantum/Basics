void Game_Run(HWND window)
{

	if (!d3ddev) return;
	myInput->DirectInput_UpdateState();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL , D3DCOLOR_XRGB(0, 108, 255), 1.0f, 0);

	// slow rendering to approximately 60 fps
	if (timeGetTime() > screentimer + 14)
	{
		screentimer = GetTickCount();
		//start rendering
		if (d3ddev->BeginScene())
		{		
			//Change the camera view
			View_Change();
			//concrete rendering............................................................
			D3DXMATRIX matWorld;
			D3DXMatrixTranslation(&matWorld, 0.0f,0.0f,0.0f);

			D3DXMATRIX mScal,mRot1,mRot2,mTrans,mFinal;   
			D3DXMatrixScaling(&mScal,20.0f,20.0f,20.0f);  
			D3DXMatrixTranslation(&mTrans,0,8000,0);
			D3DXMatrixRotationX(&mRot1, D3DX_PI/2); 
			D3DXMatrixRotationY(&mRot2, D3DX_PI/2); 
			mFinal=mScal*mRot1*mRot2*mTrans*matWorld;
			d3ddev->SetTransform(D3DTS_WORLD, &mFinal);
			for (int i=0;i<nums;i++)
			{
				d3ddev->SetMaterial(&mats[i]);
				d3ddev->SetTexture(0,textures[i]);
				mesh->DrawSubset(i);	
			}
			//font
			RECT rect={0,0,0,0};
			char strInfo[30];
			sprintf_s(strInfo, "(%.2f, %.2f, %.2f)", g_matWorld._41, g_matWorld._42, g_matWorld._43);
			string message = strInfo;
			font->DrawTextA(nullptr,message.c_str(),message.length(),&rect,DT_SINGLELINE | DT_NOCLIP | DT_LEFT,D3DCOLOR_XRGB(255,0,0));

			//Terrain
			myTerrain->RenderTerrain(&matWorld, false);

			//SkyBox
			D3DXMATRIX matSky,matTransSky,matRotSky;
			D3DXMatrixTranslation(&matTransSky,0.0f,-3500.0f,0.0f);
			D3DXMatrixRotationY(&matRotSky,-0.000005f*timeGetTime());
			matSky = matRotSky*matTransSky;
			mySkyBox->RenderSkyBox(&matSky,FALSE);
			//Cylinder
			D3DXMATRIX TransMatrix, RotMatrix, FinalMatrix;
			D3DXMatrixRotationX(&RotMatrix, -D3DX_PI * 0.5f);
			d3ddev->SetMaterial(&cylinderMat);
			for(int i = 0; i < 4; i++)
			{
				D3DXMatrixTranslation(&TransMatrix, -10000.0f, 0.0f, -15000.0f + (i * 20000.0f));
				FinalMatrix = RotMatrix * TransMatrix ;
				d3ddev->SetTransform(D3DTS_WORLD, &FinalMatrix);
				cylinder->DrawSubset(0);

				D3DXMatrixTranslation(&TransMatrix, 10000.0f, 0.0f, -15000.0f + (i * 20000.0f));
				FinalMatrix = RotMatrix * TransMatrix ;
				d3ddev->SetTransform(D3DTS_WORLD, &FinalMatrix);
				cylinder->DrawSubset(0);
			}
		


			//concrete rendering............................................................

			//stop rendering
			d3ddev->EndScene();
			d3ddev->Present(NULL, NULL, NULL, NULL);
		}
	}
	if (myInput->Key_Down(DIK_ESCAPE)) gameOver = true;
}