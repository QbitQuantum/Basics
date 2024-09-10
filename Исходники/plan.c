int plan(const char *satellite, const char *beam_mode, double look_angle,
         long startdate, long enddate, double min_lat, double max_lat,
         double clat, double clon, int pass_type,
         int zone, Poly *aoi, const char *tle_filename,
         PassCollection **pc_out, char **errorstring)
{
  BeamModeInfo *bmi = get_beam_mode_info(satellite, beam_mode);
  if (!bmi) {
    *errorstring = STRDUP("Unknown satellite/beam mode combination.\n");
    return -1;
  }

  // Convert the input start/end times from longdates (dates as long ints)
  // to seconds from some reference time.  (midnight jan 1, 1900)
  // We add a day to the end date, so that the passed-in range is inclusive
  double start_secs = seconds_from_long(startdate);
  double end_secs = seconds_from_long(add_a_day(enddate));

  sat_t sat;
  read_tle(tle_filename, satellite, &sat);

  // if the planned acquisition period is further away than this amount,
  // we subtract multiples of the repeat cyle time until we are within
  // this threshold time of this tle
  double tle_time =
    time_to_secs(sat.tle.epoch_year, sat.tle.epoch_day, sat.tle.epoch_fod);

  // FIXME this is alos specific FIXME!!
  // should really read this out of a config file... or calculate it
  // from the TLE info?
  const double repeat_days = 46;
  const double orbits_per_cycle = 671;

  // repeat time, in seconds, all time references are in seconds
  double repeat_cycle_time = repeat_days * 24.*60.*60.;

  // how many days to pad the repeat cycle time, before modding the
  // start/end time
  const double days_of_padding = 5;

  // this is the cutoff, 
  double threshold = repeat_cycle_time + 24*60*60 * days_of_padding;

  int cycles_adjustment=0;
  if (start_secs-tle_time > threshold) {
    while (start_secs-tle_time > threshold) {
      start_secs -= repeat_cycle_time;
      end_secs -= repeat_cycle_time;
      ++cycles_adjustment;
    }
  }
  else if (tle_time-start_secs > threshold) { // planning backwards...
    while (tle_time-start_secs > threshold) {
      start_secs += repeat_cycle_time;
      end_secs += repeat_cycle_time;
      --cycles_adjustment;
    }
  }

  double time_adjustment = cycles_adjustment*repeat_cycle_time;
  if (cycles_adjustment != 0)
    asfPrintStatus("Adjusted start/end times %s by %d repeat cycle%s.\n",
           cycles_adjustment > 0 ? "forward" : "backward",
           cycles_adjustment > 0 ? cycles_adjustment : -cycles_adjustment,
           cycles_adjustment == 1 || cycles_adjustment == -1 ? "" : "s");

  // no deep space orbits can be planned
  assert((sat.flags & DEEP_SPACE_EPHEM_FLAG) == 0);

  if (is_utm(zone)) {
    asfPrintStatus("Target: UTM zone %d\n"
                   "  (%10.2f, %10.2f)  (%10.2f, %10.2f)\n"
                   "  (%10.2f, %10.2f)  (%10.2f, %10.2f)\n",
                   zone,
                   aoi->x[0], aoi->y[0],
                   aoi->x[1], aoi->y[1],
                   aoi->x[2], aoi->y[2],
                   aoi->x[3], aoi->y[3]);
  }
  else {
    asfPrintStatus("Target: Polar Stereo %s\n"
                   "  (%10.2f, %10.2f)  (%10.2f, %10.2f)\n"
                   "  (%10.2f, %10.2f)  (%10.2f, %10.2f)\n",
                   zone>0 ? "North" : "South",
                   aoi->x[0], aoi->y[0],
                   aoi->x[1], aoi->y[1],
                   aoi->x[2], aoi->y[2],
                   aoi->x[3], aoi->y[3]);
  }

  double curr = start_secs;
  double incr = bmi->image_time;
  stateVector st = tle_propagate(&sat, start_secs-incr);
  double lat_prev = sat.ssplat;
  int i,num_found = 0;

  // 
  // Calculate the number of frames to include before we hit the
  // area of interest.  Add 1 (i.e., round up), but if user puts in
  // zero seconds, then we want 0 lead-up frames.
  PassCollection *pc = pass_collection_new(clat, clon, aoi);

  asfPrintStatus("Searching...\n");
  while (curr < end_secs) {
    st = tle_propagate(&sat, curr);
    char dir = sat.ssplat > lat_prev ? 'A' : 'D';

    if ((dir=='A' && pass_type!=DESCENDING_ONLY) ||
        (dir=='D' && pass_type!=ASCENDING_ONLY))
    {
      OverlapInfo *oi =
        overlap(curr, &st, bmi, look_angle, zone, clat, clon, aoi);

      if (oi) {
        int n=0;

        // Calculate the orbit number -- we have to fudge this if we
        // modded the start time.
        int orbit_num = sat.orbit + orbits_per_cycle*cycles_adjustment;

        // This is an alternate way of calculating the orbit number that
        // was being used during testing... seems to produce numbers close
        // to (within 1) of the number obtained by sgpsdp...
        //double secs_per_orbit = repeat_cycle_time / orbits_per_cycle;
        // ALOS was launced on 1/24/06
        //double launch_secs = seconds_from_long(20060124);
        //double orbit_num2 = (curr - launch_secs) / secs_per_orbit;
        //orbit_num2 += orbits_per_cycle*cycles_adjustment;
        //printf("%f %f %f\n", orbit_num + sat.orbit_part,
        //       orbit_num2, orbit_num+sat.orbit_part-orbit_num2);

        // UPDATE!!  All this orbit number calculation business doesn't get
        // used for ALOS planning -- orbit number is re-calculated using
        // time since a refrence orbit.
        // See planner.c -- get_alos_orbit_number_at_time()

        PassInfo *pass_info = pass_info_new(orbit_num, sat.orbit_part, dir);
        double start_time = curr - bmi->num_buffer_frames*incr;

        // add on the buffer frames before the area of interest
        for (i=bmi->num_buffer_frames; i>0; --i) {
          double t = curr - i*incr;
          stateVector st1 = tle_propagate(&sat, t);
          double rclat, rclon; // viewable region center lat/lon

          Poly *region = get_viewable_region(&st1, bmi, look_angle,
                                             zone, clat, clon, &rclat, &rclon);

          if (region) {
            OverlapInfo *oi1 = overlap_new(0, 1000, region, zone, clat, clon,
                                           &st1, t);
            pass_info_add(pass_info, t+time_adjustment, oi1);

            if (pass_info->start_lat == -999) {
              // at the first valid buffer frame -- set starting latitude
              double start_lat, end_lat;
              get_latitude_range(region, zone, dir, &start_lat, &end_lat);
              pass_info_set_start_latitude(pass_info, start_lat);
            }
          }
        }

        // add the frames that actually image the area of interest
        while (curr < end_secs && oi) {
          pass_info_add(pass_info, curr+time_adjustment, oi);
          ++n;

          curr += incr;
          st = tle_propagate(&sat, curr);

          oi = overlap(curr, &st, bmi, look_angle, zone, clat, clon, aoi);
        }

        double end_time = curr + (bmi->num_buffer_frames-1)*incr;
        pass_info_set_duration(pass_info, end_time-start_time);

        // add on the buffer frames after the area of interest
        for (i=0; i<bmi->num_buffer_frames; ++i) {
          double t = curr + i*incr;
          stateVector st1 = tle_propagate(&sat, t);
          double rclat, rclon; // viewable region center lat/lon
          Poly *region = get_viewable_region(&st1, bmi, look_angle,
                                             zone, clat, clon, &rclat, &rclon);
          if (region) {
            OverlapInfo *oi1 = overlap_new(0, 1000, region, zone, clat, clon,
                                           &st1, t);
            pass_info_add(pass_info, t+time_adjustment, oi1);

            // set stopping latitude -- each frame overwrites the previous,
            // so the last valid frame will set the stopping latitude
            double start_lat, end_lat;
            get_latitude_range(region, zone, dir, &start_lat, &end_lat);
            pass_info_set_stop_latitude(pass_info, end_lat);
          }
        }

        // make sure we set all the required "after the fact" info
        // if not, then do not add the pass... must be invalid
        // (these used to be asserts, so it doesn't seem to ever happen)
        if (n>0 &&
            pass_info->start_lat != -999 &&
            pass_info->stop_lat != -999 &&
            pass_info->duration != -999)
        {
          // add the pass!
          pass_collection_add(pc, pass_info);
          ++num_found;
        }
        else
        {
          asfPrintStatus("Invalid pass found.  Skipped... \n"
                         " -- number of frames: %d, dir: %c\n"
                         " -- date: %s, orbit %d, %f\n --> (%f,%f,%f)\n",
                         n, pass_info->dir,
                         pass_info->start_time_as_string,
                         pass_info->orbit, pass_info->orbit_part,
                         pass_info->start_lat, pass_info->stop_lat,
                         pass_info->duration);
        }
      }
    }

    curr += incr;
    lat_prev = sat.ssplat;

    //printf("Lat: %f, Orbit: %d, Orbit Part: %f\n", sat.ssplat,
    //       (int)sat.orbit, sat.orbit_part);

    asfPercentMeter((curr-start_secs)/(end_secs-start_secs));
  }
  asfPercentMeter(1.0);

  *pc_out = pc;
  return num_found;
}