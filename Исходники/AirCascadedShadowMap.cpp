		Air::U1 CascadedShadowMap::UpdateCamera( Camera* pMainCamera )
		{
			Float3 axis(1,0.001,0.005);
			axis.Normalize();
			float fSec = -13;//floor(GetTimer().GetTotalTime());
			Common::Quaternion q(axis,fSec*0.001);//m_vLightDirection
			m_vLightDirection	=	q*Float3(-1,1,0.5).Normalize();//m_vLightDirection;
			m_vLightDirection.Normalize();
			if(m_vLightDirection.y>0){
				m_vLightDirection	=	-m_vLightDirection;
			}
			for(U32 i=0;i<m_vecCSMCamera.size();i++){
				m_vecCSMCamera[i]->SetDir(m_vLightDirection);
			}

			Float3 vCamPos	=	m_pMainCamera->GetRealPosition();
			Float3 vCamDir	=	m_pMainCamera->GetRealDirection();

			Matrix matPInv = m_pMainCamera->GetProjMatrix();
			matPInv.Inverse();
			Float3 v =	matPInv*Float3(1,1,0);
			float fSlope	=	sqrt(v.x*v.x+v.y*v.y);

			float fLastZ	=	1.0f;

			for(U32 i=0;i<m_vecCSMCamera.size();i++){
				Camera*	pLight	=	m_vecCSMCamera[i];
				float fRadius	=	pLight->GetWidth()*0.5f;
				float fSize	=	fSlope*fLastZ;
				float fDis	=	fLastZ+sqrt(fRadius*fRadius-fSize*fSize);
				Float3 vPos	=	vCamPos+vCamDir*fDis;

				float a		=	(fSlope*fSlope+1);
				float b		=	-2*fDis;
				float c		=	fDis*fDis-fRadius*fRadius;
				fLastZ		=	(-b+sqrt(b*b-4*a*c))/(2*a);
				

				float fScale	=	pLight->GetWidth()/1024.0f;
				///float fScale2	=	fScale*2/256.0f;
				Float3 pos		=	vPos-m_vLightDirection*200;

				Float44	view = pLight->GetViewMatrix();
				Float3 viewpos	=	view*pos;
				view.Inverse();
				viewpos/=fScale;
				viewpos	=	Float3(floor(viewpos.x),floor(viewpos.y),floor(viewpos.z))*fScale;
				Float3 vpos	=	view*viewpos;
				pLight->SetPosition(vpos);
			}


			return true;
		}