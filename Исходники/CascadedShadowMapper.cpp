    void CascadedShadowMapper::VRender(ISceneGraph* graph)
    {

        IRenderer* renderer = CmGetApp()->VGetHumanView()->VGetRenderer();
        IDeviceTexture* vn[4];
        for(UCHAR i = 0; i < m_cascades + 1; ++i)
        {
            vn[i] = NULL;
        }
        renderer->VSetTextures(eEffect0, (vn+1), m_cascades);

        ICamera* playerView = graph->VGetCamera().get();

        Frustum cascadeFrusta;
        Frustum ortographicFrusta;

        CameraComponent* lcc = GetActorCompnent<CameraComponent>(m_lightActorCamera, CM_CMP_CAMERA);

        //std::shared_ptr<chimera::CameraComponent> vcc = m_viewActor->GetComponent<chimera::CameraComponent>(chimera::CameraComponent::COMPONENT_ID).lock();
        
        renderer->VPushViewTransform(lcc->GetCamera()->GetView(), lcc->GetCamera()->GetIView(), lcc->GetCamera()->GetEyePos(), lcc->GetCamera()->GetViewDir());

        ICamera* lightCamera = lcc->GetCamera().get();
        //util::ICamera* viewCamera = vcc->GetCamera().get();
        ICamera* viewCamera = playerView;

        //util::Mat4 viewToLight = util::Mat4::Mul(lightCamera->GetView(), viewCamera->GetIView());//vcc->GetCamera()->GetIView());

        float distances[3];

        for(UCHAR ci = 0; ci < m_cascades; ++ci)
        {
            CascadeSettings& settings = m_pCascadesSettings[ci];
            
            /*util::StaticCamera* staticCam;
            staticCam = (util::StaticCamera*)(m_cascadeCameraActor[ci]->GetComponent<chimera::CameraComponent>(chimera::CameraComponent::COMPONENT_ID).lock()->GetCamera().get());*/

            float farr = settings.end;
            float nnear = settings.start;
 
            cascadeFrusta.CreatePerspective(viewCamera->GetAspect(), viewCamera->GetFoV(), nnear, farr);

            util::Vec3 vmin(FLT_MAX, FLT_MAX, FLT_MAX);
            util::Vec3 vmax(FLT_MIN, FLT_MIN, FLT_MIN);
            util::Vec3 vFrustumPoints[8];
            util::Vec3 vecs[8];

            for(uint i = 0; i < 8; ++i)
            {
                util::Vec3 v = util::Mat4::Transform(viewCamera->GetIView(), cascadeFrusta.GetPoints()[i]);

                vFrustumPoints[i] = v;

                util::Vec3 pos = util::Mat4::Transform(lightCamera->GetView(), v);

                vmax = util::Vec3::Max(vmax, pos);
                vmin = util::Vec3::Min(vmin, pos);
            }

            /*FLOAT bound = (farr - nnear) / 1024.0f;

            util::Vec3 fmin((INT)vmin.x / bound, (INT)vmin.y / bound, (INT)vmin.y / bound);
            fmin.Scale(bound);
            vmin = fmin;

            util::Vec3 fmax((INT)(vmax.x / bound), (INT)(vmax.y / bound), (INT)(vmax.y / bound));
            fmax.Scale(bound);
            vmax = fmax; */

            /*vmax = util::Mat4::Transform(lightCamera->GetIView(), vmax);
            vmin = util::Mat4::Transform(lightCamera->GetIView(), vmin); */
            /*util::Vec3 vDiagonal = vFrustumPoints[tbd::rightUpNear] - vFrustumPoints[tbd::leftDownFar];
            FLOAT l = vDiagonal.Length();
            vDiagonal.Set(l, l, l);
            // The offset calculated will pad the ortho projection so that it is always the same size 
            // and big enough to cover the entire cascade interval.
            util::Vec3 diff = vmax - vmin;
            util::Vec3 vBoarderOffset = vDiagonal - diff;
            vBoarderOffset.Scale(0.5f);

            vBoarderOffset.z = 0;
            // Add the offsets to the projection.
            vmax = vmax + vBoarderOffset;
            vmin = vmin - vBoarderOffset; */
            
            float n = min(-120, vmin.z); //todo
            float ff = vmax.z;

            distances[ci] = ff - n;

            XMMATRIX mat = XMMatrixOrthographicOffCenterLH(vmin.x, vmax.x, vmin.y, vmax.y, n, ff);

            XMStoreFloat4x4(&settings.m_projection.m_m, mat);

            /*
            util::StaticCamera staticCam(1,1,1,1);
#ifdef CSM_DEBUG
            staticCam.SetOrthographicProjectionOffCenter(vmin.x, vmax.x, vmin.y, vmax.y, n, ff);
            staticCam.SetView(lightCamera->GetView(), lightCamera->GetIView());
            ortographicFrusta = staticCam.GetFrustum();
#endif*/
            ortographicFrusta.CreateOrthographicOffCenter(vmin.x, vmax.x, vmin.y, vmax.y, n, ff);
            ortographicFrusta.Transform(lightCamera->GetIView());
   
            renderer->VPushProjectionTransform(settings.m_projection, ff - n, 1);

            m_ppTargets[ci]->VClear();
            m_ppTargets[ci]->VBind();

            graph->VPushFrustum(&ortographicFrusta);
            m_pProgram->VBind();
            graph->VOnRender(CM_RENDERPATH_SHADOWMAP);

            m_pProgramInstanced->VBind();
            graph->VOnRender(CM_RENDERPATH_SHADOWMAP_INSTANCED);

            /*m_pProgramInstanced->VBind();
            graph->VOnRender(eRenderPath_DrawToShadowMapInstanced);*/
            graph->VPopFrustum();

            renderer->VPopProjectionTransform();

            m_ppBlurChain[ci]->VProcess();

         //   d3d::GetContext()->GenerateMips(m_ppBlurredTargets[ci]->GetShaderRessourceView());
        }

        renderer->VPopViewTransform();
        CmGetApp()->VGetHumanView()->VGetRenderer()->VGetCurrentRenderTarget()->VBind();

        IDeviceTexture* v[3];
        for(UCHAR i = 0; i < m_cascades; ++i)
        {
            v[i] = m_ppBlurredTargets[i]->VGetTexture();
        }
        renderer->VSetTextures(eEffect0, v, m_cascades);

        //ID3D11ShaderResourceView* debugView = m_ppBlurredTargets[0]->GetShaderRessourceView();
        //d3d::GetContext()->PSSetShaderResources(d3d::eEffect3, 1, &debugView); //debugging samplers
        
        util::Mat4 mats[3]; //TODO
        //FLOAT distances[3];
        for(UCHAR i = 0; i < m_cascades; ++i)
        {
            mats[i] = m_pCascadesSettings[i].m_projection;
        }

        IConstShaderBuffer* lb = renderer->VGetConstShaderBuffer(eEnvLightingBuffer);
        _LightingBuffer* _lb = (_LightingBuffer*)lb->VMap();
        _lb->m_view = lightCamera->GetView().m_m;
        _lb->m_iView = lightCamera->GetIView().m_m;
        _lb->m_projection[0] = mats[0].m_m;
        _lb->m_projection[1] = mats[1].m_m;
        _lb->m_projection[2] = mats[2].m_m;
        _lb->m_lightPos.x = lcc->GetCamera()->GetEyePos().x;
        _lb->m_lightPos.y = lcc->GetCamera()->GetEyePos().y;
        _lb->m_lightPos.z = lcc->GetCamera()->GetEyePos().z;
        _lb->m_intensity.x = m_intensity.x;
        _lb->m_intensity.y = m_intensity.y;
        _lb->m_intensity.z = m_intensity.z;
        _lb->m_ambient.x = m_ambient.x;
        _lb->m_ambient.y = m_ambient.y;
        _lb->m_ambient.z = m_ambient.z;
        _lb->m_distances.x = distances[0];
        _lb->m_distances.y = distances[1];
        _lb->m_distances.z = distances[2];
        lb->VUnmap();
       // renderer->SetCSMSettings(lightCamera->GetView(), lightCamera->GetIView(), mats, lcc->GetCamera()->GetEyePos(), distances);
    }