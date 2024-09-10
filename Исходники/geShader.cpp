  bool Shader::compile (ShaderType::Enum target, const CharString &source)
  {
    //Make sure old shaders are detached
    detachShaders();

    //Create a new shader
    GLShader *shader = new GLShader;
    shader->create( target );

    //Add to shader list
    switch (target) {
    case ShaderType::Vertex:
      vertShaders.pushBack( shader ); break;
    case ShaderType::Fragment:
      fragShaders.pushBack( shader ); break; }

    //Compile the source
    bool status = shader->compile( source );

    if (status)
      printf( "%s shader compiled.\n",
        target == ShaderType::Vertex ? "Vertex" : "Fragment" );
    else
      printf( "Failed compiling %s shader!",
        target == ShaderType::Vertex ? "vertex" : "fragment" );

    CharString infoLog = shader->getInfoLog ();
    if (infoLog.length() > 0)
      printf ("Info Log:\n%s\n", infoLog.buffer());

    return status;
  }