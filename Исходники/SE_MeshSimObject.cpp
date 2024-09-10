SE_SimObject::RenderUnitVector SE_MeshSimObject::createRenderUnit()
{
    if(!mMesh)
        return RenderUnitVector();
    RenderUnitVector ruv;

    SE_SimObject* simple = getSpatial()->getSimpleObject();

    if(!simple)
    {
        simple = this;
    }

    bool enableDof =  SE_Application::getInstance()->getCurrentCamera()->isNeedDof();

    SE_Camera* c = SE_Application::getInstance()->getCurrentCamera();
    if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::MIRRORGENERATOR) &&( SE_Application::getInstance()->getRenderManager()->isNeedUpdateMirrorMap() || c->isChanged()) )
    {
        SE_Application::getInstance()->getRenderManager()->insertMirrorGenerator(this->getSpatial());
    }

    if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::SHADOWGENERATOR) &&( SE_Application::getInstance()->getRenderManager()->isNeedUpdateShadowMap() || c->isChanged()) )
    {
        SE_Application::getInstance()->getRenderManager()->insertShadowGenerator(this->getSpatial());
    }

    if(!SE_Application::getInstance()->getSceneManager()->isSceneManagerHasStatus(ENABLELIGHT))
    {
        this->getSpatial()->setSpatialEffectAttribute(SE_SpatialAttribute::LIGHTING,false);
    }

    if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::SHADOWOBJECT))
    {
        //if enable shadow, disable draw shadow object
        this->getSpatial()->setShadowObjectVisibility(false);
        return RenderUnitVector();;
    }

    //render object
    int surfaceNum = getSurfaceNum();
    for(int i = 0 ; i < surfaceNum; i++)
    {
        std::string indexStr = SE_Util::intToString(i);
        std::string renderUnitName = std::string(getName()) + "_" + indexStr;
        SE_Surface* surface = mMesh->getSurface(i);
        //SE_TriSurfaceRenderUnit* tsru = new SE_TriSurfaceRenderUnit(surface);

#ifdef USE_RUMANAGER
        SE_RenderUnitManager* srum = SE_Application::getInstance()->getRenderUnitManager();
        SE_TriSurfaceRenderUnit* tsru = (SE_TriSurfaceRenderUnit*)srum->find(renderUnitName.c_str());

        if(!tsru)
        {
            tsru = new SE_TriSurfaceRenderUnit(surface);
            srum->insert(renderUnitName.c_str(),tsru);
        }
        else
        {
            tsru->reset();
        }
#else
        SE_TriSurfaceRenderUnit* tsru = new SE_TriSurfaceRenderUnit(surface);
#endif

        if(this->getSpatial()->isSpatialHasRuntimeAttribute(SE_SpatialAttribute::IGNORVERTEXBUFFER))
        {
            tsru->setDontUseVertexBuffer(true);
        }


        tsru->setTexCoordXYReverse(this->getSpatial()->getTexCoordXYReverse());


        if(enableDof)
        {
            tsru->setName(renderUnitName.c_str());
            tsru->setPrimitiveType(getPrimitiveType());
            tsru->setRenderableSpatial(this->getSpatial());
            if(!isUseWorldMatrix())
            {
                tsru->setWorldTransform(getSpatial()->getWorldTransform().mul(getLocalMatrix()));
            }
            else
            {
                tsru->setWorldTransform(getWorldMatrix());
            }
            //SE_RenderState** rs = getRenderState();
            for(int j = 0 ; j < RENDERSTATE_NUM ; j++)
            {
                //tsru->setRenderState((RENDER_STATE_TYPE)j, rs[j], NOT_OWN);
                tsru->setRenderState((RENDER_STATE_TYPE)j, getSpatial()->getRenderState((RENDER_STATE_TYPE)j), NOT_OWN);
            }

            //fix me:
            tsru->setBlendState(false);

            tsru->setLayer(*getSpatial()->getWorldLayer());
            bool needCullFace = getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::CULLFACE);
            tsru->setEnableCullFace(needCullFace);

            if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::LIGHTING))
            {
                tsru->setShaderName(DOFLIGHTGEN_SHADER);
                tsru->setRenderName(DOFLIGHTGEN_RENDERER);
            }
            else
            {
                tsru->setShaderName(DOFGEN_SHADER);
                tsru->setRenderName(DOFGEN_RENDERER);
            }
            //tsru->setRenderToFbo(true);
            tsru->setNeedDofGen(true);
            SE_Application::getInstance()->getRenderManager()->setNeedBlurShadow(true);

        }
        else
        {
            SE_Application::getInstance()->getRenderManager()->setNeedBlurShadow(false);

            tsru->setName(renderUnitName.c_str());
            tsru->setPrimitiveType(getPrimitiveType());
            tsru->setRenderableSpatial(this->getSpatial());

            SE_AABBBV* aabbbv = (SE_AABBBV*)getSpatial()->getWorldBoundingVolume();

            if(aabbbv)
            {
                SE_Vector3f min = aabbbv->getGeometry().getMin();
                SE_Vector3f max = aabbbv->getGeometry().getMax();
                tsru->setMinBounding(min);
                tsru->setMaxBounding(max);
            }

            //tsru->setNewImageKey(mSecondImageKey.c_str());

            if(!isUseWorldMatrix())
            {
                tsru->setWorldTransform(getSpatial()->getWorldTransform().mul(getLocalMatrix()));
            }
            else
            {
                tsru->setWorldTransform(getWorldMatrix());
            }
            //SE_RenderState** rs = getRenderState();
            for(int j = 0 ; j < RENDERSTATE_NUM ; j++)
            {
                //tsru->setRenderState((RENDER_STATE_TYPE)j, rs[j], NOT_OWN);
                tsru->setRenderState((RENDER_STATE_TYPE)j, getSpatial()->getRenderState((RENDER_STATE_TYPE)j), NOT_OWN);
            }

            if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::BLENDABLE))
            {
                tsru->setBlendState(true);
                tsru->setAlpha(this->getSpatial()->getAlpha());

            }
            else
            {
                tsru->setBlendState(false);
            }

            if(this->getSpatial()->isNeedForeverBlend())
            {
                tsru->setBlendState(true);
                this->getSpatial()->setSpatialEffectAttribute(SE_SpatialAttribute::BLENDABLE,true);
                SE_Vector4f d = this->getSpatial()->getEffectData();
                if(d.z > 0.1)
                {
                    tsru->setAlpha(d.z);
                }
                else
                {
                    tsru->setAlpha(this->getSpatial()->getAlpha());
                }
            }

            //for shadow object
            if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::SHADOWOBJECT))
            {
                tsru->setBlendState(true);
                tsru->setAlpha(1.0);
#if 0
                SE_Layer* l = this->getSpatial()->getWorldLayer();
                if(this->getSpatial()->isSelected())
                {

                    l->setLayer(2);
                }
                else
                {
                    l->setLayer(0);
                }
#endif
            }

            tsru->setLayer(*getSpatial()->getWorldLayer());

            bool needCullFace = getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::CULLFACE);
            tsru->setEnableCullFace(needCullFace);
            tsru->setShaderName(DEFAULT_SHADER);
            tsru->setRenderName(DEFAULT_RENDERER);
            if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::NEEDFOG))
            {
                tsru->setShaderName(DEFAULTFOG_SHADER);
                tsru->setRenderName(DEFAULTFOG_RENDERER);
            }

            tsru->setIsUseFbo(false);

            //one object has just one effect,now
            /*int mirrorGeneratorCount = SE_Application::getInstance()->getSpatialManager()->mirrorGeneratorCount();
            int shadowGeneratorCount = SE_Application::getInstance()->getSpatialManager()->shadowGeneratorCount();*/


            if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::ALPHATEST))
            {
                tsru->setShaderName(ALPHATEST_SHADER);
                tsru->setRenderName(ALPHATEST_RENDERER);
            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::FLAGWAVE))
            {
                tsru->setShaderName(FLAGWAVE_SHADER);
                tsru->setRenderName(FLAGWAVE_RENDERER);
                if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::NEEDFOG))
                {
                    tsru->setShaderName(FLAGWAVEFOG_SHADER);
                    tsru->setRenderName(FLAGWAVEFOG_RENDERER);
                }
                tsru->setEnableCullFace(false);
            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::CLOAKFLAGWAVE))
            {
                tsru->setShaderName(CLOAKFLAGWAVE_SHADER);
                tsru->setRenderName(CLOAKFLAGWAVE_RENDERER);
                tsru->setEnableCullFace(false);
            }
            else if(this->getSpatial()->isNeedDrawLine())
            {
                tsru->setShaderName(DRAWLINE_SHADER);
                tsru->setRenderName(DRAWLINE_RENDERER);
                tsru->setDontUseVertexBuffer(true);

            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::SHADOWRENDER))
            {
                tsru->setNeedRenderShadow(true);
                if(USEVSM)
                {
                    //vsm
                    //need render shadow,disable other fbo function
                    tsru->setFboReplaceCurrentTexture(false);
                    tsru->setShaderName(SHADOWMAP_SHADER);
                    tsru->setRenderName(SHADOWMAP_RENDERER);
                    tsru->setNeedUseBluredShadowMap(false);
                    //tsru->setIsUseFbo(true);
                    if(tsru->getRenderableSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::LIGHTING))
                    {
                        tsru->setShaderName(SHADOWMAPWITHLIGHT_SHADER);
                        tsru->setRenderName(SHADOWMAPWITHLIGHT_RENDERER);
                    }

                }
                else
                {
                    //normal shadow map
                    tsru->setShaderName(RENDERDEPTHSHADOW_SHADER);
                    tsru->setRenderName(RENDERDEPTHSHADOW_RENDERER);
                }

            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::MIRRORRENDER))
            {
                tsru->setNeedRenderMirror(true);
                tsru->setFboReplaceCurrentTexture(false);
                tsru->setShaderName(MIRROR_SHADER);
                tsru->setRenderName(MIRROR_RENDERER);
                tsru->setIsUseFbo(true);
                tsru->setBlendState(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::BLENDABLE));

