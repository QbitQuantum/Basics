/*
============
idAASBuild::IsLedgeSide_r
============
*/
bool idAASBuild::IsLedgeSide_r( idBrushBSPNode *node, idFixedWinding *w, const idPlane &plane, const idVec3 &normal, const idVec3 &origin, const float radius ) {
	int res, i;
	idFixedWinding back;
	float dist;

	if ( !node ) {
		return false;
	}

	while ( node->GetChild(0) && node->GetChild(1) ) {
		dist = node->GetPlane().Distance( origin );
		if ( dist > radius ) {
			res = SIDE_FRONT;
		}
		else if ( dist < -radius ) {
			res = SIDE_BACK;
		}
		else {
			res = w->Split( &back, node->GetPlane(), LEDGE_EPSILON );
		}
		if ( res == SIDE_FRONT ) {
			node = node->GetChild(0);
		}
		else if ( res == SIDE_BACK ) {
			node = node->GetChild(1);
		}
		else if ( res == SIDE_ON ) {
			// continue with the side the winding faces
			if ( node->GetPlane().Normal() * normal > 0.0f ) {
				node = node->GetChild(0);
			}
			else {
				node = node->GetChild(1);
			}
		}
		else {
			if ( IsLedgeSide_r( node->GetChild(1), &back, plane, normal, origin, radius ) ) {
				return true;
			}
			node = node->GetChild(0);
		}
	}

	if ( node->GetContents() & AREACONTENTS_SOLID ) {
		return false;
	}

	for ( i = 0; i < w->GetNumPoints(); i++ ) {
		if ( plane.Distance( (*w)[i].ToVec3() ) > 0.0f ) {
			return true;
		}
	}

	return false;
}