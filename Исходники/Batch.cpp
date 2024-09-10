void Batch::Prepare(View* view, bool setModelTransform) const
{
    if (!vertexShader_ || !pixelShader_)
        return;
    
    Graphics* graphics = view->GetGraphics();
    Renderer* renderer = view->GetRenderer();
    Node* cameraNode = camera_ ? camera_->GetNode() : 0;
    Light* light = lightQueue_ ? lightQueue_->light_ : 0;
    Texture2D* shadowMap = lightQueue_ ? lightQueue_->shadowMap_ : 0;

    // Set pass / material-specific renderstates
    if (pass_ && material_)
    {
        bool isShadowPass = pass_->GetType() == PASS_SHADOW;
        
        BlendMode blend = pass_->GetBlendMode();
        // Turn additive blending into subtract if the light is negative
        if (light && light->IsNegative())
        {
            if (blend == BLEND_ADD)
                blend = BLEND_SUBTRACT;
            else if (blend == BLEND_ADDALPHA)
                blend = BLEND_SUBTRACTALPHA;
        }
        
        graphics->SetBlendMode(blend);
        renderer->SetCullMode(isShadowPass ? material_->GetShadowCullMode() : material_->GetCullMode(), camera_);
        if (!isShadowPass)
        {
            const BiasParameters& depthBias = material_->GetDepthBias();
            graphics->SetDepthBias(depthBias.constantBias_, depthBias.slopeScaledBias_);
        }
        graphics->SetDepthTest(pass_->GetDepthTestMode());
        graphics->SetDepthWrite(pass_->GetDepthWrite());
    }
    
    // Set shaders first. The available shader parameters and their register/uniform positions depend on the currently set shaders
    graphics->SetShaders(vertexShader_, pixelShader_);
    
    // Set global (per-frame) shader parameters
    if (graphics->NeedParameterUpdate(SP_FRAME, (void*)0))
        view->SetGlobalShaderParameters();
    
    // Set camera shader parameters
    unsigned cameraHash = overrideView_ ? (unsigned)(size_t)camera_ + 4 : (unsigned)(size_t)camera_;
    if (graphics->NeedParameterUpdate(SP_CAMERA, reinterpret_cast<void*>(cameraHash)))
        view->SetCameraShaderParameters(camera_, true, overrideView_);
    
    // Set viewport shader parameters
    IntVector2 rtSize = graphics->GetRenderTargetDimensions();
    IntRect viewport = graphics->GetViewport();
    unsigned viewportHash = (viewport.left_) | (viewport.top_ << 8) | (viewport.right_ << 16) | (viewport.bottom_ << 24);
    
    if (graphics->NeedParameterUpdate(SP_VIEWPORT, reinterpret_cast<void*>(viewportHash)))
    {
        float rtWidth = (float)rtSize.x_;
        float rtHeight = (float)rtSize.y_;
        float widthRange = 0.5f * viewport.Width() / rtWidth;
        float heightRange = 0.5f * viewport.Height() / rtHeight;
        
        #ifdef URHO3D_OPENGL
        Vector4 bufferUVOffset(((float)viewport.left_) / rtWidth + widthRange,
            1.0f - (((float)viewport.top_) / rtHeight + heightRange), widthRange, heightRange);
        #else
        Vector4 bufferUVOffset((0.5f + (float)viewport.left_) / rtWidth + widthRange,
            (0.5f + (float)viewport.top_) / rtHeight + heightRange, widthRange, heightRange);
        #endif
        graphics->SetShaderParameter(VSP_GBUFFEROFFSETS, bufferUVOffset);
        
        float sizeX = 1.0f / rtWidth;
        float sizeY = 1.0f / rtHeight;
        graphics->SetShaderParameter(PSP_GBUFFERINVSIZE, Vector4(sizeX, sizeY, 0.0f, 0.0f));
    }
    
    // Set model or skinning transforms
    if (setModelTransform && graphics->NeedParameterUpdate(SP_OBJECTTRANSFORM, worldTransform_))
    {
        if (geometryType_ == GEOM_SKINNED)
        {
            graphics->SetShaderParameter(VSP_SKINMATRICES, reinterpret_cast<const float*>(worldTransform_), 
                12 * numWorldTransforms_);
        }
        else
            graphics->SetShaderParameter(VSP_MODEL, *worldTransform_);
        
        // Set the orientation for billboards, either from the object itself or from the camera
        if (geometryType_ == GEOM_BILLBOARD)
        {
            if (numWorldTransforms_ > 1)
                graphics->SetShaderParameter(VSP_BILLBOARDROT, worldTransform_[1].RotationMatrix());
            else
                graphics->SetShaderParameter(VSP_BILLBOARDROT, cameraNode->GetWorldRotation().RotationMatrix());
        }
    }
    
    // Set zone-related shader parameters
    BlendMode blend = graphics->GetBlendMode();
    // If the pass is additive, override fog color to black so that shaders do not need a separate additive path
    bool overrideFogColorToBlack = blend == BLEND_ADD || blend == BLEND_ADDALPHA;
    unsigned zoneHash = (unsigned)(size_t)zone_;
    if (overrideFogColorToBlack)
        zoneHash += 0x80000000;
    if (zone_ && graphics->NeedParameterUpdate(SP_ZONE, reinterpret_cast<void*>(zoneHash)))
    {
        graphics->SetShaderParameter(VSP_AMBIENTSTARTCOLOR, zone_->GetAmbientStartColor());
        graphics->SetShaderParameter(VSP_AMBIENTENDCOLOR, zone_->GetAmbientEndColor().ToVector4() - zone_->GetAmbientStartColor().ToVector4());
        
        const BoundingBox& box = zone_->GetBoundingBox();
        Vector3 boxSize = box.Size();
        Matrix3x4 adjust(Matrix3x4::IDENTITY);
        adjust.SetScale(Vector3(1.0f / boxSize.x_, 1.0f / boxSize.y_, 1.0f / boxSize.z_));
        adjust.SetTranslation(Vector3(0.5f, 0.5f, 0.5f));
        Matrix3x4 zoneTransform = adjust * zone_->GetInverseWorldTransform();
        graphics->SetShaderParameter(VSP_ZONE, zoneTransform);
        
        graphics->SetShaderParameter(PSP_AMBIENTCOLOR, zone_->GetAmbientColor());
        graphics->SetShaderParameter(PSP_FOGCOLOR, overrideFogColorToBlack ? Color::BLACK : zone_->GetFogColor());
        
        float farClip = camera_->GetFarClip();
        float fogStart = Min(zone_->GetFogStart(), farClip);
        float fogEnd = Min(zone_->GetFogEnd(), farClip);
        if (fogStart >= fogEnd * (1.0f - M_LARGE_EPSILON))
            fogStart = fogEnd * (1.0f - M_LARGE_EPSILON);
        float fogRange = Max(fogEnd - fogStart, M_EPSILON);
        Vector4 fogParams(fogEnd / farClip, farClip / fogRange, 0.0f, 0.0f);
        
        Node* zoneNode = zone_->GetNode();
        if (zone_->GetHeightFog() && zoneNode)
        {
            Vector3 worldFogHeightVec = zoneNode->GetWorldTransform() * Vector3(0.0f, zone_->GetFogHeight(), 0.0f);
            fogParams.z_ = worldFogHeightVec.y_;
            fogParams.w_ = zone_->GetFogHeightScale() / Max(zoneNode->GetWorldScale().y_, M_EPSILON);
        }
        
        graphics->SetShaderParameter(PSP_FOGPARAMS, fogParams);
    }
    
    // Set light-related shader parameters
    if (lightQueue_)
    {
        if (graphics->NeedParameterUpdate(SP_VERTEXLIGHTS, lightQueue_) && graphics->HasShaderParameter(VS, VSP_VERTEXLIGHTS))
        {
            Vector4 vertexLights[MAX_VERTEX_LIGHTS * 3];
            const PODVector<Light*>& lights = lightQueue_->vertexLights_;
            
            for (unsigned i = 0; i < lights.Size(); ++i)
            {
                Light* vertexLight = lights[i];
                Node* vertexLightNode = vertexLight->GetNode();
                LightType type = vertexLight->GetLightType();
                
                // Attenuation
                float invRange, cutoff, invCutoff;
                if (type == LIGHT_DIRECTIONAL)
                    invRange = 0.0f;
                else
                    invRange = 1.0f / Max(vertexLight->GetRange(), M_EPSILON);
                if (type == LIGHT_SPOT)
                {
                    cutoff = Cos(vertexLight->GetFov() * 0.5f);
                    invCutoff = 1.0f / (1.0f - cutoff);
                }
                else
                {
                    cutoff = -1.0f;
                    invCutoff = 1.0f;
                }
                
                // Color
                float fade = 1.0f;
                float fadeEnd = vertexLight->GetDrawDistance();
                float fadeStart = vertexLight->GetFadeDistance();
                
                // Do fade calculation for light if both fade & draw distance defined
                if (vertexLight->GetLightType() != LIGHT_DIRECTIONAL && fadeEnd > 0.0f && fadeStart > 0.0f && fadeStart < fadeEnd)
                    fade = Min(1.0f - (vertexLight->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
                
                Color color = vertexLight->GetEffectiveColor() * fade;
                vertexLights[i * 3] = Vector4(color.r_, color.g_, color.b_, invRange);
                
                // Direction
                vertexLights[i * 3 + 1] = Vector4(-(vertexLightNode->GetWorldDirection()), cutoff);
                
                // Position
                vertexLights[i * 3 + 2] = Vector4(vertexLightNode->GetWorldPosition(), invCutoff);
            }
            
            if (lights.Size())
                graphics->SetShaderParameter(VSP_VERTEXLIGHTS, vertexLights[0].Data(), lights.Size() * 3 * 4);
        }
    }
    
    if (light && graphics->NeedParameterUpdate(SP_LIGHT, light))
    {
        // Deferred light volume batches operate in a camera-centered space. Detect from material, zone & pass all being null
        bool isLightVolume = !material_ && !pass_ && !zone_;
        
        Matrix3x4 cameraEffectiveTransform = camera_->GetEffectiveWorldTransform();
        Vector3 cameraEffectivePos = cameraEffectiveTransform.Translation();

        Node* lightNode = light->GetNode();
        Matrix3 lightWorldRotation = lightNode->GetWorldRotation().RotationMatrix();
        
        graphics->SetShaderParameter(VSP_LIGHTDIR, lightWorldRotation * Vector3::BACK);
        
        float atten = 1.0f / Max(light->GetRange(), M_EPSILON);
        graphics->SetShaderParameter(VSP_LIGHTPOS, Vector4(lightNode->GetWorldPosition(), atten));
        
        if (graphics->HasShaderParameter(VS, VSP_LIGHTMATRICES))
        {
            switch (light->GetLightType())
            {
            case LIGHT_DIRECTIONAL:
                {
                    Matrix4 shadowMatrices[MAX_CASCADE_SPLITS];
                    unsigned numSplits = lightQueue_->shadowSplits_.Size();
                    for (unsigned i = 0; i < numSplits; ++i)
                        CalculateShadowMatrix(shadowMatrices[i], lightQueue_, i, renderer, Vector3::ZERO);
                    
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, shadowMatrices[0].Data(), 16 * numSplits);
                }
                break;
                
            case LIGHT_SPOT:
                {
                    Matrix4 shadowMatrices[2];
                    
                    CalculateSpotMatrix(shadowMatrices[0], light, Vector3::ZERO);
                    bool isShadowed = shadowMap && graphics->HasTextureUnit(TU_SHADOWMAP);
                    if (isShadowed)
                        CalculateShadowMatrix(shadowMatrices[1], lightQueue_, 0, renderer, Vector3::ZERO);
                    
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, shadowMatrices[0].Data(), isShadowed ? 32 : 16);
                }
                break;
                
            case LIGHT_POINT:
                {
                    Matrix4 lightVecRot(lightNode->GetWorldRotation().RotationMatrix());
                    // HLSL compiler will pack the parameters as if the matrix is only 3x4, so must be careful to not overwrite
                    // the next parameter
                    #ifdef URHO3D_OPENGL
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, lightVecRot.Data(), 16);
                    #else
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, lightVecRot.Data(), 12);
                    #endif
                }
                break;
            }
        }
        
        float fade = 1.0f;
        float fadeEnd = light->GetDrawDistance();
        float fadeStart = light->GetFadeDistance();
        
        // Do fade calculation for light if both fade & draw distance defined
        if (light->GetLightType() != LIGHT_DIRECTIONAL && fadeEnd > 0.0f && fadeStart > 0.0f && fadeStart < fadeEnd)
            fade = Min(1.0f - (light->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
        
        // Negative lights will use subtract blending, so write absolute RGB values to the shader parameter
        graphics->SetShaderParameter(PSP_LIGHTCOLOR, Color(light->GetEffectiveColor().Abs(),
            light->GetEffectiveSpecularIntensity()) * fade);
        graphics->SetShaderParameter(PSP_LIGHTDIR, lightWorldRotation * Vector3::BACK);
        graphics->SetShaderParameter(PSP_LIGHTPOS, Vector4((isLightVolume ? (lightNode->GetWorldPosition() -
            cameraEffectivePos) : lightNode->GetWorldPosition()), atten));
        
        if (graphics->HasShaderParameter(PS, PSP_LIGHTMATRICES))
        {
            switch (light->GetLightType())
            {
            case LIGHT_DIRECTIONAL:
                {
                    Matrix4 shadowMatrices[MAX_CASCADE_SPLITS];
                    unsigned numSplits = lightQueue_->shadowSplits_.Size();
                    for (unsigned i = 0; i < numSplits; ++i)
                    {
                        CalculateShadowMatrix(shadowMatrices[i], lightQueue_, i, renderer, isLightVolume ? cameraEffectivePos :
                            Vector3::ZERO);
                    }
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, shadowMatrices[0].Data(), 16 * numSplits);
                }
                break;
                
            case LIGHT_SPOT:
                {
                    Matrix4 shadowMatrices[2];
                    
                    CalculateSpotMatrix(shadowMatrices[0], light, cameraEffectivePos);
                    bool isShadowed = lightQueue_->shadowMap_ != 0;
                    if (isShadowed)
                    {
                        CalculateShadowMatrix(shadowMatrices[1], lightQueue_, 0, renderer, isLightVolume ? cameraEffectivePos :
                            Vector3::ZERO);
                    }
                    
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, shadowMatrices[0].Data(), isShadowed ? 32 : 16);
                }
                break;
                
            case LIGHT_POINT:
                {
                    Matrix4 lightVecRot(lightNode->GetWorldRotation().RotationMatrix());
                    // HLSL compiler will pack the parameters as if the matrix is only 3x4, so must be careful to not overwrite
                    // the next parameter
                    #ifdef URHO3D_OPENGL
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, lightVecRot.Data(), 16);
                    #else
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, lightVecRot.Data(), 12);
                    #endif
                }
                break;
            }
        }
        
        // Set shadow mapping shader parameters
        if (shadowMap)
        {
            {
                // Calculate point light shadow sampling offsets (unrolled cube map)
                unsigned faceWidth = shadowMap->GetWidth() / 2;
                unsigned faceHeight = shadowMap->GetHeight() / 3;
                float width = (float)shadowMap->GetWidth();
                float height = (float)shadowMap->GetHeight();
                #ifdef URHO3D_OPENGL
                    float mulX = (float)(faceWidth - 3) / width;
                    float mulY = (float)(faceHeight - 3) / height;
                    float addX = 1.5f / width;
                    float addY = 1.5f / height;
                #else
                    float mulX = (float)(faceWidth - 4) / width;
                    float mulY = (float)(faceHeight - 4) / height;
                    float addX = 2.5f / width;
                    float addY = 2.5f / height;
                #endif
                // If using 4 shadow samples, offset the position diagonally by half pixel
                if (renderer->GetShadowQuality() & SHADOWQUALITY_HIGH_16BIT)
                {
                    addX -= 0.5f / width;
                    addY -= 0.5f / height;
                }
                graphics->SetShaderParameter(PSP_SHADOWCUBEADJUST, Vector4(mulX, mulY, addX, addY));
            }
            
            {
                // Calculate shadow camera depth parameters for point light shadows and shadow fade parameters for
                //  directional light shadows, stored in the same uniform
                Camera* shadowCamera = lightQueue_->shadowSplits_[0].shadowCamera_;
                float nearClip = shadowCamera->GetNearClip();
                float farClip = shadowCamera->GetFarClip();
                float q = farClip / (farClip - nearClip);
                float r = -q * nearClip;
                
                const CascadeParameters& parameters = light->GetShadowCascade();
                float viewFarClip = camera_->GetFarClip();
                float shadowRange = parameters.GetShadowRange();
                float fadeStart = parameters.fadeStart_ * shadowRange / viewFarClip;
                float fadeEnd = shadowRange / viewFarClip;
                float fadeRange = fadeEnd - fadeStart;
                
                graphics->SetShaderParameter(PSP_SHADOWDEPTHFADE, Vector4(q, r, fadeStart, 1.0f / fadeRange));
            }
            
            {
                float intensity = light->GetShadowIntensity();
                float fadeStart = light->GetShadowFadeDistance();
                float fadeEnd = light->GetShadowDistance();
                if (fadeStart > 0.0f && fadeEnd > 0.0f && fadeEnd > fadeStart)
                    intensity = Lerp(intensity, 1.0f, Clamp((light->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 0.0f, 1.0f));
                float pcfValues = (1.0f - intensity);
                float samples = renderer->GetShadowQuality() >= SHADOWQUALITY_HIGH_16BIT ? 4.0f : 1.0f;

                graphics->SetShaderParameter(PSP_SHADOWINTENSITY, Vector4(pcfValues / samples, intensity, 0.0f, 0.0f));
            }
            
            float sizeX = 1.0f / (float)shadowMap->GetWidth();
            float sizeY = 1.0f / (float)shadowMap->GetHeight();
            graphics->SetShaderParameter(PSP_SHADOWMAPINVSIZE, Vector4(sizeX, sizeY, 0.0f, 0.0f));
            
            Vector4 lightSplits(M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE);
            if (lightQueue_->shadowSplits_.Size() > 1)
                lightSplits.x_ = lightQueue_->shadowSplits_[0].farSplit_ / camera_->GetFarClip();
            if (lightQueue_->shadowSplits_.Size() > 2)
                lightSplits.y_ = lightQueue_->shadowSplits_[1].farSplit_ / camera_->GetFarClip();
            if (lightQueue_->shadowSplits_.Size() > 3)
                lightSplits.z_ = lightQueue_->shadowSplits_[2].farSplit_ / camera_->GetFarClip();
            
            graphics->SetShaderParameter(PSP_SHADOWSPLITS, lightSplits);
        }
    }
    
    // Set material-specific shader parameters and textures
    if (material_)
    {
        if (graphics->NeedParameterUpdate(SP_MATERIAL, material_))
        {
            // Update shader parameter animations
            material_->UpdateShaderParameterAnimations();

            const HashMap<StringHash, MaterialShaderParameter>& parameters = material_->GetShaderParameters();
            for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
                graphics->SetShaderParameter(i->first_, i->second_.value_);
        }
        
        const SharedPtr<Texture>* textures = material_->GetTextures();
        for (unsigned i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
        {
            TextureUnit unit = (TextureUnit)i;
            if (textures[i] && graphics->HasTextureUnit(unit))
                graphics->SetTexture(i, textures[i]);
        }
    }
    
    // Set light-related textures
    if (light)
    {
        if (shadowMap && graphics->HasTextureUnit(TU_SHADOWMAP))
            graphics->SetTexture(TU_SHADOWMAP, shadowMap);
        if (graphics->HasTextureUnit(TU_LIGHTRAMP))
        {
            Texture* rampTexture = light->GetRampTexture();
            if (!rampTexture)
                rampTexture = renderer->GetDefaultLightRamp();
            graphics->SetTexture(TU_LIGHTRAMP, rampTexture);
        }
        if (graphics->HasTextureUnit(TU_LIGHTSHAPE))
        {
            Texture* shapeTexture = light->GetShapeTexture();
            if (!shapeTexture && light->GetLightType() == LIGHT_SPOT)
                shapeTexture = renderer->GetDefaultLightSpot();
            graphics->SetTexture(TU_LIGHTSHAPE, shapeTexture);
        }
    }
}