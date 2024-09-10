void FrameRenderer::setBackgroundColor( const math::Vector4f& bc )
{
    pimpl->backgroundColor[ 0 ] = bc.x();
    pimpl->backgroundColor[ 1 ] = bc.y();
    pimpl->backgroundColor[ 2 ] = bc.z();
    pimpl->backgroundColor[ 3 ] = bc.w();
    pimpl->backgroundColorChanged = true;
}