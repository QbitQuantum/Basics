void odeSpringUpdate( float damping ) {
	// APPLY spring forces
	for( int i=0; i<ODESPRINGS_MAX; i++ ) {
		if( odeSprings[i].active ) {

			FVec3 p0;
			if( odeSprings[i].dBody[0] ) {
				dReal *pos0 = (dReal *)dBodyGetPosition( odeSprings[i].dBody[0] );
				dReal *rot0 = (dReal *)dBodyGetRotation( odeSprings[i].dBody[0] );
				FMat4  mat0 = zmathODERotPosToFMat4( rot0, pos0 );
				p0 = mat0.mul( odeSprings[i].offset[0] );
			}
			else {
				p0 = odeSprings[i].offset[0];
			}

			FVec3 p1;
			if( odeSprings[i].dBody[1] ) {
				dReal *pos1 = (dReal *)dBodyGetPosition( odeSprings[i].dBody[1] );
				dReal *rot1 = (dReal *)dBodyGetRotation( odeSprings[i].dBody[1] );
				FMat4  mat1 = zmathODERotPosToFMat4( rot1, pos1 );
				p1 = mat1.mul( odeSprings[i].offset[1] );
			}
			else {
				p1 = odeSprings[i].offset[1];
			}

			FVec3 springVec = p1;
			springVec.sub( p0 );
			float len = springVec.mag();

			float formLen = odeSprings[i].formLenPtr ? *odeSprings[i].formLenPtr : odeSprings[i].formLen;
			if( len < formLen && formLen > 0.f ) {
				odeSprings[i].disabled = 0;
			}

			if( len > 0.00001f && ! odeSprings[i].disabled ) {
				springVec.div( len );

				float naturalLen = odeSprings[i].naturalLenPtr ? *odeSprings[i].naturalLenPtr : odeSprings[i].naturalLen;
				float breakLen = odeSprings[i].breakLenPtr ? *odeSprings[i].breakLenPtr : odeSprings[i].breakLen;
				float maximumForce = odeSprings[i].maximumForcePtr ? *odeSprings[i].maximumForcePtr : odeSprings[i].maximumForce;
				float constant = odeSprings[i].constantPtr ? *odeSprings[i].constantPtr : odeSprings[i].constant;

				if( len > breakLen && breakLen > 0.f ) {
					odeSprings[i].disabled = 1;
					continue;
				}

				len -= naturalLen;
				switch( odeSprings[i].type ) {
					case ODESPRING_TYPE_HOOKE:
						springVec.mul( constant * len );
						break;
					case ODESPRING_TYPE_INV_SQUARE:
						springVec.mul( constant / (len*len) );
						break;
					case ODESPRING_TYPE_CONSTANT:
						springVec.mul( constant );
						break;
				}

				float l = springVec.mag();
				if( maximumForce > 0.f && l > maximumForce ) {
					springVec.div( l );
					springVec.mul( maximumForce );
				}

				odeSpringApplyForce( odeSprings[i].dBody[0], odeSprings[i].dBody[1], odeSprings[i].offset[0], odeSprings[i].offset[1], springVec, damping );
			}
		}
	}
}