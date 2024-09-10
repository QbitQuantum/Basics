void TrackProgress::ReportState(char *my_state){
      time(&analysis_current_time);
      fprintf(stdout, "\n%s: Elapsed: %.1lf minutes\n\n", my_state, difftime(analysis_current_time, analysis_start_time) / 60);
      fprintf(fpLog, "%s = %.1lf minutes\n", my_state, difftime(analysis_current_time, analysis_start_time) / 60);
      fflush(NULL);
}