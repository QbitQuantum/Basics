void ac::Random_FilterSubFilter(cv::Mat &frame) {
    if(subfilter == -1 || draw_strings[subfilter] == "Random_FilterSubFilter")
        return;
    cv::Mat copy1 = frame.clone(), copy2 = frame.clone();
    Random_Filter(copy1);
    CallFilter(subfilter, copy2);
    AlphaBlend(copy1, copy2, frame, 0.5);
    AddInvert(frame);
}