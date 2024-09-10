void CgFXPassChunk::updateStateUniforms(DrawEnv  *pEnv)
{
    CgFXMaterial *pMat = _sfMaterial.getValue();

    OSG_ASSERT(pMat != NULL);

          CGeffect     pEffect        = pMat->getEffect        ();
          UInt32       uiStateVars    = pMat->getStateVariables();
    const std::string *vStateVarNames = pMat->getStateVarNames ();

          UInt32       uiMask         = 0x0001;


    OSG_ASSERT(pEffect != NULL);

    Matrix mObj2World = pEnv->getObjectToWorld();

    std::string szTmp;

    for(UInt32 i = 0; i < CgFXMaterial::NumStateVars; ++i)
    {
        if(uiStateVars == 0x0000)
            break;
        
        switch(uiStateVars & uiMask)
        {
            case CgFXMaterial::CgProjectionMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(
                    pMatrixParam,
                    pEnv->_openGLState.getProjection().getValues());
            }
            break;

            case CgFXMaterial::CgModelViewProjectionMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelViewProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mWorld2Scrn = pEnv->getWorldToScreen();

                mWorld2Scrn.mult(mObj2World);                

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mWorld2Scrn.getValues());
            }
            break;


            // -------------
            // Model | World
            // -------------
            case CgFXMaterial::CgModelMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModel].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mObj2World.getValues());
            }
            break;
            case CgFXMaterial::CgModelIMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mModelI = mObj2World;

                mModelI.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mModelI.getValues());
           }
            break;
            case CgFXMaterial::CgModelITMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mModelIT = mObj2World;

                mModelIT.invert   ();
                mModelIT.transpose();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mModelIT.getValues());
            }
            break;


            // ---------------------
            // ModelView | WorldView
            // ---------------------
            case CgFXMaterial::CgModelViewMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelView].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult(mObj2World);
                
                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgModelViewIMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelViewI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult(mObj2World);
                mCameraViewing.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgModelViewITMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelViewIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult     (mObj2World);
                mCameraViewing.invert   (          );
                mCameraViewing.transpose(          );

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;


            // -------------
            // View
            // -------------
            case CgFXMaterial::CgViewMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgView].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         pEnv->getCameraViewing().getValues());
            }
            break;
            case CgFXMaterial::CgViewIMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                OSG::Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgViewITMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                OSG::Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.invert   ();
                mCameraViewing.transpose();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;


            case CgFXMaterial::CgViewProjectionMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         pEnv->getWorldToScreen().getValues());
            }
            break;

            default:
                break;
        };

        uiStateVars &= ~uiMask;
        uiMask      =   uiMask << 1;
    }
}