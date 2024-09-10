void TrajectoryController::runBezierCurve() {
	if (bezierCurve.isActive()) {
		unsigned long now = millis();
		TimedPosition startPos = trajectory.get(0);
		TimedPosition& endPos = trajectory.get(1);
		TimedPosition afterPos;
		if (trajectory.size() > 2)
			afterPos = trajectory.get(2);

		// compute ratio 0..1 where we are in current part of the curve
		float t = ((float)now-(float)startPos.atTime) / ((float)endPos.atTime- (float)startPos.atTime);
		if (t <= 1.0) {
			TimedPosition tensor = bezierCurve.getCurrent(t);


			// limit the acceleration for a smooth movement
			Kinematics::getInstance().limitAcceleration(tensor);

			// check if we need to adapt the curve online by looking at a stupid face
			// do this by adapting the end point of the curve in order to smooth the movement
			static Point filteredFacePosition;
			if (startPos.isStareAtFace() || startPos.isLookAtFace()) {
				// current face is either the just detected face (stareAtFace),
				// or the defined face from start point (lookAtFace)
				TimedPosition currentFace =
						startPos.isStareAtFace()?
								TrajectoryController::getInstance().getDetectedFace():
								TimedPosition(startPos.atTime,Position(startPos.getLookAtFacePoint(), Rotation()));

				if (!currentFace.isNull()) {
					if (filteredFacePosition.isNull()) {
						// define an artificial point Luci is currently looking
						// at in the same distance like the found face
						Position curr = Kinematics::getInstance().getCurrentPosition();
						Point lookAt = Kinematics::getInstance().getLookAtPoint(curr, currentFace.pos.point.distance(curr.point));
						filteredFacePosition = lookAt;
					}
					else {
						float dist = filteredFacePosition.distance(currentFace.pos.point);
						float f = (1.0-dist/(150+dist))/10 - 0.02;
						filteredFacePosition = filteredFacePosition*(1.0-f) + currentFace.pos.point*f;
						// cout << "d=" << dist << "f" << f*100 << "%" << endl;
					}
				}

				if (!filteredFacePosition.isNull()) {
					Rotation orientationTowardsFace;
					Kinematics::getInstance().lookAt(tensor.pos.point,
							filteredFacePosition,
							orientationTowardsFace);
					tensor.pos.rot = orientationTowardsFace;
				}

				static unsigned long lastFaceDetection = 0;
				if (currentFace.atTime != lastFaceDetection) {
					lastFaceDetection = currentFace.atTime;
					// new face has been detected
					// patch the end of the trajctory, to ensure that in case the next piece is supposed to
					// not stare at the face, there is no sudden movement.

					// patch the end position of the trajectory
					// (if possible patch the next trajectory as well)
					// dont use amend, since it is anyhow patched with every iteration
					Rotation endPointRot;
					Kinematics::getInstance().lookAt(endPos.pos.point,filteredFacePosition,endPointRot);
					endPos.pos.rot = endPointRot;
					bezierCurve.patchB(endPos,endPos.pos);
				}
				if (debugBezier) {
					tensor.println("faced-bezier-pnt");
				}
			} else {
				// reset the latest face position to not have a jump when stare/lookAtFace-mode starts again
				filteredFacePosition.null();

				if (debugBezier) {
					tensor.println("bezier-pnt");
					cout << "t=" << t;
					// bezierCurve.print();
				}
			}
			Kinematics::getInstance().moveServosTo(tensor.pos);
		} else {
			// we are later than approaching time, so this piece of the curve has been done already, take next piece
			startNextTrajectoryPiece();
			runBezierCurve();
		}
	}
}