void ray_intersect_pdm( inout vec3 p, inout vec3 v )
{	
	const float EPSILON = 0.001;
	const int MAX_LEVEL = 8;
	const float NODE_COUNT = 256.0;	// displacement map resolution
	const float TEXEL_SPAN_HALF = 1.0 / NODE_COUNT / 2.0;	

	float fDeltaNC = TEXEL_SPAN_HALF * .1; //d_factor;	// offset for node crossing

	vec3 p2 = p;		// current position	
	int level = MAX_LEVEL;	// current level
	while ( level >= 0 )
	{
//		vec4 uv = vec4( p2.xyz, level );
//		float d = texture2DLod( pyramid_map, uv.xy, (float)level).w;

		float d = texture2DLod(pyramid_map, p2.xy, float(level)).w;
		if ( d > p2.z + EPSILON )
		{
			vec3 tmpP2 = p + v * d;	// new point ( predictive )

			// test node IDs
			float nodeCount = exp2(float(MAX_LEVEL - level));
			vec4 nodeID = vec4( p2.xy, tmpP2.xy );	
			nodeID = floor( nodeID * nodeCount );
			vec2 test = abs( nodeID.xy - nodeID.zw );

			if ( test.x + test.y > EPSILON )
			{
				float texelSpan = 1.0 / nodeCount;

				vec2 dirSign = ( sign(v.xy ) + 1.0 ) * 0.5;

				// distance to the next node's boundary
				vec2 a = p2.xy - p.xy;
				vec2 p3 = ( nodeID.xy + dirSign ) * texelSpan;
				vec2 b = p3.xy - p.xy;

				// node crossing
				vec2 dNC = ( b.xy * p2.z ) / a.xy;                
				d = min( d, min( dNC.x, dNC.y ) ) + fDeltaNC;

				++level;
			}

			p2 = p + v * d;
		}


		
#if 1

//TESTING

		// refinement with linearly filtered depth
		if ( level <= 0 )
		{
			vec2 ray2D =  p2.xy - p.xy;
			float rayLength = length( ray2D );
			
			float depthb = p2.z * ( rayLength + TEXEL_SPAN_HALF ) / rayLength;
			vec4 p2b = vec4( p + v * depthb, level );
			float depth2b = texture2DLod(depth_map, p2b.xy, float(level)).w;		// linearly filtered sampler
			if ( depth2b > p2b.z + EPSILON )
			{
				p2 = p2b.xyz;
				level++;
			}	
		}

//~TESTING
#endif
		count++;
		if (count>100) break;  // DEBUGGED: without this, couple of pixels may result in INFINITE LOOP =>fps=0.01

		--level;
	} // end loop
	p = p2;
}