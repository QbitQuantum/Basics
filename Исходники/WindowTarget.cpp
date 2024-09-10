//----------------------------------------------------------------------------//
void OgreWindowTarget::initRenderTarget(Ogre::RenderTarget& target)
{
    d_renderTarget = &target;

    Rectf init_area(glm::vec2(0.0f, 0.0f),
                    Sizef(static_cast<float>(d_renderTarget->getWidth()), 
                          static_cast<float>(d_renderTarget->getHeight())) );

    setArea(init_area);
}