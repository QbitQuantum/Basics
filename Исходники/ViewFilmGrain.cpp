void ViewFilmGrain::render(gl::Texture texture) {
    shader->bind();
    shader->uniform("texture", 0);
    shader->uniform("time", _count);
    shader->uniform("width", float(getWindowWidth()));
    shader->uniform("height", float(getWindowHeight()));
    texture.bind();
    gl::draw(mesh);
    texture.unbind();
    shader->unbind();
    
    _count += .01;
}