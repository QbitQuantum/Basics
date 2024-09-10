void IKRRTWindow::saveScreenshot()
{
    static int counter = 0;
    SbString framefile;

    framefile.sprintf("renderFrame_%06d.png", counter);
    counter++;
    redraw();
    viewer->getSceneManager()->render();
    viewer->getSceneManager()->scheduleRedraw();
    QGLWidget* w = (QGLWidget*)viewer->getGLWidget();

    QImage i = w->grabFrameBuffer();
    bool bRes = i.save(framefile.getString(), "BMP");

    if (bRes)
    {
        cout << "wrote image " << counter << endl;
    }
    else
    {
        cout << "failed writing image " << counter << endl;
    }

}