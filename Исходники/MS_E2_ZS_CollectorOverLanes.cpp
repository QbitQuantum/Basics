void
MS_E2_ZS_CollectorOverLanes::extendTo(SUMOReal length) {
    bool done = false;
    while (!done) {
        done = true;
        LengthVector::iterator leni = myLengths.begin();
        LaneVectorVector::iterator lanei = myLaneCombinations.begin();
        DetectorVectorVector::iterator deti = myDetectorCombinations.begin();
        for (; leni != myLengths.end(); leni++, lanei++, deti++) {
            if ((*leni) < length) {
                done = false;
                // copy current values
                LaneVector lv = *lanei;
                DetectorVector dv = *deti;
                SUMOReal clength = *leni;
                assert(lv.size() > 0);
                assert(dv.size() > 0);
                // erase previous elements
                assert(leni != myLengths.end());
                myLengths.erase(leni);
                myLaneCombinations.erase(lanei);
                myDetectorCombinations.erase(deti);
                // get the lane to look before
                MSLane* toExtend = lv.back();
                // and her predecessors
                std::vector<MSLane*> predeccessors = getLanePredeccessorLanes(toExtend);
                if (predeccessors.size() == 0) {
                    int off = 1;
                    MSEdge& e = toExtend->getEdge();
                    const std::vector<MSLane*>& lanes = e.getLanes();
                    int idx = (int) distance(lanes.begin(), find(lanes.begin(), lanes.end(), toExtend));
                    while (predeccessors.size() == 0) {
                        if (idx - off >= 0) {
                            MSLane* tryMe = lanes[idx - off];
                            predeccessors = getLanePredeccessorLanes(tryMe);
                        }
                        if (predeccessors.size() == 0 && idx + off < (int) lanes.size()) {
                            MSLane* tryMe = lanes[idx + off];
                            predeccessors = getLanePredeccessorLanes(tryMe);
                        }
                        off++;
                    }
                }

                /*                LaneContinuations::const_iterator conts =
                                    laneContinuations.find(toExtend->id());
                                assert(conts!=laneContinuations.end());
                                const std::vector<std::string> &predeccessors =
                                    (*conts).second;*/
                // go through the predeccessors and extend the detector
                for (std::vector<MSLane*>::const_iterator i = predeccessors.begin(); i != predeccessors.end(); i++) {
                    // get the lane
                    MSLane* l = *i;
                    // compute detector length
                    SUMOReal lanelen = length - clength;
                    if (lanelen > l->getLength()) {
                        lanelen = l->getLength() - (SUMOReal) 0.2;
                    }
                    // build new info
                    LaneVector nlv = lv;
                    nlv.push_back(l);
                    DetectorVector ndv = dv;
                    MSE2Collector* coll = 0;
                    if (myAlreadyBuild.find(l) == myAlreadyBuild.end()) {
                        coll = buildCollector(0, 0, l, (SUMOReal) 0.1, lanelen);
                    } else {
                        coll = myAlreadyBuild.find(l)->second;
                    }
                    myAlreadyBuild[l] = coll;
                    ndv.push_back(coll);
                    // store new info
                    myLaneCombinations.push_back(nlv);
                    myDetectorCombinations.push_back(ndv);
                    myLengths.push_back(clength + lanelen);
                }
                // restart
                leni = myLengths.end() - 1;
            }
        }
    }
}