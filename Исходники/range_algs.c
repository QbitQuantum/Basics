float get_initial_range_guess(float bearing, float heading, uint8_t power){
	int8_t bestS = (6-((int8_t)ceilf((3.0*bearing)/M_PI)))%6;
	float alpha = pretty_angle(bearing - basis_angle[bestS]);				  //alpha using infinite approximation
	int8_t bestE = (6-((int8_t)ceilf((3.0*(bearing-heading-M_PI))/M_PI)))%6;					
	float  beta = pretty_angle(bearing - heading - basis_angle[bestE] - M_PI); //beta using infinite approximation	
	
	//printf("(alpha: %f, sensor %u)\r\n", rad_to_deg(alpha), bestS); 	
	if((alpha > M_PI_2) || (alpha < -M_PI_2)){
		printf("ERROR: alpha out of range (alpha: %f, sensor %u)\r\n", rad_to_deg(alpha), bestS); 
		return 0;
	}
	if((beta > M_PI_2)  || (beta < -M_PI_2)){
		printf("ERROR: beta out of range (beta: %f, emitter %u)\r\n",  beta, bestE); 
		return 0;
	}
	//printf("(beta: %f, emitter %u)\r\n",  rad_to_deg(beta), bestE); 	
	// expected contribution (using infinite distance approximation)
	float amplitude;
	float exp_con = sensor_model(alpha)*emitter_model(beta);
	
	if(exp_con > 0)	amplitude = brightMeas[bestE][bestS]/exp_con;	
	else{
		printf("ERROR: exp_con (%f) is negative (or zero)!\r\n", exp_con); 
		return 0;
	}
	//printf("amp_for_inv: %f\t",amplitude);
	float rMagEst = inverse_amplitude_model(amplitude, power);
	
	float RX = rMagEst*cos(bearing)+DROPLET_RADIUS*(bearingBasis[bestS][0]-headingBasis[bestE][0]);
	float RY = rMagEst*sin(bearing)+DROPLET_RADIUS*(bearingBasis[bestS][1]-headingBasis[bestE][1]);
	
	float rangeEst = hypotf(RX,RY);
	
	return rangeEst;
}