#if 0
                SE_Layer* l = this->getSpatial()->getWorldLayer();
                l->setLayer(3);
#endif

                tsru->setLayer(*getSpatial()->getWorldLayer());

                tsru->setAlpha(this->getSpatial()->getAlpha());

                //tsru->setMirrorObject(this->getSpatial());
                tsru->setMirrorPlan(this->getSpatial()->getMirrorPlan());

            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::UVANIMATION))
            {
                tsru->setShaderName(UVANIMATION_SHADER);
                tsru->setRenderName(UVANIMATION_RENDERER);
                if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::NEEDFOG))
                {
                    //disable now
                    /*
                    tsru->setShaderName(UVANIMATIONFOG_SHADER);
                    tsru->setRenderName(UVANIMATIONFOG_RENDERER);
                    */
                }
                tsru->setTexCoordOffset(this->getSpatial()->getTexCoordOffset());
            }
            else if(this->getSpatial()->isNeedParticle())
            {
                tsru->setShaderName(PARTICLE_SHADER);
                tsru->setRenderName(PARTICLE_RENDERER);
                if(this->getSpatial()->isNeedDepthTest())
                {
                    tsru->setDepthState(true);
                }
                else
                {
                    tsru->setDepthState(false);
                }
            }
            else if(this->getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::LIGHTING))
            {
                if(this->getMesh()->getSurface(0)->hasSpotLight())
                {
                    tsru->setShaderName(SIMPLELIGHTING_SPOT_SHADER);
                    tsru->setRenderName(SIMPLELIGHTING_SPOT_RENDERER);
                }
                else
                {
#ifdef WIN32
                    tsru->setShaderName(SIMPLELIGHTING_SHADER);
                    tsru->setRenderName(SIMPLELIGHTING_RENDERER);
#else
                    tsru->setShaderName(SIMPLELIGHTING_SHADER);
                    tsru->setRenderName(SIMPLELIGHTING_RENDERER);
#endif
                }

                //for "pc_face" object
                tsru->setNeedSpecLight(this->getSpatial()->isNeedSpecLight());

            }
            else
            {

            }

