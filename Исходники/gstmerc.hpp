 inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
 {
     double L, LC, sinC;
     L= atan(sinh((xy_x*this->m_par.a - this->m_proj_parm.XS)/this->m_proj_parm.n2)/cos((xy_y*this->m_par.a - this->m_proj_parm.YS)/this->m_proj_parm.n2));
     sinC= sin((xy_y*this->m_par.a - this->m_proj_parm.YS)/this->m_proj_parm.n2)/cosh((xy_x*this->m_par.a - this->m_proj_parm.XS)/this->m_proj_parm.n2);
     LC= log(pj_tsfn(-1.0*asin(sinC),0.0,0.0));
     lp_lon= L/this->m_proj_parm.n1;
     lp_lat= -1.0*pj_phi2(exp((LC-this->m_proj_parm.c)/this->m_proj_parm.n1),this->m_par.e);
     /*fprintf(stderr,"inv:\nL      =%16.13f\nsinC   =%16.13f\nLC     =%16.13f\nXY(%16.4f,%16.4f)=LP(%16.13f,%16.13f)\n",L,sinC,LC,((xy_x/this->m_par.ra)+this->m_par.x0)/this->m_par.to_meter,((xy_y/this->m_par.ra)+this->m_par.y0)/this->m_par.to_meter,lp_lon+this->m_par.lam0,lp_lat);*/
 }