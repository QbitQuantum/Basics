		void TileBaseLight::Update( const FrameTime& frameTime,RenderTarget* pLighting )
		{
			if(m_vecPointLight.empty()){
				m_vecLayeredLight.resize(32768);
				memset(m_LayerInfo,0,sizeof(LayerInfo)*256);
			}

#ifdef _OPENMP
			omp_set_dynamic(1); 
			omp_set_num_threads(2); 
#pragma message("OPENMP Enable!")
#else
#pragma message("OPENMP Closed!")
#endif
			//BuildSO();

			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			void* pLightingUAV[]	=	{pLighting->GetUAV(0),pLighting->GetUAV(1)};
			pDevice->SetUAV(2,(void**)pLightingUAV);

			

			
			m_MainWaitBackEvent.Wait();

			m_pLightPosColor->UpdateData(&m_vecLayeredLight[0]);
			m_pLayerBuffer->UpdateData(m_LayerInfo);



			pDevice->SetSRV(enCS,2,m_pLightPosColor->GetSRV());
			pDevice->SetSRV(enCS,3,m_pLayerBuffer->GetSRV());

			Float4 v[10];
			v[0]=Float4(pLighting->GetWidth(),pLighting->GetHeight(),0,0);
			Matrix* pProjInvMat	=	(Matrix*)&v[1];
			m_pPipeline->GetMainCamera()->GetProjMatrix(*pProjInvMat);
			pProjInvMat->Inverse();
			Matrix* pViewMat	=	(Matrix*)&v[5];
			m_pPipeline->GetMainCamera()->GetViewMatrix(*pViewMat);


			Float3 v1=(*pProjInvMat)*Float3(1,1,0);
			
			v[0].z=	v1.x;
			v[0].w=v1.y;
			
			v[9]	=	Float4(
				Engine::GetGlobalSetting().m_pInputSystem->m_iX,
				Engine::GetGlobalSetting().m_pInputSystem->m_iY,
				m_vecPointLight.size(),
				0
				);


			m_pPointMaterial->GetConstantBuffer()->UpdateData(v);
			int x	=	(pLighting->GetWidth()+15)>>4;
			int y	=	(pLighting->GetHeight()+15)>>4;
			m_pCSRenderable->m_Dispatch[0]	=	x;
			m_pCSRenderable->m_Dispatch[1]	=	y;
			m_pPointMaterial->RenderOneObject(m_pCSRenderable);

			pDevice->SetShader(enCS,NULL);
			pLightingUAV[0]=NULL;
			pLightingUAV[1]=NULL;
			pDevice->SetUAV(2,(void**)pLightingUAV);

			m_vecPointLight.clear();
		}