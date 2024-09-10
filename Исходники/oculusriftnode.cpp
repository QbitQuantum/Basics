void OculusRiftNode::render( qint64 pTimeStamp, QUuid pSourcePinId )
{
	Q_UNUSED( pSourcePinId )

#if !defined( OCULUS_PLUGIN_SUPPORTED )
	Q_UNUSED( pTimeStamp )
#else
	fugio::Performance	Perf( mNode, "drawGeometry", pTimeStamp );

	if( !mNode->isInitialised() )
	{
		return;
	}

	if( !mOculusRift->hmd() )
	{
		return;
	}

	// We need to keep a reference to ourselves here as ovr_SubmitFrame can
	// call the main app event loop, which can close the context and delete us!

	QSharedPointer<fugio::NodeControlInterface>	C = mNode->control();

	mOculusRift->drawStart();

	const float		NearPlane = variant( mPinNearPlane ).toFloat();
	const float		FarPlane  = variant( mPinFarPlane ).toFloat();

	//	float Yaw(3.141592f);
	//	Vector3f Pos2(0.0f,1.6f,-5.0f);
	//	Pos2.y = ovrHmd_GetFloat(mHMD, OVR_KEY_EYE_HEIGHT, Pos2.y);

	QMatrix4x4		MatEye = variant( mPinViewMatrix ).value<QMatrix4x4>();
	QVector3D		TrnEye = MatEye.column( 3 ).toVector3D();

	MatEye.setColumn( 3, QVector4D( 0, 0, 0, 1 ) );

	const Vector3f Pos2( TrnEye.x(), TrnEye.y(), TrnEye.z() );

	Matrix4f tempRollPitchYaw;

	memcpy( tempRollPitchYaw.M, MatEye.constData(), sizeof( float ) * 16 );

	const Matrix4f rollPitchYaw = tempRollPitchYaw;

	// Render Scene to Eye Buffers
	for (int eye = 0; eye < 2; eye++)
	{
		mOculusRift->drawEyeStart( eye );

		// Get view and projection matrices
		//Matrix4f rollPitchYaw = Matrix4f( MatEye.transposed().data() );
		Matrix4f finalRollPitchYaw = rollPitchYaw * Matrix4f( mOculusRift->eyeRenderPos( eye ).Orientation);
		Vector3f finalUp = finalRollPitchYaw.Transform(Vector3f(0, 1, 0));
		Vector3f finalForward = finalRollPitchYaw.Transform(Vector3f(0, 0, -1));
		Vector3f shiftedEyePos = Pos2 + rollPitchYaw.Transform( mOculusRift->eyeRenderPos( eye ).Position );

		Matrix4f view = Matrix4f::LookAtRH(shiftedEyePos, shiftedEyePos + finalForward, finalUp);
		Matrix4f proj = ovrMatrix4f_Projection( mOculusRift->defaultEyeFOV( eye ), NearPlane, FarPlane, ovrProjection_None );

		mProjection->setVariant( QMatrix4x4( &proj.M[ 0 ][ 0 ], 4, 4 ).transposed() );

		mView->setVariant( QMatrix4x4( &view.M[ 0 ][ 0 ], 4, 4 ).transposed() );

		fugio::OpenGLStateInterface		*CurrentState = 0;

		for( QSharedPointer<fugio::PinInterface> P : mNode->enumInputPins() )
		{
			if( !P->isConnected() )
			{
				continue;
			}

			if( P->connectedPin().isNull() )
			{
				continue;
			}

			if( P->connectedPin()->control().isNull() )
			{
				continue;
			}

			QObject					*O = P->connectedPin()->control()->qobject();

			if( !O )
			{
				continue;
			}

			if( true )
			{
				fugio::RenderInterface		*Geometry = qobject_cast<fugio::RenderInterface *>( O );

				if( Geometry )
				{
					Geometry->render( pTimeStamp );

					continue;
				}
			}

			if( true )
			{
				fugio::OpenGLStateInterface		*NextState = qobject_cast<fugio::OpenGLStateInterface *>( O );

				if( NextState != 0 )
				{
					if( CurrentState != 0 )
					{
						CurrentState->stateEnd();
					}

					CurrentState = NextState;

					CurrentState->stateBegin();

					continue;
				}
			}
		}

		if( CurrentState != 0 )
		{
			CurrentState->stateEnd();
		}

		mOculusRift->drawEyeEnd( eye );
	}

	mOculusRift->drawEnd();

	pinUpdated( mPinProjection );
	pinUpdated( mPinView );
#endif
}