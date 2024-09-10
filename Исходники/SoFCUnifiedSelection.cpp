// doc from parent
void
SoFCUnifiedSelection::handleEvent(SoHandleEventAction * action)
{
    // If off then don't handle this event
    if (!selectionRole.getValue()) {
        inherited::handleEvent(action);
        return;
    }

    static char buf[513];
    HighlightModes mymode = (HighlightModes) this->highlightMode.getValue();
    const SoEvent * event = action->getEvent();

    // If we don't need to pick for locate highlighting,
    // then just behave as separator and return.
    // NOTE: we still have to pick for ON even though we don't have
    // to re-render, because the app needs to be notified as the mouse
    // goes over locate highlight nodes.
    //if (highlightMode.getValue() == OFF) {
    //    inherited::handleEvent( action );
    //    return;
    //}

    
    //
    // If this is a mouseMotion event, then check for locate highlighting
    //
    if (event->isOfType(SoLocation2Event::getClassTypeId())) {
        // NOTE: If preselection is off then we do not check for a picked point because otherwise this search may slow
        // down extremely the system on really big data sets. In this case we just check for a picked point if the data
        // set has been selected.
        if (mymode == AUTO || mymode == ON) {
            // check to see if the mouse is over our geometry...
            const SoPickedPoint * pp = this->getPickedPoint(action);
            SoFullPath *pPath = (pp != NULL) ? (SoFullPath *) pp->getPath() : NULL;
            ViewProvider *vp = 0;
            ViewProviderDocumentObject* vpd = 0;
            if (pPath && pPath->containsPath(action->getCurPath()))
                vp = viewer->getViewProviderByPathFromTail(pPath);
            if (vp && vp->isDerivedFrom(ViewProviderDocumentObject::getClassTypeId()))
                vpd = static_cast<ViewProviderDocumentObject*>(vp);

            SbBool old_state = highlighted;
            highlighted = FALSE;
            if (vpd && vpd->useNewSelectionModel() && vpd->isSelectable()) {
                std::string documentName = vpd->getObject()->getDocument()->getName();
                std::string objectName = vpd->getObject()->getNameInDocument();
                std::string subElementName = vpd->getElement(pp ? pp->getDetail() : 0);

                static char buf[513];
                snprintf(buf,512,"Preselected: %s.%s.%s (%f,%f,%f)",documentName.c_str()
                                           ,objectName.c_str()
                                           ,subElementName.c_str()
                                           ,pp->getPoint()[0]
                                           ,pp->getPoint()[1]
                                           ,pp->getPoint()[2]);

                getMainWindow()->showMessage(QString::fromAscii(buf),3000);

                if (Gui::Selection().setPreselect(documentName.c_str()
                                       ,objectName.c_str()
                                       ,subElementName.c_str()
                                       ,pp->getPoint()[0]
                                       ,pp->getPoint()[1]
                                       ,pp->getPoint()[2])){

                    SoSearchAction sa;
                    sa.setNode(vp->getRoot());
                    sa.apply(vp->getRoot());
                    if (sa.getPath()) {
                        highlighted = TRUE;
                        if (currenthighlight && currenthighlight->getTail() != sa.getPath()->getTail()) {
                            SoHighlightElementAction action;
                            action.setHighlighted(FALSE);
                            action.apply(currenthighlight);
                            currenthighlight->unref();
                            currenthighlight = 0;
                            old_state = !highlighted;
                        }

                        currenthighlight = static_cast<SoFullPath*>(sa.getPath()->copy());
                        currenthighlight->ref();
                    }
                }
            }

            if (currenthighlight/* && old_state != highlighted*/) {
                SoHighlightElementAction action;
                action.setHighlighted(highlighted);
                action.setColor(this->colorHighlight.getValue());
                action.setElement(pp ? pp->getDetail() : 0);
                action.apply(currenthighlight);
                if (!highlighted) {
                    currenthighlight->unref();
                    currenthighlight = 0;
                }
                this->touch();
            }
        }
    }
    // key press events
    else if (event->isOfType(SoKeyboardEvent ::getClassTypeId())) {
        SoKeyboardEvent  * const e = (SoKeyboardEvent  *) event;
        if (SoKeyboardEvent::isKeyPressEvent(e,SoKeyboardEvent::LEFT_SHIFT)     ||
            SoKeyboardEvent::isKeyPressEvent(e,SoKeyboardEvent::RIGHT_SHIFT)     )
            bShift = true;
        if (SoKeyboardEvent::isKeyReleaseEvent(e,SoKeyboardEvent::LEFT_SHIFT)   ||
            SoKeyboardEvent::isKeyReleaseEvent(e,SoKeyboardEvent::RIGHT_SHIFT)   )
            bShift = false;
        if (SoKeyboardEvent::isKeyPressEvent(e,SoKeyboardEvent::LEFT_CONTROL)   ||
            SoKeyboardEvent::isKeyPressEvent(e,SoKeyboardEvent::RIGHT_CONTROL)   )
            bCtrl = true;
        if (SoKeyboardEvent::isKeyReleaseEvent(e,SoKeyboardEvent::LEFT_CONTROL) ||
            SoKeyboardEvent::isKeyReleaseEvent(e,SoKeyboardEvent::RIGHT_CONTROL) )
            bCtrl = false;
    }
    // mouse press events for (de)selection
    else if (event->isOfType(SoMouseButtonEvent::getClassTypeId()) && 
             selectionMode.getValue() == SoFCUnifiedSelection::ON) {
        const SoMouseButtonEvent* e = static_cast<const SoMouseButtonEvent *>(event);
        if (SoMouseButtonEvent::isButtonReleaseEvent(e,SoMouseButtonEvent::BUTTON1)) {
            // check to see if the mouse is over a geometry...
            const SoPickedPoint * pp = this->getPickedPoint(action);
            SoFullPath *pPath = (pp != NULL) ? (SoFullPath *) pp->getPath() : NULL;
            ViewProvider *vp = 0;
            ViewProviderDocumentObject* vpd = 0;
            if (pPath && pPath->containsPath(action->getCurPath()))
                vp = viewer->getViewProviderByPathFromTail(pPath);
            if (vp && vp->isDerivedFrom(ViewProviderDocumentObject::getClassTypeId()))
                vpd = static_cast<ViewProviderDocumentObject*>(vp);
            if (vpd && vpd->useNewSelectionModel() && vpd->isSelectable()) {
                SoSelectionElementAction::Type type = SoSelectionElementAction::None;
                std::string documentName = vpd->getObject()->getDocument()->getName();
                std::string objectName = vpd->getObject()->getNameInDocument();
                std::string subElementName = vpd->getElement(pp ? pp->getDetail() : 0);
                if (bCtrl) {
                    if (Gui::Selection().isSelected(documentName.c_str()
                                         ,objectName.c_str()
                                         ,subElementName.c_str())) {
                        Gui::Selection().rmvSelection(documentName.c_str()
                                          ,objectName.c_str()
                                          ,subElementName.c_str());
                        type = SoSelectionElementAction::Remove;
                    }
                    else {
                        bool ok = Gui::Selection().addSelection(documentName.c_str()
                                          ,objectName.c_str()
                                          ,subElementName.c_str()
                                          ,pp->getPoint()[0]
                                          ,pp->getPoint()[1]
                                          ,pp->getPoint()[2]);
                        if (ok)
                            type = SoSelectionElementAction::Append;
                        if (mymode == OFF) {
                            snprintf(buf,512,"Selected: %s.%s.%s (%f,%f,%f)",documentName.c_str()
                                                       ,objectName.c_str()
                                                       ,subElementName.c_str()
                                                       ,pp->getPoint()[0]
                                                       ,pp->getPoint()[1]
                                                       ,pp->getPoint()[2]);

                            getMainWindow()->showMessage(QString::fromAscii(buf),3000);
                        }
                    }
                }
                else { // Ctrl
                    if (!Gui::Selection().isSelected(documentName.c_str()
                                         ,objectName.c_str()
                                         ,subElementName.c_str())) {
                        Gui::Selection().clearSelection(documentName.c_str());
                        bool ok = Gui::Selection().addSelection(documentName.c_str()
                                              ,objectName.c_str()
                                              ,subElementName.c_str()
                                              ,pp->getPoint()[0]
                                              ,pp->getPoint()[1]
                                              ,pp->getPoint()[2]);
                        if (ok)
                            type = SoSelectionElementAction::Append;
                    }
                    else {
                        Gui::Selection().clearSelection(documentName.c_str());
                        bool ok = Gui::Selection().addSelection(documentName.c_str()
                                              ,objectName.c_str()
                                              ,0
                                              ,pp->getPoint()[0]
                                              ,pp->getPoint()[1]
                                              ,pp->getPoint()[2]);
                        if (ok)
                            type = SoSelectionElementAction::All;
                    }

                    if (mymode == OFF) {
                        snprintf(buf,512,"Selected: %s.%s.%s (%f,%f,%f)",documentName.c_str()
                                                   ,objectName.c_str()
                                                   ,subElementName.c_str()
                                                   ,pp->getPoint()[0]
                                                   ,pp->getPoint()[1]
                                                   ,pp->getPoint()[2]);

                        getMainWindow()->showMessage(QString::fromAscii(buf),3000);
                    }
                }

                action->setHandled(); 
                if (currenthighlight) {
                    SoSelectionElementAction action(type);
                    action.setColor(this->colorSelection.getValue());
                    action.setElement(pp ? pp->getDetail() : 0);
                    action.apply(currenthighlight);
                    this->touch();
                }
            } // picked point
        } // mouse release
    }

    inherited::handleEvent(action);
}