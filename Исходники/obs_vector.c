bool obs_vector_load_from_HISTORY_OBSERVATION(obs_vector_type * obs_vector ,
                                              const conf_instance_type * conf_instance ,
                                              time_map_type * obs_time ,
                                              const history_type * history ,
                                              ensemble_config_type * ensemble_config,
                                              double std_cutoff ) {

  if(!conf_instance_is_of_class(conf_instance, "HISTORY_OBSERVATION"))
    util_abort("%s: internal error. expected \"HISTORY_OBSERVATION\" instance, got \"%s\".\n",__func__, conf_instance_get_class_name_ref(conf_instance) );

  {
    bool initOK = false;
    int          size , restart_nr;
    double_vector_type * value              = double_vector_alloc(0,0);
    double_vector_type * std                = double_vector_alloc(0,0);
    bool_vector_type   * valid              = bool_vector_alloc(0 , false);

    /* The auto_corrf parameters can not be "segmentized" */
    double auto_corrf_param                 = -1;
    const char * auto_corrf_name            = NULL;


    double         error      = conf_instance_get_item_value_double(conf_instance, "ERROR"     );
    double         error_min  = conf_instance_get_item_value_double(conf_instance, "ERROR_MIN" );
    const char *   error_mode = conf_instance_get_item_value_ref(   conf_instance, "ERROR_MODE");
    const char *   sum_key    = conf_instance_get_name_ref(         conf_instance              );

    if(conf_instance_has_item(conf_instance, "AUTO_CORRF")) {
      auto_corrf_name  = conf_instance_get_item_value_ref( conf_instance , "AUTO_CORRF");
      auto_corrf_param = conf_instance_get_item_value_double(conf_instance, "AUTO_CORRF_PARAM");
      if(conf_instance_has_item(conf_instance, "AUTO_CORRF_PARAM"))
        auto_corrf_param = conf_instance_get_item_value_double(conf_instance, "AUTO_CORRF_PARAM");
      else
        util_abort("%s: When specifying AUTO_CORRF you must also give a vlaue for AUTO_CORRF_PARAM",__func__);
    }


    // Get time series data from history object and allocate
    size = time_map_get_last_step( obs_time );
    if (history_init_ts( history , sum_key , value , valid )) {

      // Create  the standard deviation vector
      if(strcmp(error_mode, "ABS") == 0) {
        for( restart_nr = 0; restart_nr < size; restart_nr++)
          double_vector_iset( std , restart_nr , error );
      } else if(strcmp(error_mode, "REL") == 0) {
        for( restart_nr = 0; restart_nr < size; restart_nr++)
          double_vector_iset( std , restart_nr , error * abs( double_vector_iget( value , restart_nr )));
      } else if(strcmp(error_mode, "RELMIN") == 0) {
        for(restart_nr = 0; restart_nr < size; restart_nr++) {
          double tmp_std = util_double_max( error_min , error * abs( double_vector_iget( value , restart_nr )));
          double_vector_iset( std , restart_nr , tmp_std);
        }
      } else
        util_abort("%s: Internal error. Unknown error mode \"%s\"\n", __func__, error_mode);


      // Handle SEGMENTs which can be used to customize the observation error. */
      {
        stringlist_type * segment_keys = conf_instance_alloc_list_of_sub_instances_of_class_by_name(conf_instance, "SEGMENT");
        stringlist_sort( segment_keys , NULL );

        int num_segments = stringlist_get_size(segment_keys);

        for(int segment_nr = 0; segment_nr < num_segments; segment_nr++)
          {
            const char * segment_name = stringlist_iget(segment_keys, segment_nr);
            const conf_instance_type * segment_conf = conf_instance_get_sub_instance_ref(conf_instance, segment_name);

            int start                         = conf_instance_get_item_value_int(   segment_conf, "START"     );
            int stop                          = conf_instance_get_item_value_int(   segment_conf, "STOP"      );
            double         error_segment      = conf_instance_get_item_value_double(segment_conf, "ERROR"     );
            double         error_min_segment  = conf_instance_get_item_value_double(segment_conf, "ERROR_MIN" );
            const char *   error_mode_segment = conf_instance_get_item_value_ref(   segment_conf, "ERROR_MODE");

            if(start < 0)
              {
                printf("%s: WARNING - Segment out of bounds. Truncating start of segment to 0.\n", __func__);
                start = 0;
              }

            if(stop >= size)
              {
                printf("%s: WARNING - Segment out of bounds. Truncating end of segment to %d.\n", __func__, size - 1);
                stop = size -1;
              }

            if(start > stop)
              {
                printf("%s: WARNING - Segment start after stop. Truncating end of segment to %d.\n", __func__, start );
                stop = start;
              }

            // Create  the standard deviation vector
            if(strcmp(error_mode_segment, "ABS") == 0) {
              for( restart_nr = start; restart_nr <= stop; restart_nr++)
                double_vector_iset( std , restart_nr , error_segment) ;
            } else if(strcmp(error_mode_segment, "REL") == 0) {
              for( restart_nr = start; restart_nr <= stop; restart_nr++)
                double_vector_iset( std , restart_nr , error_segment * abs(double_vector_iget( value , restart_nr)));
            } else if(strcmp(error_mode_segment, "RELMIN") == 0) {
              for(restart_nr = start; restart_nr <= stop ; restart_nr++) {
                double tmp_std = util_double_max( error_min_segment , error_segment * abs( double_vector_iget( value , restart_nr )));
                double_vector_iset( std , restart_nr , tmp_std);
              }
            } else
              util_abort("%s: Internal error. Unknown error mode \"%s\"\n", __func__, error_mode);
          }
        stringlist_free(segment_keys);
      }


      /*
        This is where the summary observations are finally added.
      */
      for (restart_nr = 0; restart_nr < size; restart_nr++) {
        if (bool_vector_safe_iget( valid , restart_nr)) {
          if (double_vector_iget( std , restart_nr) > std_cutoff) {
            obs_vector_add_summary_obs( obs_vector , restart_nr , sum_key , sum_key ,
                                        double_vector_iget( value ,restart_nr) , double_vector_iget( std , restart_nr ) ,
                                        auto_corrf_name , auto_corrf_param);
          } else
            fprintf(stderr,"** Warning: to small observation error in observation %s:%d - ignored. \n", sum_key , restart_nr);
        }
      }
      initOK = true;
    }
    double_vector_free(std);
    double_vector_free(value);
    bool_vector_free(valid);
    return initOK;
  }
}