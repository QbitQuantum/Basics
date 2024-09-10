 inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
 {
     lp_lat = pj_authlat(asin( 2. * xy_y * this->m_par.k0 / this->m_proj_parm.qp), this->m_proj_parm.apa);
     lp_lon = xy_x / this->m_par.k0;
 }