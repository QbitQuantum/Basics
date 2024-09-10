void
WMTouchPlugin::onTouch(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    BOOL bHandled = FALSE;
    UINT cInputs = LOWORD(wParam);
    PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
    if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT))){
        AC_DEBUG << "found " << cInputs << " Cursors!";
        for (UINT i=0; i < cInputs; i++){
            const TOUCHINPUT & ti = pInputs[i];
            // create a y60 event for each InputInfo
            GenericEventPtr myEvent(new GenericEvent("onWMTouch", _myEventSchemaDocument, _myEventValueFactory));
            NodePtr myNode = myEvent->getNode();

            asl::Vector2f myPosition = product(Vector2f(static_cast<float>(ti.x), static_cast<float>(ti.y)), 0.01f);
            asl::Vector2f myCalibratedRelativePosition = asl::Vector2f(0.0, 0.0);
            float myWidth = _calibrationPositionTopRight[0] - _calibrationPositionBottomLeft[0];
            float myHeight = _calibrationPositionTopRight[1] - _calibrationPositionBottomLeft[1];
            if (myWidth != 0) {
                myCalibratedRelativePosition[0] = (myPosition[0] - _calibrationPositionBottomLeft[0]) / myWidth;
            }
            if (myHeight != 0) {
                myCalibratedRelativePosition[1] = (myPosition[1] - _calibrationPositionBottomLeft[1]) / myHeight;
            }

            myNode->appendAttribute<int>("id", ti.dwID);
            myNode->appendAttribute<Vector2f>("position", myPosition);
            myNode->appendAttribute<Vector2f>("calibrated_relative_position", myCalibratedRelativePosition);
            if (ti.dwMask & TOUCHINPUTMASKF_CONTACTAREA) {
                myNode->appendAttribute<Vector2f>("contactarea", product(Vector2f(static_cast<float>(ti.cxContact), static_cast<float>(ti.cyContact)), 0.01f));
            }
            myNode->appendAttribute<bool>("inrange", (ti.dwFlags & TOUCHEVENTF_INRANGE) != 0);
            myNode->appendAttribute<bool>("primary", (ti.dwFlags & TOUCHEVENTF_PRIMARY) != 0);
            myNode->appendAttribute<bool>("nocoalesce", (ti.dwFlags & TOUCHEVENTF_NOCOALESCE) != 0);
            myNode->appendAttribute<bool>("palm", (ti.dwFlags & TOUCHEVENTF_PALM) != 0);
            // Note: we seem to be getting duplicate events, probably due to the way we are hooking the msg queue.
            // So we filter the events here. Only queue a DOWN event if the cursor wasn't down yet,
            // and only queue an UP or MOVE event if the cursor was down.
            if ((ti.dwFlags & TOUCHEVENTF_DOWN) != 0 && _downCursors.find(ti.dwID) == _downCursors.end()) {
                myNode->appendAttribute<DOMString>("type", "down");
                _queuedEvents.push_back(myEvent);
                _downCursors.insert(ti.dwID);
            } else if ((ti.dwFlags & TOUCHEVENTF_UP) != 0 && _downCursors.find(ti.dwID) != _downCursors.end()) {
                myNode->appendAttribute<DOMString>("type", "up");
                _queuedEvents.push_back(myEvent);
                _downCursors.erase(ti.dwID);
            } else if ((ti.dwFlags & TOUCHEVENTF_MOVE) != 0 && _downCursors.find(ti.dwID) != _downCursors.end()) {
                _queuedEvents.push_back(myEvent);
                myNode->appendAttribute<DOMString>("type", "move");
            }
        }            
        bHandled = TRUE;
    }else{
        /* handle the error here */
        AC_ERROR << errorDescription(lastError());
    }
    // clean up
    delete [] pInputs;

    if (bHandled){
        // if you handled the message, close the touch input handle and return
        CloseTouchInputHandle((HTOUCHINPUT)lParam);
        return;
    }
};