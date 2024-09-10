    SceneManager::SceneManager(GLint width, GLint height)
#endif
    {
        Log << Function << endl;

        // The projection matrix is represented by the perspective matrix given by glm, assign it to each one of the objects
        GLfloat aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
        projectionMatrix = glm::perspective(
            45.0f,      // Field of view, is the amount of zoom. A wide angle is 90 and a narrow angle is 30
            aspect,     // Depends on the size of the window
            0.1f,       // Near clipping plane
            500.0f      // Far clipping plane
        );

        // Read the resources.txt file to obtain the valid configuration for the engine
        string resourcesFileName = "resources.txt";
#if defined(__ANDROID__)
        AAssetManager* mgr = AAssetManager_fromJava(*env, assetManager);
        AAsset* pFile = AAssetManager_open(mgr, resourcesFileName.c_str(), AASSET_MODE_UNKNOWN);
        if (!pFile)
#else
        ifstream resourcesFile(resourcesFileName, ios::in);
        if (!resourcesFile.is_open())
#endif
        {
            Log << Error << "Unable to read the resources file: " << resourcesFileName << endl;
            terminate();
        }

#if defined(__ANDROID__)
        // Get the file size
        size_t fileSize = AAsset_getLength(pFile);
        // Read data from the file
        char* pData = (char*)calloc(fileSize + 1, sizeof(char));
        AAsset_read(pFile, pData, fileSize);
        // fix the string to be zero-terminated
        pData[fileSize] = 0;
        // Copy the data to a stringstream
        stringstream resourcesFile(pData);
        AAsset_close(pFile);
        free(pData);
#endif

        Log << Debug << "Parsing the resources.txt file." << endl;
        string line, name, vertex, fragment, object, texture, projection, modelview;
        vector<string> cubeTextures{ NumCubeFaces };
        GLuint size, bufferType;
        vec3 pos, scl, rot;
        char token;
        bool finished = true;

        while (getline(resourcesFile, line))
        {
            stringstream ssLine(line);
            // Ignore empty lines on the configuration file
            if(line.size() == 0)
                continue;

            ssLine >> token;
            switch (token)
            {
            // If the line is a comment get the next token
            case '#':
                continue;
            // Start of object definition
            case '.':
                // Create a new scene object
                Log << Debug << "Starting an object definition." << endl;
                sceneobjects.push_back(make_unique<SceneObject>());
                finished = false;
                break;
            // End of an object definition
            case '-':
                Log << Debug << "End an object definition." << endl;
                finished = true;
                break;
            // Attributes used on the shaders
            case 'A':
                ssLine >> name >> size >> bufferType;
                Log << Debug << "Adding the attribute: " << name << endl;
                attributes.push_back(make_unique<Variable>(name, size, (BufferType)bufferType));
                break;
            // Uniforms used on the shaders
            case 'U':
                ssLine >> name;
                Log << Debug << "Adding the uniform: " << name << endl;
                uniforms.push_back(make_unique<Variable>(name));
                break;
            // Shaders creation
            case 'S':
                ssLine >> vertex >> fragment;
                Log << Debug << "Creating the shaders." << endl;
#if defined (__ANDROID__)
                sceneobjects.back()->SetShader(make_shared<Shader>(&mgr, vertex, fragment, attributes, uniforms));
#else
                sceneobjects.back()->SetShader(make_shared<Shader>(vertex, fragment, attributes, uniforms));
#endif
                break;
            // Object definitions
            case 'O':
                ssLine >> object;
                Log << Debug << "Loading a model." << endl;
#if defined (__ANDROID__)
                sceneobjects.back()->SetMesh(make_unique<Mesh>(&mgr, object, sceneobjects.back()->GetShader()));
#else
                sceneobjects.back()->SetMesh(make_unique<Mesh>(object, sceneobjects.back()->GetShader()));
#endif
                break;
            // Textures
            case 'T':
                ssLine >> texture;
                Log << Debug << "Loading a texture." << endl;
#if defined(__ANDROID__)
                sceneobjects.back()->SetTexture(make_unique<Texture>(&mgr, texture, sceneobjects.back()->GetShader()));
#else
                sceneobjects.back()->SetTexture(make_unique<Texture>(texture, sceneobjects.back()->GetShader()));
#endif
                break;
            // Initial coordinates
            case 'C':
                Log << Debug << "Adding coordinates to the object." << endl;
                ssLine >> pos.x >> pos.y >> pos.z >> scl.x >> scl.y >> scl.z >> rot.x >> rot.y >> rot.z >> angle;
                sceneobjects.back()->SetCoordinates(pos, scl, rot, angle);
                break;
            // Projection matrix
            case 'P':
                ssLine >> projection;
                break;
            // Modelview matrix
            case 'M':
                ssLine >> modelview;
                break;
            // Skybox
            case 'B':
                Log << Debug << "Adding a skybox." << endl;
                ssLine >> cubeTextures[0] >> cubeTextures[1] >> cubeTextures[2] >> cubeTextures[3] >> cubeTextures[4] >> cubeTextures[5];
                sceneobjects.back()->SetSkymap();
#if defined(__ANDROID__)
                sceneobjects.back()->SetMesh(make_unique<Mesh>(&mgr, string(""), sceneobjects.back()->GetShader()));
                sceneobjects.back()->SetTexture(make_unique<Texture>(&mgr, cubeTextures, sceneobjects.back()->GetShader()));
#else
                sceneobjects.back()->SetMesh(make_unique<Mesh>(string(""), sceneobjects.back()->GetShader()));
                sceneobjects.back()->SetTexture(make_unique<Texture>(cubeTextures, sceneobjects.back()->GetShader()));
#endif
                break;
            // Terrain Heightmap
            case 'H':
                Log << Debug << "Loading the terrain." << endl;
                ssLine >> texture >> object;
#if defined(__ANDROID__)
                sceneobjects.back()->SetTexture(make_unique<Texture>(&mgr, texture, sceneobjects.back()->GetShader()));
                sceneobjects.back()->SetMesh(make_unique<Mesh>(&mgr, object, sceneobjects.back()->GetShader(), &sceneobjects.back()->GetTexture()));
#else
                sceneobjects.back()->SetTexture(make_unique<Texture>(texture, sceneobjects.back()->GetShader()));
                sceneobjects.back()->SetMesh(make_unique<Mesh>(object, sceneobjects.back()->GetShader(), &sceneobjects.back()->GetTexture()));
#endif
                break;
            default:
                continue;
            }

            // Check if the definition of an object is complete or if more lines are needed
            if (finished)
            {
                // Get the projection and modelview uniforms
                if (!projection.empty())
                {
                    sceneobjects.back()->SetProjectionUni(glGetUniformLocation(sceneobjects.back()->GetShader()->getProgramObject(), "Projection"));
                    projection.clear();
                }
                if (!modelview.empty())
                {
                    sceneobjects.back()->SetModelviewUni(glGetUniformLocation(sceneobjects.back()->GetShader()->getProgramObject(), "Modelview"));
                    modelview.clear();
                }

                // Clear the attributes and uniforms in order to load the next object
                attributes.clear();
                uniforms.clear();
            }
        }
#if !defined(__ANDROID__)
        // Close de the resources file
        resourcesFile.close();
#endif

        // Set the initial position of the camera
        camera = vec3(2.5f, -1.0f, -5.0f);

        // Initial value of the rotation angle
        angle = 0.0f;
    }