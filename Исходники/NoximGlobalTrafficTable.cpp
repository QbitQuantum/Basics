bool NoximGlobalTrafficTable::load(const char *fname)
{
  // Open file
  ifstream fin(fname, ios::in);
  if (!fin)
    return false;

  // Initialize variables
  traffic_table.clear();

  // Cycle reading file
  while (!fin.eof()) {
    char line[512];
    fin.getline(line, sizeof(line) - 1);

    if (line[0] != '\0') {
      if (line[0] != '%') {
	int src, dst;	// Mandatory
	float pir, por;
	int t_on, t_off, t_period;
	int t_use_lvp;

	int params =
	  sscanf(line, "%d %d %d %f %f %d %d %d", &src, &dst, &t_use_lvp, &pir,
		 &por, &t_on, &t_off, &t_period);
	if (params >= 2) {
	  // Create a communication from the parameters read on the line
	  NoximCommunication communication;

	  // Mandatory fields
	  communication.src = src;
	  communication.dst = dst;

	  // Use low voltage path
	  if (params >= 3 && t_use_lvp == 1)
	    communication.use_low_voltage_path = true;
	  else
	    communication.use_low_voltage_path = false;

	  // Custom PIR
	  if (params >= 4 && pir >= 0 && pir <= 1)
	    communication.pir = pir;
	  else
	    communication.pir =
	      NoximGlobalParams::packet_injection_rate;

	  // Custom POR
	  if (params >= 5 && por >= 0 && por <= 1)
	    communication.por = por;
	  else
	    communication.por = communication.pir;	// NoximGlobalParams::probability_of_retransmission;

	  // Custom Ton
	  if (params >= 6 && t_on >= 0)
	    communication.t_on = t_on;
	  else
	    communication.t_on = 0;

	  // Custom Toff
	  if (params >= 7 && t_off >= 0) {
	    assert(t_off > t_on);
	    communication.t_off = t_off;
	  } else
	    communication.t_off =
	      DEFAULT_RESET_TIME +
	      NoximGlobalParams::simulation_time;

	  // Custom Tperiod
	  if (params >= 8 && t_period > 0) {
	    assert(t_period > t_off);
	    communication.t_period = t_period;
	  } else
	    communication.t_period =
	      DEFAULT_RESET_TIME +
	      NoximGlobalParams::simulation_time;

	  // Add this communication to the vector of communications
	  traffic_table.push_back(communication);
	}
      }
    }
  }

  return true;
}