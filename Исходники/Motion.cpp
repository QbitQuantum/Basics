// This is the lookahead algorithm.  From a high level, we simply 
// limit our end speed and the next start speed to appropriate limits, 
// then further limit them to a speed where reaching a stop is possible.
void Motion::gcode_optimize(GCode& gcode, GCode& nextg)
{
#ifdef LOOKAHEAD
  // THIS NEEDS SERIOUS REFACTORIN
  if(gcode.optimized)
    return;

  gcode.optimized = true;

  // If this isn't a move, we have nothing to do.
  if(gcode[G].isUnused() || gcode[G].getInt() != 1 || gcode.movesteps == 0)
    return;

  // If the NEXT gcode isn't a move, then we will just recomute our accels
  // (assuming the previous move changed them during it's optimization)
  if(nextg[G].isUnused() || nextg[G].getInt() != 1 || nextg.movesteps == 0)
  {
    computeAccel(gcode);
    return;
  }

  // Calculate the requested speed of each axis at its peak during this move,
  // including a direction sign.  TODO: We calculated this once already, maybe we can store it.
  int32_t axisspeeds[NUM_AXES];
  int32_t endspeeds[NUM_AXES];
  int32_t nextspeeds[NUM_AXES];
  int32_t startspeeds[NUM_AXES];
  float mult1 = (float)gcode.maxfeed / gcode.actualmm;
  float mult2 = (float)nextg.maxfeed / nextg.actualmm;
  for(int ax=0;ax<NUM_AXES;ax++)
  {
    axisspeeds[ax] = (float)((float)gcode.axismovesteps[ax] / AXES[ax].getStepsPerMM()) * mult1;
    axisspeeds[ax] *= gcode.axisdirs[ax] ? 1 : -1;
    endspeeds[ax] = axisspeeds[ax];
    nextspeeds[ax] = (float)((float)nextg.axismovesteps[ax] / AXES[ax].getStepsPerMM()) * mult2;
    nextspeeds[ax] *= nextg.axisdirs[ax] ? 1 : -1;
    startspeeds[ax] = nextspeeds[ax];
  }

  int32_t *ends, *starts, *temp;
  ends = endspeeds;
  starts = startspeeds;
  // TODO this is stupid shit.
  int MAX_OPTS = (float)AXES[0].getMaxFeed() / (float)AXES[0].getStartFeed();
  if(MAX_OPTS < 4)
    MAX_OPTS = 4;

  int c;
// this algorithm is crap.
  for(c=0;c<MAX_OPTS;c++)
  {
    // Calculate the end speeds (of this move) we can use to meet the start speeds (of the next move).
    if(!join_moves(ends,starts) && c >= 1)
      break;
    temp = ends;
    ends = starts;
    starts = temp;
  }

  for(int ax=0;ax<NUM_AXES;ax++)
  {
#ifdef DEBUG_OPT    
  HOST.labelnum("OPTS:",c);
    HOST.labelnum("ASP[", ax, false);
    HOST.labelnum("]:", axisspeeds[ax],false);
    HOST.labelnum("->", endspeeds[ax],false);
    HOST.labelnum(", ", startspeeds[ax],false);
    HOST.labelnum("->", nextspeeds[ax], false);
    HOST.labelnum(" @jump:", AXES[ax].getStartFeed());
#endif

    if(labs(endspeeds[ax] - startspeeds[ax]) > AXES[ax].getStartFeed())
    {
      if(labs(endspeeds[ax] - startspeeds[ax]) - AXES[ax].getStartFeed() > (float)AXES[ax].getStartFeed())
      {
#ifdef DEBUG_JUMP    
        HOST.labelnum("JUMP EXCEED LINE ", gcode.linenum);
#endif
        endspeeds[gcode.leading_axis] = AXES[gcode.leading_axis].getStartFeed() / 2;
        startspeeds[nextg.leading_axis] = AXES[nextg.leading_axis].getStartFeed() / 2;
      }
    }
  }

  // Speed at which the next move's leading axis can reach 0 during the next move.
  float speedto0 = AXES[nextg.leading_axis].
                    getSpeedAtEnd(AXES[nextg.leading_axis].getStartFeed()/2,
                                  nextg.accel, 
                                  nextg.movesteps);

  // NOT TODO: startspeeds/endspeeds is signed previous to this operation but unsigned
  // after.  Not important, though.

  // If the next move cannot reach 0, limit it so it can.
  if(speedto0 < labs(startspeeds[nextg.leading_axis]))
  {
#ifdef DEBUG_LAME
    HOST.labelnum("st0beg:",speedto0);
    HOST.labelnum("beg:",startspeeds[nextg.leading_axis]);
#endif
    startspeeds[nextg.leading_axis] = speedto0;
  }
    
  // now speedto0 is the maximum speed the primary in the next move can be going.  We need the equivalent speed of the primary in this move.
  speedto0 = (speedto0 * gcode.axisratio[nextg.leading_axis]);
  // If this move isn't moving the primary of the next move, then speedto0 will come out to 0.
  // This is obviously incorrect...
  if(speedto0 < labs(endspeeds[gcode.leading_axis]))
  {
#ifdef DEBUG_LAME
    HOST.labelnum("st0end:",speedto0);
    HOST.labelnum("end:",endspeeds[gcode.leading_axis]);
#endif
    endspeeds[gcode.leading_axis] = speedto0;
  }

#ifdef DEBUG_LAME
    HOST.labelnum("ef: ", gcode.endfeed, false);
    HOST.labelnum("sf: ", gcode.startfeed, false);
#endif    

  gcode.endfeed = max(gcode.endfeed,labs(endspeeds[gcode.leading_axis]));
  nextg.startfeed = max(nextg.startfeed,labs(startspeeds[nextg.leading_axis]));
  // because we only lookahead one move, our maximum exit speed has to be either the desired
  // exit speed or the speed that the next move can reach to 0 (0+jerk, actually) during.

  computeAccel(gcode, &nextg);

#endif // LOOKAHEAD
}