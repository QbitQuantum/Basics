	int Object::createPlane( Material* mat , float w , float h , float* color , float xTile , float yTile , 
		                       Vector3 const& normal , Vector3 const& alignDir , Vector3 const& offset , bool invYDir )
	{
		Vector3 yLen =  normal.cross( alignDir );
		assert( yLen.length2() > 1e-4 );

		yLen.normalize();
		Vector3 xLen = yLen.cross( normal );

		xLen *= 0.5f * w;
		yLen *= 0.5f * h;

		if ( invYDir )
			yLen = -yLen;

		Vector3 n = normal;
		n.normalize();

		int texLen = 2;
		VertexType type = ( color ) ? CFVT_XYZ_N_CF1 : CFVT_XYZ_N;
		//VertexType type = ( color ) ? CFVT_XYZ_CF1 : CFVT_XYZ;

		MeshBuilder builder = MeshBuilder( type | CFVF_TEX1( 2 ) );

		if ( color )
			builder.setColor( color );

		builder.setNormal( n );

		builder.reserveVexterBuffer( 4 );
		builder.reserveIndexBuffer( 12 );

		builder.setPosition( offset - xLen - yLen );
		builder.setTexCoord( 0 , 0 , 0 );
		builder.addVertex();

		builder.setPosition( offset + xLen - yLen );
		builder.setTexCoord( 0 ,xTile, 0 );
		builder.addVertex();

		builder.setPosition( offset + xLen + yLen );
		builder.setTexCoord( 0 , xTile , yTile );
		builder.addVertex();

		builder.setPosition( offset - xLen + yLen );
		builder.setTexCoord( 0 , 0 , yTile );
		builder.addVertex();

		builder.addQuad( 0 , 1 , 2 , 3 );

		return builder.createIndexTrangle( this , mat );
	}