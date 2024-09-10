    //-----------------------------------------------------------------------
    bool BspRaySceneQuery::processLeaf(const BspNode* leaf, const Ray& tracingRay, 
        RaySceneQueryListener* listener, Real maxDistance, Real traceDistance)
    {
        const BspNode::IntersectingObjectSet& objects = leaf->getObjects();

        BspNode::IntersectingObjectSet::const_iterator i, iend;
        iend = objects.end();
        //Check ray against objects
        for(i = objects.begin(); i != iend; ++i)
        {
            // cast away constness, constness of node is nothing to do with objects
            MovableObject* obj = const_cast<MovableObject*>(*i);
            // Skip this object if not enabled
            if(!(obj->getQueryFlags() & mQueryMask) ||
				!((obj->getTypeFlags() & mQueryTypeMask)))
                continue;

            // check we haven't reported this one already
            // (objects can be intersecting more than one node)
            if (mObjsThisQuery.find(obj) != mObjsThisQuery.end())
                continue;

            //Test object as bounding box
            std::pair<bool, Real> result = 
                tracingRay.intersects(obj->getWorldBoundingBox());
            // if the result came back positive and intersection point is inside
            // the node, fire the event handler
            if(result.first && result.second <= maxDistance)
            {
                if (!listener->queryResult(obj, result.second + traceDistance))
					return false;
            }
        }


        // Check ray against brushes
        if (mQueryTypeMask & SceneManager::WORLD_GEOMETRY_TYPE_MASK)
        {
            const BspNode::NodeBrushList& brushList = leaf->getSolidBrushes();
            BspNode::NodeBrushList::const_iterator bi, biend;
            biend = brushList.end();
            bool intersectedBrush = false;
            for (bi = brushList.begin(); bi != biend; ++bi)
            {
                BspNode::Brush* brush = *bi;
                

                std::pair<bool, Real> result = Math::intersects(tracingRay, brush->planes, true);
                // if the result came back positive and intersection point is inside
                // the node, check if this brush is closer
                if(result.first && result.second <= maxDistance)
                {
                    intersectedBrush = true;
                    if(mWorldFragmentType == SceneQuery::WFT_SINGLE_INTERSECTION)
                    {
                        // We're interested in a single intersection
                        // Have to create these 
                        SceneQuery::WorldFragment* wf = OGRE_ALLOC_T(SceneQuery::WorldFragment, 1, MEMCATEGORY_SCENE_CONTROL);
                        wf->fragmentType = SceneQuery::WFT_SINGLE_INTERSECTION;
                        wf->singleIntersection = tracingRay.getPoint(result.second);
                        // save this so we can clean up later
                        mSingleIntersections.push_back(wf);
                        if (!listener->queryResult(wf, result.second + traceDistance))
							return false;
                    }
                    else if (mWorldFragmentType ==  SceneQuery::WFT_PLANE_BOUNDED_REGION)
                    {
                        // We want the whole bounded volume
                        assert((*bi)->fragment.fragmentType == SceneQuery::WFT_PLANE_BOUNDED_REGION);
                        if (!listener->queryResult(const_cast<WorldFragment*>(&(brush->fragment)), 
                            result.second + traceDistance))
							return false; 

                    }
                }
            }
            if (intersectedBrush)
            {
                return false; // stop here
            }
        }

        return true;

    } 