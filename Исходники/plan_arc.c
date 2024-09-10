static stat_t _compute_arc()
{
	// Compute radius. A non-zero radius value indicates a radius arc
    if (fp_NOT_ZERO(arc.radius)) {                  // indicates a radius arc
        _compute_arc_offsets_from_radius();
    } else {                                        // compute start radius
        arc.radius = hypotf(-arc.offset[arc.plane_axis_0], -arc.offset[arc.plane_axis_1]);
    }

    // Test arc specification for correctness according to:
    // http://linuxcnc.org/docs/html/gcode/gcode.html#sec:G2-G3-Arc
    // "It is an error if: when the arc is projected on the selected plane, the distance from
    //  the current point to the center differs from the distance from the end point to the
    //  center by more than (.05 inch/.5 mm) OR ((.0005 inch/.005mm) AND .1% of radius)."

    // Compute end radius from the center of circle (offsets) to target endpoint
    float end_0 = arc.gm.target[arc.plane_axis_0] - arc.position[arc.plane_axis_0] - arc.offset[arc.plane_axis_0];
    float end_1 = arc.gm.target[arc.plane_axis_1] - arc.position[arc.plane_axis_1] - arc.offset[arc.plane_axis_1];
    float err = fabs(hypotf(end_0, end_1) - arc.radius);   // end radius - start radius
    if ( (err > ARC_RADIUS_ERROR_MAX) || 
        ((err < ARC_RADIUS_ERROR_MIN) && 
         (err > arc.radius * ARC_RADIUS_TOLERANCE)) ) {
//        return (STAT_ARC_HAS_IMPOSSIBLE_CENTER_POINT);
        return (STAT_ARC_SPECIFICATION_ERROR);
    }

	// Calculate the theta (angle) of the current point (position)
	// arc.theta is angular starting point for the arc (also needed later for calculating center point)
    arc.theta = atan2(-arc.offset[arc.plane_axis_0], -arc.offset[arc.plane_axis_1]);

    // g18_correction is used to invert G18 XZ plane arcs for proper CW orientation
    float g18_correction = (cm.gm.select_plane == CANON_PLANE_XZ) ? -1 : 1;

	if (arc.full_circle) {                                  // if full circle you can skip the stuff in the else clause
    	arc.angular_travel = 0;                             // angular travel always starts as zero for full circles
    	if (fp_ZERO(arc.rotations)) {                       // handle the valid case of a full circle arc w/P=0
            arc.rotations = 1.0;
        }
    } else {                                                // ... it's not a full circle
        arc.theta_end = atan2(end_0, end_1);

        // Compute the angular travel
        if (fp_EQ(arc.theta_end, arc.theta)) {
	        arc.angular_travel = 0;                         // very large radii arcs can have zero angular travel (thanks PartKam)
        } else {
	        if (arc.theta_end < arc.theta) {                // make the difference positive so we have clockwise travel
                arc.theta_end += (2*M_PI * g18_correction);
            }
	        arc.angular_travel = arc.theta_end - arc.theta; // compute positive angular travel
    	    if (cm.gm.motion_mode == MOTION_MODE_CCW_ARC) { // reverse travel direction if it's CCW arc
                arc.angular_travel -= (2*M_PI * g18_correction);
            }
        }
	}

    // Add in travel for rotations
    if (cm.gm.motion_mode == MOTION_MODE_CW_ARC) {
        arc.angular_travel += (2*M_PI * arc.rotations * g18_correction);
    } else {
        arc.angular_travel -= (2*M_PI * arc.rotations * g18_correction);
    }

	// Calculate travel in the depth axis of the helix and compute the time it should take to perform the move
	// arc.length is the total mm of travel of the helix (or just a planar arc)
	arc.linear_travel = arc.gm.target[arc.linear_axis] - arc.position[arc.linear_axis];
	arc.planar_travel = arc.angular_travel * arc.radius;
	arc.length = hypotf(arc.planar_travel, arc.linear_travel);  // NB: hypot is insensitive to +/- signs
	_estimate_arc_time();	// get an estimate of execution time to inform arc_segment calculation

	// Find the minimum number of arc_segments that meets these constraints...
	float arc_segments_for_chordal_accuracy = arc.length / sqrt(4*cm.chordal_tolerance * (2 * arc.radius - cm.chordal_tolerance));
	float arc_segments_for_minimum_distance = arc.length / cm.arc_segment_len;
	float arc_segments_for_minimum_time = arc.arc_time * MICROSECONDS_PER_MINUTE / MIN_ARC_SEGMENT_USEC;

	arc.arc_segments = floor(min3(arc_segments_for_chordal_accuracy,
							      arc_segments_for_minimum_distance,
							      arc_segments_for_minimum_time));

	arc.arc_segments = max(arc.arc_segments, 1);            //...but is at least 1 arc_segment
 	arc.gm.move_time = arc.arc_time / arc.arc_segments;     // gcode state struct gets arc_segment_time, not arc time
	arc.arc_segment_count = (int32_t)arc.arc_segments;
	arc.arc_segment_theta = arc.angular_travel / arc.arc_segments;
	arc.arc_segment_linear_travel = arc.linear_travel / arc.arc_segments;
    arc.center_0 = arc.position[arc.plane_axis_0] - sin(arc.theta) * arc.radius;
    arc.center_1 = arc.position[arc.plane_axis_1] - cos(arc.theta) * arc.radius;
	arc.gm.target[arc.linear_axis] = arc.position[arc.linear_axis];	// initialize the linear target
	return (STAT_OK);
}