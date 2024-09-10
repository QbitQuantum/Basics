    Status ProjectionExec::transform(WorkingSetMember* member) const {
        if (_hasReturnKey) {
            BSONObj keyObj;

            if (member->hasComputed(WSM_INDEX_KEY)) {
                const IndexKeyComputedData* key
                    = static_cast<const IndexKeyComputedData*>(member->getComputed(WSM_INDEX_KEY));
                keyObj = key->getKey();
            }

            member->state = WorkingSetMember::OWNED_OBJ;
            member->obj = keyObj;
            member->keyData.clear();
            member->loc = DiskLoc();
            return Status::OK();
        }

        BSONObjBuilder bob;
        if (!requiresDocument()) {
            // Go field by field.
            if (_includeID) {
                BSONElement elt;
                // Sometimes the _id field doesn't exist...
                if (member->getFieldDotted("_id", &elt) && !elt.eoo()) {
                    bob.appendAs(elt, "_id");
                }
            }

            BSONObjIterator it(_source);
            while (it.more()) {
                BSONElement specElt = it.next();
                if (mongoutils::str::equals("_id", specElt.fieldName())) {
                    continue;
                }

                BSONElement keyElt;
                // We can project a field that doesn't exist.  We just ignore it.
                if (member->getFieldDotted(specElt.fieldName(), &keyElt) && !keyElt.eoo()) {
                    bob.appendAs(keyElt, specElt.fieldName());
                }
            }
        }
        else {
            // Planner should have done this.
            verify(member->hasObj());

            MatchDetails matchDetails;

            // If it's a positional projection we need a MatchDetails.
            if (transformRequiresDetails()) {
                matchDetails.requestElemMatchKey();
                verify(NULL != _queryExpression);
                verify(_queryExpression->matchesBSON(member->obj, &matchDetails));
            }

            Status projStatus = transform(member->obj, &bob, &matchDetails);
            if (!projStatus.isOK()) {
                return projStatus;
            }
        }

        for (MetaMap::const_iterator it = _meta.begin(); it != _meta.end(); ++it) {
            if (META_GEONEAR_DIST == it->second) {
                if (member->hasComputed(WSM_COMPUTED_GEO_DISTANCE)) {
                    const GeoDistanceComputedData* dist
                        = static_cast<const GeoDistanceComputedData*>(
                                member->getComputed(WSM_COMPUTED_GEO_DISTANCE));
                    bob.append(it->first, dist->getDist());
                }
                else {
                    return Status(ErrorCodes::InternalError,
                                  "near loc dist requested but no data available");
                }
            }
            else if (META_GEONEAR_POINT == it->second) {
                if (member->hasComputed(WSM_GEO_NEAR_POINT)) {
                    const GeoNearPointComputedData* point
                        = static_cast<const GeoNearPointComputedData*>(
                                member->getComputed(WSM_GEO_NEAR_POINT));
                    BSONObj ptObj = point->getPoint();
                    if (ptObj.couldBeArray()) {
                        bob.appendArray(it->first, ptObj);
                    }
                    else {
                        bob.append(it->first, ptObj);
                    }
                }
                else {
                    return Status(ErrorCodes::InternalError,
                                  "near loc proj requested but no data available");
                }
            }
            else if (META_TEXT_SCORE == it->second) {
                if (member->hasComputed(WSM_COMPUTED_TEXT_SCORE)) {
                    const TextScoreComputedData* score
                        = static_cast<const TextScoreComputedData*>(
                                member->getComputed(WSM_COMPUTED_TEXT_SCORE));
                    bob.append(it->first, score->getScore());
                }
                else {
                    bob.append(it->first, 0.0);
                }
            }
            else if (META_DISKLOC == it->second) {
                bob.append(it->first, member->loc.toBSONObj());
            }
        }

        BSONObj newObj = bob.obj();
        member->state = WorkingSetMember::OWNED_OBJ;
        member->obj = newObj;
        member->keyData.clear();
        member->loc = DiskLoc();

        return Status::OK();
    }