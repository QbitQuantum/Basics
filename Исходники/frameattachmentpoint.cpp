bool FrameAttachmentPoint::attach(AttachableFrame* frame)
{
    QLayout* layout;
    QWidget* attWidget;
    QFrame* attFrame;
    QDockWidget* attDockWidget;
    QTabWidget* attTabWidget;
    QMainWindow* attMainWindow;
    int index = 0;

    if ((int)mAttachedFrames.size() >= mMaxAttachmentCount)
    {
        LOG_ERROR() << "FrameAttachmentPoint::attach(): cannot attach more than " << mMaxAttachmentCount <<
                       " Frame" << (mMaxAttachmentCount > 1 ? "s" : "") << " to Attachment Point " << mName << ".";
       return false;
    }

    //Attach the frame in a way depending on its type
    switch (mType)
    {
    case ATTACHMENT_NONE:
         LOG_ERROR() << "FrameAttachmentPoint::attach(): cannot attach to illegal Attachment Point.";
         return false;
        break;
    case ATTACHMENT_WIDGET:
        //Attach to Widget with adding a new layout
        layout = WindowManager::createNeutralLayout();
        layout->addWidget(&*frame);
        frame->show();
        attWidget = (dynamic_cast<QWidget*>(mAttachmentPoint));
        attWidget->setLayout(layout);
        attWidget->show();
        break;
    case ATTACHMENT_FRAME:
        //Attach to Frame with adding a new layout
        layout = WindowManager::createNeutralLayout();
        layout->addWidget(&*frame);
        frame->show();
        attFrame = (dynamic_cast<QFrame*>(mAttachmentPoint));
        attFrame->setLayout(layout);
        attFrame->show();
        break;
    case ATTACHMENT_TABWIDGET:
        //Attach to TabWidget with adding a new page and (automatically) a layout
        attTabWidget = (dynamic_cast<QTabWidget*>(mAttachmentPoint));
        index = attTabWidget->addTab(&*frame, frame->getCaption());
        WindowManager::changeToNeutralLayout(attTabWidget->widget(index)->layout());
        break;
    case ATTACHMENT_DOCKWIDGET:
        //Attach to DockWidget with adding a new layout
        layout = WindowManager::createNeutralLayout();
        layout->addWidget(&*frame);
        frame->show();
        attDockWidget = (dynamic_cast<QDockWidget*>(mAttachmentPoint));
        attDockWidget->setLayout(layout);
        attDockWidget->show();
        break;
    case ATTACHMENT_MAINWINDOW:
        //Attach to MainWindow with adding a new layout
        layout = WindowManager::createNeutralLayout();
        layout->addWidget(&*frame);
        frame->show();
        attMainWindow = (dynamic_cast<QMainWindow*>(mAttachmentPoint));
        attMainWindow->setLayout(layout);
        attMainWindow->show();
        break;
    default:
         LOG_ERROR() << "FrameAttachmentPoint::attach(): unknown Attachment Point.";
        return false;
        break;
    }

    //Store the attachment pointer
    mAttachedFrames.insert(frame->getPluginId(), frame);

    return true;
}