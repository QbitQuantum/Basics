BOOL LLViewerTextEditor::handleMouseDown(S32 x, S32 y, MASK mask)
{
	BOOL	handled = FALSE;

	// Let scrollbar have first dibs
	handled = LLView::childrenHandleMouseDown(x, y, mask) != NULL;

	// enable I Agree checkbox if the user scrolled through entire text
	BOOL was_scrolled_to_bottom = (mScrollbar->getDocPos() == mScrollbar->getDocPosMax());
	if (mOnScrollEndCallback && was_scrolled_to_bottom)
	{
		mOnScrollEndCallback(mOnScrollEndData);
	}

	if( !handled && mTakesNonScrollClicks)
	{
		if (!(mask & MASK_SHIFT))
		{
			deselect();
		}

		BOOL start_select = TRUE;
		if( allowsEmbeddedItems() )
		{
			setCursorAtLocalPos( x, y, FALSE );
			llwchar wc = 0;
			if (mCursorPos < getLength())
			{
				wc = getWChar(mCursorPos);
			}
			LLInventoryItem* item_at_pos = LLEmbeddedItems::getEmbeddedItem(wc);
			if (item_at_pos)
			{
				mDragItem = item_at_pos;
				mDragItemChar = wc;
				mDragItemSaved = LLEmbeddedItems::getEmbeddedItemSaved(wc);
				gFocusMgr.setMouseCapture( this );
				mMouseDownX = x;
				mMouseDownY = y;
				S32 screen_x;
				S32 screen_y;
				localPointToScreen(x, y, &screen_x, &screen_y );
				LLToolDragAndDrop::getInstance()->setDragStart( screen_x, screen_y );

				start_select = FALSE;
			}
			else
			{
				mDragItem = NULL;
			}
		}

		if( start_select )
		{
			// If we're not scrolling (handled by child), then we're selecting
			if (mask & MASK_SHIFT)
			{
				S32 old_cursor_pos = mCursorPos;
				setCursorAtLocalPos( x, y, TRUE );

				if (hasSelection())
				{
					/* Mac-like behavior - extend selection towards the cursor
					if (mCursorPos < mSelectionStart
						&& mCursorPos < mSelectionEnd)
					{
						// ...left of selection
						mSelectionStart = llmax(mSelectionStart, mSelectionEnd);
						mSelectionEnd = mCursorPos;
					}
					else if (mCursorPos > mSelectionStart
						&& mCursorPos > mSelectionEnd)
					{
						// ...right of selection
						mSelectionStart = llmin(mSelectionStart, mSelectionEnd);
						mSelectionEnd = mCursorPos;
					}
					else
					{
						mSelectionEnd = mCursorPos;
					}
					*/
					// Windows behavior
					mSelectionEnd = mCursorPos;
				}
				else
				{
					mSelectionStart = old_cursor_pos;
					mSelectionEnd = mCursorPos;
				}
				// assume we're starting a drag select
				mIsSelecting = TRUE;

			}
			else
			{
				setCursorAtLocalPos( x, y, TRUE );
				startSelection();
			}
			gFocusMgr.setMouseCapture( this );
		}

		handled = TRUE;
	}

	if (hasTabStop())
	{
		setFocus(TRUE);
		handled = TRUE;
	}

	// Delay cursor flashing
	resetKeystrokeTimer();

	return handled;
}