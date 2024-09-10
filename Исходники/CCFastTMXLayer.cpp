void TMXLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    updateTotalQuads();
    
    if( flags != 0 || _dirty || _quadsDirty )
    {
        Size s = Director::getInstance()->getWinSize();
        auto rect = Rect(0, 0, s.width, s.height);
        
        Mat4 inv = transform;
        inv.inverse();
        rect = RectApplyTransform(rect, inv);
        
        updateTiles(rect);
        updateIndexBuffer();
        updatePrimitives();
        _dirty = false;
    }
    
    if(_renderCommands.size() < static_cast<size_t>(_primitives.size()))
    {
        _renderCommands.resize(_primitives.size());
    }
	_texture->prepareDraw();
    int index = 0;
    for(const auto& iter : _primitives)
    {
        if(iter.second->getCount() > 0)
        {
            auto& cmd = _renderCommands[index++];
			//修改混合模式，满足美术需求和PS一样 added by tokentong 20150327
            cmd.init(iter.first, _texture->getName(), getGLProgramState(), BlendFunc::ALPHA_PREMULTIPLIED, iter.second, _modelViewTransform, flags);
            renderer->addCommand(&cmd);
        }
    }
}