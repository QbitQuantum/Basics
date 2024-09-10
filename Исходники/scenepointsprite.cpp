void ScenePointSprite::initScene()
{
    compileAndLinkShader();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

    numSprites = 50;
    locations = new float[numSprites * 3];
    srand( (unsigned int)time(0) );
    for( int i = 0; i < numSprites; i++ ) {
        vec3 p(((float)rand() / RAND_MAX * 2.0f) - 1.0f,
               ((float)rand() / RAND_MAX * 2.0f) - 1.0f,
               ((float)rand() / RAND_MAX * 2.0f) - 1.0f);
        locations[i*3] = p.x;
        locations[i*3+1] = p.y;
        locations[i*3+2] = p.z;
    }

    // Set up the buffers
    GLuint handle;
    glGenBuffers(1, &handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, numSprites * 3 * sizeof(float), locations, GL_STATIC_DRAW);

    delete [] locations;

    // Set up the vertex array object
    glGenVertexArrays( 1, &sprites );
    glBindVertexArray(sprites);

    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindVertexArray(0);

    // Load texture file
    GLuint w, h;
    const char * texName = "../media/texture/flower.bmp";
    BMPReader::loadTex(texName, w, h);

    prog.setUniform("SpriteTex", 0);
    prog.setUniform("Size2", 0.15f);
}