 /**
 @brief  turn the duration into seconds unit
  the duration is using std::chrono::system_clock, 
  which the unit is in "microseconds..."
 
 @param d
 
 @return duration in second units...
 */
 static double duration_to_second(Clock::duration d){
     return d.count() / 1'000'000.0;
 }