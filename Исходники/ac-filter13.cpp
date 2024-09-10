void ac::ShuffleAlphaSubFilter(cv::Mat &frame) {
    if(subfilter == -1 || ac::draw_strings[subfilter] == "ShuffleAlphaSubFilter")
        return;
    cv::Mat copyf = frame.clone(), copyi = frame.clone();
    ShuffleAlpha(copyf);
    CallFilter(subfilter, copyi);
    AlphaBlend(copyf, copyi, frame, 0.5);
    AddInvert(frame);
}