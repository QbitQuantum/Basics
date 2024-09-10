 void RenderingEngine::Initialize(const vector<ISurface*>& surfaces)
 {
     vector<ISurface*>::const_iterator surface;
     for (surface = surfaces.begin(); surface != surfaces.end(); ++surface) {
         
         // Create the VBO for the vertices.
         vector<float> vertices;
         (*surface)->GenerateVertices(vertices, VertexFlagsNormals|VertexFlagsTexCoords);
         GLuint vertexBuffer;
         glGenBuffers(1, &vertexBuffer);
         glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
         glBufferData(GL_ARRAY_BUFFER,
                      vertices.size() * sizeof(vertices[0]),
                      &vertices[0],
                      GL_STATIC_DRAW);
         
         // Create a new VBO for the indices if needed.
         int indexCount = (*surface)->GetTriangleIndexCount();
         GLuint indexBuffer;
         if (!m_drawables.empty() && indexCount == m_drawables[0].IndexCount) {
             indexBuffer = m_drawables[0].IndexBuffer;
         } else {
             vector<GLushort> indices(indexCount);
             (*surface)->GenerateTriangleIndices(indices);
             glGenBuffers(1, &indexBuffer);
             glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
             glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                          indexCount * sizeof(GLushort),
                          &indices[0],
                          GL_STATIC_DRAW);
         }
         int lineIndexCount = (*surface)->GetLineIndexCount();
         GLuint lineIndexBuffer;
         vector<GLushort> lineIndices(lineIndexCount);
         (*surface)->GenerateLineIndices(lineIndices);
         glGenBuffers(1, &lineIndexBuffer);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      lineIndexCount * sizeof(GLushort),
                      &lineIndices[0],
                      GL_STATIC_DRAW);
         
         Drawable drawable = { vertexBuffer, indexBuffer , indexCount};
         m_drawables.push_back(drawable);
     }
     
     // Extract width and height.
     int width, height;
     glGetRenderbufferParameteriv(GL_RENDERBUFFER,
                                  GL_RENDERBUFFER_WIDTH, &width);
     glGetRenderbufferParameteriv(GL_RENDERBUFFER,
                                  GL_RENDERBUFFER_HEIGHT, &height);
     
     // Create a depth buffer that has the same size as the color buffer.
     glGenRenderbuffers(1, &m_depthRenderbuffer);
     glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
     
     // Create the framebuffer object.
     GLuint framebuffer;
     glGenFramebuffers(1, &framebuffer);
     glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_RENDERBUFFER, m_colorRenderbuffer);
     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                               GL_RENDERBUFFER, m_depthRenderbuffer);
     glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
     
     // Create the GLSL program.
     GLuint program = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
     glUseProgram(program);
     
     // Extract the handles to attributes and uniforms.
     m_attributes.Position = glGetAttribLocation(program, "Position");
     m_attributes.Normal = glGetAttribLocation(program, "Normal");
     m_attributes.Diffuse = glGetAttribLocation(program, "DiffuseMaterial");
     m_attributes.TextureCoord = glGetAttribLocation(program, "TextureCoord");
     m_uniforms.Projection = glGetUniformLocation(program, "Projection");
     m_uniforms.Modelview = glGetUniformLocation(program, "Modelview");
     m_uniforms.NormalMatrix = glGetUniformLocation(program, "NormalMatrix");
     m_uniforms.LightPosition = glGetUniformLocation(program, "LightPosition");
     m_uniforms.AmbientMaterial = glGetUniformLocation(program, "AmbientMaterial");
     m_uniforms.SpecularMaterial = glGetUniformLocation(program, "SpecularMaterial");
     m_uniforms.Shininess = glGetUniformLocation(program, "Shininess"); 
     
     // Set up some default material parameters.
     glUniform3f(m_uniforms.AmbientMaterial, 0.04f, 0.04f, 0.04f);
     glUniform3f(m_uniforms.SpecularMaterial, 0.5, 0.5, 0.5);
     glUniform1f(m_uniforms.Shininess, 50);
     // Set the active sampler to stage 0.  Not really necessary since the uniform
     // defaults to zero anyway, but good practice.
     glActiveTexture(GL_TEXTURE0);
     glUniform1i(m_uniforms.Sampler, 0);
     // Load the texture.
     glGenTextures(1,&m_gridTexture);
     glBindTexture(GL_TEXTURE_2D, m_gridTexture);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     m_resourceManager = CreateResourceManager();
     m_resourceManager->LoadPngImage("Grid16.png");
     void* pixels = m_resourceManager->GetImageData();
     ivec2 size = m_resourceManager->GetImageSize();
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, 
                  size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
     m_resourceManager->UnloadImage();
     // Initialize various state.
     glEnableVertexAttribArray(m_attributes.Position);
     glEnableVertexAttribArray(m_attributes.Normal);
     glEnableVertexAttribArray(m_attributes.TextureCoord);
     glEnable(GL_DEPTH_TEST);
     
     // Set up transforms.
     m_translation = mat4::Translate(0, 0, -7);
 }