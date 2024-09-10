std::string
HdxColorCorrectionTask::_CreateOpenColorIOResources()
{
    #ifdef PXR_OCIO_PLUGIN_ENABLED
        // Use client provided OCIO values, or use default fallback values
        OCIO::ConstConfigRcPtr config = OCIO::GetCurrentConfig();

        const char* display = _displayOCIO.empty() ? 
                              config->getDefaultDisplay() : 
                              _displayOCIO.c_str();

        const char* view = _viewOCIO.empty() ? 
                           config->getDefaultView(display) :
                           _viewOCIO.c_str();

        std::string inputColorSpace = _colorspaceOCIO;
        if (inputColorSpace.empty()) {
            OCIO::ConstColorSpaceRcPtr cs = config->getColorSpace("default");
            if (cs) {
                inputColorSpace = cs->getName();
            } else {
                inputColorSpace = OCIO::ROLE_SCENE_LINEAR;
            }
        }

        // Setup the transformation we need to apply
        OCIO::DisplayTransformRcPtr transform = OCIO::DisplayTransform::Create();
        transform->setDisplay(display);
        transform->setView(view);
        transform->setInputColorSpaceName(inputColorSpace.c_str());
        if (!_looksOCIO.empty()) {
            transform->setLooksOverride(_looksOCIO.c_str());
            transform->setLooksOverrideEnabled(true);
        } else {
            transform->setLooksOverrideEnabled(false);
        }

        OCIO::ConstProcessorRcPtr processor = config->getProcessor(transform);

        // Create a GPU Shader Description
        OCIO::GpuShaderDesc shaderDesc;
        shaderDesc.setLanguage(OCIO::GPU_LANGUAGE_GLSL_1_0);
        shaderDesc.setFunctionName("OCIODisplay");
        shaderDesc.setLut3DEdgeLen(_lut3dSizeOCIO);

        // Compute and the 3D LUT
        int num3Dentries = 3 * _lut3dSizeOCIO*_lut3dSizeOCIO*_lut3dSizeOCIO;
        std::vector<float> lut3d;
        lut3d.resize(num3Dentries);
        processor->getGpuLut3D(&lut3d[0], shaderDesc);

        // Load the data into an OpenGL 3D Texture
        if (_texture3dLUT != 0) {
            glDeleteTextures(1, &_texture3dLUT);
        }
        GLint restoreTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_3D, &restoreTexture);
        glGenTextures(1, &_texture3dLUT);
        glBindTexture(GL_TEXTURE_3D, _texture3dLUT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB32F,
                     _lut3dSizeOCIO, _lut3dSizeOCIO, _lut3dSizeOCIO,
                     0, GL_RGB, GL_FLOAT, &lut3d[0]);
        glBindTexture(GL_TEXTURE_3D, restoreTexture);

        const char* gpuShaderText = processor->getGpuShaderText(shaderDesc);

        GLF_POST_PENDING_GL_ERRORS();
        return std::string(gpuShaderText);
    #else
        return std::string();
    #endif
}