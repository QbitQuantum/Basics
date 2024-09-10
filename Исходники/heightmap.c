int main(int argc, char** argv)
{
    GLFWwindow window;
    int ch, iter;
    double dt;
    double last_update_time;
    int frame;
    float f;
    GLint uloc_modelview;
    GLint uloc_project;

    char* vertex_shader_path = NULL;
    char* fragment_shader_path = NULL;
    char* vertex_shader_src = NULL;
    char* fragment_shader_src = NULL;
    GLuint shader_program;

    while ((ch = getopt(argc, argv, "f:v:h")) != -1)
    {
        switch (ch)
        {
            case 'f':
                fragment_shader_path = optarg;
                break;
            case 'v':
                vertex_shader_path = optarg;
                break;
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    if (fragment_shader_path)
    {
        vertex_shader_src = read_file_content(fragment_shader_path);
        if (!fragment_shader_src)
        {
            fprintf(stderr,
                    "ERROR: unable to load fragment shader from '%s'\n",
                    fragment_shader_path);
            exit(EXIT_FAILURE);
        }
    }

    if (vertex_shader_path)
    {
        vertex_shader_src = read_file_content(vertex_shader_path);
        if (!vertex_shader_src)
        {
            fprintf(stderr,
                    "ERROR: unable to load vertex shader from '%s'\n",
                    fragment_shader_path);
            exit(EXIT_FAILURE);
        }
    }

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
        usage();

        free(vertex_shader_src);
        free(fragment_shader_src);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_WINDOW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

    window = glfwCreateWindow(800, 600, GLFW_WINDOWED, "GLFW OpenGL3 Heightmap demo", NULL);
    if (! window )
    {
        fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
        usage();

        free(vertex_shader_src);
        free(fragment_shader_src);
        exit(EXIT_FAILURE);
    }

    /* Register events callback */
    glfwSetWindowCloseCallback(window_close_callback);
    glfwSetKeyCallback(key_callback);

    glfwMakeContextCurrent(window);
    if (GL_TRUE != init_opengl())
    {
        fprintf(stderr, "ERROR: unable to resolve OpenGL function pointers\n");
        free(vertex_shader_src);
        free(fragment_shader_src);
        exit(EXIT_FAILURE);
    }
    /* Prepare opengl resources for rendering */
    shader_program = make_shader_program(vertex_shader_src , fragment_shader_src);
    free(vertex_shader_src);
    free(fragment_shader_src);

    if (shader_program == 0u)
    {
        fprintf(stderr, "ERROR: during creation of the shader program\n");
        usage();
        exit(EXIT_FAILURE);
    }

    pglUseProgram(shader_program);
    uloc_project   = pglGetUniformLocation(shader_program, "project");
    uloc_modelview = pglGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
    f = 1.0f / tanf(view_angle / 2.0f);
    projection_matrix[0]  = f / aspect_ratio;
    projection_matrix[5]  = f;
    projection_matrix[10] = (z_far + z_near)/ (z_near - z_far);
    projection_matrix[11] = -1.0f;
    projection_matrix[14] = 2.0f * (z_far * z_near) / (z_near - z_far);
    pglUniformMatrix4fv(uloc_project, 1, GL_FALSE, projection_matrix);

    /* Set the camera position */
    modelview_matrix[12]  = -5.0f;
    modelview_matrix[13]  = -5.0f;
    modelview_matrix[14]  = -20.0f;
    pglUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix);

    /* Create mesh data */
    init_map();
    make_mesh(shader_program);

    /* Create vao + vbo to store the mesh */
    /* Create the vbo to store all the information for the grid and the height */

    /* setup the scene ready for rendering */
    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* main loop */
    frame = 0;
    iter = 0;
    dt = last_update_time = glfwGetTime();

    while (running)
    {
        ++frame;
        /* render the next frame */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_LINES, 2* MAP_NUM_LINES , GL_UNSIGNED_INT, 0);

        /* display and process events through callbacks */
        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Check the frame rate and update the heightmap if needed */
        dt = glfwGetTime();
        if ((dt - last_update_time) > 0.2)
        {
            /* generate the next iteration of the heightmap */
            if (iter < MAX_ITER)
            {
                update_map(NUM_ITER_AT_A_TIME);
                update_mesh();
                iter += NUM_ITER_AT_A_TIME;
            }
            last_update_time = dt;
            frame = 0;
        }
    }

    exit(EXIT_SUCCESS);
}