void TessMeshApp::Update(){
    App::Update();
    
    
    mesh->Update();
    
    meshShaderProgram->use();
    
    GLuint m = meshShaderProgram->uniform("model");
    glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(mesh->modelMatrix));
    
    GLuint v = meshShaderProgram->uniform("view");
    glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(camera.view));
    
    GLuint p = meshShaderProgram->uniform("projection");
    glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(camera.projection));
    
    
    meshShaderProgram->disable();
    
    
    mouseShaderProgram->use();
    
    m = mouseShaderProgram->uniform("model");
    glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(mesh->modelMatrix));
    
    v = mouseShaderProgram->uniform("view");
    glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(camera.view));
    
    p = mouseShaderProgram->uniform("projection");
    glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(camera.projection));
    


    // cursor
    {
        vec2 mouse = mouse_cursor;
        
        
        
        vec3 view = normalize( camera.camera_look_at - camera.camera_position );
        
        vec3 h = normalize(cross(view, camera.camera_up));
        
        vec3 v = normalize(cross(h, view));
        float rad = radians(camera.field_of_view);
        
        float vLength = tanf(rad /2.0f) * camera.near_clip;
        float hLength = vLength * camera.aspect;
        
        v *= vLength;
        h *= hLength;
        
        mouse.x -= window_width/2;
        mouse.y = window_height - mouse.y - window_height/2;
        
        mouse.x /= window_width/2;
        mouse.y /= window_height/2;
        
        vec3 pos = camera.camera_position + view * (float)camera.near_clip + h*mouse.x + v*mouse.y;
        
        
        GLuint mousePosition = mouseShaderProgram->uniform("mousePosition");

        glUniform3fv(mousePosition, 1, value_ptr(pos));
    
    }
    
    mouseShaderProgram->disable();
    
}