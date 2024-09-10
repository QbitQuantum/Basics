	void LightCategory::doCopyComponent( Point2f const & component
		, uint32_t index
		, uint32_t & offset
		, PxBufferBase & data )const
	{
		uint8_t * dst = &( *data.getAt( index * shader::MaxLightComponentsCount + offset++, 0u ) );
		std::memcpy( dst, component.constPtr(), 2 * sizeof( float ) );
	}