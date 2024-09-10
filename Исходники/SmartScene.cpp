void SmartScene::pushLayer( Layer* layer, bool exitPrevios )
{
	shadow_appearance();
	if( layer )
	{
		assert( _stack.empty() == false );
		auto top = _stack.back();
		int z = top->getLocalZOrder() + 2;
		_shadow->setLocalZOrder( z - 1 );

		layer->setOnExitCallback( std::bind( &SmartScene::on_layerClosed, this, layer ) );
		addChild( layer, z );

		_stack.push_back( layer );
		if( exitPrevios )
			top->onExit();
	}
}