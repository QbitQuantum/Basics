/*
================
R_CalcInteractionFacing

Determines which triangles of the surface are facing towards the light origin.

The facing array should be allocated with one extra index than
the number of surface triangles, which will be used to handle dangling
edge silhouettes.
================
*/
void R_CalcInteractionFacing( const idRenderEntityLocal *ent, const srfTriangles_t *tri, const idRenderLightLocal *light, srfCullInfo_t &cullInfo ) {
	SCOPED_PROFILE_EVENT( "R_CalcInteractionFacing" );

	if ( cullInfo.facing != NULL ) {
		return;
	}

	idVec3 localLightOrigin;
	R_GlobalPointToLocal( ent->modelMatrix, light->globalLightOrigin, localLightOrigin );

	const int numFaces = tri->numIndexes / 3;
	cullInfo.facing = (byte *) R_StaticAlloc( ( numFaces + 1 ) * sizeof( cullInfo.facing[0] ), TAG_RENDER_INTERACTION );

	// exact geometric cull against face
	for ( int i = 0, face = 0; i < tri->numIndexes; i += 3, face++ ) {
		const idDrawVert & v0 = tri->verts[tri->indexes[i + 0]];
		const idDrawVert & v1 = tri->verts[tri->indexes[i + 1]];
		const idDrawVert & v2 = tri->verts[tri->indexes[i + 2]];

		const idPlane plane( v0.xyz, v1.xyz, v2.xyz );
		const float d = plane.Distance( localLightOrigin );

		cullInfo.facing[face] = ( d >= 0.0f );
	}
	cullInfo.facing[numFaces] = 1;	// for dangling edges to reference
}