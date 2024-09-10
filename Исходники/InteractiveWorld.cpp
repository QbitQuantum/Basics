/**
 *	This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
 */
bool InteractiveWorld::onMouseEvent(int eventType, int button, int mouseX, int mouseY){
	//need to figure out if the mouse is in the push interface window (and if we care)...
	if (Globals::drawPushInterface == 1 && button == MOUSE_LBUTTON && eventType != MOUSE_UP){
		Vector3d input;
		Point3d p;
		if (bInterface == false){
			tprintf("Warning: No interaction interface was created!\n");
			return false;
		}

		if (world == NULL){
			tprintf("Warning: There is no valid reference to a world!\n");
			return false;
		}

		RigidBody* dBall = world->getRBByName("dodgeBall");
		if (dBall == NULL){
			tprintf("Warning: No dodgeBall loaded!\n");
			return false;
		}

		bool eventHandled = bInterface->handleMouseEvent(mouseX, mouseY, &input);
		if (eventHandled ){
			if (input.length() > 0){
				//get the object that we will be throwing...
				getDodgeBallPosAndVel(-input.x, input.y, input.length(), &p, &input);
				dBall->setCMPosition(p);
				dBall->setCMVelocity(input);
//				dBall->updateToWorldTransformation();
			}
			return true;
		}
	}
	return false;
}