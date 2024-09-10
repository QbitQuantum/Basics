GLUSboolean init(GLUSvoid)
{
    GLfloat textureToWorldNormalMatrix[16];

    // The maximum detail level which is 2^s = sMapExtend.
    GLuint sMaxDetailLevel;

    // The maximum detail level which is 2^t = tMapExtend.
    GLuint tMaxDetailLevel;

    // The overall maximum detail level from s and t.
    GLuint overallMaxDetailLevel;

    // Step for s and t direction.
    GLfloat detailStep;

    GLuint s, t;

    GLUStgaimage image;

    GLfloat* map = 0;

    GLuint* indices = 0;

    GLUStextfile vertexSource;
    GLUStextfile controlSource;
    GLUStextfile evaluationSource;
    GLUStextfile geometrySource;
    GLUStextfile fragmentSource;

    GLfloat lightDirection[3] = { 1.0f, 1.0f, 1.0f };

    glusVector3Normalizef(lightDirection);

    g_topView.cameraPosition[0] = 0.0f;
    g_topView.cameraPosition[1] = 30000.0f * METERS_TO_VIRTUAL_WORLD_SCALE;
    g_topView.cameraPosition[2] = 0.0f;
    g_topView.cameraPosition[3] = 1.0;
    g_topView.cameraDirection[0] = 0.0f;
    g_topView.cameraDirection[1] = -1.0f;
    g_topView.cameraDirection[2] = 0.0f;
    g_topView.cameraUp[0] = 0.0f;
    g_topView.cameraUp[1] = 0.0f;
    g_topView.cameraUp[2] = -1.0f;
    g_topView.fov = 40.0f;

    g_personView.cameraPosition[0] = 0.0f;
    g_personView.cameraPosition[1] = 4700.0f * METERS_TO_VIRTUAL_WORLD_SCALE;
    g_personView.cameraPosition[2] = 0.0f;
    g_personView.cameraPosition[3] = 1.0;
    g_personView.cameraDirection[0] = 0.0f;
    g_personView.cameraDirection[1] = 0.0f;
    g_personView.cameraDirection[2] = -1.0f;
    g_personView.cameraUp[0] = 0.0f;
    g_personView.cameraUp[1] = 1.0f;
    g_personView.cameraUp[2] = 0.0f;
    g_personView.fov = 60.0f;

    g_activeView = &g_personView;

    if (!glusLoadTgaImage(NORMAL_MAP, &image))
    {
        printf("Could not load normal picture '%s'!\n", NORMAL_MAP);

        return GLUS_FALSE;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &g_normalMapTexture);

    glBindTexture(GL_TEXTURE_RECTANGLE, g_normalMapTexture);

    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glusDestroyTgaImage(&image);

    if (!glusLoadTgaImage(HEIGHT_MAP, &image))
    {
        printf("Could not load height picture '%s'!\n", HEIGHT_MAP);

        return GLUS_FALSE;
    }

    glGenTextures(1, &g_heightMapTexture);

    glBindTexture(GL_TEXTURE_RECTANGLE, g_heightMapTexture);

    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    g_sMapExtend = (GLfloat) image.width;

    g_tMapExtend = (GLfloat) image.height;

    glusDestroyTgaImage(&image);

    // Calculate the detail level for the s and ...
    sMaxDetailLevel = (GLuint) floorf(logf(g_sMapExtend) / logf(2.0f));

    // ... t extend
    tMaxDetailLevel = (GLuint) floorf(logf(g_tMapExtend) / logf(2.0f));

    overallMaxDetailLevel = glusMinf(sMaxDetailLevel, tMaxDetailLevel);

    // Do checking of calculated parameters
    if (MINIMUM_DETAIL_LEVEL > overallMaxDetailLevel)
    {
        printf("Detail level to high %d > %d\n", MINIMUM_DETAIL_LEVEL, overallMaxDetailLevel);

        return GLUS_FALSE;
    }

    if (MINIMUM_DETAIL_LEVEL + DETAIL_LEVEL_FIRST_PASS > overallMaxDetailLevel)
    {
        printf("First pass detail level to high %d > %d\n", MINIMUM_DETAIL_LEVEL + DETAIL_LEVEL_FIRST_PASS, overallMaxDetailLevel);

        return GLUS_FALSE;
    }

    if (powf(2.0f, overallMaxDetailLevel - (MINIMUM_DETAIL_LEVEL + DETAIL_LEVEL_FIRST_PASS)) > 32.0f)
    {
        printf("Tessellation level to high %d > 32\n", (GLint) powf(2.0f, overallMaxDetailLevel - (MINIMUM_DETAIL_LEVEL + DETAIL_LEVEL_FIRST_PASS)));

        return GLUS_FALSE;
    }

    detailStep = powf(2.0f, overallMaxDetailLevel - MINIMUM_DETAIL_LEVEL);

    g_sNumPoints = (GLuint) ceilf(g_sMapExtend / detailStep) - 1;

    g_tNumPoints = (GLuint) ceilf(g_tMapExtend / detailStep) - 1;

    //
    // Generate the flat terrain mesh.
    //

    map = (GLUSfloat*) malloc(g_sNumPoints * g_tNumPoints * 2 * sizeof(GLfloat));

    indices = (GLuint*) malloc(g_sNumPoints * g_tNumPoints * sizeof(GLuint));

    for (t = 0; t < g_tNumPoints; t++)
    {
        for (s = 0; s < g_sNumPoints; s++)
        {
            map[t * g_sNumPoints * 2 + s * 2 + 0] = 0.5f + detailStep / 2.0f + (GLfloat) s * detailStep;
            map[t * g_sNumPoints * 2 + s * 2 + 1] = 0.5f + detailStep / 2.0f + (GLfloat) t * detailStep;

            indices[t * g_sNumPoints + s + 0] = (t + 0) * g_sNumPoints + s + 0;
        }
    }

    //
    // Transferring vertices and indices into GPU
    //

    // Pass one

    glGenBuffers(1, &g_verticesPassOneVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_verticesPassOneVBO);
    glBufferData(GL_ARRAY_BUFFER, g_sNumPoints * g_tNumPoints * 2 * sizeof(GLfloat), map, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &g_indicesPassOneVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesPassOneVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_sNumPoints * g_tNumPoints * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Pass two.

    glGenBuffers(1, &g_verticesPassTwoVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_verticesPassTwoVBO);
    // Calculate enough space!
    glBufferData(GL_ARRAY_BUFFER, g_sNumPoints * g_tNumPoints * (GLuint) pow(4, DETAIL_LEVEL_FIRST_PASS + 1) * 2 * sizeof(GLfloat), 0, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //

    free(map);
    map = 0;

    free(indices);
    indices = 0;

    //

    if (!glusLoadTgaImage(COLOR_MAP, &image))
    {
        printf("Could not load color picture '%s'!\n", COLOR_MAP);

        return GLUS_FALSE;
    }

    glGenTextures(1, &g_colorMapTexture);

    glBindTexture(GL_TEXTURE_2D, g_colorMapTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glusDestroyTgaImage(&image);

    //

    glGenQueries(1, &g_transformFeedbackQuery);

    //
    // Creating the shader program.
    //

    // Pass one.

    glusLoadTextFile("../Example14/shader/PassOne.vert.glsl", &vertexSource);
    glusLoadTextFile("../Example14/shader/PassOne.geom.glsl", &geometrySource);
    glusLoadTextFile("../Example14/shader/PassOne.frag.glsl", &fragmentSource);

    // Compile and ...
    glusCreateProgramFromSource(&g_programPassOne, (const GLUSchar**) &vertexSource.text, 0, 0, (const GLUSchar**) &geometrySource.text, (const GLUSchar**) &fragmentSource.text);

    // ... add the transform variable ...
    glTransformFeedbackVaryings(g_programPassOne.program, 1, (const GLchar**) &TRANSFORM_VARYING, GL_SEPARATE_ATTRIBS);

    // ... and link the program
    if (!glusLinkProgram(&g_programPassOne))
    {
        printf("Could not build program one\n");

        return GLUS_FALSE;
    }

    // Destroy the text resource
    glusDestroyTextFile(&vertexSource);
    glusDestroyTextFile(&geometrySource);
    glusDestroyTextFile(&fragmentSource);

    g_halfDetailStepPassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_halfDetailStep");

    g_detailLevelPassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_detailLevel");

    g_fovRadiusPassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_fovRadius");

    g_positionTextureSpacePassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_positionTextureSpace");
    g_leftNormalTextureSpacePassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_leftNormalTextureSpace");
    g_rightNormalTextureSpacePassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_rightNormalTextureSpace");
    g_backNormalTextureSpacePassOneLocation = glGetUniformLocation(g_programPassOne.program, "u_backNormalTextureSpace");

    // Pass two.

    glusLoadTextFile("../Example14/shader/PassTwo.vert.glsl", &vertexSource);
    glusLoadTextFile("../Example14/shader/PassTwo.cont.glsl", &controlSource);
    glusLoadTextFile("../Example14/shader/PassTwo.eval.glsl", &evaluationSource);
    glusLoadTextFile("../Example14/shader/PassTwo.geom.glsl", &geometrySource);
    glusLoadTextFile("../Example14/shader/PassTwo.frag.glsl", &fragmentSource);

    if (!glusBuildProgramFromSource(&g_shaderProgramPassTwo, (const GLUSchar**) &vertexSource.text, (const GLUSchar**) &controlSource.text, (const GLUSchar**) &evaluationSource.text, (const GLUSchar**) &geometrySource.text, (const GLUSchar**) &fragmentSource.text))
    {
        printf("Could not build program two\n");

        return GLUS_FALSE;
    }

    glusDestroyTextFile(&vertexSource);
    glusDestroyTextFile(&controlSource);
    glusDestroyTextFile(&evaluationSource);
    glusDestroyTextFile(&geometrySource);
    glusDestroyTextFile(&fragmentSource);

    g_maxTessellationLevelPassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_maxTessellationLevel");

    g_quadrantStepPassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_quadrantStep");

    g_positionTextureSpacePassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_positionTextureSpace");

    g_heightMapTexturePassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_heightMapTexture");
    g_normalMapTexturePassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_normalMapTexture");

    g_tmvpPassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_tmvpMatrix");

    g_lightDirectionPassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_lightDirection");

    g_colorMapTexturePassTwoLocation = glGetUniformLocation(g_shaderProgramPassTwo.program, "u_colorMapTexture");

    //

    // One time matrix calculations to convert between texture and world space

    glusMatrix4x4Identityf(g_textureToWorldMatrix);
    glusMatrix4x4Identityf(textureToWorldNormalMatrix);

    glusMatrix4x4Scalef(g_textureToWorldMatrix, HORIZONTAL_PIXEL_SPACING * METERS_TO_VIRTUAL_WORLD_SCALE, VERTICAL_PIXEL_RANGE * METERS_TO_VIRTUAL_WORLD_SCALE, HORIZONTAL_PIXEL_SPACING * METERS_TO_VIRTUAL_WORLD_SCALE);
    // Skip this scale for the normal matrix

    glusMatrix4x4Scalef(g_textureToWorldMatrix, 1.0f, 1.0f, -1.0f);
    glusMatrix4x4Scalef(textureToWorldNormalMatrix, 1.0f, 1.0f, -1.0f);

    glusMatrix4x4Translatef(g_textureToWorldMatrix, -g_sMapExtend / 2.0f, 0.0f, -g_tMapExtend / 2.0f);
    // No need for the translation matrix in the normal matrix

    glusMatrix4x4Copyf(g_worldToTextureMatrix, g_textureToWorldMatrix, GLUS_FALSE);
    glusMatrix4x4Inversef(g_worldToTextureMatrix);

    glusMatrix4x4Copyf(g_worldToTextureNormalMatrix, textureToWorldNormalMatrix, GLUS_FALSE);
    glusMatrix4x4Inversef(g_worldToTextureNormalMatrix);

    // Pass one

    glUseProgram(g_programPassOne.program);

    glUniform1f(g_halfDetailStepPassOneLocation, detailStep / 2.0f);
    glUniform1ui(g_detailLevelPassOneLocation, DETAIL_LEVEL_FIRST_PASS);
    glUniform1f(g_fovRadiusPassOneLocation, FOV_RADIUS / HORIZONTAL_PIXEL_SPACING * METERS_TO_VIRTUAL_WORLD_SCALE);

    glGenVertexArrays(1, &g_vaoPassOne);
    glBindVertexArray(g_vaoPassOne);

    glBindBuffer(GL_ARRAY_BUFFER, g_verticesPassOneVBO);
    // First 0 is the location = 0. See shader source
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable location = 0
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesPassOneVBO);

   // Pass two

    glUseProgram(g_shaderProgramPassTwo.program);

    glUniform3fv(g_lightDirectionPassTwoLocation, 1, lightDirection);
    glUniform1ui(g_maxTessellationLevelPassTwoLocation, overallMaxDetailLevel - (MINIMUM_DETAIL_LEVEL + DETAIL_LEVEL_FIRST_PASS));
    glUniform1i(g_quadrantStepPassTwoLocation, QUADRANT_STEP);

    glGenVertexArrays(1, &g_vaoPassTwo);
    glBindVertexArray(g_vaoPassTwo);

    glBindBuffer(GL_ARRAY_BUFFER, g_verticesPassTwoVBO);
    // First 0 is the location = 0. See shader source
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable location = 0
    glEnableVertexAttribArray(0);

    //

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(g_heightMapTexturePassTwoLocation, 0);
    glBindTexture(GL_TEXTURE_RECTANGLE, g_heightMapTexture);

    glActiveTexture(GL_TEXTURE1);
    glUniform1i(g_colorMapTexturePassTwoLocation, 1);
    glBindTexture(GL_TEXTURE_2D, g_colorMapTexture);

    glActiveTexture(GL_TEXTURE2);
    glUniform1i(g_normalMapTexturePassTwoLocation, 2);
    glBindTexture(GL_TEXTURE_RECTANGLE, g_normalMapTexture);

    //

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    return GLUS_TRUE;
}