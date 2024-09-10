void schedule::check_flight(void)
{

   if ((airport.get_current_location() == &plane1) ||
         (airport.get_current_location() == &plane2) ||
           (airport.get_current_location() == &plane3) ||
             (airport.get_current_location() == &plane4)) 
   {
                                               // You must have a ticket
      if (!personal_items.item_here(ticket))
      {
         cout <<
         "Unfortunately, you don't have a ticket, you are arrested\n"
         "as a stowaway and drug off the plane screaming.  No vaca-\n"
         "tion for you.\n";
      }
      
                                            // On plane 1 from gate 1
      else if ((airport.get_current_location() == &plane1) &&
                                                      (my_gate != 0))
      {
         cout <<
         "Unfortunately, you are at gate 1 and this flight is going\n"
         " to " << destination[0] << ".  Better luck next time.\n";
      }
      
                                            // On plane 2 from gate 2
      else if ((airport.get_current_location() == &plane2) &&
                                                      (my_gate != 1))
      {
         cout <<
         "Unfortunately, you are at gate 2 and this flight is going\n"
         " to " << destination[1] << ".  Better luck next time.\n";
      }
      
                                            // On plane 3 from gate 3
      else if ((airport.get_current_location() == &plane3) &&
                                                      (my_gate != 2))
      {
         cout <<
         "Unfortunately, you are at gate 3 and this flight is going\n"
         " to " << destination[2] << ".  Better luck next time.\n";
      }
      
                                            // On plane 4 from gate 4
      else if ((airport.get_current_location() == &plane4) &&
                                                      (my_gate != 3))
      {
         cout <<
         "Unfortunately, you are at gate 4 and this flight is going\n"
         " to " << destination[3] << ".  Better luck next time.\n";
      }
      
                                               // You must be on time
      else if ((time_of_day.present_hour() > depart_hour[my_gate]) ||
               (time_of_day.present_minute() > depart_minute[my_gate]))
      {
         cout <<
         "Unfortunately, you are too late for your flight and are\n"
         "aboard a cargo plane to Greasy Creek, Missouri.  Better\n"
         "luck next time.\n";
      }
      
                                               // You must have candy
      else if (!personal_items.item_here(candy))
      {
         cout <<
         "Unfortunately, you failed to bring any food along and you\n"
         "died of malnutrition half way to your destination.\n";
      }

                                      // You must visit the rest room
      else if (!visited_rest_room)
      {
         cout <<
         "Unfortunately, you forgot to take care of your bladder\n"
         "problem back at the airport.  The restrooms on this plane\n"
         "are out-of-order.  You suffer a ruptured bladder and die\n"
         "enroute to your destination.\n";
      }

                             // A successful trip through the airport
      else
      {
         cout <<
         "Congratulations, you are comfortably enroute to your well\n"
         "deserved vacation.  You can study the source code to this\n"
         "program on the plane.  If you do not have the source code,\n"
         "you can read the paper in the lobby for the address where\n"
         "you can write for more information.\n";
      }

      input_words.stop_game();  // End the game
   }
}