    //---------------------------------------
    void MaterialExporter::setSetParam ( const cgfxShaderNode* shaderNodeCgfx, const cgfxAttrDef* attribute )
    {
        COLLADASW::StreamWriter* streamWriter = mDocumentExporter->getStreamWriter();
        String attributeName = attribute->fName.asChar();

        cgfxAttrDef::cgfxAttrType attributeType = attribute->fType;
        switch ( attributeType )
        {
        case cgfxAttrDef::kAttrTypeBool:
            {
                COLLADASW::SetParamBool setParam ( streamWriter );
                setParam.openParam ( attributeName );
                setParam.appendValues ( attribute->fNumericDef && attribute->fNumericDef[0] );
                setParam.closeParam ();
                break;
            }
        case cgfxAttrDef::kAttrTypeInt:
            {
                COLLADASW::SetParamInt setParam ( streamWriter );
                setParam.openParam ( attributeName );
                setParam.appendValues ( (int) attribute->fNumericDef[0] );
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeString:
            {
                COLLADASW::SetParamString setParam ( streamWriter );
                setParam.openParam ( attributeName );
                if ( attribute->fStringDef != NULL ) 
                    setParam.appendValues ( String ( attribute->fStringDef.asChar() ) );
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeFloat:
            {
                COLLADASW::SetParamFloat setParam ( streamWriter );
                setParam.openParam ( attributeName );
                if ( attribute->fNumericDef!=NULL /*&& attribute->fNumericDef[0]!=0*/ )  
                    setParam.appendValues ( attribute->fNumericDef[0] );
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeVector2:
            {
                COLLADASW::SetParamFloat2 setParam ( streamWriter );
                setParam.openParam ( attributeName );
                for ( int i=0; i<attribute->fSize; ++i )
                {
                    if ( attribute->fNumericDef!=NULL /*&& attribute->fNumericDef[i]!=0*/ )  
                    {
                        double val = attribute->fNumericDef[i];
                        setParam.appendValues( val );
                    }
                }
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeVector3:
        case cgfxAttrDef::kAttrTypeColor3:
            {
                COLLADASW::SetParamFloat3 setParam ( streamWriter );
                setParam.openParam ( attributeName );
                for ( int i=0; i<attribute->fSize; ++i )
                {
                    if ( attribute->fNumericDef!=NULL /*&& attribute->fNumericDef[i]!=0*/ )  
                    {
                        double val = attribute->fNumericDef[i];
                        setParam.appendValues( val );
                    }
                }
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeVector4:
        case cgfxAttrDef::kAttrTypeColor4:
            {
                COLLADASW::SetParamFloat4 setParam ( streamWriter );
                setParam.openParam ( attributeName );
                for ( int i=0; i<attribute->fSize; ++i )
                {
                    if ( attribute->fNumericDef!=NULL /*&& attribute->fNumericDef[i]!=0*/ )  
                    {
                        double val = attribute->fNumericDef[i];
                        setParam.appendValues( val );
                    }
                }
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeWorldDir:
        case cgfxAttrDef::kAttrTypeWorldPos:
            {
                // Read the value
                double tmp[4];
                for ( int i=0; i<attribute->fSize; ++i )
                {
                    tmp[i] = attribute->fNumericDef[i];
                }
                if (attribute->fSize == 3) tmp[3] = 1.0;

                // Find the coordinate space, and whether it is a point or a vector
                int base = cgfxAttrDef::kAttrTypeFirstPos;
                if (attribute->fType <= cgfxAttrDef::kAttrTypeLastDir) 
                    base = cgfxAttrDef::kAttrTypeFirstDir;
                int space = attribute->fType - base;

                // Compute the transform matrix
                MMatrix mat;
                switch (space)
                {
                    /* case 0:	object space, handled in view dependent method */
                case 1:	/* world space  - do nothing, identity */ break;
                    /* case 2: eye space, unsupported yet */
                    /* case 3: clip space, unsupported yet */
                    /* case 4: screen space, unsupported yet */
                }

                if ( base == cgfxAttrDef::kAttrTypeFirstPos )
                {
                    MPoint point(tmp[0], tmp[1], tmp[2], tmp[3]);
                    point *= mat;
                    tmp[0] = point.x;
                    tmp[1] = point.y;
                    tmp[2] = point.z;
                    tmp[3] = point.w;
                }
                else
                {
                    MVector vec(tmp[0], tmp[1], tmp[2]);
                    vec *= mat;
                    tmp[0] = vec.x;
                    tmp[1] = vec.y;
                    tmp[2] = vec.z;
                    tmp[3] = 1;
                }

                COLLADASW::SetParamFloat4 setParam ( streamWriter );
                setParam.openParam ( attributeName );
                setParam.appendValues( tmp[0], tmp[1], tmp[2], tmp[3] );
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeMatrix:
        case cgfxAttrDef::kAttrTypeWorldMatrix:
        case cgfxAttrDef::kAttrTypeViewMatrix:
        case cgfxAttrDef::kAttrTypeProjectionMatrix:
        case cgfxAttrDef::kAttrTypeWorldViewMatrix:
        case cgfxAttrDef::kAttrTypeWorldViewProjectionMatrix:
            {
                COLLADASW::SetParamFloat4x4 setParam ( streamWriter );
                setParam.openParam ( attributeName );

                MMatrix mayaMatrix;
                double* p = &mayaMatrix.matrix[0][0];
                for ( int k=0; k<attribute->fSize; ++k )
                {
                    p[k] = attribute->fNumericDef[k];
                }

                MMatrix wMatrix, vMatrix, pMatrix, sMatrix;
                MMatrix wvMatrix, wvpMatrix, wvpsMatrix;
                {
                    float tmp[4][4];

                    wMatrix.setToIdentity();

                    glGetFloatv(GL_MODELVIEW_MATRIX, &tmp[0][0]);
                    wvMatrix = MMatrix(tmp);

                    vMatrix = wMatrix.inverse() * wvMatrix;

                    glGetFloatv(GL_PROJECTION_MATRIX, &tmp[0][0]);
                    pMatrix = MMatrix(tmp);

                    wvpMatrix = wvMatrix * pMatrix;

                    float vpt[4];
                    float depth[2];

                    glGetFloatv(GL_VIEWPORT, vpt);
                    glGetFloatv(GL_DEPTH_RANGE, depth);

                    // Construct the NDC -> screen space matrix
                    //
                    float x0, y0, z0, w, h, d;

                    x0 = vpt[0];
                    y0 = vpt[1];
                    z0 = depth[0];
                    w  = vpt[2];
                    h  = vpt[3];
                    d  = depth[1] - z0;

                    // Make a reference to ease the typing
                    //
                    double* s = &sMatrix.matrix[0][0];

                    s[ 0] = w/2;	s[ 1] = 0.0;	s[ 2] = 0.0;	s[ 3] = 0.0;
                    s[ 4] = 0.0;	s[ 5] = h/2;	s[ 6] = 0.0;	s[ 7] = 0.0;
                    s[ 8] = 0.0;	s[ 9] = 0.0;	s[10] = d/2;	s[11] = 0.0;
                    s[12] = x0+w/2;	s[13] = y0+h/2;	s[14] = z0+d/2;	s[15] = 1.0;

                    wvpsMatrix = wvpMatrix * sMatrix;
                }		

                switch ( attribute->fType )
                {
                case cgfxAttrDef::kAttrTypeWorldMatrix:
                    mayaMatrix = wMatrix; break;
                case cgfxAttrDef::kAttrTypeViewMatrix:
                    mayaMatrix = vMatrix; break;
                case cgfxAttrDef::kAttrTypeProjectionMatrix:
                    mayaMatrix = pMatrix; break;
                case cgfxAttrDef::kAttrTypeWorldViewMatrix:
                    mayaMatrix = wvMatrix; break;
                case cgfxAttrDef::kAttrTypeWorldViewProjectionMatrix:
                    mayaMatrix = wvpMatrix; break;
                default:
                    break;
                }

                if (attribute->fInvertMatrix)
                    mayaMatrix = mayaMatrix.inverse();

                if (!attribute->fTransposeMatrix)
                    mayaMatrix = mayaMatrix.transpose();

                double matrix[4][4];
                convertMayaMatrixToTransposedDouble4x4 ( matrix, mayaMatrix, getTolerance () );
                setParam.appendValues( matrix );
                setParam.closeParam();
                break;
            }
        case cgfxAttrDef::kAttrTypeColor1DTexture:
        case cgfxAttrDef::kAttrTypeColor2DTexture:
        case cgfxAttrDef::kAttrTypeColor3DTexture:
        case cgfxAttrDef::kAttrTypeColor2DRectTexture:
        case cgfxAttrDef::kAttrTypeNormalTexture:
        case cgfxAttrDef::kAttrTypeBumpTexture:
        case cgfxAttrDef::kAttrTypeCubeTexture:
        case cgfxAttrDef::kAttrTypeEnvTexture:
        case cgfxAttrDef::kAttrTypeNormalizationTexture:
            {
                CGparameter cgParameter = attribute->fParameterHandle;
                HwShaderExporter hwShaderExporter ( mDocumentExporter );
                hwShaderExporter.setShaderFxFileUri ( getShaderFxFileUri () );

                MObject shaderNode = shaderNodeCgfx->thisMObject();
                hwShaderExporter.exportSampler ( shaderNode, cgParameter, false );


                // -------------------------------
//                 String imageName = attribute->fStringDef.asChar();
// 
//                 MObject oNode = shaderNodeCgfx->thisMObject();
//                 MFnDependencyNode oNodeFn ( oNode );
//                 String oNodeName = oNodeFn.name().asChar(); // cgfxShader1
// 
//                 MPlug plug;
//                 if ( DagHelper::getPlugConnectedTo( oNode, attributeName, plug ) )
//                 {
//                     String plugName = plug.name().asChar(); // file1.outColor
//                     MObject textureNode = plug.node();
// 
//                     //COLLADASW::Surface::SurfaceType surfaceType;
//                     COLLADASW::Sampler::SamplerType samplerType;
//                     COLLADASW::ValueType::ColladaType samplerValueType;
// 
//                     switch ( attributeType )
//                     {
//                     case cgfxAttrDef::kAttrTypeColor1DTexture:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_1D;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_1D;
//                         samplerValueType = COLLADASW::ValueType::SAMPLER_1D;
//                         break;
//                     case cgfxAttrDef::kAttrTypeColor2DTexture:
//                     case cgfxAttrDef::kAttrTypeNormalTexture:
//                     case cgfxAttrDef::kAttrTypeBumpTexture:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_2D;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_2D;
//                         samplerValueType = COLLADASW::ValueType::SAMPLER_2D;
//                         break;
//                     case cgfxAttrDef::kAttrTypeColor3DTexture:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_3D;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_3D;
//                         samplerValueType = COLLADASW::ValueType::SAMPLER_3D;
//                         break;
//                     case cgfxAttrDef::kAttrTypeColor2DRectTexture:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_RECT;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_RECT;
//                         samplerValueType = COLLADASW::ValueType::SAMPLER_RECT;
//                         break;
//                     case cgfxAttrDef::kAttrTypeCubeTexture:
//                     case cgfxAttrDef::kAttrTypeEnvTexture:
//                     case cgfxAttrDef::kAttrTypeNormalizationTexture:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_CUBE;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_CUBE;
//                         samplerValueType = COLLADASW::ValueType::SAMPLER_CUBE;
//                         break;
//                     default:
//                         //surfaceType = COLLADASW::Surface::SURFACE_TYPE_UNTYPED;
//                         samplerType = COLLADASW::Sampler::SAMPLER_TYPE_UNSPECIFIED;
//                         samplerValueType = COLLADASW::ValueType::VALUE_TYPE_UNSPECIFIED;
//                     }
// 
//                     // Write the params elements
//                     setSetParamTexture ( attribute, textureNode, samplerType, samplerValueType );
//                }
            }
        }
    }