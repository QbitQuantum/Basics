    bool _O2 unified_bed_leveling::prepare_segmented_line_to(const float (&rtarget)[XYZE], const float &feedrate) {

      if (!position_is_reachable(rtarget[X_AXIS], rtarget[Y_AXIS]))  // fail if moving outside reachable boundary
        return true; // did not move, so current_position still accurate

      const float total[XYZE] = {
        rtarget[X_AXIS] - current_position[X_AXIS],
        rtarget[Y_AXIS] - current_position[Y_AXIS],
        rtarget[Z_AXIS] - current_position[Z_AXIS],
        rtarget[E_AXIS] - current_position[E_AXIS]
      };

      const float cartesian_xy_mm = HYPOT(total[X_AXIS], total[Y_AXIS]);  // total horizontal xy distance

      #if IS_KINEMATIC
        const float seconds = cartesian_xy_mm / feedrate;                                  // seconds to move xy distance at requested rate
        uint16_t segments = lroundf(delta_segments_per_second * seconds),                  // preferred number of segments for distance @ feedrate
                 seglimit = lroundf(cartesian_xy_mm * (1.0f / (DELTA_SEGMENT_MIN_LENGTH))); // number of segments at minimum segment length
        NOMORE(segments, seglimit);                                                        // limit to minimum segment length (fewer segments)
      #else
        uint16_t segments = lroundf(cartesian_xy_mm * (1.0f / (DELTA_SEGMENT_MIN_LENGTH))); // cartesian fixed segment length
      #endif

      NOLESS(segments, 1U);                        // must have at least one segment
      const float inv_segments = 1.0f / segments;  // divide once, multiply thereafter

      #if IS_SCARA // scale the feed rate from mm/s to degrees/s
        scara_feed_factor = cartesian_xy_mm * inv_segments * feedrate;
        scara_oldA = planner.get_axis_position_degrees(A_AXIS);
        scara_oldB = planner.get_axis_position_degrees(B_AXIS);
      #endif

      const float diff[XYZE] = {
        total[X_AXIS] * inv_segments,
        total[Y_AXIS] * inv_segments,
        total[Z_AXIS] * inv_segments,
        total[E_AXIS] * inv_segments
      };

      // Note that E segment distance could vary slightly as z mesh height
      // changes for each segment, but small enough to ignore.

      float raw[XYZE] = {
        current_position[X_AXIS],
        current_position[Y_AXIS],
        current_position[Z_AXIS],
        current_position[E_AXIS]
      };

      // Only compute leveling per segment if ubl active and target below z_fade_height.
      if (!planner.leveling_active || !planner.leveling_active_at_z(rtarget[Z_AXIS])) {   // no mesh leveling
        while (--segments) {
          LOOP_XYZE(i) raw[i] += diff[i];
          ubl_buffer_segment_raw(raw, feedrate);
        }
        ubl_buffer_segment_raw(rtarget, feedrate);
        return false; // moved but did not set_current_from_destination();
      }

      // Otherwise perform per-segment leveling

      #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
        const float fade_scaling_factor = planner.fade_scaling_factor_for_z(rtarget[Z_AXIS]);
      #endif

      // increment to first segment destination
      LOOP_XYZE(i) raw[i] += diff[i];

      for (;;) {  // for each mesh cell encountered during the move

        // Compute mesh cell invariants that remain constant for all segments within cell.
        // Note for cell index, if point is outside the mesh grid (in MESH_INSET perimeter)
        // the bilinear interpolation from the adjacent cell within the mesh will still work.
        // Inner loop will exit each time (because out of cell bounds) but will come back
        // in top of loop and again re-find same adjacent cell and use it, just less efficient
        // for mesh inset area.

        int8_t cell_xi = (raw[X_AXIS] - (MESH_MIN_X)) * (1.0f / (MESH_X_DIST)),
               cell_yi = (raw[Y_AXIS] - (MESH_MIN_Y)) * (1.0f / (MESH_Y_DIST));

        cell_xi = constrain(cell_xi, 0, (GRID_MAX_POINTS_X) - 1);
        cell_yi = constrain(cell_yi, 0, (GRID_MAX_POINTS_Y) - 1);

        const float x0 = mesh_index_to_xpos(cell_xi),   // 64 byte table lookup avoids mul+add
                    y0 = mesh_index_to_ypos(cell_yi);

        float z_x0y0 = z_values[cell_xi  ][cell_yi  ],  // z at lower left corner
              z_x1y0 = z_values[cell_xi+1][cell_yi  ],  // z at upper left corner
              z_x0y1 = z_values[cell_xi  ][cell_yi+1],  // z at lower right corner
              z_x1y1 = z_values[cell_xi+1][cell_yi+1];  // z at upper right corner

        if (isnan(z_x0y0)) z_x0y0 = 0;              // ideally activating planner.leveling_active (G29 A)
        if (isnan(z_x1y0)) z_x1y0 = 0;              //   should refuse if any invalid mesh points
        if (isnan(z_x0y1)) z_x0y1 = 0;              //   in order to avoid isnan tests per cell,
        if (isnan(z_x1y1)) z_x1y1 = 0;              //   thus guessing zero for undefined points

        float cx = raw[X_AXIS] - x0,   // cell-relative x and y
              cy = raw[Y_AXIS] - y0;

        const float z_xmy0 = (z_x1y0 - z_x0y0) * (1.0f / (MESH_X_DIST)),   // z slope per x along y0 (lower left to lower right)
                    z_xmy1 = (z_x1y1 - z_x0y1) * (1.0f / (MESH_X_DIST));   // z slope per x along y1 (upper left to upper right)

              float z_cxy0 = z_x0y0 + z_xmy0 * cx;            // z height along y0 at cx (changes for each cx in cell)

        const float z_cxy1 = z_x0y1 + z_xmy1 * cx,            // z height along y1 at cx
                    z_cxyd = z_cxy1 - z_cxy0;                 // z height difference along cx from y0 to y1

              float z_cxym = z_cxyd * (1.0f / (MESH_Y_DIST));  // z slope per y along cx from y0 to y1 (changes for each cx in cell)

        //    float z_cxcy = z_cxy0 + z_cxym * cy;            // interpolated mesh z height along cx at cy (do inside the segment loop)

        // As subsequent segments step through this cell, the z_cxy0 intercept will change
        // and the z_cxym slope will change, both as a function of cx within the cell, and
        // each change by a constant for fixed segment lengths.

        const float z_sxy0 = z_xmy0 * diff[X_AXIS],                                     // per-segment adjustment to z_cxy0
                    z_sxym = (z_xmy1 - z_xmy0) * (1.0f / (MESH_Y_DIST)) * diff[X_AXIS];  // per-segment adjustment to z_cxym

        for (;;) {  // for all segments within this mesh cell

          if (--segments == 0)                      // if this is last segment, use rtarget for exact
            COPY(raw, rtarget);

          const float z_cxcy = (z_cxy0 + z_cxym * cy) // interpolated mesh z height along cx at cy
            #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
              * fade_scaling_factor                   // apply fade factor to interpolated mesh height
            #endif
          ;

          const float z = raw[Z_AXIS];
          raw[Z_AXIS] += z_cxcy;
          ubl_buffer_segment_raw(raw, feedrate);
          raw[Z_AXIS] = z;

          if (segments == 0)                        // done with last segment
            return false;                           // did not set_current_from_destination()

          LOOP_XYZE(i) raw[i] += diff[i];

          cx += diff[X_AXIS];
          cy += diff[Y_AXIS];

          if (!WITHIN(cx, 0, MESH_X_DIST) || !WITHIN(cy, 0, MESH_Y_DIST))    // done within this cell, break to next
            break;

          // Next segment still within same mesh cell, adjust the per-segment
          // slope and intercept to compute next z height.

          z_cxy0 += z_sxy0;   // adjust z_cxy0 by per-segment z_sxy0
          z_cxym += z_sxym;   // adjust z_cxym by per-segment z_sxym

        } // segment loop
      } // cell loop

      return false; // caller will update current_position
    }