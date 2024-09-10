QVector<EcgStDescriptor> EcgStAnalyzer::analyze(const EcgStData &data, double sampleFreq)
{
    QVector<EcgStDescriptor> result;

    int num = data.rData.size();
    int snum = data.ecgSamples.size();

    if (num < 2 || snum == 0)
        return result;

    int p = smoothSize;
    int w = detectionSize;
    double lamdba = morphologyCoeff;

    QVector<int> stOn(num);
    QVector<int> stEnd(num);

    int i;

    // detect STend points
    for (i = 0; i < num; i++)
    {
        double ka = data.jData[i];
        double kb = data.tEndData[i];

        QVector<double> aVal(kb - ka + 1);

        for (int k = ka; k <= kb; k++)
        {
            int ke = std::max(1, std::min(k + p, snum));
            int nsr = ke - k + p + 1;
            QVector<double> wnd = data.ecgSamples.mid(k - p - 1, nsr);
            double sk = EcgUtils::sum(wnd) / nsr;
            ke = std::max(1, std::min(k + w - 1, snum));

            QVector<double> sqr(ke - k);
            for (int j = 0; j < sqr.size(); j++) {
                double smp = data.ecgSamples[k + j - 1] - sk;

                if (algorithm == ST_QUADRATIC)
                    sqr[j] = smp * smp;
                else
                    sqr[j] = smp;
            }

            aVal[k - ka] = EcgUtils::sum(sqr);
        }

        int kp, kp1, kp2;
        double ap1 = EcgUtils::max(aVal, &kp1);
        double ap2 = EcgUtils::min(aVal, &kp2);

        double at = fabs(ap1) / fabs(ap2);
        if ((1.0 / lamdba < at) && (at < lamdba))
            kp = std::min(kp1, kp2);
        else
            kp = fabs(ap1) > fabs(ap2) ? kp1 : kp2;

        stEnd[i] = ka + kp;
    }

    // calculate heart rate
    QVector<int> rr = EcgUtils::diff(data.rData);
    QVector<double> hr(num);
    for (i = 0; i < num - 1; i++)
        hr[i] = 60.0 / ((double) rr[i] / sampleFreq);
    hr[num - 1] = hr[num - 2];

    for (i = 0; i < num; i++)
    {
        double rt = stEnd[i] - data.rData[i];

        double x;
        double hrc = hr[i];
        if (hrc < 100)
            x = 0.4;
        else if (hrc < 110)
            x = 0.45;
        else if (hrc < 120)
            x = 0.5;
        else
            x = 0.55;

        int test = (int) round((double) data.rData[i] + x * rt);
        stOn[i] = std::min(data.jData[i] + 1, test);
    }

    // create and classify interval descriptors
    for (i = 0; i < num; i++)
    {
        EcgStDescriptor desc;

        desc.STOn = stOn[i];
        desc.STEnd = stEnd[i];
        desc.STMid = desc.STOn + (int) round((desc.STEnd - desc.STOn) / 2.0);

        desc.offset = data.ecgSamples[desc.STMid];

        int x1 = desc.STOn;
        int x2 = desc.STMid;
        double y1 = data.ecgSamples[x1];
        double y2 = desc.offset;
        double d1 = (y1 - y2) / ((x1 - x2) / sampleFreq);
        desc.slope1 = RAD_TO_DEG(atan(d1));

        x1 = desc.STMid;
        x2 = desc.STEnd;
        y1 = desc.offset;
        y2 = data.ecgSamples[x2];
        double d2 = (y1 - y2) / ((x1 - x2) / sampleFreq);
        desc.slope2 = RAD_TO_DEG(atan(d2));

        classifyInterval(desc);

        result.push_back(desc);
    }

    return result;
}