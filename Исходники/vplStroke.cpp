    void Stroker::handleArcSegment(Segment* segment)
    {
        // Where are we going to?
        updateCurrentPoint(segment->getSegment());

        // First point is already added
        float* points = segment->beginPointIteration();

        points = segment->getNextPoint();

        // First normal using segment end points
        Vector firstNormal = prevPoint_ - currentPoint_;
        firstNormal.normalize();
        firstNormal *= size_ /2;

        scale_.transform(firstNormal);

        // Calculate first and second normal from points
        Vector secondNormal;
        calculateStrokeNormal(points,normal_);
        calculateStrokeNormal(points + 2,secondNormal);

        // Adjust first normal so it points
        // in the same direction as the second normal
        Winding firstWinding  = determineWinding(firstNormal,normal_);
        Winding secondWinding = determineWinding(normal_,secondNormal);

        if(firstWinding != secondWinding)
            firstNormal.invert();

        // Join segments or begin the first segment
        Vector outer;
        Vector inner;

        if(numSegments_ == 0)
        {
            firstPoint_  = prevPoint_;
            firstNormal_ = firstNormal;

            outer = firstPoint_ + firstNormal_;
            inner = firstPoint_ - firstNormal_;

            addPoint(&outerPoints_,outer);
            addPoint(&innerPoints_,inner);
        }
        else
            joiner_(this,prevPoint_,prevNormal_,firstNormal);


        // Add points
        while(segment->hasMorePoints())
        {
            Vector point(*points,*(points + 1));

            calculateStrokeNormal(points,normal_);

            outer = point + normal_;
            inner = point - normal_;

            addPoint(&outerPoints_,outer);
            addPoint(&innerPoints_,inner);

            points = segment->getNextPoint();
        }

        // Add last
        normal_ = invert(firstNormal);

        outer = currentPoint_ + normal_;
        inner = currentPoint_ - normal_;

        addPoint(&outerPoints_,outer);
        addPoint(&innerPoints_,inner);

        prevPoint_  = currentPoint_;
        prevNormal_ = normal_;
    }