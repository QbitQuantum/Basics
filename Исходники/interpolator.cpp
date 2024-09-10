// function for SLERP bezier quaternion interpolation
void Interpolator::BezierInterpolationQuaternion(Motion * pInputMotion, Motion * pOutputMotion, int N)
{
  // students should implement this
  int inputLength = pInputMotion->GetNumFrames(); // frames are indexed 0, ..., inputLength-1

  int startKeyframe = 0;
  // default and next 'a' values for bezier are stored in memory
  Quaternion<double> aDef[MAX_BONES_IN_ASF_FILE];
  Quaternion<double> aNext[MAX_BONES_IN_ASF_FILE];

  double bezRatio = 1.0/3.0;
  vector aNextRoot;
  // use a0 for the first frame by backtracking from next 2 known frames
  vector v1 = pInputMotion->GetPosture(0)->root_pos;
  vector v2 = pInputMotion->GetPosture(N+1)->root_pos;
  vector v3 = pInputMotion->GetPosture(N+1+N+1)->root_pos;
  vector aDefRoot = v1*(1-bezRatio) + (v3 * (-1) + v2 * 2) * bezRatio;

  for (int i = 0; i < MAX_BONES_IN_ASF_FILE; i++)
  {
	Quaternion<double> q1 = Vector2Quaternion(pInputMotion->GetPosture(0)->bone_rotation[i]);
	Quaternion<double> q2 = Vector2Quaternion(pInputMotion->GetPosture(N+1)->bone_rotation[i]);
	Quaternion<double> q3 = Vector2Quaternion(pInputMotion->GetPosture(N+1+N+1)->bone_rotation[i]);
	aDef[i] = Slerp(bezRatio, q1, Slerp(2.0, q3, q2));
  }

  while (startKeyframe + N + 1 < inputLength)
  {
    int endKeyframe = startKeyframe + N + 1;

    Posture * startPosture = pInputMotion->GetPosture(startKeyframe);
    Posture * endPosture = pInputMotion->GetPosture(endKeyframe);
	Posture * nextPosture;
	if (endKeyframe + N + 1 >= inputLength)	nextPosture = pInputMotion->GetPosture(inputLength-1);
	else nextPosture = pInputMotion->GetPosture(endKeyframe + (N+1));
	
    // copy start and end keyframe
    pOutputMotion->SetPosture(startKeyframe, *startPosture);
    pOutputMotion->SetPosture(endKeyframe, *endPosture);

    // interpolate in between
    for(int frame=1; frame<=N; frame++)
    {
      Posture interpolatedPosture;
      double t = 1.0 * frame / (N+1);

	  // bez interpolate root position
	  vector rootStartPos = startPosture->root_pos;
  	  vector rootEndPos = endPosture->root_pos;
	  vector rootNextPos = nextPosture->root_pos;
	  vector p1 = startKeyframe == 0? aDefRoot : aNextRoot; // use a0 if first frame, otherwise use a calculated in previous iteration
	  vector aN = rootEndPos*(1-bezRatio) + ((rootStartPos*-1+ rootEndPos*2)*0.5+ rootNextPos*0.5)*bezRatio;
	  vector p2 = aN*-1+rootEndPos*2; // bn

	  interpolatedPosture.root_pos = DeCasteljauEuler(t, rootStartPos, p1, p2, rootEndPos);

	  // interpolate bone rotations
      for (int bone = 0; bone < MAX_BONES_IN_ASF_FILE; bone++)
	  {
		  Quaternion<double> boneStartRot = Vector2Quaternion(startPosture->bone_rotation[bone]); // qn
		  Quaternion<double> boneEndRot = Vector2Quaternion(endPosture->bone_rotation[bone]); // qn+1
		  Quaternion<double> boneNextRot = Vector2Quaternion(nextPosture->bone_rotation[bone]); // qn+2

		  Quaternion<double> p1 = startKeyframe == 0? aDef[bone] : aNext[bone]; // use a0 if first frame, otherwise use a calculated in previous iteration

		  Quaternion<double> aBar = Slerp(0.5, Slerp(2.0, boneStartRot, boneEndRot), boneNextRot);
		  Quaternion<double> p2 = Slerp(-bezRatio, boneEndRot, aBar);

		  double interpolatedAngles[3];
		  Quaternion2Euler(DeCasteljauQuaternion(t, boneStartRot, p1, p2, boneEndRot), interpolatedAngles);

		  interpolatedPosture.bone_rotation[bone].setValue(interpolatedAngles);
	  }
	  pOutputMotion->SetPosture(startKeyframe + frame, interpolatedPosture);
    }

	// set the aN values for the next N frames (bezier)
	vector rootStartPos = startPosture->root_pos;
  	vector rootEndPos = endPosture->root_pos;
	vector rootNextPos = nextPosture->root_pos;
	aNextRoot = rootEndPos*(1-bezRatio) + ((rootStartPos*-1+ rootEndPos*2)*0.5+ rootNextPos*0.5)*bezRatio;

	for (int bone = 0; bone < MAX_BONES_IN_ASF_FILE; bone++)
    {
	   Quaternion<double>  boneStartRot = Vector2Quaternion(startPosture->bone_rotation[bone]); // qn
	   Quaternion<double> boneEndRot = Vector2Quaternion(endPosture->bone_rotation[bone]); // qn+1
	   Quaternion<double> boneNextRot = Vector2Quaternion(nextPosture->bone_rotation[bone]); // qn+2
	   aNext[bone] = Slerp(bezRatio, boneEndRot, Slerp(0.5, Slerp(2.0, boneStartRot, boneEndRot), boneNextRot)); // an+1
	}

    startKeyframe = endKeyframe;
  }

  for(int frame=startKeyframe+1; frame<inputLength; frame++)
    pOutputMotion->SetPosture(frame, *(pInputMotion->GetPosture(frame)));
}