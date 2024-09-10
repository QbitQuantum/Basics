void BoltEffect::Draw( const Vector3F* eyeDir )
{
	if (    d1 > d0
		 && !done ) 
	{
		Vector3F q0 = p0 + normal*d0;
		Vector3F q1 = p0 + normal*d1;

		Vector3F right;
		CrossProduct( eyeDir[Camera::NORMAL], q1-q0, &right );
		right.Normalize();

		float halfWidth = width*0.5f;

		// FIXME: hardcoded texture coordinates
		static const float tx = 0.50f;
		static const float ty = 0.0f;
		PTVertex pV[4];

		pV[0].pos = q0 - right*halfWidth;
		pV[0].tex.Set( tx+0.0f, ty+0.0f );
			
		pV[1].pos = q0 + right*halfWidth;
		pV[1].tex.Set( tx+0.25f, ty+0.0f );

		pV[2].pos = q1 + right*halfWidth;
		pV[2].tex.Set( tx+0.25f, ty+0.25f );

		pV[3].pos = q1 - right*halfWidth;
		pV[3].tex.Set( tx+0.0f, ty+0.25f );

		static const U16 index[6] = { 0, 1, 2, 0, 2, 3 };

		QuadParticleShader shader;
		shader.SetTexture0( TextureManager::Instance()->GetTexture( "particleQuad" ) );

		GPUStream stream;
		stream.stride = sizeof( pV[0] );
		stream.nPos = 3;
		stream.posOffset = 0;
		stream.nTexture0 = 2;
		stream.texture0Offset = 12;
		shader.SetColor( color );

		shader.SetStream( stream, pV, 6, index );
		shader.Draw();
	}
}