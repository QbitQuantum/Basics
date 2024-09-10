// poly clipping algorithm Aug 2007
bool
cropPolygonPart( const GeoPointList& initial_input, const GeoExtent& window, GeoPartList& final_outputs )
{
    // trivial rejection for a non-polygon:
    if ( initial_input.size() < 3 )
    {
        return false;
    }

    // check for trivial acceptance.
    if ( window.contains( initial_input ) )
    {
        final_outputs.push_back( initial_input );
        return true;
    }

    // prepare the list of input parts to process.
    GeoPartList inputs;
    inputs.push_back( initial_input );

    // run the algorithm against all four sides of the window in succession.
    for( UINT stage = 0; stage < 4; stage++ )
    {
        GeoPoint s1, s2;
        switch( stage )
        {
            case STAGE_SOUTH: s1 = window.getSouthwest(), s2 = window.getSoutheast(); break;
            case STAGE_EAST:  s1 = window.getSoutheast(), s2 = window.getNortheast(); break;
            case STAGE_NORTH: s1 = window.getNortheast(), s2 = window.getNorthwest(); break;
            case STAGE_WEST:  s1 = window.getNorthwest(), s2 = window.getSouthwest(); break;
        }

        // output parts to send to the next stage (or to return).
        GeoPartList outputs;

        // run against each input part.
        for( GeoPartList::iterator i = inputs.begin(); i != inputs.end(); i++ )
        {
            //GeoPointList& input = *i;
            GeoPointList input = *i;
            scrubPart( input );

            // trivially reject a degenerate part (should never happen ;)
            if ( input.size() < 3 )
            {
                continue;
            }
            
            // trivially accept if the window contains the entire extent of the part:
            GeoExtent input_extent;
            input_extent.expandToInclude( input );

            // trivially accept when the part lies entirely within the line:
            if ( extentInsideOrOnLine( input_extent, s1, s2 ) )
            {
                outputs.push_back( input );
                continue;
            }

            // trivially reject when there's no overlap:
            if ( !window.intersects( input_extent ) || extentInsideOrOnLine( input_extent, s2, s1 ) )
            {
                continue;
            }                

            // close the part in preparation for cropping. The cropping process with undo
            // this automatically.
            input.push_back( input.front() );

            // 1a. Traverse the part and find all intersections. Insert them into the input shape.
            // 1b. Create a traversal-order list, ordering the isect points in the order in which they are encountered.
            // 1c. Create a spatial-order list, ordering the isect points along the boundary segment in the direction of the segment.
            GeoPointList working;
            UINTList traversal_order;
            UINTList spatial_order;
            GeoPoint prev_p;
            bool was_inside = true;

            for( UINT input_i = 0; input_i < input.size(); input_i++ )
            {
                const GeoPoint& p = input[ input_i ];
                bool is_inside = pointInsideOrOnLine( p, s1, s2 );

                if ( input_i > 0 )
                {
                    if ( was_inside != is_inside ) // entering or exiting
                    {
                        GeoPoint isect_p;
                        if ( getIsectPoint( prev_p, p, s1, s2, /*out*/ isect_p ) )
                        {
                            working.push_back( isect_p );
                            traversal_order.push_back( working.size()-1 );
                            spatialInsert( spatial_order, working.size()-1, stage, working );
                        }
                        else
                        {
                            osgGIS::notify( osg::WARN ) 
                                << "getIsectPoint failed" << std::endl;
                        }
                    }
                }

                working.push_back( p );
                prev_p = p;
                was_inside = is_inside;
            }

            if ( spatial_order.size() == 0 )
            {
                outputs.push_back( input );
                continue;
            }

            // 2. Start at the point preceding the first isect point (in spatial order). This will be the first
            //    outside point (since the first isect point is always an ENTRY.
            UINT overall_start_ptr = spatial_order[0];
            UINT shape_ptr = overall_start_ptr;

            // initialize the isect traversal pointer to start at the spatial order's first isect point:
            UINT trav_ptr = findIndexOf( traversal_order, spatial_order[0] );
            UINT traversals = 0;

            std::stack<DeferredPart> part_stack;
            GeoPointList current_part;

            // Process until we make it all the way around.
            while( traversals < traversal_order.size() )
            {
                // 4. We are outside. Find the next ENTRY point and either start a NEW part, or RESUME
                //    a previously deferred part that is on top of the stack.
                shape_ptr = traversal_order[trav_ptr]; // next ENTRY
                trav_ptr = (trav_ptr + 1) % traversal_order.size();
                traversals++;

                UINT part_start_ptr = shape_ptr;

                if ( part_stack.size() > 0 && part_stack.top().waiting_on_ptr == part_start_ptr )
                {
                    // time to resume a part that we deferred earlier.
                    DeferredPart& top = part_stack.top();
                    current_part = top.part;
                    part_start_ptr = top.part_start_ptr;
                    part_stack.pop();
                }
                else
                {
                    // start a new part
                    current_part = GeoPointList();
                }

                // 5. Traverse to the next EXIT, adding all points along the way. 
                //    Then check the spatial order of the EXIT against the part's starting point. If the former
                //    is ONE MORE than the latter, close out the part.
                for( bool part_done = false; !part_done && traversals < traversal_order.size(); )
                {
                    UINT next_exit_ptr = traversal_order[trav_ptr];
                    trav_ptr = (trav_ptr + 1) % traversal_order.size();
                    traversals++;
                
                    for( ; shape_ptr != next_exit_ptr; shape_ptr = (shape_ptr+1)%working.size() )
                    {
                        current_part.push_back( working[shape_ptr] );
                    }

                    // record the exit point:
                    current_part.push_back( working[next_exit_ptr] );

                    UINT part_start_order = findIndexOf( spatial_order, part_start_ptr );
                    UINT next_exit_order = findIndexOf( spatial_order, next_exit_ptr );
                    if ( next_exit_order - part_start_order == 1 )
                    {
                        outputs.push_back( current_part );
                        part_done = true;
                        continue;
                    }

                    // 6. Find the next ENTRY. If the spatial order of the ENTRY is one less than the 
                    //    spatial ordering of the preceding EXIT, continue on with the part.
                    UINT next_entry_ptr = traversal_order[trav_ptr];
                    trav_ptr = (trav_ptr + 1) % traversal_order.size();
                    traversals++;

                    // check whether we are back at the beginning:
                    if ( traversals >= traversal_order.size() )
                    {
                        current_part.push_back( working[next_entry_ptr] );
                        continue;
                    }

                    // check whether we are continuing the current part:
                    UINT next_entry_order = findIndexOf( spatial_order, next_entry_ptr );
                    if ( next_exit_order - next_entry_order == 1 )
                    {
                        shape_ptr = next_entry_ptr; // skip ahead to the entry point
                        continue;
                    }

                    // 7. We encountered an out-of-order traversal, so need to push the current part onto
                    //    the deferral stack until later, and start a new part.
                    part_stack.push( DeferredPart(
                        current_part,
                        part_start_ptr,
                        spatial_order[next_exit_order-1] ) );

                    current_part = GeoPointList();
                    //current_part.push_back( working[next_entry_ptr] );
                    part_start_ptr = next_entry_ptr;
                    shape_ptr = next_entry_ptr;
                }
            }

            // pop any parts left on the stack (they're complete now)
            while( part_stack.size() > 0 )
            {
                GeoPointList& part = part_stack.top().part;
                part.push_back( working[part_stack.top().waiting_on_ptr] );
                outputs.push_back( part );
                part_stack.pop();
            }
        }

        // set up for next iteration
        outputs.swap( inputs );
    }

    // go through and make sure no polys are "closed" (probably unnecessary).
    //for( GeoPartList::iterator k = inputs.begin(); k != inputs.end(); k++ )
    //{
    //    while ( k->size() > 3 && k->front() == k->back() )
    //        k->erase( k->end()-1 );
    //}

    final_outputs.swap( inputs );
    return true;
}