void printline(report_parsed_data_t *recived){
    printf("%15.2f %10s %10s %10s %10s\n", recived->temperature, YN( recived->pre_heat ), YN( recived->is_heating ), YN( recived->is_cooling ), YN( recived->reached_temp ));

}