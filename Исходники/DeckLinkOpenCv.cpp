bool deckLinkVideoFrameToCvMat(ComPtr<IDeckLinkVideoInputFrame> in,
                               cv::Mat &out) {
    BOOST_LOG_TRIVIAL(info) << "Printing out input: " << in << std::endl;


    switch (in->GetPixelFormat()) {
        case bmdFormat8BitYUV: {
            void *data;

            bool stat = FAILED(in->GetBytes(&data));

            if (FAILED(in->GetBytes(&data)))
                return false;

            cv::Mat mat = cv::Mat(in->GetHeight(), in->GetWidth(), CV_8UC2, data,
                                  in->GetRowBytes());

            cv::cvtColor(mat, out, CV_YUV2BGR_UYVY);
            

            BOOST_LOG_TRIVIAL(info) << "Prining out channels: " << mat.channels() << std::endl;

            return true;
        }
        case bmdFormat8BitBGRA: {
            void *data;
            if (FAILED(in->GetBytes(&data)))
                return false;

            cv::Mat mat = cv::Mat(in->GetHeight(), in->GetWidth(), CV_8UC4, data);
            cv::cvtColor(mat, out, CV_BGRA2BGR);
            return true;
        }
        default: {
            ComPtr<IDeckLinkVideoConversion> deckLinkVideoConversion =
                    CreateVideoConversionInstance();
            if (!deckLinkVideoConversion)
                return false;

            CvMatDeckLinkVideoFrame cvMatWrapper(in->GetHeight(), in->GetWidth());
            if (FAILED(deckLinkVideoConversion->ConvertFrame(in.get(), &cvMatWrapper)))
                return false;
            cv::cvtColor(cvMatWrapper.mat, out, CV_BGRA2BGR);
            return true;
        }
    }
}