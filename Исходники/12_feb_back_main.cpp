int main(int argc, char *argv[])
{
    Mat frame;
    Mat back;
    Mat fore;
    VideoCapture cap(0);
	int i=0;
    BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures",3);
    bg.set("detectShadows",false);
    namedWindow("Frame");
    namedWindow("Background");
    int backgroundFrame=500;
    for(;;)
    {
        //Get the frame
        cap >> frame;
        //Update the current background model and get the foreground
    if(backgroundFrame>0)
        {bg.operator ()(frame,fore);backgroundFrame--;}
    else
        {bg.operator()(frame,fore,0);}
    //Get background image to display it
    bg.getBackgroundImage(back);
    imshow("Frame",frame);
    imshow("Background",back);
	if(waitKey(10) >= 0) break;
    }
return 0;
}