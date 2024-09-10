bool TextEntityRenderer::needsRenderUpdateFromTypedEntity(const TypedEntityPointer& entity) const {
    if (_text != entity->getText()) {
        return true;
    }

    if (_lineHeight != entity->getLineHeight()) {
        return true;
    }

    if (_textColor != toGlm(entity->getTextColor())) {
        return true;
    }

    if (_backgroundColor != toGlm(entity->getBackgroundColor())) {
        return true;
    }

    if (_dimensions != entity->getScaledDimensions()) {
        return true;
    }

    if (_faceCamera != entity->getFaceCamera()) {
        return true;
    }
    return false;
}