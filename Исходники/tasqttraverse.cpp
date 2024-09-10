/*!
  Traverse QObject based items.
*/
void TasQtTraverse::traverseObject(TasObject* objectInfo, QObject* object, TasCommand* command)
{
     // Embedded apps must use coordinates for operations, as the parent has no knowledge of the
    // Actual items
    bool embeddedApp = false;
    if (command && command->parameter("embedded") == "true") {
        embeddedApp = true;
    }
    //TasLogger::logger()->debug("TasQtTraverse::traverseObject in");
    mTraverseUtils->addObjectDetails(objectInfo, object);
    QGraphicsObject* graphicsObject = qobject_cast<QGraphicsObject*>(object);
    if(graphicsObject){
        objectInfo->addAttribute("objectType", embeddedApp? TYPE_WEB : TYPE_GRAPHICS_VIEW);
        mTraverseUtils->addGraphicsItemCoordinates(objectInfo, graphicsObject, command);
        mTraverseUtils->printGraphicsItemProperties(objectInfo, graphicsObject);

        //add details only for graphicsitems
        QGraphicsWidget* graphicsWidget = qobject_cast<QGraphicsWidget*>(object);
        if(graphicsWidget){
            mTraverseUtils->addFont(objectInfo, graphicsWidget->font());
            // Elided format "this is a text" -> "this is a..." text for
            // items that have the "text" property.
            QVariant text = graphicsWidget->property("text");
            if (text.isValid()) {
                mTraverseUtils->addTextInfo(objectInfo, text.toString(), graphicsWidget->font(), graphicsWidget->size().width());

            }
            QVariant plainText = graphicsWidget->property("plainText");
            if (plainText.isValid()) {
                mTraverseUtils->addTextInfo(objectInfo, plainText.toString(), graphicsWidget->font(), graphicsWidget->size().width());
            }
        }
    }
    else{
        QQuickItem* quickObject = qobject_cast<QQuickItem*>(object);

        if (quickObject) {
            objectInfo->addAttribute("objectType", TYPE_QSCENEGRAPH );
        }
        //make sure that we are dealing with a widget
        else if (object->isWidgetType()){
            QWidget* widget = qobject_cast<QWidget*>(object);
            objectInfo->addAttribute("objectType", TYPE_STANDARD_VIEW );

            addWidgetCoordinates(objectInfo, widget,command);
            mTraverseUtils->addFont(objectInfo, widget->font());
            //check is the widget a viewport to graphicsscene
            QWidget* parentWidget = widget->parentWidget();
            bool isViewPort = false;
            if(parentWidget && parentWidget->inherits("QGraphicsView")){
                QGraphicsView* view = qobject_cast<QGraphicsView*>(parentWidget);
                if(view->viewport() == widget){
                    isViewPort = true;
                }
            }
            //add transformation details
            QGraphicsView* graphicsView = qobject_cast<QGraphicsView*>(object);
            if(graphicsView){
                objectInfo->addBooleanAttribute("isTransformed", graphicsView->isTransformed());
                if(graphicsView->isTransformed()){
                    QTransform tr = graphicsView->transform();
                    objectInfo->addAttribute("transformM11",tr.m11());
                    objectInfo->addAttribute("transformM12",tr.m12());
                    objectInfo->addAttribute("transformM13",tr.m13());
                    objectInfo->addAttribute("transformM21",tr.m21());
                    objectInfo->addAttribute("transformM22",tr.m22());
                    objectInfo->addAttribute("transformM23",tr.m23());
                    objectInfo->addAttribute("transformM31",tr.m31());
                    objectInfo->addAttribute("transformM32",tr.m32());
                    objectInfo->addAttribute("transformM33",tr.m33());
                }
            }
            objectInfo->addBooleanAttribute("isViewPort", isViewPort);
// Add special window id attribute into qwidget atttributes
#if defined(Q_WS_X11)
            unsigned long wid = static_cast<unsigned long>(widget->effectiveWinId());
            objectInfo->addAttribute("xWindow", (int)wid); // can this fail due to precision?
#endif


        } else if(object->isWindowType()) {
            objectInfo->addAttribute("objectType", TYPE_WINDOW_VIEW);
        } else {
            if(object != qApp){
                objectInfo->addAttribute("objectType", embeddedApp? TYPE_WEB : TYPE_STANDARD_VIEW );
            }
        }

    }
}