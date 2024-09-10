int ShaderD3D::prepareSourceAndReturnOptions(std::stringstream *shaderSourceStream)
{
    uncompile();

    int additionalOptions = 0;

    const std::string &source = mData.getSource();

#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
    if (gl::DebugAnnotationsActive())
    {
        std::string sourcePath = getTempPath();
        writeFile(sourcePath.c_str(), source.c_str(), source.length());
        additionalOptions |= SH_LINE_DIRECTIVES | SH_SOURCE_PATH;
        *shaderSourceStream << sourcePath;
    }
#endif

    *shaderSourceStream << source;
    return additionalOptions;
}