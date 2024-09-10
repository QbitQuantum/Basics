void GuiViewport3D::onDraw(sf::RenderTarget& window)
{
#if FEATURE_3D_RENDERING
    if (my_spaceship)
        soundManager->setListenerPosition(my_spaceship->getPosition(), my_spaceship->getRotation());
    else
        soundManager->setListenerPosition(sf::Vector2f(camera_position.x, camera_position.y), camera_yaw);
    window.popGLStates();

    ShaderManager::getShader("billboardShader")->setUniform("camera_position", camera_position);

    float camera_fov = 60.0f;
    float sx = window.getSize().x * window.getView().getViewport().width / window.getView().getSize().x;
    float sy = window.getSize().y * window.getView().getViewport().height / window.getView().getSize().y;
    glViewport(rect.left * sx, (float(window.getView().getSize().y) - rect.height - rect.top) * sx, rect.width * sx, rect.height * sy);

    glClearDepth(1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glColor4f(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    _glPerspective(camera_fov, rect.width/rect.height, 1.f, 25000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(90, 1, 0, 0);
    glScalef(1,1,-1);
    glRotatef(-camera_pitch, 1, 0, 0);
    glRotatef(-camera_yaw - 90, 0, 0, 1);

    glGetDoublev(GL_PROJECTION_MATRIX, projection_matrix);
    glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix);
    glGetDoublev(GL_VIEWPORT, viewport);

    glDepthMask(false);
    sf::Texture::bind(textureManager.getTexture("StarsBack"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0); glVertex3f( 100, 100, 100);
    glTexCoord2f(0.0, 1.0); glVertex3f( 100, 100,-100);
    glTexCoord2f(1.0, 0.0); glVertex3f(-100, 100, 100);
    glTexCoord2f(1.0, 1.0); glVertex3f(-100, 100,-100);
    glEnd();
    sf::Texture::bind(textureManager.getTexture("StarsLeft"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0); glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0, 1.0); glVertex3f(-100, 100,-100);
    glTexCoord2f(1.0, 0.0); glVertex3f(-100,-100, 100);
    glTexCoord2f(1.0, 1.0); glVertex3f(-100,-100,-100);
    glEnd();
    sf::Texture::bind(textureManager.getTexture("StarsFront"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0); glVertex3f(-100,-100, 100);
    glTexCoord2f(0.0, 1.0); glVertex3f(-100,-100,-100);
    glTexCoord2f(1.0, 0.0); glVertex3f( 100,-100, 100);
    glTexCoord2f(1.0, 1.0); glVertex3f( 100,-100,-100);
    glEnd();
    sf::Texture::bind(textureManager.getTexture("StarsRight"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0); glVertex3f( 100,-100, 100);
    glTexCoord2f(0.0, 1.0); glVertex3f( 100,-100,-100);
    glTexCoord2f(1.0, 0.0); glVertex3f( 100, 100, 100);
    glTexCoord2f(1.0, 1.0); glVertex3f( 100, 100,-100);
    glEnd();
    sf::Texture::bind(textureManager.getTexture("StarsTop"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0); glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0, 1.0); glVertex3f(-100,-100, 100);
    glTexCoord2f(1.0, 0.0); glVertex3f( 100, 100, 100);
    glTexCoord2f(1.0, 1.0); glVertex3f( 100,-100, 100);
    glEnd();
    sf::Texture::bind(textureManager.getTexture("StarsBottom"), sf::Texture::Normalized);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0, 0.0); glVertex3f( 100,-100,-100);
    glTexCoord2f(0.0, 0.0); glVertex3f(-100,-100,-100);
    glTexCoord2f(1.0, 1.0); glVertex3f( 100, 100,-100);
    glTexCoord2f(0.0, 1.0); glVertex3f(-100, 100,-100);
    glEnd();

    if (gameGlobalInfo)
    {
        //Render the background nebulas from the gameGlobalInfo. This ensures that all screens see the same background as it is replicated across clients.
        for(int n=0; n<GameGlobalInfo::max_nebulas; n++)
        {
            sf::Texture::bind(textureManager.getTexture(gameGlobalInfo->nebula_info[n].textureName), sf::Texture::Pixels);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glPushMatrix();
            glRotatef(180, gameGlobalInfo->nebula_info[n].vector.x, gameGlobalInfo->nebula_info[n].vector.y, gameGlobalInfo->nebula_info[n].vector.z);
            glColor4f(1,1,1,0.1);
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(1.0,    0); glVertex3f( 100, 100, 100);
            glTexCoord2f(   0,    0); glVertex3f( 100, 100,-100);
            glTexCoord2f(1.0, 1.0); glVertex3f(-100, 100, 100);
            glTexCoord2f(   0, 1.0); glVertex3f(-100, 100,-100);
            glEnd();
            glPopMatrix();
        }
    }

    {
        float lightpos1[4] = {0, 0, 0, 1.0};
        glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

        float lightpos0[4] = {20000, 20000, 20000, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
    }

    class RenderInfo
    {
    public:
        RenderInfo(SpaceObject* obj, float d)
        : object(obj), depth(d)
        {}
    
        SpaceObject* object;
        float depth;
    };
    std::vector<std::vector<RenderInfo>> render_lists;
    
    sf::Vector2f viewVector = sf::vector2FromAngle(camera_yaw);
    float depth_cutoff_back = camera_position.z * -tanf((90+camera_pitch + camera_fov/2.0) / 180.0f * M_PI);
    float depth_cutoff_front = camera_position.z * -tanf((90+camera_pitch - camera_fov/2.0) / 180.0f * M_PI);
    if (camera_pitch - camera_fov/2.0 <= 0.0)
        depth_cutoff_front = std::numeric_limits<float>::infinity();
    if (camera_pitch + camera_fov/2.0 >= 180.0)
        depth_cutoff_back = -std::numeric_limits<float>::infinity();
    foreach(SpaceObject, obj, space_object_list)
    {
        float depth = sf::dot(viewVector, obj->getPosition() - sf::Vector2f(camera_position.x, camera_position.y));
        if (depth + obj->getRadius() < depth_cutoff_back)
            continue;
        if (depth - obj->getRadius() > depth_cutoff_front)
            continue;
        if (depth > 0 && obj->getRadius() / depth < 1.0 / 500)
            continue;
        int render_list_index = std::max(0, int((depth + obj->getRadius()) / 25000));
        while(render_list_index >= int(render_lists.size()))
            render_lists.emplace_back();
        render_lists[render_list_index].emplace_back(*obj, depth);
    }