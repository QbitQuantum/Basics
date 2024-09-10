void ItemRange::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
}