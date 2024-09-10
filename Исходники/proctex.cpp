// Compile shaders
void PrepareShader(GLint shaderNum)
{
    char fullFileName[255];
    GLchar *shString;
    const GLchar *shStringPtr[1];
    GLint success;

    // Create shader objects and specify shader text
    sprintf(fullFileName, "./shaders/%s.vs", shaderNames[shaderNum]);
    shString = LoadShaderText(fullFileName);
    if (!shString)
    {
        fprintf(stderr, "Unable to load \"%s\"\n", fullFileName);
        Sleep(5000);
        exit(0);
    }
    vShader[shaderNum] = glCreateShader(GL_VERTEX_SHADER);
    shStringPtr[0] = shString;
    glShaderSource(vShader[shaderNum], 1, shStringPtr, NULL);
    free(shString);

    // Compile shaders and check for any errors
    glCompileShader(vShader[shaderNum]);
    glGetShaderiv(vShader[shaderNum], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(vShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in vertex shader #%d compilation!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }

    sprintf(fullFileName, "./shaders/%s.fs", shaderNames[shaderNum]);
    shString = LoadShaderText(fullFileName);
    if (!shString)
    {
        fprintf(stderr, "Unable to load \"%s\"\n", fullFileName);
        Sleep(5000);
        exit(0);
    }
    fShader[shaderNum] = glCreateShader(GL_FRAGMENT_SHADER);
    shStringPtr[0] = shString;
    glShaderSource(fShader[shaderNum], 1, shStringPtr, NULL);
    free(shString);

    // Compile shaders and check for any errors
    glCompileShader(fShader[shaderNum]);
    glGetShaderiv(fShader[shaderNum], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(fShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in fragment shader #%d compilation!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }
    else
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(fShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        //fprintf(stderr, "Fragment shader #%d info log: %s\n", shaderNum, infoLog);
    }

    // Create program object, attach shader, then link
    progObj[shaderNum] = glCreateProgram();
    glAttachShader(progObj[shaderNum], vShader[shaderNum]);
    glAttachShader(progObj[shaderNum], fShader[shaderNum]);

    glLinkProgram(progObj[shaderNum]);
    glGetProgramiv(progObj[shaderNum], GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetProgramInfoLog(progObj[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in program #%d linkage!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }
    else
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetProgramInfoLog(progObj[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        //fprintf(stderr, "Program #%d info log: %s\n", shaderNum, infoLog);
    }

    // Program object has changed, so we should revalidate
    needsValidation[shaderNum] = GL_TRUE;
}