void CubeTest::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
        case Touch::TOUCH_PRESS: {
            Rectangle viewport;
            viewport.x = 0;
            viewport.y = 0;
            viewport.width = getWidth();
            viewport.height = getHeight();
            
            Ray touchRay;
            _camera->pickRay( viewport, x, y, &touchRay );
            
            auto bsphere = _scene->findNode("box")->getBoundingSphere();
            if( touchRay.intersects( bsphere ) != Ray::INTERSECTS_NONE ) {
                _wireframe = !_wireframe;
            }
        }   break;
        case Touch::TOUCH_RELEASE:
            break;
        case Touch::TOUCH_MOVE:
            break;
    };
}