void DrawUtils::activate_state (    const std::shared_ptr<CameraObject> &camera,
                                    const std::shared_ptr<MaterialResource> &material,
                                    const std::shared_ptr<ShaderResource> &shader,
                                    const Matrix4 &transform)
{
    if (camera) {
        camera->calculate_frustum();
        
        shader->set_uniform_value(  shader->uniform_slot(DT3GL_UNIFORM_MODELVIEW), camera->modelview() * transform );
        shader->set_uniform_value(  shader->uniform_slot(DT3GL_UNIFORM_PROJECTION), camera->projection());
    }
    
    
    // Set some shader parameters that were set in the material
    for (DTuint i = 0; i < 16; ++i) {
        material->set_current_unit(i);
        shader->set_uniform_value(  shader->uniform_slot((DT3GLStandardUniform) (DT3GL_UNIFORM_TEX_MATRIX0 + i)), material->transform());
    }

    material->activate();
    shader->activate();
}