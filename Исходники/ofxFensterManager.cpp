bool ofxFensterManager::processEvent(GHOST_IEvent* event)
{
	if(event->getType()==GHOST_kEventUnknown)
		return false;
	
	GHOST_IWindow* window = event->getWindow();
	bool handled = true;
	
	ofxFenster* win=getFensterByHandler(window);
	
	GHOST_Rect winPos; //why on every process...?
	window->getWindowBounds(winPos);
	
	switch (event->getType())
	{
			//////////////////// MOUSE
        case GHOST_kEventCursorMove:
        {
            GHOST_TEventCursorData* bd=(GHOST_TEventCursorData*)event->getData();
			GHOST_TInt32 x,y;
			window->screenToClient(bd->x, bd->y, x, y);
			
			ofPoint p(x, y);
			p.y -= 1;
			
            if(win->isButtonDown) {
                //win->mouseDragged(bd->x-winPos.m_l, bd->y-winPos.m_t, win->buttonDown);
                win->mouseDragged(p.x, p.y, win->buttonDown);
            } else {
                //win->mouseMoved(bd->x-winPos.m_l, bd->y-winPos.m_t);
                win->mouseMoved(p.x, p.y);
            }
            break;
        }
        case GHOST_kEventWheel:
        {
            break;
        }
        case GHOST_kEventButtonDown:
        {
            GHOST_TEventButtonData* bd=(GHOST_TEventButtonData*)event->getData();
            win->isButtonDown=true;
            win->buttonDown=bd->button;
            win->mousePressed(bd->button);
            break;
        }
        case GHOST_kEventButtonUp:
        {
            GHOST_TEventButtonData* bd=(GHOST_TEventButtonData*)event->getData();
            win->isButtonDown=false;
            win->mouseReleased(bd->button);
            break;
        }
			////////////////// KEYBOARD
        case GHOST_kEventKeyUp:
        {
            int key=handleKeyData((GHOST_TEventKeyData*) event->getData());
            if(key==OF_KEY_ESC)
                break;
            win->keyReleased(key);
            break;
        }
        case GHOST_kEventKeyDown:
        {
            int key=handleKeyData((GHOST_TEventKeyData*) event->getData());
            if(key==OF_KEY_ESC)
                ofExit(0);
            win->keyPressed(key);
            break;
        }
			////////////////// WINDOW
        case GHOST_kEventWindowSize:
        {
            GHOST_Rect rect;
            window->getClientBounds(rect);
            win->windowResized(rect.getWidth(), rect.getHeight());
            break;
        }
        case GHOST_kEventWindowMove:
        {
            GHOST_Rect rect;
            window->getWindowBounds(rect);
			//cout << rect.m_t << endl;
			//GHOST_TInt32 x,y;
			//window->screenToClient(rect.m_l, rect.m_t, x, y);
            win->windowMoved(rect.m_l, rect.m_t);
			
            break;
        }
        case GHOST_kEventWindowUpdate:
        {
            win->draw();
			window->swapBuffers();
            break;
        }
        case GHOST_kEventWindowActivate:
        {
            break;
        }
        case GHOST_kEventWindowDeactivate:
        {
            break;
        }
        case GHOST_kEventWindowClose:
        {
            deleteFenster(win);
            break;
        }
		//drag and drop
		case GHOST_kEventDraggingEntered:
		{
			GHOST_TEventDragnDropData* dragnDropData = (GHOST_TEventDragnDropData*)((GHOST_IEvent*)event)->getData();
			//needs to be handled, but of doesn't really provide anything out of the box
			break;
		}
		case GHOST_kEventDraggingUpdated:
		{
			GHOST_TEventDragnDropData* dragnDropData = (GHOST_TEventDragnDropData*)((GHOST_IEvent*)event)->getData();
			//needs to be handled, but of doesn't really provide anything out of the box
			break;
		}
		case GHOST_kEventDraggingExited:
		{
			GHOST_TEventDragnDropData* dragnDropData = (GHOST_TEventDragnDropData*)((GHOST_IEvent*)event)->getData();
			//needs to be handled, but of doesn't really provide anything out of the box
			break;
		}
		case GHOST_kEventDraggingDropDone:
		{
			GHOST_TEventDragnDropData* dragnDropData = (GHOST_TEventDragnDropData*)((GHOST_IEvent*)event)->getData();
			if(dragnDropData->dataType == GHOST_kDragnDropTypeFilenames){//TODO: STRING AND BITMAP IS ALSO SUPPORTED IN GHOST
				static ofDragInfo info;
				GHOST_TStringArray *strArray = (GHOST_TStringArray*)dragnDropData->data;
				for (int i=0;i<strArray->count;i++){
					const char* filename = (char*)strArray->strings[i];
					info.files.push_back(filename);
				}
				info.position.set(dragnDropData->x, dragnDropData->y); //TODO check if drag'n'drop position is actually correct
				win->fileDropped(info);
			}
			break;
		}
	}
	return handled;
}