void PPTLoaderTest::test2()
{
    PPTLoader *ppt = new PPTLoader();
    ppt->openFile("c:/test2.ppt");
    qDebug() << "Num Slides #2: "<<ppt->numSlides();
    delete ppt;
}