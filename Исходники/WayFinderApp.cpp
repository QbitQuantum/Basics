void WayFinderApp::update()
{
    if(getElapsedFrames() % FRAME_COUNT_THRESHOLD == 0) {
        detected = false;

        // TODO: Consider converting capture to grayscale or blurring then thresholding to improve performance.
        if(capture && capture->checkNewFrame()) {
            frame = toOcv(capture->getSurface());
            //cv::Mat frameGray, frameBlurred, frameThresh, foreGray, backGray;
            //cvtColor(frame, frameGray, CV_BGR2GRAY);
            int blurAmount = 10;
            //cv::blur(frame, frameBlurred, cv::Size(blurAmount, blurAmount));
            //threshold(frameBlurred, frameThresh, 100, 255, CV_THRESH_BINARY);

            // Get all contours.
            //bg.operator()(frameThresh,fore);
            bg.operator()(frame, fore);
            bg.getBackgroundImage(back);
            cv::erode(fore, fore, cv::Mat());
            cv::dilate(fore, fore, cv::Mat());
            cv::findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

            // Get largest contour: http://stackoverflow.com/questions/15012073/opencv-draw-draw-contours-of-2-largest-objects
            unsigned largestIndex = 0;
            unsigned largestContour = 0;
            for(unsigned i = 0; i < contours.size(); i++) {
                if(contours[i].size() > largestContour) {
                    largestContour = contours[i].size();
                    largestIndex = i;
                }
            }

            vector<std::vector<cv::Point>> hack;
            cv::Rect rect;
            cv::Point center;

            if(contours.size() > 0) {
                hack.push_back(contours[largestIndex]);

                // Find bounding rectangle for largest countour.
                rect = boundingRect(contours[largestIndex]);

                // Make sure the blog is large enough to be a track-worthy.
                println("Rext area = " + boost::lexical_cast<std::string>(rect.area()));
                if(rect.area() >= 5000) { // TODO: Tweak this value.
                    // Get center of rectangle.
                    center = cv::Point(
                                 rect.x + (rect.width / 2),
                                 rect.y + (rect.height / 2)
                             );

                    // Show guide.
                    spotlightCenter2D.x = (float)center.x;
                    spotlightCenter2D.y = (float)center.y;
                    spotlightCenter3D.x = (float)center.x;
                    spotlightCenter3D.y = (float)center.y;
                    //spotlightRadius = (rect.width + rect.y) / 2;
                    detected = true;
                }
            }

            // When debug mode is off, the background should be black.
            if(debugView) {
                if(contours.size() > 0) {
                    cv::drawContours(frame, contours, -1, cv::Scalar(0, 0, 255), 2);
                    cv::drawContours(frame, hack, -1, cv::Scalar(255, 0, 0), 2);
                    rectangle(frame, rect, cv::Scalar(0, 255, 0), 3);
                    circle(frame, center, 10, cv::Scalar(0, 255, 0), 3);
                }
                mTexture = gl::Texture(fromOcv(frame));
            }
        }

        // TODO: Create control panel for all inputs.
    }
}