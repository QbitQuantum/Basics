  double JointProb::probparam(double parameter, int thecoord, double maxd0sig   ) const
  {
    
    double prob = 0;
    double resolutionparameters[3][5];
    if (_ResolutionParameterRphi.size() != 5 || _ResolutionParameterZ.size() != 5 || _ResolutionParameter3D.size() != 5) 
    std::cerr << "Warning jointprob.cpp:229 Parameters of wrong length" << std::endl;
    for( int iii=0; iii<5; iii++)
    {
	resolutionparameters[0][iii] = _ResolutionParameterRphi[iii];
	resolutionparameters[1][iii] = _ResolutionParameterZ[iii];
	resolutionparameters[2][iii] = _ResolutionParameter3D[iii];
    }
    
    // The if statement takes into account a different parametrization for different coordinates. 
    if ( thecoord < 2 )
      {
	// part one is the gaussian part
	// to understand this part better one should look at the meaning of the complementary error function
	prob = erfc( parameter / (sqrt( double(2) ) * resolutionparameters[thecoord][0] ))
	  -erfc( maxd0sig / ( sqrt( double(2) ) *  resolutionparameters[thecoord][0] ) );
	
	// part 2 is the added exponential tails
      
      prob += resolutionparameters[thecoord][1]* ( exp(- resolutionparameters[thecoord][2] * parameter )
						   -exp(- resolutionparameters[thecoord][2] * maxd0sig ) )
	+resolutionparameters[thecoord][3]* ( exp(- resolutionparameters[thecoord][4] * parameter )
					      -exp(- resolutionparameters[thecoord][4] * maxd0sig ) );
      
      
      }
    else
      {
	
	//in this view the gaussian part is just squared. 
	
	prob = exp(- ( parameter * parameter ) /  ( resolutionparameters[thecoord][0] * resolutionparameters[thecoord][0] * double ( 2 ) ) ) 
	  -exp(- ( maxd0sig * maxd0sig )  /  ( resolutionparameters[thecoord][0] * resolutionparameters[thecoord][0] * double ( 2 ) ) );

	prob +=  resolutionparameters[thecoord][1]* ( ( 1 + resolutionparameters[thecoord][2] * parameter )
						      *exp ( - resolutionparameters[thecoord][2] * parameter )
						      - ( 1 + resolutionparameters[thecoord][2] * maxd0sig )
						      *exp ( - resolutionparameters[thecoord][2] * maxd0sig ))
	  +resolutionparameters[thecoord][3]* ( ( 1 + resolutionparameters[thecoord][4] * parameter )
						*exp ( - resolutionparameters[thecoord][4] * parameter )
						- ( 1 + resolutionparameters[thecoord][4] * maxd0sig )
						*exp ( - resolutionparameters[thecoord][4] * maxd0sig ));
	
      }

    return prob;
    
  }