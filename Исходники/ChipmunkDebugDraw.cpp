GLint
LinkProgram(GLint vshader, GLint fshader)
{
    GLint program = glCreateProgram();

    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);

    // todo return placeholder program instead?
    cpAssertHard(CheckError(program, GL_LINK_STATUS, glGetProgramiv, glGetProgramInfoLog), "Error linking shader program");

    return program;
}