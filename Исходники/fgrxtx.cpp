void FGNetFDM2Props( FGNetFDM *net ) {
    unsigned int i;

    //if ( net_byte_order ) {
        // Convert to the net buffer from network format
        net->version = ntohl(net->version);

        htond(net->longitude);  // use
        htond(net->latitude);   // use 
        htond(net->altitude);   // use
        htonf(net->agl);
        htonf(net->phi);
        htonf(net->theta);
        htonf(net->psi);
        htonf(net->alpha);
        htonf(net->beta);

		///  custom- put ifdef around?
        htonf(net->p);		// use
        htonf(net->q);	// use
        htonf(net->r); 	// use


        htonf(net->phidot);		// use
        htonf(net->thetadot);	// use
        htonf(net->psidot); 	// use
        htonf(net->vcas);
        htonf(net->climb_rate);
        htonf(net->v_north);
        htonf(net->v_east);
        htonf(net->v_down);
        htonf(net->v_wind_body_north);
        htonf(net->v_wind_body_east);
        htonf(net->v_wind_body_down);

        htonf(net->A_X_pilot);	// use
        htonf(net->A_Y_pilot);  // use
        htonf(net->A_Z_pilot);	// use

        htonf(net->stall_warning);
        htonf(net->slip_deg);

}