#if 0

            tsru->setRenderToFbo(true);
//just for demo

            std::string spatialname = this->getSpatial()->getSpatialName();

            //
            if(spatialname == "guang@group_house@ceshi_basedata.cbf" || spatialname == "guang1@group_house@ceshi_basedata.cbf" || spatialname == "guang2@group_house@ceshi_basedata.cbf"
                    || spatialname == "guang3@group_house@ceshi_basedata.cbf" || spatialname == "guang4@group_house@ceshi_basedata.cbf" || spatialname == "guang05@group_house@ceshi_basedata.cbf"
                    || spatialname == "guang06@group_house@ceshi_basedata.cbf")
            {
                SE_Layer* l = this->getSpatial()->getWorldLayer();
                l->setLayer(2);
                tsru->setLayer(*l);
                tsru->setNeedColorEffect(true);
                tsru->setBlendState(true);
                tsru->setAlpha(1.0);
            }
            if(spatialname == "Object50@group_house@ceshi_basedata.cbf" || spatialname == "Object51@group_house@ceshi_basedata.cbf" || spatialname == "Object52@group_house@ceshi_basedata.cbf"
                    || spatialname == "Object53@group_house@ceshi_basedata.cbf" || spatialname == "Object54@group_house@ceshi_basedata.cbf" || spatialname == "Object55@group_house@ceshi_basedata.cbf"
                    || spatialname == "Object02@group_house@ceshi_basedata.cbf" || spatialname == "Object56@group_house@ceshi_basedata.cbf")
            {
                SE_Layer* l = this->getSpatial()->getWorldLayer();
                l->setLayer(1);
                tsru->setLayer(*l);
            }

            if(spatialname == "wenzi@group_house@ceshi_basedata.cbf" || spatialname == "Box01@group_house@ceshi_basedata.cbf"
                    || spatialname == "Box02@group_house@ceshi_basedata.cbf" || spatialname == "Box03@group_house@ceshi_basedata.cbf"
                    || spatialname == "Plane18@group_house@ceshi_basedata.cbf")
            {
                tsru->setNeedHighLight(true);
            }
