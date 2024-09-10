void SoWidgetShape::generatePrimitives(SoAction *action)
{
    if (this->image.isNull()) return;

    SoState *state = action->getState();
    state->push();

    SbVec2s size;
    SbVec3f v0, v1, v2, v3;
    this->getQuad(action->getState(), v0, v1, v2, v3);

    SbVec3f n = (v1-v0).cross(v2-v0);
    n.normalize();

    this->beginShape(action, SoShape::QUADS);
    SoPrimitiveVertex vertex;
    vertex.setNormal(n);

    vertex.setTextureCoords(SbVec2f(0,0));
    vertex.setPoint(v0);
    this->shapeVertex(&vertex);

    vertex.setTextureCoords(SbVec2f(1,0));
    vertex.setPoint(v1);
    this->shapeVertex(&vertex);

    vertex.setTextureCoords(SbVec2f(1,1));
    vertex.setPoint(v2);
    this->shapeVertex(&vertex);

    vertex.setTextureCoords(SbVec2f(0,1));
    vertex.setPoint(v3);
    this->shapeVertex(&vertex);

    this->endShape();

    state->pop();
}