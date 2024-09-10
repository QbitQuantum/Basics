    SoccerPitchData(const Size &size) {
        pitchPoints.push_back(Point2f(0, 0));
        pitchPoints.push_back(Point2f(13.85, 0));
        pitchPoints.push_back(Point2f(24.85, 0));
        pitchPoints.push_back(Point2f(43.15, 0));
        pitchPoints.push_back(Point2f(54.15, 0));
        pitchPoints.push_back(Point2f(68, 0));

        pitchPoints.push_back(Point2f(24.85, 5.5));
        pitchPoints.push_back(Point2f(43.15, 5.5));

        pitchPoints.push_back(Point2f(13.85, 16.5));
        pitchPoints.push_back(Point2f(26.69, 16.5));
        pitchPoints.push_back(Point2f(41.31, 16.5));
        pitchPoints.push_back(Point2f(54.15, 16.5));

        pitchPoints.push_back(Point2f(0, 52.5));
        pitchPoints.push_back(Point2f(24.85, 52.5));
        pitchPoints.push_back(Point2f(43.15, 52.5));
        pitchPoints.push_back(Point2f(68, 52.5));

        pitchPoints.push_back(Point2f(13.85, 88.5));
        pitchPoints.push_back(Point2f(26.69, 88.5));
        pitchPoints.push_back(Point2f(41.31, 88.5));
        pitchPoints.push_back(Point2f(54.15, 88.5));

        pitchPoints.push_back(Point2f(24.85, 99.5));
        pitchPoints.push_back(Point2f(43.15, 99.5));

        pitchPoints.push_back(Point2f(0, 105));
        pitchPoints.push_back(Point2f(13.85, 105));
        pitchPoints.push_back(Point2f(24.85, 105));
        pitchPoints.push_back(Point2f(43.15, 105));
        pitchPoints.push_back(Point2f(54.15, 105));
        pitchPoints.push_back(Point2f(68, 105));

        pitchOuterPoints.push_back(Point2f(0, 0));
        pitchOuterPoints.push_back(Point2f(0, 105));
        pitchOuterPoints.push_back(Point2f(68, 105));
        pitchOuterPoints.push_back(Point2f(68, 0));

        worldToScreen(size, pitchPoints);
        worldToScreen(size, pitchOuterPoints);
    };