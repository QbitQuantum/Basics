void SimplePostProcess::apply(const Viewport& viewport, 
                              Texture& color_buffer,
                              Camera& camera,
                              Texture& particle_overlay)
{
    glDisable(GL_DEPTH_TEST);
    viewport.set_viewport();

    _post_shader.bind();

    color_buffer.bind();
    particle_overlay.bind();
    
    _post_shader.set_uniform("color_buffer", color_buffer);
    _post_shader.set_uniform("offset", viewport.render_pixel_offset());
    _post_shader.set_uniform("viewport_size", viewport.render_size());
    _post_shader.set_uniform("particle_overlay", particle_overlay);

    _screen_filling_plane->draw(_post_shader);

    color_buffer.unbind();
    particle_overlay.unbind();
    _post_shader.unbind();
}