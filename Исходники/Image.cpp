    std::unique_ptr<Image> leastSquarePatch(const std::unique_ptr<Image>& image)
    {
        // process grayscale patches only
        if (image->getChannelNum() > 1)
            return std::unique_ptr<Image>();

        auto data_ptr = image->getValues(0);
        const auto w = image->getWidth();
        const auto h = image->getHeight();

        // least square fit to linear plane for light compensation
        float xsum_orig = 0;
        float ysum_orig = 0;
        float csum_orig = 0;
        for (size_t j = 0; j < h; j++)
        {
            for (size_t i = 0; i < w; i++)
            {
                xsum_orig += (i * data_ptr[j*w + i]);
                ysum_orig += (j * data_ptr[j*w + i]);
                csum_orig += (data_ptr[j*w + i]);
            }
        }
        Eigen::Vector3d vsum(xsum_orig, ysum_orig, csum_orig);

        float x2sum = 0, y2sum = 0, xysum = 0, xsum = 0, ysum = 0;
        float csum = w*h;
        for (size_t j = 0; j < h; j++)
        {
            for (size_t i = 0; i < w; i++)
            {
                x2sum += (i*i);
                y2sum += (j*j);
                xysum += (i*j);
                xsum += i;
                ysum += j;
            }
        }
        Eigen::Matrix3d msum;
        msum << x2sum, xysum, xsum,
             xysum, y2sum, ysum,
             xsum, ysum, csum;
        
        auto vcoeff = msum.inverse() * vsum;
        
        auto newImage = std::make_unique<Image>(w, h, 1);
        for (size_t j = 0; j < h; j++)
        {
            for (size_t i = 0; i < w; i++)
            {
                (newImage->getValues(0))[j*w + i] = data_ptr[j*w + i]
                    - i*vcoeff[0] - j*vcoeff[1] - vcoeff[2];
            }
        }
        return newImage;
    }