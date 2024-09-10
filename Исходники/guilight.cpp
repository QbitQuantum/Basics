void GUI3DDirectionArrow::handleMsg( ZMsg *msg ) {
	if( zmsgIs(type,MouseClickOn) && zmsgIs(which,L) && zmsgIs(dir,D) ) {
		startDrag = FVec2( zmsgF(localX), zmsgF(localY) );
		startDragMat = mat;
		requestExclusiveMouse( 1, 1 );
		zMsgUsed();
		sendMsg();
	}
	else if( zmsgIs(type,MouseReleaseDrag) ) {
		requestExclusiveMouse( 1, 0 );
		zMsgUsed();
	}
	else if( zmsgIs(type,MouseDrag) ) {
		FVec2 mouseDelta( zmsgF(localX), zmsgF(localY) );
		mouseDelta.sub( startDrag );
		mouseDelta.mul( 0.03f );
		mat = startDragMat;
		FMat4 eye = mat;
		eye.setTrans( FVec3::Origin );
		eye.inverse();
		FVec3 yEye = eye.mul( FVec3::YAxisMinus );
		FVec3 xEye = eye.mul( FVec3::XAxis );
		mat.cat( rotate3D( yEye, mouseDelta.x ) );
		mat.cat( rotate3D( xEye, mouseDelta.y ) );
		zMsgUsed();
		sendMsg();
	}
	else if( zmsgIs(type,SetDir) ) {
		FVec3 xaxis( zmsgF(x), zmsgF(y), zmsgF(z) );
		xaxis.mul(-1.f);
		FVec3 yaxis( 0.f, 1.f, 0.f );
		yaxis.cross( xaxis );
		FVec3 zaxis = yaxis;
		zaxis.cross( xaxis );
		xaxis.normalize();
		yaxis.normalize();
		zaxis.normalize();
		mat.m[0][0] = xaxis.x;
		mat.m[0][1] = xaxis.y;
		mat.m[0][2] = xaxis.z;
		mat.m[0][3] = 0.f;
		mat.m[1][0] = yaxis.x;
		mat.m[1][1] = yaxis.y;
		mat.m[1][2] = yaxis.z;
		mat.m[1][3] = 0.f;
		mat.m[2][0] = zaxis.x;
		mat.m[2][1] = zaxis.y;
		mat.m[2][2] = zaxis.z;
		mat.m[2][3] = 0.f;
		mat.m[3][0] = 0.f;
		mat.m[3][1] = 0.f;
		mat.m[3][2] = 0.f;
		mat.m[3][3] = 1.f;
	}
}