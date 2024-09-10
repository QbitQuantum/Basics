int main(int argc, char** argv)
{
    if(argc < 2) {
        printf("usage : %s \"tty device\"\n\t ex) %s /dev/ttyACM0\n\n", argv[0], argv[0]);
        return 1;
    }

    /*
     * Initialize myAHRS+
     */
    const char* serial_device = argv[1];
	const char* demo_dir = argv[2];

    MyAhrsPlusForMaliSdk sensor(serial_device, 115200);
    if(sensor.initialize() == false) {
        fprintf(stderr, "ERROR: myAHRS+ initialization failure.\n");
        exit(1);
    }

    /* Result of linking a program. */
    GLint link_status = GL_FALSE;

    /* Location of a 'viewMat' uniform variable. */
    GLint location_viewMat = 0;

    /* ID of a program object. */
    GLuint program_id = 0;

    /* ID of a fragment shader. */
    GLuint frag_shader_id = 0;

    /* ID of a vertex shader. */
    GLuint vert_shader_id = 0;

    /* Quaternions representing rotations around X, Y and Z axes. */
    Quaternion Q_X = { 0.0f, 0.0f, 0.0f, 0.0f };
    Quaternion Q_Y = { 0.0f, 0.0f, 0.0f, 0.0f };
    Quaternion Q_Z = { 0.0f, 0.0f, 0.0f, 0.0f };

    /* Quaternions to store resultant products. */
    Quaternion Q_XZ  = { 0.0f, 0.0f, 0.0f, 0.0f };
    Quaternion Q_YXZ = { 0.0f, 0.0f, 0.0f, 0.0f };

    /* Path to cubemap texture. */
//	char file_name[] = { "assets/greenhouse_skybox-0.ppm" };
	char file_name[32];

	if (demo_dir == NULL)
	{
		demo_dir = "sky";
	}

	sprintf(file_name, "%s/0.ppm", demo_dir);

    /* Used to hold cube-map texture face data when initializing skybox cube-map texture. */
    ImageFile cubemap_image = { 0, 0, NULL };

    /* Texture cubemap targets. */
    GLenum cubemap_faces[] =
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    /* Texture cubemap name. */
    GLuint cubemap_texture = 0;

    /* Number of degrees to rotate counterclockwise around X, Y and Z axes respectively. */
    float angle_X = 0.0f, angle_Y = 0.0f, angle_Z = 0.0f;

    /* 4x4 matrix that transforms the skybox's vertices from model space to world space. */
    float model_view_matrix[16] = {0.0f};

    /* Intialise the Platform object for platform specific functions. */
    Platform* platform = Platform::getInstance();

    if(platform == NULL)
    {
        fprintf(stderr, "Could not create platform\n");
        exit(-1);
    }

    /* Initialize windowing system. */
    platform->createWindow(window_width, window_height);

    /* Initialize EGL. */
    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES3);
    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));

    /* Generate texture name and bind it to the texture cubemap target. */
    GL_CHECK(glGenTextures(1, &cubemap_texture));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture));

    /* Set up texture parameters. */
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    /* Load cubemap texture. */
    cubemap_image = load_ppm_file(file_name);

    /* Specify storage for all levels of a cubemap texture. */
    GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP,    /* Texture target */
                            1,                      /* Number of texture levels */
                            GL_RGB8,                /* Internal format for texture storage */
                            cubemap_image.width,    /* Width of the texture image */
                            cubemap_image.height)); /* Height of the texture image */

    for (int n_face = 0; n_face < sizeof(cubemap_faces) / sizeof(cubemap_faces[0]); n_face++)
    {
        if (n_face != 0)
        {
//            sprintf(file_name, "assets/greenhouse_skybox-%d.ppm", n_face);
			sprintf(file_name, "%s/%d.ppm", demo_dir, n_face);

            cubemap_image = load_ppm_file(file_name);
        }

        GL_CHECK(glTexSubImage2D(cubemap_faces[n_face],                  /* Texture target. */
                                 0,                                      /* Level-of-detail number. */
                                 0,                                      /* Texel offset in the x direction. */
                                 0,                                      /* Texel offset in the y direction. */
                                 cubemap_image.width,                    /* Width of the texture image. */
                                 cubemap_image.height,                   /* Height of the texture image. */
                                 GL_RGB,                                 /* Format of the pixel data. */
                                 GL_UNSIGNED_BYTE,                       /* Type of the pixel data. */
                                 (const GLvoid*) cubemap_image.pixels)); /* Pointer to the image data. */

        FREE_CHECK(cubemap_image.pixels);
    }

    /* Shader initialization. */
    Shader::processShader(&vert_shader_id, "assets/shader.vert", GL_VERTEX_SHADER);
    Shader::processShader(&frag_shader_id, "assets/shader.frag", GL_FRAGMENT_SHADER);

    /* Create a program object that we will attach the fragment and vertex shader to. */
    program_id = GL_CHECK(glCreateProgram());

    /* Attach the shaders. */
    GL_CHECK(glAttachShader(program_id, vert_shader_id));
    GL_CHECK(glAttachShader(program_id, frag_shader_id));

    /* Link the program object. */
    GL_CHECK(glLinkProgram(program_id));

    /* Indicates the link operation on program was successful. */
    GL_CHECK(glGetProgramiv(program_id, GL_LINK_STATUS, &link_status));

    if (link_status != GL_TRUE)
    {
        fprintf(stderr, "Linking a program object has failed.\n");
        exit(-1);
    }

    /* The program object has been successfully linked. Let's use it. */
    GL_CHECK(glUseProgram(program_id));

    /* Retrieve uniform location for "viewMat" uniform defined in vertex shader. */
    location_viewMat = GL_CHECK(glGetUniformLocation(program_id, "viewMat"));

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Text* text = new Text("assets/", window_width, window_height);
    text->clear();
    text->addString(0, 0, "Skybox Sample", 255, 255, 0, 255);

    /* Rendering loop to draw the scene starts here. */
    bool shouldContinueTheLoop = true;

    while (shouldContinueTheLoop)
    {
        /* If something happened to the window, leave the loop. */
        if (platform->checkWindow() != Platform::WINDOW_IDLE)
        {
            shouldContinueTheLoop = false;
        }

        WithRobot::EulerAngle euler_angle = sensor.get_data().euler_angle;

        angle_X  = -euler_angle.pitch; // y
        angle_Y  =  euler_angle.yaw;   // z
        angle_Z  = -euler_angle.roll;  // x

        /* Construct quaternions for X, Y and Z axes. */
        Q_X = construct_quaternion(1.0f, 0.0f, 0.0f, angle_X);
        Q_Y = construct_quaternion(0.0f, 1.0f, 0.0f, angle_Y);
        Q_Z = construct_quaternion(0.0f, 0.0f, 1.0f, angle_Z);

        // Y->X->Z
        /* Obtain the resultant quaternion. */
        Q_XZ  = multiply_quaternions(Q_X, Q_Z);
        Q_YXZ = multiply_quaternions(Q_Y, Q_XZ);

        /* Compute a modelview matrix. Model matrix is a unit matrix. */
        construct_modelview_matrix(Q_YXZ, model_view_matrix);

        /* In this demo, we do not need to provide the vertex shader with any mesh data, because a predefined set
           of 4 vertices is embedded within the shader. These vertices, expressed in Normalized Device Coordinates,
           correspond to four corners of the visible screen space. By using this vertices to form a triangle strip,
           we end up with a full-screen quad that is later used for rasterization stage. */

        /* Restore the cubemap program object, because it has been changed by text rendering call. */
        GL_CHECK(glUseProgram(program_id));

        /* Upload the matrix to view matrix uniform so that it can be used for vertex shader stage. */
        GL_CHECK(glUniformMatrix4fv(location_viewMat, 1, GL_FALSE, (const GLfloat*) model_view_matrix));

        /* Render a full-screen quad, as described above.
           Note that the actual content of the quad is drawn within the fragment shader. */
        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

        char str_angle[256];
//        sprintf(str_angle, "# myAHRS+ (www.withrobot.com) : roll %.1f, pitch %.1f, yaw %.1f\n", euler_angle.roll, euler_angle.pitch, euler_angle.yaw);
		sprintf(str_angle, "[ LG V Task Demo ]\n");
        text->clear();
//        text->addString(0, 0, str_angle, 255, 255, 0, 255);
        text->addString(0, 0, str_angle, 0, 255, 0, 255);
        text->draw();

        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);

        /* Limit to 100 fps. */
        #ifdef _WIN32
                Sleep(10);
        #else
                usleep(10000);
        #endif
    }

    /*
     * stop myAHRS+
     */
    sensor.stop();

    /* End of event loop.
       The window has been closed.
       The only thing we should do now is a clean up. */

    /* Delete the cube map texture. */
    GL_CHECK(glDeleteTextures(1, &cubemap_texture));

    /* Release shaders. */
    GL_CHECK(glUseProgram(0));
    GL_CHECK(glDeleteShader(vert_shader_id));
    GL_CHECK(glDeleteShader(frag_shader_id));
    GL_CHECK(glDeleteProgram(program_id));

    /* Shut down EGL. */
    EGLRuntime::terminateEGL();

    /* Shut down windowing system. */
    platform->destroyWindow();

    /* Shut down the Platform object. */
    delete platform;

    return 0;
}