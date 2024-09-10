void TrackFace::on_recognition_clicked()
{
    TrackFace::capture.open(0);
    string windowName="Track Face";
    cv::namedWindow(windowName.c_str(), cv::WINDOW_AUTOSIZE);
    moveWindow(windowName.c_str(), window_x, window_y);
    setMouseCallback(windowName.c_str(), trackFaceCallBack, NULL);

    while (true)
    {
        cv::Mat frame, buffer;
        if (!capture.isOpened()) break;

        capture >> buffer;
        cv::resize(buffer, frame,Size(buffer.cols/2,buffer.rows/2),0,0,INTER_LINEAR);

        vector<Rect_<int> > faces=haar_faces(frame);

        for (size_t i=0;i<faces.size();i++)
        {
            cv::Mat face_resized=resizeRecognitionFace(frame, faces[i]);

            int prediction=model->predict(face_resized);

            double confidence=0.0;
            model->predict(face_resized, prediction, confidence);

            cout << confidence << endl;

            string box_text="";
            if (confidence<=2400)
                box_text="Prediction is family";
            else box_text="Prediction is stranger";

            //string box_text=format("Prediction is %s", names[prediction].c_str());

            drawFace(frame, faces[i], box_text);
        }

        putText(frame, "Recognizing Face", Point(frame.cols/2-100, 30), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(0,0,255),2.0);

        cv::imshow(windowName.c_str(), frame);
        while (cv::waitKey(5)==27)
        {
            capture.release();
            cv::destroyWindow(windowName.c_str());
        }
    }
}