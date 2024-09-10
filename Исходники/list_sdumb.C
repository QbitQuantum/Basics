local void print_star(hdyn *bi, bool bound, vec pos, vec vel,
		      real &Up, real &Bp, real &Vp, real &Rp, real &Ip, 
		      bool verbose) { 


  int id = bi->get_index();

  //  vec cod_vel = 0;
  //  bool bound = star_is_bound(bi, cod_vel);

  // To solar radii
  //  vec pos = bi->get_pos() - dc_pos;
  pos[0] = bi->get_starbase()->conv_r_dyn_to_star(pos[0]);
  pos[1] = bi->get_starbase()->conv_r_dyn_to_star(pos[1]);
  pos[2] = bi->get_starbase()->conv_r_dyn_to_star(pos[2]);

  real time = bi->get_starbase()->conv_t_dyn_to_star(bi->get_system_time());

  // And now to parsec
  real Rsun_per_parsec = cnsts.parameters(solar_radius)
                       / cnsts.parameters(parsec);
  pos[0] *= Rsun_per_parsec;
  pos[1] *= Rsun_per_parsec;
  pos[2] *= Rsun_per_parsec;

//  real to_Rsun_Myr = cnsts.physics(km_per_s) * cnsts.physics(Myear)
//               / cnsts.parameters(solar_radius);
                       
//      real to_Rsun_Myr = cnsts.physics(km_per_s) * cnsts.physics(Myear)
//	               / cnsts.parameters(solar_radius);
//                       
//      real to_dyn      = bi->get_starbase()->conv_r_star_to_dyn(1)
//                       / bi->get_starbase()->conv_t_star_to_dyn(1);
//      vel = vel/(to_Rsun_Myr * to_dyn);
                       
  real to_km_per_second = cnsts.parameters(solar_radius)
                        / (cnsts.physics(km_per_s) * cnsts.physics(Myear));
  real to_star      = bi->get_starbase()->conv_r_dyn_to_star(1)/
	              bi->get_starbase()->conv_t_dyn_to_star(1);
  to_km_per_second = to_star*to_km_per_second;

//	PRC(to_star);PRL(to_km_per_second);
  vel[0] *= to_km_per_second;
  vel[1] *= to_km_per_second;
  vel[2] *= to_km_per_second;

     star_type_spec tpe_class = NAC;
     spectral_class star_class;
     stellar_type stype = NAS;
     stellar_type_summary sstype = ZAMS;
     real t_cur, m_rel, m_env, m_core, mco_core, T_eff, L_eff, p_rot, b_fld;
     real t_rel=0, R_eff=0;
     real M_tot, Us, Bs, Vs, Rs, Is;	
     if (bi->get_use_sstar()) {
       	stype = bi->get_starbase()->get_element_type();
	M_tot  = bi->get_starbase()->conv_m_dyn_to_star(bi->get_mass());
        t_cur = bi->get_starbase()->get_current_time();
        t_rel = bi->get_starbase()->get_relative_age();
        T_eff = bi->get_starbase()->temperature();
        L_eff = bi->get_starbase()->get_luminosity();
        star_class = get_spectral_class(T_eff);
	R_eff = bi->get_starbase()->get_effective_radius();
	ltm_to_ubvri(log10(L_eff), log10(T_eff), M_tot,
		     Us, Bs, Vs, Rs, Is);

     }
     else if (bi->get_star_story()) {

       extract_story_chapter(stype, t_cur, t_rel, 
			     m_rel, m_env, m_core, mco_core,
			     T_eff, L_eff, p_rot, b_fld,
			     *bi->get_star_story());

       M_tot = m_env + m_core;
       sstype = summarize_stellar_type(stype);
       star_class = get_spectral_class(T_eff);
       
       ltm_to_ubvri(log10(L_eff), log10(T_eff), M_tot,
		     Us, Bs, Vs, Rs, Is);
       
       if (find_qmatch(bi->get_star_story(), "Class"))
	 tpe_class = extract_stellar_spec_summary_string(
             getsq(bi->get_star_story(), "Class"));
       if (L_eff>0)
          R_eff = pow(T_eff/cnsts.parameters(solar_temperature), 2)
	        * sqrt(L_eff);
     }
     else {
       cout << "    No stellar information found for: ";
       bi->pretty_print_node(cout);
       return;
     }

     real U, B, V, R, I;
     combine_ubvri(Up, Bp, Vp, Rp, Ip,
 	           Us, Bs, Vs, Rs, Is,
                   U, B, V, R, I);

     if(verbose)
       cout << " Time= " << time << " id= " << id << " b= " << bound 
	    << " type= " << stype << " m= " << M_tot << " R= " << R_eff
	    << " L= " << L_eff 
	    << " T_eff= " << T_eff 
	    << " r= "  << pos[0] << " " << pos[1] << " " << pos[2] 
	    << " v= "  << vel[0] << " " << vel[1] << " " << vel[2] 
	    << " ubvri= "<<  U << " " << B << " " << V << " " << R << " "
	    << I	<< " :: ";
     else {
       cout << time <<" "<< id << bound <<" "
	    <<" "<< stype <<" "
	    << M_tot <<" "<< R_eff <<" "<< L_eff  <<" "<< T_eff 
	    <<" "<< pos[0] << " " << pos[1] << " " << pos[2] 
	    <<" "<< vel[0] << " " << vel[1] << " " << vel[2] 
	    <<" "<< U << " " << B << " " << V << " " << R << " "
	    << I	<< " ";
       //       PRC(id);PRC(pos[0]);PRC(pos[1]);PRL(pos[2]);
     }

     Up=U;
     Bp=B;
     Vp=V;
     Ip=I;
}