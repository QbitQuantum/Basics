void SpaceNavigatorSSM::mouseButtonPress(UInt16 button, Int16 x, Int16 y)
{
	switch (button)
	{
		case MouseLeft:
			// test if an object is picked
			if(_objectPicking)
			{
				Line ray = calcViewRay(x, y);
				IntersectAction *iAct = IntersectAction::create();
				iAct->setLine(ray);
				iAct->apply(this->getRoot());

				// we have a hit
				if(iAct->didHit())
				{
					_pickedObjectNode = iAct->getHitObject();
					#ifdef SPACENAVIGATOR_DEBUG_OUTPUT
					std::cout << "SpaceNavigatorSSM: Object transformation mode active ( " << getName(_pickedObjectNode) << " )" << std::endl;
					#endif // SPACENAVIGATOR_DEBUG_OUTPUT

					// go up in the graph to the next transformation
					while(!_pickedObjectNode->getCore()->getType().isDerivedFrom(Transform::getClassType()))
					{
						if(_pickedObjectNode->getParent() != this->getRoot())
							_pickedObjectNode = _pickedObjectNode->getParent();
						else
						{
							// insert a new transformation node
							NodePtr pickedObject = iAct->getHitObject();
							TransformPtr newTransform = Transform::create();
							Matrix m;
							m.setIdentity();
							beginEditCP(newTransform, Transform::MatrixFieldMask);
								newTransform->setMatrix(m);
							endEditCP(newTransform, Transform::MatrixFieldMask);

							NodePtr newTransformNode = Node::create();

							beginEditCP(newTransformNode, Node::CoreFieldMask);
								newTransformNode->setCore(newTransform);
							endEditCP(newTransformNode, Node::CoreFieldMask);
							
							NodePtr pickedObjectParent = pickedObject->getParent();

							// add reference because reCount would be 0 and then it will
							// be deleted
							addRefCP(pickedObject);

							beginEditCP(pickedObjectParent);
								pickedObjectParent->replaceChildBy(pickedObject, newTransformNode);
							endEditCP(pickedObjectParent);

							beginEditCP(newTransformNode);
								newTransformNode->addChild(pickedObject);
							endEditCP(newTransformNode);
							
							// sub the reference which was added before
							subRefCP(pickedObject);

							_pickedObjectNode = newTransformNode;
						}
					}

					// a transformation was found and the objects bounding box is showed
					this->setHighlight(_pickedObjectNode);
				}
			}
			_navigator.buttonPress(Navigator::LEFT_MOUSE,x,y);
			break;

		case MouseMiddle: 
			_navigator.buttonPress(Navigator::MIDDLE_MOUSE,x,y);
			break;

		case MouseRight:
			// release picked object and switch off bounding box rendering
			if(_objectPicking)
			{
				_pickedObjectNode = NullFC;
				this->setHighlight(NullFC);
				#ifdef SPACENAVIGATOR_DEBUG_OUTPUT
					std::cout << "SpaceNavigatorSSM: Camera transformation mode active" << std::endl;
				#endif // SPACENAVIGATOR_DEBUG_OUTPUT
			}
			_navigator.buttonPress(Navigator::RIGHT_MOUSE,x,y);
			break;

		case MouseUp:     
			_navigator.buttonPress(Navigator::UP_MOUSE,x,y);
			break;

		case MouseDown:    
			_navigator.buttonPress(Navigator::DOWN_MOUSE,x,y);
			break;
		}

		_mousebuttons |= 1 << button;
		_lastx = x;
		_lasty = y;
}