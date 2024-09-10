void RendererHUDClassic::Compute()
{
	{
		FastVertex thrustBuffer[6 * 32];
		memset( thrustBuffer, 0, sizeof( thrustBuffer ) );
		for ( uint32_t i = 0; i < 32; i++ ) {
			float height = std::exp( i * 0.05f );
			int ofsy = height * 10.0f;
			float x = 50 + i * ( 5 + 1 );
			float y = 720 - 75 - ofsy;
			
			thrustBuffer[i*6 + 0].x = x;
			thrustBuffer[i*6 + 0].y = y;
			thrustBuffer[i*6 + 1].x = x+5;
			thrustBuffer[i*6 + 1].y = y+ofsy;
			thrustBuffer[i*6 + 2].x = x+5;
			thrustBuffer[i*6 + 2].y = y;
			thrustBuffer[i*6 + 3].x = x;
			thrustBuffer[i*6 + 3].y = y;
			thrustBuffer[i*6 + 4].x = x;
			thrustBuffer[i*6 + 4].y = y+ofsy;
			thrustBuffer[i*6 + 5].x = x+5;
			thrustBuffer[i*6 + 5].y = y+ofsy;

			for ( int j = 0; j < 6; j++ ) {
				Vector2f vec = VR_Distort( Vector2f( thrustBuffer[i*6 + j].x, thrustBuffer[i*6 + j].y ) );
				thrustBuffer[i*6 + j].x = vec.x;
				thrustBuffer[i*6 + j].y = vec.y;
			}
		}
		glGenBuffers( 1, &mThrustVBO );
		glBindBuffer( GL_ARRAY_BUFFER, mThrustVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof(FastVertex) * 6 * 32, thrustBuffer, GL_STATIC_DRAW );
	}

	{
		FastVertexColor linkBuffer[6 * 16];
		memset( linkBuffer, 0, sizeof( linkBuffer ) );
		for ( uint32_t i = 0; i < 16; i++ ) {
			float height = std::exp( i * 0.1f );
			int ofsy = height * 12.0f;
			float x = 1280.0f * 0.03f + i * ( 13 + 1 );
			float y = 145.0f;

			linkBuffer[i*6 + 0].x = x;
			linkBuffer[i*6 + 0].y = y-ofsy;
			linkBuffer[i*6 + 1].x = x+13;
			linkBuffer[i*6 + 1].y = y;
			linkBuffer[i*6 + 2].x = x+13;
			linkBuffer[i*6 + 2].y = y-ofsy;
			linkBuffer[i*6 + 3].x = x;
			linkBuffer[i*6 + 3].y = y-ofsy;
			linkBuffer[i*6 + 4].x = x;
			linkBuffer[i*6 + 4].y = y;
			linkBuffer[i*6 + 5].x = x+13;
			linkBuffer[i*6 + 5].y = y;
			Vector4f fcolor = Vector4f( 0.5f + 0.5f * 0.0625f * ( 15 - i ), 0.5f + 0.5f * 0.0625f * i, 0.5f, 1.0f );
			uint32_t color = 0xFF7F0000 | ( (uint32_t)( fcolor.y * 255.0f ) << 8 ) | ( (uint32_t)( fcolor.x * 255.0f ) );
			linkBuffer[i*6 + 0].color = linkBuffer[i*6 + 1].color = linkBuffer[i*6 + 2].color = linkBuffer[i*6 + 3].color = linkBuffer[i*6 + 4].color = linkBuffer[i*6 + 5].color = color;

			for ( int j = 0; j < 6; j++ ) {
				Vector2f vec = VR_Distort( Vector2f( linkBuffer[i*6 + j].x, linkBuffer[i*6 + j].y ) );
				linkBuffer[i*6 + j].x = vec.x;
				linkBuffer[i*6 + j].y = vec.y;
			}
		}
		glGenBuffers( 1, &mLinkVBO );
		glBindBuffer( GL_ARRAY_BUFFER, mLinkVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof(FastVertexColor) * 6 * 16, linkBuffer, GL_STATIC_DRAW );
	}

	{
		glGenBuffers( 1, &mBatteryVBO );
		glBindBuffer( GL_ARRAY_BUFFER, mBatteryVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof(FastVertex) * 6, nullptr, GL_DYNAMIC_DRAW );
	}

	{
		glGenBuffers( 1, &mLineVBO );
		glBindBuffer( GL_ARRAY_BUFFER, mLineVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof(FastVertexColor) * 2 * 128, nullptr, GL_DYNAMIC_DRAW );
	}
}