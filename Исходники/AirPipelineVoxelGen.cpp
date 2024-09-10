		void VoxelGenerator::Update( Renderable* pRenderable ,Pipeline* pPipeline)
		{
			if(!m_bDebugSVO)
				return;

			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
#if 1


#else
			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			pDevice->SetVP(0,0,128,128);

			//m_pCamera->Render2D(128,128);
			m_pRT->SetClearFlag(true,true,true);
			if(m_pRT->BeforeUpdate()){
				m_pCamera->Render2D(128,128);

				m_pGenVoxelTree->RenderOneObject(pEnt);

				m_pRT->AfterUpdate();
			}

#endif

#ifdef GPU_DEBUG
			pPipeline->GetMainWindow()->SetClearFlag(false,false,false);
			pPipeline->GetMainWindow()->BeforeUpdate();
			pPipeline->GetMainCamera()->Render2D(pPipeline->GetMainWindow()->GetWidth(),pPipeline->GetMainWindow()->GetHeight());

			pDevice->SetSRV(enPS,0,m_pNodeTree->GetSRV());
			pDevice->SetSRV(enPS,1,m_pVoxel->GetSRV());
			Matrix matViewProjInv;

			pPipeline->GetMainCamera()->GetViewProjMatrix(matViewProjInv);
			matViewProjInv.Inverse();

			Float4 v[5];
			memcpy(v,&matViewProjInv,sizeof(Matrix));
			v[4]	=	m_SVOParam;
			m_pDebugSVOMaterial->GetConstantBuffer()->UpdateData(v);
			m_pDebugSVOMaterial->RenderOneObject(pRenderable);

			pPipeline->GetMainWindow()->AfterUpdate(false);
#else
			U32 iLevel	=	GetTimer().m_FrameTime.fTotalTime;
			iLevel=iLevel>>1;
			iLevel%=4;
			iLevel+=2;
			static Data data;
			if(data.IsNull())
				Common::File::Load("../Data/AirMesh/Teapot.svo",data);
			U32*	pSVO	=	(U32*)data.buff;

			U32 uiDepth=0;
			U32 uiOffset[10]={0};
			U32	uiStack[10]={0};
			Float3 vOffset[8]={
				Float3(0,0,0),
				Float3(0,0,1),
				Float3(0,1,0),
				Float3(0,1,1),

				Float3(1,0,0),
				Float3(1,0,1),
				Float3(1,1,0),
				Float3(1,1,1),
			};
			Float3 vMin(-64,-64,-64);
			Float3 vHalfSize(64,64,64);
			float	fMaxDis		=	10000;
			while(1){
				for(U32 i=uiStack[uiDepth];i<8;){
					U32 addr		=	(uiOffset[uiDepth]+i);
					U32 uiChild	=	pSVO[addr];
					if(uiChild==0){
						i++;
						continue;
					}
					Float3	vNewMin	=	vMin+vOffset[i]*vHalfSize;
					Float3	vNewMax	=	vNewMin+vHalfSize;
					if(uiDepth	==	iLevel){
						((BoxRenderable*)m_pDebugSVORenderable)->m_WorldMatrix	=	Float44((vNewMin+vNewMax)*0.5,vHalfSize*0.5,Float4(0,0,0,1));
						m_pDebugSVOMaterial->RenderOneObject(m_pDebugSVORenderable);
						i++;
						continue;
					}else{
						uiStack[uiDepth]	=	i+1;
						uiDepth++;
						uiStack[uiDepth]	=	0;
						uiOffset[uiDepth]	=	uiChild;
						vHalfSize	/=	2.0f;
						vMin		=	vNewMin;
						i=0;
					}

				}
				if(uiDepth==0){
					break;
				}else{
					uiDepth--;
					vHalfSize*=2.0f;
					vMin	-=	vOffset[uiStack[uiDepth]-1]*vHalfSize;
				}
			}
#endif
		}