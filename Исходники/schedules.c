/**
 * check the departure time
 * return True if the train should go
 */
Boolean checkScheduleTime( iILcDriverInt inst, const char* scheduleID, int scheduleIdx ) {
  iOLcDriverData data = Data(inst);
  Boolean go = False;
  iONode schedule = data->model->getSchedule( data->model, scheduleID );

  if( schedule != NULL ) {
    int idx = 0;
    int timeprocessing = wSchedule.gettimeprocessing(schedule);
    int timeframe      = wSchedule.gettimeframe(schedule);
    int fromhour       = wSchedule.getfromhour(schedule);
    int tohour         = wSchedule.gettohour(schedule);
    int maxdelay       = wSchedule.getmaxdelay(schedule);

    iONode entry = wSchedule.getscentry( schedule );

    /* check if the schedule index is correct: */
    while( entry != NULL ) {
      if( idx == scheduleIdx ) {
        long modeltime = data->model->getTime( data->model );
        struct tm* ltm;
        int modelminutes    = 0;
        int scheduleminutes = 0;
        int mins  = 0;
        int hours = 0;

        if( timeprocessing == wSchedule.time_relative ) {
          modeltime = modeltime - data->scheduletime;
          modelminutes = modeltime / 60;
          mins  = modelminutes % 60;
          hours = modelminutes / 60;
          TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203, "using relative time: modeltime=%d", modeltime );
        }
        else {
          ltm = localtime( &modeltime );
          hours = ltm->tm_hour;
          mins  = ltm->tm_min;
          TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203, "using real time: modeltime=%d", modeltime );
        }

        TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203, "modeltime %02d:%02d (%ld)",
            hours, mins, modeltime );

        scheduleminutes = wScheduleEntry.gethour(entry) * 60 + wScheduleEntry.getminute(entry);

        if(timeprocessing == wSchedule.time_hourly ) {
          TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203, "using hourly timing" );
          /* processing hourly timing */
          modelminutes = mins;
          if( hours < fromhour || tohour < hours ) {
            TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
                "current hour, %d, is not in the hourly range from %d to %d",
                hours, fromhour, tohour );
            scheduleminutes += 60;
          }
          else if( modelminutes > scheduleminutes && modelminutes - scheduleminutes > timeframe ) {
            TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
                "diff between schedule[%d] and model[%d] time is bigger then the allowed frame of %d; force wait for next hour...",
                scheduleminutes, modelminutes, timeframe );
            scheduleminutes += 60;
          }
        }
        else {
          modelminutes = hours * 60 + mins;
        }


        TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
            "check departure time schedule=%d model=%d index=%d",
            scheduleminutes, modelminutes, scheduleIdx );

        /* compare clock with departure time */
        if( scheduleminutes <= modelminutes ) {
          if( (modelminutes - scheduleminutes) <= maxdelay ) {
            TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
                "train must leave now %d <= %d and is delayed by %d minutes", scheduleminutes, modelminutes, modelminutes - scheduleminutes );
            go = True;
          }
          else {
            TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
                "train exceeded the max.(%d) delay time: %d", maxdelay, modelminutes - scheduleminutes );
          }
        }
        else {
          TraceOp.trc( name, TRCLEVEL_USER1, __LINE__, 4203,
              "train must wait %d > %d", scheduleminutes, modelminutes );
        }

        break;
      }
      idx++;
      entry = wSchedule.nextscentry( schedule, entry );
    };

  }
  else
    go = True;

  return go;
}