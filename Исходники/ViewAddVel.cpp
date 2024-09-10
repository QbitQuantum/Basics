void ViewAddVel::render(gl::Texture texturePos, gl::Texture textureVel) {
    shader->bind();
    shader->uniform("texturePos", 0);
    texturePos.bind(0);
    shader->uniform("textureVel", 1);
    textureVel.bind(1);
    gl::draw(mesh);
    texturePos.unbind();
    textureVel.unbind();
    shader->unbind();
}