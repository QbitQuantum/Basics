    void on_draw() override
    {
        glfwMakeContextCurrent(window);

        if (igm) igm->begin_frame();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDepthMask(GL_TRUE);

        float windowAspectRatio = (float) width / (float) height;

        const auto proj = camera.get_projection_matrix(windowAspectRatio);
        const float4x4 view = camera.get_view_matrix();
        const float4x4 viewProj = mul(proj, view);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skydome.render(viewProj, camera.get_eye_point(), camera.farClip);

        float3 target = camera.pose.position;

        ////////////////////////////////////////////
        // Directional Light Shadowmap Pass (sun) //
        ////////////////////////////////////////////
        {
            shadowFramebuffer.bind_to_draw();
            shadowmapShader->bind();

            glClear(GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, shadowmapResolution, shadowmapResolution);

            shadowmapShader->uniform("u_lightViewProj", sunLight->get_view_proj_matrix(target));

            for (auto & object : sceneObjects)
            {
                if (object->castsShadow)
                {
                    shadowmapShader->uniform("u_modelMatrix", object->get_model());
                    object->draw();
                }
            }

            shadowmapShader->unbind();
            shadowFramebuffer.unbind();
        }


        ///////////////////////////////
        // Spot Light Shadowmap Pass //
        ///////////////////////////////
        {

            for (int i = 0; i < spotLightFramebuffers.size(); ++i)
            {
                spotLightFramebuffers[i]->shadowFramebuffer.bind_to_draw();
                shadowmapShader->bind();

                glClear(GL_DEPTH_BUFFER_BIT);
                glViewport(0, 0, shadowmapResolution, shadowmapResolution);

                shadowmapShader->uniform("u_lightViewProj", spotLights[0]->get_view_proj_matrix()); // only take the first into account for debugging

                for (auto & object : sceneObjects)
                {
                    if (object->castsShadow)
                    {
                        shadowmapShader->uniform("u_modelMatrix", object->get_model());
                        object->draw();
                    }
                }

                shadowmapShader->unbind();
                spotLightFramebuffers[i]->shadowFramebuffer.unbind();
            }

        }

        ////////////////////////////////
        // Point Light Shadowmap Pass //
        ////////////////////////////////
        {
            glViewport(0, 0, shadowmapResolution, shadowmapResolution);

            for (int i = 0; i < 6; ++i)
            {
                pointLightFramebuffer->bind(pointLightFramebuffer->faces[i].face);

                pointLightShader->bind();

                glClear(GL_DEPTH_BUFFER_BIT);

                pointLightFramebuffer->faces[i].faceCamera.set_position(pointLight->position); // set position from light data to camera for shadow fbo
                auto viewProj = mul(pointLightFramebuffer->get_projection(), pointLightFramebuffer->faces[i].faceCamera.get_view_matrix());

                pointLightShader->uniform("u_lightWorldPosition", pointLight->position);
                pointLightShader->uniform("u_lightViewProj", viewProj);

                for (auto & object : sceneObjects)
                {
                    if (object->castsShadow)
                    {
                        pointLightShader->uniform("u_modelMatrix", object->get_model());
                        object->draw();
                    }
                }

                pointLightShader->unbind();
                pointLightFramebuffer->unbind();
            }
        }

        // Blur applied to the directional light shadowmap only (others later)
        {
            shadowBlurFramebuffer.bind_to_draw();
            glDrawBuffer(GL_COLOR_ATTACHMENT0);

            gaussianBlurShader->bind();

            // Configured for a 7x7
            gaussianBlurShader->uniform("blurSize", 1.0f / shadowmapResolution);
            gaussianBlurShader->uniform("sigma", blurSigma);
            gaussianBlurShader->uniform("u_modelViewProj", Identity4x4);

            // Horizontal
            gaussianBlurShader->texture("s_blurTexure", 0, shadowDepthTexture);
            gaussianBlurShader->uniform("numBlurPixelsPerSide", 3.0f);
            gaussianBlurShader->uniform("blurMultiplyVec", float2(1.0f, 0.0f));
            fullscreen_post_quad.draw_elements();

            // Vertical
            gaussianBlurShader->texture("s_blurTexure", 0, shadowBlurTexture);
            gaussianBlurShader->uniform("numBlurPixelsPerSide", 3.0f);
            gaussianBlurShader->uniform("blurMultiplyVec", float2(0.0f, 1.0f));
            fullscreen_post_quad.draw_elements();

            gaussianBlurShader->unbind();

            shadowBlurFramebuffer.unbind();
        }

        {
            glViewport(0, 0, width, height);
            sceneShader->bind();

            sceneShader->uniform("u_viewProj", viewProj);
            sceneShader->uniform("u_eye", camera.get_eye_point());
            sceneShader->uniform("u_directionalLight.color", sunLight->color);
            sceneShader->uniform("u_directionalLight.direction", sunLight->direction);
            sceneShader->uniform("u_dirLightViewProjectionMat", sunLight->get_view_proj_matrix(target));

            int samplerIndex = 0;
            sceneShader->uniform("u_shadowMapBias", 0.01f / shadowmapResolution); // fixme
            sceneShader->uniform("u_shadowMapTexelSize", float2(1.0f / shadowmapResolution));
            sceneShader->texture("s_directionalShadowMap", samplerIndex++, shadowBlurTexture);

            sceneShader->uniform("u_spotLightViewProjectionMat[0]", spotLights[0]->get_view_proj_matrix());

            sceneShader->uniform("u_spotLights[0].color", spotLights[0]->color);
            sceneShader->uniform("u_spotLights[0].direction", spotLights[0]->direction);
            sceneShader->uniform("u_spotLights[0].position", spotLights[0]->position);
            sceneShader->uniform("u_spotLights[0].cutoff", spotLights[0]->get_cutoff());
            sceneShader->uniform("u_spotLights[0].constantAtten", spotLights[0]->attenuation.x);
            sceneShader->uniform("u_spotLights[0].linearAtten", spotLights[0]->attenuation.y);
            sceneShader->uniform("u_spotLights[0].quadraticAtten", spotLights[0]->attenuation.z);

            sceneShader->uniform("u_pointLights[0].color", pointLight->color);
            sceneShader->uniform("u_pointLights[0].position", pointLight->position);
            sceneShader->uniform("u_pointLights[0].constantAtten", pointLight->attenuation.x);
            sceneShader->uniform("u_pointLights[0].linearAtten", pointLight->attenuation.y);
            sceneShader->uniform("u_pointLights[0].quadraticAtten", pointLight->attenuation.z);

            // Update the spotlight 2D sampler
            for (int i = 0; i < spotLightFramebuffers.size(); ++i)
            {
                auto & fbo = spotLightFramebuffers[i];
                std::string uniformLocation = "s_spotLightShadowMap[" + std::to_string(i) + "]";
                sceneShader->texture(uniformLocation.c_str(), samplerIndex + i, fbo->shadowDepthTexture);
            }

            // Update the pointlight cube sampler
            for (int i = 0; i < 6; i++)
                sceneShader->texture("s_pointLightCubemap[0]", 2 + i, pointLightFramebuffer->cubeMapHandle, GL_TEXTURE_CUBE_MAP);

            for (auto & object : sceneObjects)
            {
                sceneShader->uniform("u_modelMatrix", object->get_model());
                sceneShader->uniform("u_modelMatrixIT", inv(transpose(object->get_model())));
                object->draw();
                gl_check_error(__FILE__, __LINE__);
            }

            sceneShader->unbind();
        }

        {
            ImGui::Separator();
            ImGui::SliderFloat("Near Clip", &camera.nearClip, 0.1f, 2.0f);
            ImGui::SliderFloat("Far Clip", &camera.farClip, 2.0f, 75.0f);
            ImGui::DragFloat3("Light Direction", &sunLight->direction[0], 0.1f, -1.0f, 1.0f);
            ImGui::Separator();
            ImGui::SliderFloat("Blur Sigma", &blurSigma, 0.05f, 9.0f);
            ImGui::Separator();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        viewA->draw(uiSurface.children[0]->bounds, int2(width, height));
        viewB->draw(uiSurface.children[1]->bounds, int2(width, height));
        viewC->draw(uiSurface.children[2]->bounds, int2(width, height));
        viewD->draw(uiSurface.children[3]->bounds, int2(width, height));

        gl_check_error(__FILE__, __LINE__);

        if (igm) igm->end_frame();

        glfwSwapBuffers(window);
    }