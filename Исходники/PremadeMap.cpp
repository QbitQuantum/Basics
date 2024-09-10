void PremadeMap::drawReflect(void) const
{
    glPushMatrix();
    flatTexture reflect(Bomberman::ModelHandler::get().getModel("loadmap_reflect"));
    glTranslated(515, 203, 0);
    reflect.draw();
    glPopMatrix();
}