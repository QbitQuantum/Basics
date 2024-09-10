void Controller_StateMachine_v2::processTurn() {	// "during:"

	// 1º proyectar posicion sobre el plano r_ur, r_ur2
	Vector aux_ur2(3), aux_vector(3);
	aux_vector.copy(&r_ur);
	jesus_library::multiplyDoubleVsVector( jesus_library::dotProduct(r_ur, r_ur2), aux_vector );
	aux_ur2.substraction( &r_ur2, &aux_vector);
	jesus_library::unitarizeVector(aux_ur2); // vector ortogonal a r_ur; para formar base ortonormal en el plano r_ur, r_ur2

	Vector pos_act(3);
	pos_act.setValueData(xei,1);
	pos_act.setValueData(yei,2);
	pos_act.setValueData(zei,3);

	aux_vector.substraction( &pos_act, &c_pc);
	Vector pos_act_proy_ur(3),pos_act_proy_ur2(3);
	pos_act_proy_ur.copy(&r_ur);
	pos_act_proy_ur2.copy(&aux_ur2);

	jesus_library::multiplyDoubleVsVector( jesus_library::dotProduct(r_ur, aux_vector), pos_act_proy_ur );
	jesus_library::multiplyDoubleVsVector( jesus_library::dotProduct(aux_ur2, aux_vector), pos_act_proy_ur2 );

	Vector pos_act_proy(3);
	pos_act_proy.addition( &pos_act_proy_ur, &pos_act_proy_ur2);
	cvg_double current_radius = jesus_library::normOfVector(pos_act_proy);

	#ifdef SM_STATEMACHINE_DEBUG
	std::cout << "c_pc = \n"; c_pc.mostrar();
	std::cout << "c_pinit = \n"; c_pinit.mostrar();
	std::cout << "c_pend = \n"; c_pend.mostrar();
	std::cout << "pos_act_proy = \n"; pos_act_proy.mostrar();
	#endif // SM_STATEMACHINE_DEBUG

	// 2º localizar pref
	Vector u_ro(3);
	u_ro.copy(&pos_act_proy);
	jesus_library::unitarizeVector(u_ro);
	aux_vector.copy(&u_ro);
	jesus_library::multiplyDoubleVsVector( c_Rt, aux_vector);
	Vector pos_ref(3);
	pos_ref.addition(&c_pc, &aux_vector);
	jesus_library::getVectorComponents(pos_ref, xrefo, yrefo, zrefo);
	cvg_double current_altitude_error = (zei-zrefo); // fabs(zei-zrefo);

	// 3º calcular velocidad de referencia
	Vector u_fi(3);
	jesus_library::crossProduct(u_fi, c_u0, u_ro);
	jesus_library::unitarizeVector(u_fi);
	Vector v_ref(3);
	v_ref.copy(&u_fi);
	jesus_library::multiplyDoubleVsVector(c_vc, v_ref);
	jesus_library::getVectorComponents(v_ref, vxfo, vyfo, vzfo);


//	// 4º Calcular pitcho, rollo
	derivBlock_vxfo.setInput( vxfo);
	dvxfo = derivBlock_vxfo.getOutput();
	derivBlock_vyfo.setInput( vyfo);
	dvyfo = derivBlock_vyfo.getOutput();
#ifdef SM_TRAJECTORYMODE_ACTIVATE_TILTFO
	double g = 9.81;
	pitchfo  = -asin( (cvg_double) dvxfo/g);
	rollfo   =  asin( (cvg_double) dvyfo/g);
	pitchfo *= 1/SM_TRAJECTORYMODE_TILTFO_RAD2TILTREF;
	rollfo  *= 1/SM_TRAJECTORYMODE_TILTFO_RAD2TILTREF;
#else
	pitchfo = 0.0;
	rollfo  = 0.0;
#endif
//  // This is a code that never work that was intended to stop the parrot in it's current position
//	double v_act = sqrt( vxei*vxei + vyei*vyei + vzei*vzei );
//	double act_req  = pow(v_act,2)/c_Rt;
//	double tilt_req = act_req/SM_STATEMACHINE_G;
//	aux_vector.copy(&u_ro);
//	jesus_library::multiplyDoubleVsVector( -tilt_req, aux_vector);
//	aux_vector.setValueData( 0.0, 3);
//
//	Vector parrot_ux(3), parrot_uy(3);
//	parrot_ux.setValueData( cos(yawei), 1);
//	parrot_ux.setValueData( sin(yawei), 2);
//	parrot_uy.setValueData(-sin(yawei), 1);
//	parrot_uy.setValueData( cos(yawei), 2);
//
//	pitchfo = -jesus_library::dotProduct( parrot_ux, aux_vector)*SM_STATEMACHINE_TILTCOMM_CORRECT_FACTOR;
//	rollfo  =  jesus_library::dotProduct( parrot_uy, aux_vector)*SM_STATEMACHINE_TILTCOMM_CORRECT_FACTOR;
//	pitchfo /= SM_STATEMACHINE_TILTCOMM_NORMALIZATION_CONSTANT;
//	rollfo  /= SM_STATEMACHINE_TILTCOMM_NORMALIZATION_CONSTANT;

	// 5º Calculo de alpha y comparacion con c_alim
	Vector aux_vector2(3);
	aux_vector.substraction(&c_pinit,&c_pc);
	jesus_library::unitarizeVector(aux_vector);
	cvg_double aux = jesus_library::dotProduct(u_ro, aux_vector);
	jesus_library::saturate( aux, -1, 1);
	jesus_library::crossProduct(aux_vector2, aux_vector, u_ro);
	cvg_double angle_sign = ( jesus_library::dotProduct(c_u0, aux_vector2) > 0.0 ) ? +1.0 : -1.0;
	cvg_double current_alpha = angle_sign*acos(aux);

	#ifdef SM_STATEMACHINE_DEBUG
	std::cout << "c_alim = " << c_alim << "; alpha = " << current_alpha << "\n";
	#endif // SM_STATEMACHINE_DEBUG

	if ( current_alpha > c_alim) {  // ended the turn
		c_nextState = SM_stateNames::STRAIGHT;
		c_changeState = true;
		return;
	} else {  // turn not ended, check safety zones using: current_radius, current_alpha
		if ( ( current_alpha < trajectory.traj_config.turnmode_safetyzone_negalpha_rad ) ||
				( fabs(current_radius - c_Rt) > trajectory.traj_config.turnmode_safetyzone_radius_m ) ||
				( fabs(current_altitude_error) > trajectory.traj_config.turnmode_safetyzone_altitude_m ) ) { // enter hover to prev checkpoint
#ifdef SM_STATEMACHINE_DEBUG
			std::cout << "pos_act_proy_ur < 0\n";
#endif // SM_STATEMACHINE_DEBUG
			trajectory[pr_checkpoint].convert2Vector(h_checkpoint);
			c_nextState = SM_stateNames::HOVER;
			h_stay_in_last_checkpoint = false;
			c_changeState = true;

			// In this case I have to redefine the state machine output
			jesus_library::getVectorComponents(h_checkpoint, xrefo, yrefo, zrefo);
			vxfo = 0.0;
			vyfo = 0.0;
			vzfo = 0.0;
			pitchfo = 0.0;
			rollfo  = 0.0;

			return;
		} else { // Continue turn, nothing else to do
			return;
		}
	}

}