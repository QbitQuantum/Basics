void AnimationController::Interpolate( float dt ) {
	timeSinceStart += dt;
	Anim anim = *anims[currentAnim];
	float animCurrentTime = fmod( timeSinceStart, anim.totalTime );
	for( Bone* bone:anim.boneSet ) {
		XMMATRIX rotMat, scaleMat, translateMat;

		// Interpolate Rotation
		auto rotSetIt = anim.rotChannels.find( bone );
		if( rotSetIt==anim.rotChannels.end() ) {
			rotMat = XMMatrixIdentity();
		} else {
			keySet_t rotKeySet = rotSetIt->second;
			auto itLow = rotKeySet.lower_bound( animCurrentTime );
			if( itLow==rotKeySet.begin() ) {
				itLow = rotKeySet.end();
			}
			--itLow;
			auto itHigh = rotKeySet.upper_bound( animCurrentTime );
			if( itHigh==rotKeySet.end() ) {
				itHigh = rotKeySet.begin();
			}
			float factor = (animCurrentTime-itLow->first)/(itHigh->first-itLow->first);
			XMVECTOR low = XMLoadFloat4( &itLow->second );
			XMVECTOR high = XMLoadFloat4( &itHigh->second );
			XMVECTOR interp = XMQuaternionSlerp( low, high, factor );
			XMVECTOR normalized = XMQuaternionNormalize( interp );
			rotMat = XMMatrixRotationQuaternion( interp );
		}

		// Interpolate Scale
		auto scaleSetIt = anim.scaleChannels.find( bone );
		if( scaleSetIt==anim.scaleChannels.end() ) {
			scaleMat = XMMatrixIdentity();
		} else {
			keySet_t scaleKeySet = scaleSetIt->second;
			auto itLow = scaleKeySet.lower_bound( animCurrentTime );
			if( itLow==scaleKeySet.begin() ) {
				itLow = scaleKeySet.end();
			}
			--itLow;
			auto itHigh = scaleKeySet.upper_bound( animCurrentTime );
			if( itHigh==scaleKeySet.end() ) {
				itHigh = scaleKeySet.begin();
			}
			float factor = (animCurrentTime-itLow->first)/(itHigh->first-itLow->first);
			XMFLOAT4 lowVec = itLow->second;
			XMFLOAT4 highVec = itHigh->second;
			scaleMat = XMMatrixScaling(
				lowVec.x+factor*(highVec.x-lowVec.x),
				lowVec.y+factor*(highVec.y-lowVec.y),
				lowVec.z+factor*(highVec.z-lowVec.z) );
		}

		// Interpolate Position
		auto posSetIt = anim.posChannels.find( bone );
		if( posSetIt==anim.posChannels.end() ) {
			translateMat = XMMatrixIdentity();
		} else {
			keySet_t posKeySet = posSetIt->second;
			auto itLow = posKeySet.lower_bound( animCurrentTime );
			if( itLow==posKeySet.begin() ) {
				itLow = posKeySet.end();
			}
			--itLow;
			auto itHigh = posKeySet.upper_bound( animCurrentTime );
			if( itHigh==posKeySet.end() ) {
				itHigh = posKeySet.begin();
			}
			float factor = (animCurrentTime-itLow->first)/(itHigh->first-itLow->first);
			XMFLOAT4 lowVec = itLow->second;
			XMFLOAT4 highVec = itHigh->second;
			translateMat = XMMatrixTranslation(
				lowVec.x+factor*(highVec.x-lowVec.x),
				lowVec.y+factor*(highVec.y-lowVec.y),
				lowVec.z+factor*(highVec.z-lowVec.z) );
		}

		// Conversion Matrix - this converts imported coords to DirectX
		XMMATRIX reflectX = XMMatrixReflect( XMLoadFloat3( &XMFLOAT3( 1.f, 0.f, 0.f ) ) );
		XMMATRIX reflectY = XMMatrixReflect( XMLoadFloat3( &XMFLOAT3( 0.f, 1.f, 0.f ) ) );
		XMMATRIX reflectZ = XMMatrixReflect( XMLoadFloat3( &XMFLOAT3( 0.f, 0.f, 1.f ) ) );
		XMMATRIX rotX = XMMatrixRotationX( XM_PIDIV2 );
		XMMATRIX rotY = XMMatrixRotationY( XM_PIDIV2 );
		XMMATRIX rotZ = XMMatrixRotationZ( XM_PIDIV2 );
		int foo = 17; //DELETEME
		XMMATRIX flip = XMLoadFloat4x4( &XMFLOAT4X4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			) );

		XMMATRIX finalMat = scaleMat * rotMat * translateMat;
		XMFLOAT4X4 transform;
		XMStoreFloat4x4( &transform, finalMat );
		finalTransform[bone] = transform;
	}
}