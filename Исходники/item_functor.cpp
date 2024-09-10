/**
 *	Update method
 */
void MatrixMover::update( float dTime, Tool& tool )
{
	// see if we want to commit this action
	if (!InputDevices::isKeyDown( KeyEvent::KEY_LEFTMOUSE ) ||
		snapMode_ != SnapProvider::instance()->snapMode() )
	{
		std::vector<GenPositionProperty*> props = CurrentPositionProperties::properties();

		bool addUndoBarrier = (props.size() > 1) || (undoName_ != "");

		bool success = true;
		for (std::vector<GenPositionProperty*>::iterator i = props.begin(); i != props.end(); ++i)
		{
			MatrixProxyPtr pMatrix = (*i)->pMatrix();
			if (pMatrix->hasChanged())
			{
				// set its transform permanently
				if ( !pMatrix->commitState( false, !addUndoBarrier ) )
				{
					success = false;
				}
			}
			else
			{
				pMatrix->commitState( true );
			}
		}

		if (addUndoBarrier)
		{
			if (undoName_ != "")
				UndoRedo::instance().barrier( undoName_, false );
			else
				UndoRedo::instance().barrier( "Move group", true );

			if ( !success )
			{
				UndoRedo::instance().undo();
			}
		}

		// and this tool's job is over
		ToolManager::instance().popTool();
		return;
	}

	// figure out movement
	if (tool.locator())
	{
		std::vector<GenPositionProperty*> props = CurrentPositionProperties::properties();

		Vector3 locatorPos = tool.locator()->transform().applyToOrigin();

		if (!gotInitialLocatorPos_)
		{
			lastLocatorPos_ = tool.locator()->transform().applyToOrigin();
			gotInitialLocatorPos_ = true;

			if (props.size() == 1)
			{
				Vector3 objPos = props[0]->pMatrix()->get().applyToOrigin();
				Vector3 clipPos = Moo::rc().viewProjection().applyPoint( objPos );
				clipPos.x = ( clipPos.x + 1 ) / 2 * Moo::rc().screenWidth();
				clipPos.y = ( 1 - clipPos.y ) / 2 * Moo::rc().screenHeight();

				POINT pt;
				pt.x = LONG( clipPos.x );
				pt.y = LONG( clipPos.y );
				::ClientToScreen( Moo::rc().windowHandle(), &pt );
				::SetCursorPos( pt.x, pt.y );

				if (Moo::rc().device()) 
				{
					Moo::rc().device()->SetCursorPosition( pt.x, pt.y, 0 );
				}

				lastLocatorPos_ = locatorPos = objPos;
			}
		}

		totalLocatorOffset_ += locatorPos - lastLocatorPos_;
		lastLocatorPos_ = locatorPos;


		for (std::vector<GenPositionProperty*>::iterator i = props.begin(); i != props.end(); ++i)
		{
			MatrixProxyPtr pMatrix = (*i)->pMatrix();

			Matrix oldMatrix;
			pMatrix->getMatrix( oldMatrix );

			// reset the last change we made
			pMatrix->commitState( true );

			Matrix m;
			pMatrix->getMatrix( m );

			Vector3 delta = totalLocatorOffset_;

			if( snap_ )
				SnapProvider::instance()->snapPositionDelta( delta );

			Vector3 newPos = m.applyToOrigin() + delta;

            bool snapPosOK = true;
			if( snap_ )
				snapPosOK = SnapProvider::instance()->snapPosition( newPos );

            if( rotate_ && snapPosOK )
			{
				Vector3 normalOfSnap = SnapProvider::instance()->snapNormal( newPos );
				Vector3 yAxis( 0, 1, 0 );
				yAxis = m.applyVector( yAxis );

				Vector3 binormal = yAxis.crossProduct( normalOfSnap );

				normalOfSnap.normalise();
				yAxis.normalise();
				binormal.normalise();

				float angle = acosf( Math::clamp(-1.0f, yAxis.dotProduct( normalOfSnap ), +1.0f) );

				Quaternion q( binormal.x * sinf( angle / 2.f ),
					binormal.y * sinf( angle / 2.f ),
					binormal.z * sinf( angle / 2.f ),
					cosf( angle / 2.f ) );

				q.normalise();

				Matrix rotation;
				rotation.setRotate( q );

				m.postMultiply( rotation );
			}

            if (snapPosOK)
            {
			    m.translation( newPos );

			    Matrix worldToLocal;
			    pMatrix->getMatrixContextInverse( worldToLocal );

			    m.postMultiply( worldToLocal );

			    pMatrix->setMatrix( m );
            }
            else
            {
                // snapping the position failed, revert back to the previous
                // good matrix:
			    Matrix worldToLocal;
			    pMatrix->getMatrixContextInverse( worldToLocal );
			    oldMatrix.postMultiply( worldToLocal );
                pMatrix->setMatrix( oldMatrix );
            }
		}

	}
}