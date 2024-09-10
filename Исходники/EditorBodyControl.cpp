bool EditorBodyControl::ProcessMouse(UIEvent *event)
{
	Entity * selection = scene->GetProxy();
	//selection with second mouse button
    
	if (event->tid == UIEvent::BUTTON_1)
	{
		if (event->phase == UIEvent::PHASE_BEGAN)
		{
			isDrag = false;
			inTouch = true;
			touchStart = event->point;

			if (selection)
			{
				modifiedNode = selection;
				transformBeforeModification = selection->GetLocalTransform();
			}
		}
		else if (event->phase == UIEvent::PHASE_DRAG)
		{
			if (!isDrag)
			{
				Vector2 d = event->point - touchStart;
				
				if (selection && d.Length() > 5 && InModificationMode())
				{
					ArrowsNode* arrowsNode = GetArrowsNode(false);
					if (arrowsNode && arrowsNode->GetModAxis() != ArrowsNode::AXIS_NONE)
					{
						isDrag = true;
						if (InputSystem::Instance()->GetKeyboard()->IsKeyPressed(DVKEY_SHIFT))
						{
							originalNode = scene->GetProxy();

							//create temporary node to calculate transform
							modifiedNode = originalNode->Clone();
							originalNode->GetParent()->AddNode(modifiedNode);
							SelectNode(modifiedNode);
							selection = modifiedNode;

							//store original transform
							transformBeforeModification = modifiedNode->GetLocalTransform();
						}

						if (selection)
						{
							scene->SetBulletUpdate(selection, false);

							inTouch = true;
							touchStart = event->point;
						
							startTransform = selection->GetLocalTransform();
						
							InitMoving(event->point);
						
							translate1.CreateTranslation(-rotationCenter);
							translate2.CreateTranslation(rotationCenter);
						
							//calculate koefficient for moving
							Camera * cam = scene->GetCurrentCamera();
							const Vector3 & camPos = cam->GetPosition();
							const Matrix4 & wt = selection->GetWorldTransform();
							Vector3 objPos = Vector3(0,0,0) * wt;
							Vector3 dir = objPos - camPos;
							moveKf = (dir.Length() - cam->GetZNear()) * 0.003;
						}
					}
				}
			}
			else
			{
				if (selection && InModificationMode())
				{
                    Landscape *landscape = dynamic_cast<Landscape *>(selection);
                    if(!landscape)
                    {
                        PrepareModMatrix(event->point);

						if (IsLandscapeRelative())
						{
							currTransform = currTransform * GetLandscapeOffset(currTransform);
						}

						selection->SetLocalTransform(currTransform);

                        if(currentGraph)
                        {
                            currentGraph->UpdateMatricesForCurrentNode();
                        }
                    }
				}
			}
		}
		else if (event->phase == UIEvent::PHASE_ENDED)
		{
			inTouch = false;
			if (isDrag)
			{
				// originalNode should be non-zero only when clone node
				if (originalNode)
				{
					// Get final transform from temporary node
					Matrix4 transform = modifiedNode->GetLocalTransform();

					// Remove temporary node
					RemoveSelectedSGNode();
					SafeRelease(modifiedNode);
					
					CommandCloneAndTransform* cmd = new CommandCloneAndTransform(originalNode,
																				 transform,
																				 this,
																				 scene->collisionWorld);
					CommandsManager::Instance()->ExecuteAndRelease(cmd, scene);
					originalNode = NULL;

					// update selection to newly created node
					selection = scene->GetProxy();
				}
				else
				{
					CommandsManager::Instance()->ExecuteAndRelease(new CommandTransformObject(modifiedNode,
																							  transformBeforeModification,
																							  modifiedNode->GetLocalTransform()),
																   scene);
				}

				if (selection)
				{
					scene->SetBulletUpdate(selection, true);
				}
			}
			else
			{
				Vector3 from, dir;
				GetCursorVectors(&from, &dir, event->point);
				Vector3 to = from + dir * 1000.0f;
				scene->TrySelection(from, to);
				selection = scene->GetProxy();
				SelectNodeAtTree(selection);
			}
		}
	}
	else
	{
		cameraController->SetSelection(selection);
        
        if (event->phase == UIEvent::PHASE_KEYCHAR)
        {
            UITextField *tf = dynamic_cast<UITextField *>(UIControlSystem::Instance()->GetFocusedControl());
            if(!tf)
            {
                cameraController->Input(event);
            }
        }
        else
        {
            cameraController->Input(event);
        }
	}

	ArrowsNode* arrowsNode = GetArrowsNode(false);
	if (arrowsNode && arrowsNode->GetVisible() && !inTouch && event->phase != UIEvent::PHASE_KEYCHAR)
	{
		Vector3 from, dir;
		GetCursorVectors(&from, &dir, event->point);
		Vector3 to = from + dir * 1000.0f;
		arrowsNode->ProcessMouse(event, from, dir);
	}
	
    return true;
}