void DiffuseMaterial::render(const Camera &camera, std::vector<Light *> &lights) {
    Shader shader = Shader::getDiffuse();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.bind();

    shader.uniform("MVP", camera.getViewProjection() * gameObject->getTransform());

    shader.uniform("diffuseMap", 0, diffuseMap);
    shader.uniform("lightPosition", lights.front()->getGameObject()->getTranslation());
    shader.uniform("lightColour", lights.front()->getDiffuseColour());

    shader.attribute("vertexPosition", 3, nullptr);
    shader.attribute("vertexTexCoords", 2, reinterpret_cast<void *>(offsetof(Vertex, texCoords)));
    shader.attribute("vertexNormal", 3, reinterpret_cast<void *>(offsetof(Vertex, normal)));

    draw();

    shader.unbind();

    glDisable(GL_BLEND);
}