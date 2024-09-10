void DVRClipGeometry::linkContour(      DVRTriangle *startTriangle,
                                        Real32       dist2RefPlane,
                                  const Vec3f       &viewDir, 
                                        bool         positiveWinding)
{
    FDEBUG(("DVRClipGeometry - linkcontour dist = %f\n", dist2RefPlane));
  
    bool closed = false;

    // first, we have to check for the correct winding direction.

    Pnt3f vertex[2];
    bool firstEdge;
    int  first = 0, second = 0;

    if(startTriangle->edgeCut[0] && startTriangle->edgeCut[1])
    {
        vertex[0] = interpolate(startTriangle, 1, 0, dist2RefPlane); 
        vertex[1] = interpolate(startTriangle, 1, 2, dist2RefPlane);

        first = 0; second = 1;
    }
    else if (startTriangle->edgeCut[1] && startTriangle->edgeCut[2])
    {
        vertex[0] = interpolate(startTriangle, 2, 1, dist2RefPlane);
        vertex[1] = interpolate(startTriangle, 2, 0, dist2RefPlane);

        first = 1; second = 2;
    }
    else if (startTriangle->edgeCut[0] && startTriangle->edgeCut[2])
    {
        vertex[0] = interpolate(startTriangle, 0, 1, dist2RefPlane);
        vertex[1] = interpolate(startTriangle, 0, 2, dist2RefPlane);

        first = 0; second = 2;
    }

    // Now we should have both cut points on our edges.

    // If the cross product of the normal of this triangle with the 
    // vector between the two cut points (cutPoint[1] - cutPoint[0]) 
    // has a positive dot product with the viewing direction, then 
    // the edge with cutPoint[0] on it is the right direction, otherwise
    // we would have to choose the other direction.

    Vec3f tmp = vertex[1] - vertex[0];

    tmp = tmp.cross(startTriangle->transformedNormal);

    if(tmp.dot(viewDir) <= 0.0)
    {
        firstEdge = false;
    }else
    {
        firstEdge = true;
    }

    if(!positiveWinding)
        firstEdge = !firstEdge;

    DVRTriangle *current = startTriangle;

    current->inContour = true;

    if(firstEdge)
    {
        current->cutPnt      = vertex[0];
        current->cutPoint[0] = vertex[0][0];
        current->cutPoint[1] = vertex[0][1];
        current->cutPoint[2] = vertex[0][2];

        current->contourNeighbour = &_mfTriangles[current->neighbours[first]];

        //      // debugging -> remove
        //      if(!current->contourNeighbour){
        //        std::cerr<<"contour neighbour is NULL\n";
        //        exit(0);
        //      }

        current = current->contourNeighbour;
    }
    else
    {
        current->cutPnt      = vertex[1];
        current->cutPoint[0] = vertex[1][0];
        current->cutPoint[1] = vertex[1][1];
        current->cutPoint[2] = vertex[1][2];    

        current->contourNeighbour = &_mfTriangles[current->neighbours[second]];
        //      // debugging -> remove
        //      if(!current->contourNeighbour){
        //        std::cerr<<"contour neighbour is NULL\n";
        //        exit(0);
        //      }

        current = current->contourNeighbour;    
    }

    //check neighbours
    while(!closed)
    {
        closed             = true;
        current->inContour = true;

        for(UInt32 i = 0; i < 3; i++)
        {
            // if a neighbour triangle is in the active triangle list and 
            // not yet in a contour it is our new contour neighbour.
            if( current->edgeCut[i] && 
               !_mfTriangles[current->neighbours[i]].inContour)
            {
                // calculate cut point 	
                current->cutPnt = interpolate(current, 
                                              i, 
                                              (i + 1) % 3, 
                                              dist2RefPlane);

                current->cutPoint[0] = current->cutPnt[0];
                current->cutPoint[1] = current->cutPnt[1];
                current->cutPoint[2] = current->cutPnt[2];

                current->contourNeighbour = 
                    &_mfTriangles[current->neighbours[i]];

                //  	// debugging -> remove
                //  	if(!current->contourNeighbour){
                //  	  std::cerr<<"contour neighbour is NULL\n";
                //  	  exit(0);
                //  	}

                current = current->contourNeighbour;
                closed  = false;

                break;
            }// !inContour
        } // end for neighbours
    } // end while !closed

    for(UInt32 i = 0; i < 3; i++)
    {
        if(&_mfTriangles[current->neighbours[i]] == startTriangle)
        {
            current->cutPnt = interpolate(current, 
                                          i, 
                                          (i + 1) % 3, 
                                          dist2RefPlane);

            current->cutPoint[0] = current->cutPnt[0];
            current->cutPoint[1] = current->cutPnt[1];
            current->cutPoint[2] = current->cutPnt[2];

            // now the ring is closed.

            current->contourNeighbour = startTriangle;
            //        // debugging -> remove
            //        if(!current->contourNeighbour){
            //  	std::cerr<<"contour neighbour is NULL\n";
            //  	exit(0);
            //        }
            break;
        }
    } // end for neighbours

    //    // debugging -> remove
    //    if(!current->contourNeighbour){
    //      std::cerr <<"contour could not closed\n";
    //      std::cerr <<current->edgeCut[0]<<current->edgeCut[1]
    //                <<current->edgeCut[2]<<std::endl;
    //      exit(0);
    //    }
}