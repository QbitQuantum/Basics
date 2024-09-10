	void BoneNode::interpolationMotion( Vector3& pos , Quaternion& rotate , int frame  , float t )
	{
		assert( keyFrames );

		MotionKeyFrame& frame0 = keyFrames[ frame ];
		MotionKeyFrame& frame1 = keyFrames[ frame + 1 ];

		if ( t == 0 )
		{
			pos    = frame0.pos;
			rotate = frame0.rotation ;
		}
		else
		{
			pos    = lerp( frame0.pos , frame1.pos , t );
			rotate = slerp( frame0.rotation , frame1.rotation , t );
		}
	}