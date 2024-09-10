void EstimateResolutionDiffraction::estimateDetectorResolution() {
    Instrument_const_sptr instrument = m_inputWS->getInstrument();
    V3D samplepos = instrument->getSample()->getPos();

    size_t numspec = m_inputWS->getNumberHistograms();

    double mintwotheta = 10000;
    double maxtwotheta = 0;

    double mint3 = 1;
    double maxt3 = 0;

    size_t count_nodetsize = 0;

    for (size_t i = 0; i < numspec; ++i) {
        // Get detector
        IDetector_const_sptr det = m_inputWS->getDetector(i);

        double detdim;

        boost::shared_ptr<const Detector> realdet =
            boost::dynamic_pointer_cast<const Detector>(det);
        if (realdet) {
            double dy = realdet->getHeight();
            double dx = realdet->getWidth();
            detdim = sqrt(dx * dx + dy * dy) * 0.5;
        } else {
            // Use detector dimension as 0 as no-information
            detdim = 0;
            ++count_nodetsize;
        }

        // Get the distance from detector to source
        V3D detpos = det->getPos();
        double l2 = detpos.distance(samplepos);
        if (l2 < 0)
            throw runtime_error("L2 is negative");

        // Calculate T
        double centraltof = (m_L1 + l2) / m_centreVelocity;

        // Angle
        double twotheta = m_inputWS->detectorTwoTheta(det);
        double theta = 0.5 * twotheta;

        // double solidangle = m_solidangleWS->readY(i)[0];
        double solidangle = det->solidAngle(samplepos);
        double deltatheta = sqrt(solidangle);

        // Resolution
        double t1 = m_deltaT / centraltof;
        double t2 = detdim / (m_L1 + l2);
        double t3 = deltatheta * (cos(theta) / sin(theta));

        double resolution = sqrt(t1 * t1 + t2 * t2 + t3 * t3);

        m_outputWS->dataX(i)[0] = static_cast<double>(i);
        m_outputWS->dataY(i)[0] = resolution;

        if (twotheta > maxtwotheta)
            maxtwotheta = twotheta;
        else if (twotheta < mintwotheta)
            mintwotheta = twotheta;

        if (fabs(t3) < mint3)
            mint3 = fabs(t3);
        else if (fabs(t3) > maxt3)
            maxt3 = fabs(t3);

        g_log.debug() << det->type() << " " << i << "\t\t" << twotheta
                      << "\t\tdT/T = " << t1 * t1 << "\t\tdL/L = " << t2
                      << "\t\tdTheta*cotTheta = " << t3 << "\n";
    }

    g_log.notice() << "2theta range: " << mintwotheta << ", " << maxtwotheta
                   << "\n";
    g_log.notice() << "t3 range: " << mint3 << ", " << maxt3 << "\n";
    g_log.notice() << "Number of detector having NO size information = "
                   << count_nodetsize << "\n";

    return;
}