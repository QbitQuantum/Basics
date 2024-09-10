void ActorSceneCanvas::OnMouseMove(wxMouseEvent& e)
{

	ShowPos(e.GetX(), e.GetY());

    if (!GetSceneManipulator())
        return;

    if (m_pCameraManip)
    {
        wxASSERT(mDragButton != wxMOUSE_BTN_NONE);
        m_pCameraManip->onMotion(e.GetX(), e.GetY());
    }

	if (mDragStarted  && e.LeftIsDown())
	{
		mDragCurrent =Ogre::Vector2(e.GetX(), e.GetY()) ;
		mDragDelta = mDragCurrent - mDragOrigin;
		mDragOrigin = mDragCurrent;

		if (Fairy::CDataManipulator::GetDataManipulator() && mCanManipulateAxis)
		{	
			Ogre::Camera* camera = GetSceneManipulator()->getCamera();
			assert (camera);
			Ogre::Vector3 oldPos = camera->getPosition();
			Fairy::LogicModel* pModel = GetDataManipulator()->m_pObjTemplate;
			if (pModel)
			{
				Ogre::Vector3 objPos = pModel->getPosition();
				Ogre::Real distance = oldPos.distance(objPos);
				Ogre::Real factor = distance*0.1/150.0;

				Ogre::Vector3 pos=Fairy::CDataManipulator::m_baseNode->getPosition();
				Ogre::Vector3 fdeltaxi = Ogre::Vector3::ZERO;
				Ogre::Quaternion qRot = Fairy::CDataManipulator::m_baseNode->getOrientation();
				//david-<<
				 if(mXax)
					 fdeltaxi = /*qRot**/(mDragDelta.x*0.1*Ogre::Vector3::UNIT_X);
				 if(mYax)
					 fdeltaxi = /*qRot**/(mDragDelta.x*0.1*Ogre::Vector3::UNIT_Y);
				 if(mZax)
					 fdeltaxi = /*qRot**/(mDragDelta.x*0.1*Ogre::Vector3::UNIT_Z);
				 //david->>

				Fairy::CDataManipulator::GetDataManipulator()->_updateCurLocatorTrans(fdeltaxi,Ogre::Quaternion::IDENTITY,true);
			}			
		}	
	}

	if(mDragRightStarted &&  e.RightIsDown())
	{
	
		mDragCurrent =Ogre::Vector2(e.GetX(), e.GetY()) ;
		mDragDelta = mDragCurrent - mDragOrigin;
		mDragOrigin = mDragCurrent;

// 		Ogre::Radian x = Ogre::Degree(mDragDelta.val[0]);
// 		Ogre::Radian y = Ogre::Degree(mDragDelta.val[1]);
// 		Fairy::CDataManipulator::m_axex->yaw(y);
// 		Fairy::CDataManipulator::m_axex->pitch(x);

		if ( Fairy::CDataManipulator::GetDataManipulator() &&(mXax || mYax || mZax) && mCanManipulateAxis)
		{			
			Ogre::Vector3 fBaseAxis = Ogre::Vector3::ZERO;
			Ogre::Quaternion fBaseRot = Fairy::CDataManipulator::m_baseNode->getOrientation();

			if(mXax)
				fBaseAxis =/* fBaseRot**/Ogre::Vector3::UNIT_X;
			if(mYax)
				fBaseAxis =/* fBaseRot**/Ogre::Vector3::UNIT_Y;
			if(mZax)
				fBaseAxis =/* fBaseRot**/Ogre::Vector3::UNIT_Z;

			//david-<<
			Ogre::Radian angle = Ogre::Degree(mDragDelta.y);
			//david->>

			Ogre::Quaternion rot(angle, fBaseAxis);			

			if(mRotFirst)
			{
				Fairy::CDataManipulator::GetDataManipulator()->_updateCurLocatorTrans(Ogre::Vector3::ZERO, rot, false);	
			}
			else
			{
				Fairy::CDataManipulator::GetDataManipulator()->_updateCurLocatorRot(rot);	
			}				
		}
	}



    if (GetActiveAction())
    {
        //GetActiveAction()->onMotion(e.GetX(), e.GetY());
		if (e.ControlDown())
		{
			GetActiveAction()->setParameter("FUNC_KEY", "CTRL");
		}
		
		if(e.AltDown())
		{
			GetActiveAction()->setParameter("FUNC_KEY", "ATL");
		}
		
		if(e.ShiftDown())
		{
			GetActiveAction()->setParameter("FUNC_KEY", "SHIFT");
		}

	}
	else
	{
        //GetSceneManipulator()->getHitIndicator("IntersectPoint")->setHitPoint(e.GetX(), e.GetY());
	}
    // 显示标准模型
    //if ( GetSceneManipulator()->getShowStandardModel() )
    //    GetSceneManipulator()->getHitIndicator("StandardModelIndicator")->setHitPoint(0.5,0.5);
    //else
    //    GetSceneManipulator()->getHitIndicator("StandardModelIndicator")->hide();

    m_CurrentMousePos.x = e.GetX();
    m_CurrentMousePos.y = e.GetY();

	Ogre::Vector3 position;
	bool hit = GetSceneManipulator()->getTerrainIntersects(m_CurrentMousePos.x, m_CurrentMousePos.y, position);

	std::pair<int, int> gridCoord = GetSceneManipulator()->getTerrainData()->getGrid(position.x, position.z);

	if (hit)
	{
		mParentFrame->SetStatusText("World Coordinate : " + Ogre::StringConverter::toString((int)(position.x)) +
			"  " + Ogre::StringConverter::toString((int)(position.y)) + "  "
			 + Ogre::StringConverter::toString((int)(position.z)), 0);
		mParentFrame->SetStatusText("Grid Coordinate : " + Ogre::StringConverter::toString(gridCoord.first) + " " +
			Ogre::StringConverter::toString(gridCoord.second), 1);
	}

}