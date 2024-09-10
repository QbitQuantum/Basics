/////////////////////////////////////
// Name:	
// Purpose:	
// Output:	
// Return:	
/////////////////////////////////////
PUBLIC RETCODE OBJUpdateFrame(hOBJ obj)
{
	//create the world matrix
	_GFXCreateWrld(&obj->wrldMtx);

	if(!TESTFLAGS(obj->status, OBJ_PAUSE))
	{
		if(obj->states)
		{
			//there can either be keyframes or joints,
			//we cannot have both!

			//if there are key frames...
			if(TESTFLAGS(obj->theMdl->status, MDL_FRAME))
			{
				double time = TimeGetTime(&obj->ticker)*obj->animeScale;

				if(obj->states[obj->curState].delay > 0)
					time /= obj->states[obj->curState].delay;
				else
					time = 0;

				//time *= obj->animeScale;

				//advance to next frame if we reach 1
				while(time >= 1)
				{
					TimeReset(&obj->ticker);

					obj->prevFrame = obj->curFrame;
					obj->curFrame++;

					if(obj->curFrame > obj->states[obj->curState].endFrame)
					{
						if(TESTFLAGS(obj->status, OBJ_PAUSE_ON_END))
						{ OBJPause(obj, true); obj->curFrame = obj->states[obj->curState].endFrame; }
						else
							obj->curFrame = obj->states[obj->curState].startFrame;
					}

					time -= 1;
				}

				MeshInterpolate(&obj->theMdl->frames[obj->prevFrame].frameMesh, 
					&obj->theMdl->frames[obj->curFrame].frameMesh, 
					time, obj->curMesh);
			}
			//otherwise, if there are joints...
			else if(TESTFLAGS(obj->theMdl->status, MDL_JOINT))
			{
				double time = TimeGetTime(&obj->ticker)*obj->animeScale;

				if(obj->states[obj->curState].delay > 0)
					time /= obj->states[obj->curState].delay;
				else
					time = 0;

				//time *= obj->animeScale;

				//advance to next frame if we reach 1
				while(time >= 1)
				{
					TimeReset(&obj->ticker);

					obj->prevFrame = obj->curFrame;
					obj->curFrame++;

					if(obj->curFrame > obj->states[obj->curState].endFrame)
					{
						if(TESTFLAGS(obj->status, OBJ_PAUSE_ON_END))
						{ 
							SETFLAG(obj->status, OBJ_PAUSE); 
							obj->curFrame = obj->states[obj->curState].endFrame;
							time=0;
							break;
						}
						else
						{
							obj->curFrame = obj->states[obj->curState].startFrame;
						}
					}

					time -= 1;
				}

				//interpolate joint
				if(TESTFLAGS(obj->status, OBJ_CHILD))
				{
					hOBJ parent = OBJQuery(&obj->parentKey);

					JointInterpolate(obj->joints,
									obj->theMdl->joints,
									obj->theMdl->numJoints, time,
									obj->theMdl->numFrames, obj->prevFrame, obj->curFrame,
									parent ? parent->joints : 0, obj->parentJointInd);
				}
				else
				{
					JointInterpolate(obj->joints,
									obj->theMdl->joints,
									obj->theMdl->numJoints, time,
									obj->theMdl->numFrames, obj->prevFrame, obj->curFrame);
				}

				//MeshTranslateVtxJoint(obj->curMesh, obj->joints);
			}
		}

		//go through the children and update them...
		for(LISTPTR::iterator i = obj->objNode->begin(); i != obj->objNode->end(); ++i)
			OBJUpdateFrame((hOBJ)(*i));
	}

	return RETCODE_SUCCESS;
}