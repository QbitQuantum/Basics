int get_many_sensor(int num_of_units, char *buff, int *last_sensor_req_time, int *approx_hit_time) {
	Putc(COM1, 128+num_of_units);
	//Printf(COM2, "get_many_sensor: Sensors requested\n\r");
	int i =0;
	int sensor_req_time = Time();
	for(i=0; i<2*num_of_units; i+=2) {
		buff[i] = Getc(COM1);
		buff[i+1] = Getc(COM1);
	}
	*approx_hit_time = ((*last_sensor_req_time + sensor_req_time + 1)/2);
	Putc(COM1, 192);
	*last_sensor_req_time = sensor_req_time; 
	return 0;
}