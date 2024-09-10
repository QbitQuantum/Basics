void MD5Model::animate(float dt) {
	// sanity check #1
	if (currAnim < 0 || currAnim >= int(anims.size()) || !anims[currAnim])
		throw Exception("MD5Model::animate(): currAnim is invalid");

	Anim *anim = anims[currAnim];

	// sanity check #2
	if (currFrame < 0 || currFrame >= int(anim->numFrames))
		throw Exception("MD5Model::animate(): currFrame is invalid");

	// compute index of next frame
	int nextFrameIndex = currFrame >= anim->numFrames - 1 ? 0 : currFrame + 1;

	// update animation time
	animTime += dt*float(anim->frameRate);
	if (animTime > 1.0f) {
		while (animTime > 1.0f)
			animTime -= 1.0f;
		//setFrame(nextFrameIndex);
		currFrame = nextFrameIndex;
		nextFrameIndex = currFrame >= anim->numFrames - 1 ? 0 : currFrame + 1;
	}

	// make sure size of storage for interpolated frame is correct
	if (int(interpFrame.joints.size()) != numJoints)
		interpFrame.joints.resize(numJoints);

	///// now interpolate between the two frames /////

	Frame &frame = anim->frames[currFrame],
		&nextFrame = anim->frames[nextFrameIndex];

	// interpolate between the joints of the current frame and those of the next
	// frame and store them in interpFrame
	for (int i = 0; i < numJoints; i++) {
		Joint &interpJoint = interpFrame.joints[i];

		// linearly interpolate between joint positions
		float *pos1 = frame.joints[i].pos,
			*pos2 = nextFrame.joints[i].pos;
		interpJoint.pos[0] = pos1[0] + animTime*(pos2[0] - pos1[0]);
		interpJoint.pos[1] = pos1[1] + animTime*(pos2[1] - pos1[1]);
		interpJoint.pos[2] = pos1[2] + animTime*(pos2[2] - pos1[2]);

		interpJoint.quat = slerp(frame.joints[i].quat, nextFrame.joints[i].quat, animTime);
	}

	buildVerts(interpFrame);
	buildNormals();
	calculateRenderData();
}