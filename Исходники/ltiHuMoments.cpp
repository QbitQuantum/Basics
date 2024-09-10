  // On copy apply for type channel!
  bool huMoments::apply(const channel& src,dvector& dest, dvector& more) const {
    channel::value_type val;

    dest.resize(NUM_FEAT,0,false,true);
    more.resize(MORE_FEAT,0,false,true);

    double m00=0.0;
    double cm11,cm20,cm02,cm30,cm03,cm12,cm21;
    cm11=cm20=cm02=cm30=cm03=cm12=cm21=0.0;
    double xcog, ycog;
    xcog=ycog=0.0;

    int r, rows=src.rows();
    int c, cols=src.columns();

    // compute simple moments and cog
    for (r=0; r<rows; r++) {
      for (c=0; c<cols; c++) {
        val = src.at(r,c);
        m00+=val;
        xcog+=c*val;
        ycog+=r*val;
      }
    }

    // end here, if no content
    if (m00==0) {
      return false;
    }

    // compute cog's
    more[huMoments::xcog]=xcog=xcog/m00;  //xcog
    more[huMoments::ycog]=ycog=ycog/m00;  //ycog

    // compute central moments
    for (r=0; r<rows; r++) {
      for (c=0; c<cols; c++) {
        val = src.at(r,c);
        double x_xcog = c-xcog;
        double y_ycog = r-ycog;
        cm11+=(x_xcog)*(y_ycog)*val;
        cm20+=(x_xcog)*(x_xcog)*val;
        cm02+=(y_ycog)*(y_ycog)*val;
        cm30+=(x_xcog)*(x_xcog)*(x_xcog)*val;
        cm03+=(y_ycog)*(y_ycog)*(y_ycog)*val;
        cm12+=(x_xcog)*(y_ycog)*(y_ycog)*val;
        cm21+=(x_xcog)*(x_xcog)*(y_ycog)*val;
      }
    }

    double m00pow2,m00pow2_5;
    m00pow2 = m00*m00;
    m00pow2_5 = pow(m00,2.5);
    // normalized central moments
    cm02 = cm02/m00pow2;
    cm03 = cm03/m00pow2_5;
    cm11 = cm11/m00pow2;
    cm12 = cm12/m00pow2_5;
    cm20 = cm20/m00pow2;
    cm21 = cm21/m00pow2_5;
    cm30 = cm30/m00pow2_5;

    // calculate moment invariants
    dest[huMoments::hu1] = cm20 + cm02;
    dest[huMoments::hu2] = pow((cm20 - cm02),2) + 4*pow(cm11,2);
    dest[huMoments::hu3] = pow((cm30 - 3*cm12),2) + pow((3*cm21 - cm03),2);
    dest[huMoments::hu4] = pow((cm30 + cm12),2) + pow((cm21 + cm03),2);
    dest[huMoments::hu5] = (cm30-3*cm12)*(cm30+cm12)*(   pow((cm30+cm12),2) - 3*pow((cm21+cm03),2) )
                         + (3*cm21-cm03)*(cm21+cm03)*( 3*pow((cm30+cm12),2) -   pow((cm21+cm03),2) );
    dest[huMoments::hu6] = (cm20-cm02)*( pow((cm30+cm12),2) - pow((cm21+cm03),2) )
                         + 4*cm11*(cm30+cm12)*(cm21+cm03);
    dest[huMoments::hu7] = (3*cm21-cm03)*(cm30+cm12)*(   pow((cm30+cm12),2) - 3*pow((cm21+cm03),2) )
                         - (cm30-3*cm12)*(cm21+cm03)*( 3*pow((cm30+cm12),2) -   pow((cm21+cm03),2) );


    double temp = sqrt( (cm20 - cm02)*(cm20 - cm02) + 4*cm11*cm11 );
    more[huMoments::eigen1]=m00*0.5*((cm20+cm02) + temp); //eigen 1
    more[huMoments::eigen2]=m00*0.5*((cm20+cm02) - temp); //eigen 2
    more[huMoments::orientation]=0.5*atan2(2*cm11, cm20 - cm02); //orientation
    more[huMoments::m00]=m00; //m00

    const parameters& param = getParameters();

    if (param.scaling) {
      int i;
      for (i=0; i<dest.size();i++){
        dest[i]=-logn(dest[i]);
      }
    }

    return true;
  }