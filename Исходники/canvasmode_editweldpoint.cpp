void CanvasMode_EditWeldPoint::keyPressEvent(QKeyEvent *e)
{
	if (m_selectedPoint < 0)
		return;
	int kk = e->key();
	if (m_keyRepeat)
		return;
	m_keyRepeat = true;
	e->accept();

	if (e->key() == Qt::Key_Escape)
	{
		// Go back to normal mode.
		m_view->requestMode(modeNormal);
		return;
	}

	Qt::KeyboardModifiers buttonModifiers = e->modifiers();
	if ((!m_view->m_ScMW->zoomSpinBox->hasFocus()) && (!m_view->m_ScMW->pageSelector->hasFocus()))
	{
		if (m_doc->m_Selection->count() != 0)
		{
			double moveBy = 1.0;
			double moveX = 0.0;
			double moveY = 0.0;
			bool isMoving = false;
			bool doUpdate = false;
			if (m_doc->unitIndex()!=SC_INCHES)
			{
				if ((buttonModifiers & Qt::ShiftModifier) && !(buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=0.1;
				else if (!(buttonModifiers & Qt::ShiftModifier) && (buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=10.0;
				else if ((buttonModifiers & Qt::ShiftModifier) && (buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=0.01;
				moveBy/=m_doc->unitRatio();//Lets allow movement by the current doc ratio, not only points
			}
			else
			{
				if ((buttonModifiers & Qt::ShiftModifier) && !(buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=0.1/m_doc->unitRatio();
				else if (!(buttonModifiers & Qt::ShiftModifier) && (buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=1.0/m_doc->unitRatio();
				else if ((buttonModifiers & Qt::ShiftModifier) && (buttonModifiers & Qt::ControlModifier) && !(buttonModifiers & Qt::AltModifier))
					moveBy=0.01/m_doc->unitRatio();
			}
			moveBy /= m_canvas->m_viewMode.scale;
			PageItem *currItem = m_doc->m_Selection->itemAt(0);
			switch (kk)
			{
				case Qt::Key_7:
					moveX = -moveBy;
					moveY = -moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_9:
					moveX = moveBy;
					moveY = -moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_3:
					moveX = moveBy;
					moveY = moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_1:
					moveX = -moveBy;
					moveY = moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_Left:
				case Qt::Key_4:
					moveX = -moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_Right:
				case Qt::Key_6:
					moveX = moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_Up:
				case Qt::Key_8:
					moveY = -moveBy;
					isMoving = true;
					doUpdate = true;
					break;
				case Qt::Key_Down:
				case Qt::Key_2:
					moveY = moveBy;
					isMoving = true;
					doUpdate = true;
					break;
			}
			if (isMoving)
			{
				if (m_editWeldMode)
				{
					currItem->weldList[m_selectedPoint].weldPoint += FPoint(moveX, moveY);
				}
				else
				{
					currItem->setXYPos(currItem->xPos() + moveX, currItem->yPos() + moveY, true);
					currItem->setRedrawBounding();
					currItem->OwnPage = m_doc->OnPage(currItem);
				}
			}
			if (doUpdate)
			{
				currItem->update();
				m_doc->regionsChanged()->update(getUpdateRect());
			}
		}
	}
	m_keyRepeat = false;
}