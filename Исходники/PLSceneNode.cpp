/**
*  @brief
*    Writes the scene node modifiers
*/
void PLSceneNode::WriteModifiers(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	// Is there a 3ds Max node? (no 3ds Max node, no properties)
	INode *pMaxNode = GetMaxNode();
	if (pMaxNode) {
		// Has this 3ds Max node a target?
		if (pMaxNode->GetTarget()) {
			// Write down the scene node modifier
			WriteTargetRotationModifier(cSceneElement, *pMaxNode->GetTarget(), false);
		}

		// Are there any position, rotation, scale keyframes?
		bool bPositionKeyframes = false;
		bool bRotationKeyframes = false;
		bool bScaleKeyframes    = false;

		// Check 3ds Max node controllers
		Control *pTMController = pMaxNode->GetTMController();
		if (pTMController) {
			// Position controller
			Control *pController = pTMController->GetPositionController();
			if (pController) {
				// Are there any position keyframes?
				bPositionKeyframes = PLTools::HasKeyControlInterface(*pController);
				if (!bPositionKeyframes) {
					// Is there a path controller?
					IPathPosition *pPathController = GetIPathConstInterface(pController);
					if (pPathController && pPathController->GetNumTargets() > 0) {
						INode *pTarget = pPathController->GetNode(0);
						if (pTarget) {
							// Get path filename
							const String sPathFilename = PLTools::GetResourceFilename(PLTools::ResourcePath, String(pTarget->GetName()) + ".path");

							// Get the percentage along the path
							float fPercentageAlongPath = 0.0f;
							{
								IParamBlock2 *pIParamBlock2 = pPathController->GetParamBlock(path_params);
								int nRefNum = pIParamBlock2 ? pIParamBlock2->GetControllerRefNum(path_percent) : -1;
								RefTargetHandle cRefTargetHandle = (nRefNum >= 0) ? pIParamBlock2->GetReference(nRefNum) : nullptr;
								if (cRefTargetHandle)
									fPercentageAlongPath = pIParamBlock2->GetFloat(path_percent, 0);
							}

							{ // Add scene node modifier
								XmlElement *pModifierElement = new XmlElement("Modifier");
								pModifierElement->SetAttribute("Class",   "PLScene::SNMPositionPath");
								pModifierElement->SetAttribute("Filename", sPathFilename);
								pModifierElement->SetAttribute("Progress", String::Format("%f", fPercentageAlongPath));

								// [TODO] Any change to setup speed inside 3ds Max?
								static const float fSpeed = 0.03f;
								// Automatic animation playback?
								if (g_SEOptions.bAnimationPlayback)
									pModifierElement->SetAttribute("Speed", String::Format("%f", (pPathController->GetFlip() ? -fSpeed : fSpeed)));
								else
									pModifierElement->SetAttribute("Speed", "0.0");

								// Link modifier element
								cSceneElement.LinkEndChild(*pModifierElement);
							}

							// Follow?
							if (pPathController->GetFollow()) {
								// Add scene node modifier
								XmlElement *pModifierElement = new XmlElement("Modifier");
								pModifierElement->SetAttribute("Class",  "PLScene::SNMRotationMoveDirection");

								// Link modifier element
								cSceneElement.LinkEndChild(*pModifierElement);
							}
						}
					}
				}
			}

			// Rotation controller
			pController = pTMController->GetRotationController();
			if (pController) {
				// Are there any rotation keyframes?
				bRotationKeyframes = PLTools::HasKeyControlInterface(*pController);
				if (!bRotationKeyframes) {
					// Is there a look at controller?
					ILookAtConstRotation *pLookAtController = GetILookAtConstInterface(pController);
					if (pLookAtController && pLookAtController->GetNumTargets() > 0) {
						INode *pTarget = pLookAtController->GetNode(0);
						if (pTarget) {
							// Check look at controller
							bool bFlip = (pLookAtController->GetTargetAxisFlip() != 0);

							// Write down the scene node modifier
							WriteTargetRotationModifier(cSceneElement, *pTarget, bFlip);
						}
					}
				}
			}

			// Scale controller
			pController = pTMController->GetScaleController();
			if (pController) {
				// Are there any scale keyframes?
				bScaleKeyframes = PLTools::HasKeyControlInterface(*pController);
			}
		}

		// Export keyframes?
		if (bPositionKeyframes || bRotationKeyframes || bScaleKeyframes) {
			// Get timing
			Interval cInterval = GetCOREInterface()->GetAnimRange();
			int nTicksPerFrame = GetTicksPerFrame();
			int nFrameCount    = (cInterval.End() - cInterval.Start()) / nTicksPerFrame + 1;

			// Used to detect whether or not something is animated
			Point3 vFirstPos, vFirstScale;
			Quat qFirstRot;
			bool bUsePosition = false, bUseScale = false, bUseRotation = false;

			// Prepare the position chunk
			Chunk cPositionChunk;
			cPositionChunk.SetSemantic(Chunk::Position);
			cPositionChunk.Allocate(Chunk::Float, 3, nFrameCount);
			float *pfPositionData = reinterpret_cast<float*>(cPositionChunk.GetData());

			// Prepare the rotation chunk
			Chunk cRotationChunk;
			cRotationChunk.SetSemantic(Chunk::Rotation);
			cRotationChunk.Allocate(Chunk::Float, 4, nFrameCount);
			float *pfRotationData = reinterpret_cast<float*>(cRotationChunk.GetData());

			// Prepare the scale chunk
			Chunk cScaleChunk;
			cScaleChunk.SetSemantic(Chunk::Scale);
			cScaleChunk.Allocate(Chunk::Float, 3, nFrameCount);
			float *pfScaleData = reinterpret_cast<float*>(cScaleChunk.GetData());

			// Loop through all frames
			int nTime = cInterval.Start();
			for (int nFrame=0; nFrame<nFrameCount; nFrame++, nTime+=nTicksPerFrame) {
				// Get the position, rotation and scale
				Point3 vPos, vScale;
				Quat qRot;
				GetPosRotScale(vPos, qRot, vScale, nTime);

				// First frame?
				if (!nFrame) {
					vFirstPos   = vPos;
					vFirstScale = vScale;
					qFirstRot   = qRot;
				} else {
					if (!vFirstPos.Equals(vPos))
						bUsePosition = true;
					if (!vFirstScale.Equals(vScale))
						bUseScale = true;
					if (!qFirstRot.Equals(qRot))
						bUseRotation = true;
				}

				// Position
				if (bPositionKeyframes && pfPositionData) {
					// Currently ONLY the center of the container the node is in use used to make it relative
					const Point3 vParentWorldSpaceCenter = GetContainer() ? GetContainer()->GetWorldSpaceCenter() : Point3(0.0f, 0.0f, 0.0f);

					// Get the position
					const Point3 vFinalPos = (GetType() != TypeScene && GetType() != TypeCell) ? vPos-vParentWorldSpaceCenter : static_cast<const PLSceneContainer*>(this)->GetWorldSpaceCenter();

					// x
					*pfPositionData = vFinalPos.x;
					pfPositionData++;

					// y
					*pfPositionData = vFinalPos.y;
					pfPositionData++;

					// z
					*pfPositionData = vFinalPos.z;
					pfPositionData++;
				}

				// Rotation
				if (bRotationKeyframes && pfRotationData) {

					// [TODO] Check this (why do we need it?)
					qRot.Invert();

					// w
					*pfRotationData = qRot.w;
					pfRotationData++;

					// x
					*pfRotationData = qRot.x;
					pfRotationData++;

					// y
					*pfRotationData = qRot.y;
					pfRotationData++;

					// z
					*pfRotationData = qRot.z;
					pfRotationData++;
				}

				// Scale
				if (bScaleKeyframes && pfScaleData) {
					// x
					*pfScaleData = vScale.x;
					pfScaleData++;

					// y
					*pfScaleData = vScale.y;
					pfScaleData++;

					// z
					*pfScaleData = vScale.z;
					pfScaleData++;
				}
			}

			// Create keyframe animation scene node modifiers
			if (bPositionKeyframes && bUsePosition) {
				// [TODO] Better (and safer) filename
				// Save chunk
				const String sPositionKeys = PLTools::GetResourceFilename(PLTools::ResourceKeyframes, String::Format("%s_PositionKeyframes.chunk", GetName().GetASCII()).GetASCII());
				if (SaveChunk(cPositionChunk, sApplicationDrive + sApplicationDir + sPositionKeys)) {
					// Add the modifier
					XmlElement *pModifierElement = new XmlElement("Modifier");

					// Set class attribute
					pModifierElement->SetAttribute("Class", "PLScene::SNMPositionKeyframeAnimation");

					// [TODO] Currently the frame rate is by default always 24
					// Set frames per second attribute
	//				pModifierElement->SetAttribute("FramesPerSecond", GetFrameRate());


					// Automatic animation playback?
					pModifierElement->SetAttribute("Speed", g_SEOptions.bAnimationPlayback ? "1.0" : "0.0");

					// Set keys attribute
					pModifierElement->SetAttribute("Keys", sPositionKeys);

					// Link modifier elements
					cSceneElement.LinkEndChild(*pModifierElement);
				}
			}
			if (bRotationKeyframes && bUseRotation) {
				// [TODO] Better (and safer) filename
				// Save chunk
				const String sRotationKeys = PLTools::GetResourceFilename(PLTools::ResourceKeyframes, String::Format("%s_RotationKeyframes.chunk", GetName().GetASCII()).GetASCII());
				if (SaveChunk(cRotationChunk, sApplicationDrive + sApplicationDir + sRotationKeys)) {
					// Add the modifier
					XmlElement *pModifierElement = new XmlElement("Modifier");

					// Set class attribute
					pModifierElement->SetAttribute("Class", "PLScene::SNMRotationKeyframeAnimation");

					// [TODO] Currently the frame rate is by default always 24
					// Set frames per second attribute
	//				pModifierElement->SetAttribute("FramesPerSecond", GetFrameRate());

					// Automatic animation playback?
					pModifierElement->SetAttribute("Speed", g_SEOptions.bAnimationPlayback ? "1.0" : "0.0");

					// Set keys attribute
					pModifierElement->SetAttribute("Keys", sRotationKeys);

					// Link modifier elements
					cSceneElement.LinkEndChild(*pModifierElement);
				}
			}
			if (bScaleKeyframes && bUseScale) {
				// [TODO] Better (and safer) filename
				// Save chunk
				const String sScaleKeys = PLTools::GetResourceFilename(PLTools::ResourceKeyframes, String::Format("%s_ScaleKeyframes.chunk", GetName().GetASCII()).GetASCII());
				if (SaveChunk(cScaleChunk, sApplicationDrive + sApplicationDir + sScaleKeys)) {
					// Add the modifier
					XmlElement *pModifierElement = new XmlElement("Modifier");

					// Set class attribute
					pModifierElement->SetAttribute("Class", "PLScene::SNMScaleKeyframeAnimation");

					// [TODO] Currently the frame rate is by default always 24
					// Set frames per second attribute
	//				pModifierElement->SetAttribute("FramesPerSecond", GetFrameRate());

					// Automatic animation playback?
					pModifierElement->SetAttribute("Speed", g_SEOptions.bAnimationPlayback ? "1.0" : "0.0");

					// Set keys attribute
					pModifierElement->SetAttribute("Keys", sScaleKeys);

					// Link modifier elements
					cSceneElement.LinkEndChild(*pModifierElement);
				}
			}
		}

		// Use modifiers?
		if (g_SEOptions.bUserPropModifiers) {
			// Check for modifiers
			MSTR sModifier;
			int nIndex = 1;
			TSTR s3dsMaxString;
			sModifier = _T("Mod");
			while (pMaxNode->GetUserPropString(sModifier, s3dsMaxString)) {
				// Add scene node modifier
				XmlElement *pModifierElement = new XmlElement("Modifier");

				// We really NEED a 'Class' attribute!
				bool bClassFound = false;

				// Get all expressions
				static RegEx cExpressionRegEx("\\s*((\\w*\\s*=\\s*\"[^\"]*\")|(\\w*\\s*=\\s*[\\w|]*))");
				const String sString = s3dsMaxString;
				uint32 nExpressionParsePos = 0;
				while (cExpressionRegEx.Match(sString, nExpressionParsePos)) {
					// Get expression
								 nExpressionParsePos = cExpressionRegEx.GetPosition();
					const String sExpression		 = cExpressionRegEx.GetResult(0);

					// Process the found expression
					static RegEx cRegEx("\\s*(\\w*)\\s*=\\s*\"?\\s*([^\"]*)\\s*\"?");
					if (cRegEx.Match(sExpression)) {
						// Get name and value
						const String sName  = cRegEx.GetResult(0);
						const String sValue = cRegEx.GetResult(1);

						// Set attribute
						pModifierElement->SetAttribute(sName, sValue);

						// Class variable already found?
						if (!bClassFound && sName == "Class")
							bClassFound = true;
					}
				}

				// Link modifier element?
				if (bClassFound)
					cSceneElement.LinkEndChild(*pModifierElement);
				else 
					delete pModifierElement;

				// Get next modifier
				sModifier.printf(_T("Mod%d"), nIndex);
				nIndex++;
			}
		}
	}
}