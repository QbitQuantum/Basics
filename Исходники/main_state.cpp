EntityRef MainState::createText(const std::string& text, const Vector3& pos,
                                const Vector4& color) {
    EntityRef entity = _entities.createEntity(_entities.root(), "text");
    _texts.addComponent(entity);
    TextComponent* comp = _texts.get(entity);
    comp->font = _font.get();
    comp->text = text;
    comp->color = color;
    entity.place(Transform(Translation(pos)));
    return entity;
}