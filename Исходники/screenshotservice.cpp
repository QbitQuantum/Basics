void ScreenshotService::getScreenshot(TasCommandModel& model, TasResponse& response)
{
    QListIterator<TasTarget*> i(model.targetList());
    QString errorMsg = PARSE_ERROR;
    QImage screenshot;
    QString pictureFormat = "PNG";
    while (i.hasNext()) {
        TasTarget* commandTarget = i.next();
        QString targetId = commandTarget->id();
        QString targetType = commandTarget->type();
        TasCommand* command = commandTarget->findCommand("Screenshot");

        // are required for command completion
        if (targetId.isEmpty() || targetType.isEmpty() || !command) {
            continue;
        }

        if (!command->parameter("format").isEmpty()) {
            pictureFormat = command->parameter("format");
        }

        if (!isFormatSupported(pictureFormat)) {
            errorMsg = "Given format " + pictureFormat + "is not supported. Supported formats are: PNG, JPEG and BMP.";
            break;
        }

        bool draw = (command->parameter("draw") == "true");

        QWidget* widget = 0;
        QQuickWindow* qtQuickWindow = 0;
        WId winId = 0;
        QRect rect(0,0,-1,-1);

        errorMsg = "Taking screenshot failed!";

        if (targetType == TYPE_GRAPHICS_VIEW) {
            //TasLogger::logger()->debug("TYPE_GRAPHICS_VIEW Target id:" + targetId);
            QGraphicsItem* item = findGraphicsItem(targetId);

            if (item) {
                QGraphicsView* view = getViewForItem(item);
                if(view) {
                    ItemLocationDetails locationDetails = TestabilityUtils::getItemLocationDetails(item);
                    rect = QRect(locationDetails.windowPoint.x(),
                                 locationDetails.windowPoint.y(),
                                 locationDetails.width,
                                 locationDetails.height);

                    if (draw) {
                        widget = view->window();
                    } else {
                        winId = view->window()->winId();
                    }
                } else {
                    errorMsg = "Could not find a GraphicsView for the GraphicsItem!";
                }
            } else {
                errorMsg = "Could not find the GraphicsItem!";
            }
        } else if (targetType == TYPE_STANDARD_VIEW) {
            //TasLogger::logger()->debug("TYPE_STANDARD_VIEW about to find widget Target id:" + targetId);
            widget = findWidget(targetId);

            if (widget) {
                if ((widget->isWindow() && !draw) || widget->inherits("QDesktopWidget")) {
                    winId = widget->winId();
                    widget = 0;
                } else if (!draw) {
                    QPoint point = widget->mapToGlobal(QPoint(0,0));
                    QPoint windowPoint = widget->window()->mapFromGlobal(point);

                    rect = QRect(windowPoint.x(),
                                 windowPoint.y(),
                                 widget->rect().width(),
                                 widget->rect().width());
                    winId = widget->window()->winId();
                    widget = 0;
                }
            } else {
                TasLogger::logger()->debug("ScreenshotService::executeService application has no visible ui!");
                errorMsg = "Application has no visible ui!";
            }
        } else if (targetType == TYPE_QSCENEGRAPH) {
            QQuickItem* item = TestabilityUtils::findQuickItem(targetId);

            if (item) {
                QPointF offset = item->mapToScene(QPointF(0,0));
                rect = QRect(-offset.x(), -offset.y(), item->width(), item->height());
                qtQuickWindow = item->window();
            }
        } else {
            //TasLogger::logger()->debug("TYPE_APPLICATION_VIEW about to find application window Target id:" + targetId);
            widget = getApplicationWidget();

            if (!widget) {
                QWindow *window = getApplicationWindow();
                //in case no window false, return the desktop
                qtQuickWindow = qobject_cast<QQuickWindow *>(window);

                if (!window) {
                    widget = qApp->desktop();
                }
            }
        }

        if (widget) {
            screenshot = widget->grab(rect).toImage();

            if (!screenshot.isNull()) {
                screenshot.setText("tas_id", objectId(widget));
            }
        } else if (qtQuickWindow) {
            screenshot = qtQuickWindow->grabWindow();
            if (!screenshot.isNull()) {
                screenshot.setText("tas_id", objectId(qtQuickWindow));
            }
        } else if (winId) {
            screenshot = QPixmap::grabWindow(winId, rect.x(), rect.y(), rect.width(), rect.height()).toImage();

            if (!screenshot.isNull()) {
                screenshot.setText("tas_id", QString::number(winId));
            }
        }

        break;
    }

    if (!screenshot.isNull()) {
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        screenshot.save(&buffer, pictureFormat.toLatin1());
        response.setData(bytes);
        buffer.close();
    } else {
        response.setErrorMessage(errorMsg);
    }

}