#endif


        }

        ruv.push_back(tsru);
    }

#if 0
    //forward additive
    if(this->getSpatial()->isNeedLighting() && enablelighting && !this->getSpatial()->isNeedBlend()  && 0)
    {

        for(int i = 0 ; i < surfaceNum; i++)
        {
            std::string indexStr = SE_Util::intToString(i);
            std::string renderUnitName = std::string(getName()) + "_" + indexStr;
            SE_Surface* surface = mMesh->getSurface(i);
            //SE_TriSurfaceRenderUnit* tsru = new SE_TriSurfaceRenderUnit(surface);

#ifdef USE_RUMANAGER
            SE_RenderUnitManager* srum = SE_Application::getInstance()->getRenderUnitManager();
            SE_TriSurfaceRenderUnit* tsru = (SE_TriSurfaceRenderUnit*)srum->find(renderUnitName.c_str());

            if(!tsru)
            {
                tsru = new SE_TriSurfaceRenderUnit(surface);
                srum->insert(renderUnitName.c_str(),tsru);
            }
            else
            {
                tsru->reset();
            }
#else
            SE_TriSurfaceRenderUnit* tsru = new SE_TriSurfaceRenderUnit(surface);
#endif


            tsru->setName(renderUnitName.c_str());
            tsru->setPrimitiveType(getPrimitiveType());
            tsru->setRenderableSpatial(this->getSpatial());
            if(!isUseWorldMatrix())
            {
                tsru->setWorldTransform(getSpatial()->getWorldTransform().mul(getLocalMatrix()));
            }
            else
            {
                tsru->setWorldTransform(getWorldMatrix());
            }

            //SE_RenderState** rs = getRenderState();
            for(int j = 0 ; j < RENDERSTATE_NUM ; j++)
            {
                //tsru->setRenderState((RENDER_STATE_TYPE)j, rs[j], NOT_OWN);
                tsru->setRenderState((RENDER_STATE_TYPE)j, getSpatial()->getRenderState((RENDER_STATE_TYPE)j), NOT_OWN);
            }


            //additive do not need blend
            tsru->setBlendState(false);

            tsru->setLayer(*getSpatial()->getWorldLayer());
            bool needCullFace = getSpatial()->isSpatialEffectHasAttribute(SE_SpatialAttribute::CULLFACE);
            tsru->setEnableCullFace(needCullFace);
            tsru->setShaderName(DEFAULT_SHADER);
            tsru->setRenderName(DEFAULT_RENDERER);
            tsru->setIsUseFbo(false);

            tsru->setIsAdditive(1);

            //one object has just one effect,now

            if(this->getSpatial()->isNeedLighting() && enablelighting)
            {
#ifdef WIN32
                tsru->setShaderName(SIMPLELIGHTING_SHADER);
                tsru->setRenderName(SIMPLELIGHTING_RENDERER);
#else
                tsru->setShaderName(SIMPLELIGHTINGPLUGIN_SHADER);
                tsru->setRenderName(SIMPLELIGHTINGPLUGIN_RENDERER);
#endif

            }

            else
            {
                //do not need render shadow
                //set replace current mesh texture
                //bool replace = getMesh()->getSurface(0)->isNeedFboReplaceCurrentTexture();
                //tsru->setFboReplaceCurrentTexture(replace);

                ////which mesh texture should be replace with fbo(0-3)
                //tsru->setFboReplaceTextureIndex(getMesh()->getSurface(0)->getFboReplaceTextureIndex());

                //std::string fboname = surface->getUsedFboName();
                //if(fboname.empty())
                //{
                //    tsru->setUsedFboName(getSpatial()->getSpatialName());
                //}
                //else
                //{
                //    tsru->setUsedFboName(fboname.c_str());
                //}
            }

            ruv.push_back(tsru);
        }
    }
#endif

    return ruv;
}