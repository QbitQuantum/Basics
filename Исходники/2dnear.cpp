    // TODO: Refactor this back into holder class, allow to run periodically when we are seeing
    // a lot of pts
    void GeoSearch::expandEndPoints(bool finish) {
        processExtraPoints();
        // All points in array *could* be in maxDistance

        // Step 1 : Trim points to max size TODO:  This check will do little for now, but is
        // skeleton for future work in incremental $near
        // searches
        if(_max > 0){
            int numToErase = _points.size() - _max;
            if(numToErase > 0){
                Holder tested;
                // Work backward through all points we're not sure belong in the set
                Holder::iterator maybePointIt = _points.end();
                maybePointIt--;
                double approxMin = maybePointIt->distance() - 2 * _distError;

                // Insert all
                int erased = 0;
                while(_points.size() > 0
                        && (maybePointIt->distance() >= approxMin || erased < numToErase)){

                    Holder::iterator current = maybePointIt;
                    if (current != _points.begin())
                        --maybePointIt;

                    addExactPoints(*current, tested, true);
                    _points.erase(current);
                    erased++;

                    if(tested.size())
                        approxMin = tested.begin()->distance() - 2 * _distError;
                }

                int numToAddBack = erased - numToErase;
                verify(numToAddBack >= 0);

                Holder::iterator testedIt = tested.begin();
                for(int i = 0; i < numToAddBack && testedIt != tested.end(); i++){
                    _points.insert(*testedIt);
                    testedIt++;
                }
            }
        }

        // We've now trimmed first set of unneeded points

        // Step 2: iterate through all points and add as needed
        unsigned expandedPoints = 0;
        Holder::iterator it = _points.begin();
        double expandWindowEnd = -1;

        while(it != _points.end()){
            const GeoPoint& currPt = *it;
            // TODO: If one point is exact, maybe not 2 * _distError

            // See if we're in an expand window
            bool inWindow = currPt.distance() <= expandWindowEnd;
            // If we're not, and we're done with points, break
            if(! inWindow && expandedPoints >= _max) break;

            bool expandApprox = !currPt.isExact() && (finish || inWindow);

            if (expandApprox) {
                // Add new point(s). These will only be added in a radius of 2 * _distError
                // around the current point, so should not affect previously valid points.
                int before, after;
                addExactPoints(currPt, _points, before, after, false);
                expandedPoints += before;

                if(_max > 0 && expandedPoints < _max)
                    expandWindowEnd = currPt.distance() + 2 * _distError;

                // Iterate to the next point
                Holder::iterator current = it++;
                // Erase the current point
                _points.erase(current);
            } else{
                expandedPoints++;
                it++;
            }
        }

        // Finish
        // TODO:  Don't really need to trim?
        for(; expandedPoints > _max; expandedPoints--) it--;
        _points.erase(it, _points.end());
    }