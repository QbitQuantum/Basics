/*!
  multiple quality measures of a quad
*/
C_FUNC_DEF void v_quad_quality( int num_nodes, VERDICT_REAL coordinates[][3], 
    unsigned int metrics_request_flag, QuadMetricVals *metric_vals )
{

  memset( metric_vals, 0, sizeof(QuadMetricVals) );

  // for starts, lets set up some basic and common information

  /*  node numbers and side numbers used below

                  2
            3 +--------- 2
             /         +
            /          |
         3 /           | 1
          /            |
         +             |
       0 -------------+ 1
             0
  */
  
  // vectors for each side
  VerdictVector edges[4];
  make_quad_edges( edges, coordinates );

  double areas[4]; 
  signed_corner_areas( areas, coordinates );

  double lengths[4];
  lengths[0] = edges[0].length();
  lengths[1] = edges[1].length();
  lengths[2] = edges[2].length();
  lengths[3] = edges[3].length();

  VerdictBoolean is_collapsed = is_collapsed_quad(coordinates);

  // handle collapsed quads metrics here
  if(is_collapsed == VERDICT_TRUE && metrics_request_flag & 
      ( V_QUAD_MINIMUM_ANGLE | V_QUAD_MAXIMUM_ANGLE | V_QUAD_JACOBIAN |
        V_QUAD_SCALED_JACOBIAN ))
  {
    if(metrics_request_flag & V_QUAD_MINIMUM_ANGLE)
      metric_vals->minimum_angle = v_tri_minimum_angle(3, coordinates);
    if(metrics_request_flag & V_QUAD_MAXIMUM_ANGLE)
      metric_vals->maximum_angle = v_tri_maximum_angle(3, coordinates);
    if(metrics_request_flag & V_QUAD_JACOBIAN)
      metric_vals->jacobian = (VERDICT_REAL)(v_tri_area(3, coordinates) * 2.0);
    if(metrics_request_flag & V_QUAD_SCALED_JACOBIAN)
      metric_vals->jacobian = (VERDICT_REAL)(v_tri_scaled_jacobian(3, coordinates) * 2.0);
  }
  
  // calculate both largest and smallest angles
  if(metrics_request_flag & (V_QUAD_MINIMUM_ANGLE | V_QUAD_MAXIMUM_ANGLE) 
      && is_collapsed == VERDICT_FALSE )
  {
    // gather the angles
    double angles[4];
    angles[0] = acos( -(edges[0] % edges[1])/(lengths[0]*lengths[1]) );
    angles[1] = acos( -(edges[1] % edges[2])/(lengths[1]*lengths[2]) );
    angles[2] = acos( -(edges[2] % edges[3])/(lengths[2]*lengths[3]) );
    angles[3] = acos( -(edges[3] % edges[0])/(lengths[3]*lengths[0]) );

    if( lengths[0] <= VERDICT_DBL_MIN ||
        lengths[1] <= VERDICT_DBL_MIN ||
        lengths[2] <= VERDICT_DBL_MIN ||
        lengths[3] <= VERDICT_DBL_MIN )
    {
      metric_vals->minimum_angle = 360.0;
      metric_vals->maximum_angle = 0.0;
    }
    else
    {
      // if smallest angle, find the smallest angle
      if(metrics_request_flag & V_QUAD_MINIMUM_ANGLE)
      {
        metric_vals->minimum_angle = VERDICT_DBL_MAX;
        for(int i = 0; i<4; i++)
          metric_vals->minimum_angle = VERDICT_MIN(angles[i], metric_vals->minimum_angle);
        metric_vals->minimum_angle *= 180.0 / VERDICT_PI;
      }
      // if largest angle, find the largest angle
      if(metrics_request_flag & V_QUAD_MAXIMUM_ANGLE)
      {
        metric_vals->maximum_angle = 0.0;
        for(int i = 0; i<4; i++)
          metric_vals->maximum_angle = VERDICT_MAX(angles[i], metric_vals->maximum_angle);
        metric_vals->maximum_angle *= 180.0 / VERDICT_PI;

        if( areas[0] < 0 || areas[1] < 0 || 
            areas[2] < 0 || areas[3] < 0 )
          metric_vals->maximum_angle = 360 - metric_vals->maximum_angle;
      }
    }
  }

  // handle aspect, skew, taper, and area together
  if( metrics_request_flag & ( V_QUAD_ASPECT | V_QUAD_SKEW | V_QUAD_TAPER ) )
  {
    //get principle axes
    VerdictVector principal_axes[2];
    principal_axes[0] = edges[0] - edges[2];
    principal_axes[1] = edges[1] - edges[3];

    if(metrics_request_flag & (V_QUAD_ASPECT | V_QUAD_SKEW | V_QUAD_TAPER))
    {
      double len1 = principal_axes[0].length();
      double len2 = principal_axes[1].length();

      // calculate the aspect ratio 
      if(metrics_request_flag & V_QUAD_ASPECT)
      {
        if( len1 < VERDICT_DBL_MIN || len2 < VERDICT_DBL_MIN )
          metric_vals->aspect = VERDICT_DBL_MAX;
        else
          metric_vals->aspect = VERDICT_MAX( len1 / len2, len2 / len1 );
      }
    
      // calculate the taper
      if(metrics_request_flag & V_QUAD_TAPER)
      {
        double min_length = VERDICT_MIN( len1, len2 );

        VerdictVector cross_derivative = edges[1] + edges[3]; 

        if( min_length < VERDICT_DBL_MIN )
          metric_vals->taper = VERDICT_DBL_MAX;
        else
          metric_vals->taper = cross_derivative.length()/ min_length;
      }
      
      // calculate the skew 
      if(metrics_request_flag & V_QUAD_SKEW)
      {
        if( principal_axes[0].normalize() < VERDICT_DBL_MIN ||
            principal_axes[1].normalize() < VERDICT_DBL_MIN )
          metric_vals->skew = 0.0; 
        else
          metric_vals->skew = fabs( principal_axes[0] % principal_axes[1] );
      }
    }
  }

  // calculate the area
  if(metrics_request_flag & (V_QUAD_AREA | V_QUAD_RELATIVE_SIZE_SQUARED) )
  {
    metric_vals->area = 0.25 * (areas[0] + areas[1] + areas[2] + areas[3]);
  }

  // calculate the relative size 
  if(metrics_request_flag & (V_QUAD_RELATIVE_SIZE_SQUARED | V_QUAD_SHAPE_AND_SIZE |
                             V_QUAD_SHEAR_AND_SIZE ) )
  {
    double quad_area = v_quad_area (4, coordinates); 
    v_set_quad_size( quad_area );
    double w11,w21,w12,w22;
    get_weight(w11,w21,w12,w22);
    double avg_area = determinant(w11,w21,w12,w22);

    if( avg_area < VERDICT_DBL_MIN )
      metric_vals->relative_size_squared = 0.0;
    else
      metric_vals->relative_size_squared =  pow( VERDICT_MIN( 
                                              metric_vals->area/avg_area,  
                                              avg_area/metric_vals->area ), 2 );
  }

  // calculate the jacobian
  if(metrics_request_flag & V_QUAD_JACOBIAN)
  {
    metric_vals->jacobian = VERDICT_MIN(
                              VERDICT_MIN( areas[0], areas[1] ),
                              VERDICT_MIN( areas[2], areas[3] ) );
  }

  if( metrics_request_flag & ( V_QUAD_SCALED_JACOBIAN | V_QUAD_SHEAR | V_QUAD_SHEAR_AND_SIZE ) )
  {
    double scaled_jac, min_scaled_jac = VERDICT_DBL_MAX;
    
    if( lengths[0] < VERDICT_DBL_MIN ||
        lengths[1] < VERDICT_DBL_MIN ||
        lengths[2] < VERDICT_DBL_MIN ||
        lengths[3] < VERDICT_DBL_MIN )
    {
      metric_vals->scaled_jacobian = 0.0;  
      metric_vals->shear = 0.0;  
    }
    else
    {
      scaled_jac = areas[0] / (lengths[0] * lengths[3]);
      min_scaled_jac = VERDICT_MIN( scaled_jac, min_scaled_jac );

      scaled_jac = areas[1] / (lengths[1] * lengths[0]);
      min_scaled_jac = VERDICT_MIN( scaled_jac, min_scaled_jac );

      scaled_jac = areas[2] / (lengths[2] * lengths[1]);
      min_scaled_jac = VERDICT_MIN( scaled_jac, min_scaled_jac );

      scaled_jac = areas[3] / (lengths[3] * lengths[2]);
      min_scaled_jac = VERDICT_MIN( scaled_jac, min_scaled_jac );

      metric_vals->scaled_jacobian = min_scaled_jac;
     
      //what the heck...set shear as well 
      if( min_scaled_jac <= VERDICT_DBL_MIN )
        metric_vals->shear = 0.0;
      else
        metric_vals->shear = min_scaled_jac;
    }
  }

  if( metrics_request_flag & (V_QUAD_WARPAGE | V_QUAD_ODDY) )
  {
    VerdictVector corner_normals[4];
    corner_normals[0] = edges[3] * edges[0];
    corner_normals[1] = edges[0] * edges[1];
    corner_normals[2] = edges[1] * edges[2];
    corner_normals[3] = edges[2] * edges[3];

    if( metrics_request_flag & V_QUAD_ODDY )
    {
      double oddy, max_oddy = 0.0;

      double diff, dot_prod;

      double length_squared[4];
      length_squared[0] = corner_normals[0].length_squared();
      length_squared[1] = corner_normals[1].length_squared();
      length_squared[2] = corner_normals[2].length_squared();
      length_squared[3] = corner_normals[3].length_squared();

      if( length_squared[0] < VERDICT_DBL_MIN ||
          length_squared[1] < VERDICT_DBL_MIN ||
          length_squared[2] < VERDICT_DBL_MIN ||
          length_squared[3] < VERDICT_DBL_MIN )
       metric_vals->oddy = VERDICT_DBL_MAX; 
      else
      {
        diff = (lengths[0]*lengths[0]) - (lengths[1]*lengths[1]);
        dot_prod = edges[0]%edges[1];
        oddy = ((diff*diff) + 4*dot_prod*dot_prod ) / (2*length_squared[1]);
        max_oddy = VERDICT_MAX( oddy, max_oddy );

        diff = (lengths[1]*lengths[1]) - (lengths[2]*lengths[2]);
        dot_prod = edges[1]%edges[2];
        oddy = ((diff*diff) + 4*dot_prod*dot_prod ) / (2*length_squared[2]);
        max_oddy = VERDICT_MAX( oddy, max_oddy );

        diff = (lengths[2]*lengths[2]) - (lengths[3]*lengths[3]);
        dot_prod = edges[2]%edges[3];
        oddy = ((diff*diff) + 4*dot_prod*dot_prod ) / (2*length_squared[3]);
        max_oddy = VERDICT_MAX( oddy, max_oddy );

        diff = (lengths[3]*lengths[3]) - (lengths[0]*lengths[0]);
        dot_prod = edges[3]%edges[0];
        oddy = ((diff*diff) + 4*dot_prod*dot_prod ) / (2*length_squared[0]);
        max_oddy = VERDICT_MAX( oddy, max_oddy );

        metric_vals->oddy = max_oddy;
      }
    }

    if( metrics_request_flag & V_QUAD_WARPAGE )
    {
      if( corner_normals[0].normalize() < VERDICT_DBL_MIN ||
          corner_normals[1].normalize() < VERDICT_DBL_MIN ||
          corner_normals[2].normalize() < VERDICT_DBL_MIN ||
          corner_normals[3].normalize() < VERDICT_DBL_MIN )
        metric_vals->warpage = VERDICT_DBL_MAX;
      else 
      {
        metric_vals->warpage = pow( 
                             VERDICT_MIN( corner_normals[0]%corner_normals[2],
                                          corner_normals[1]%corner_normals[3]), 3 ); 
      }
    }
  }

  if( metrics_request_flag & V_QUAD_STRETCH )
  {
    VerdictVector temp;

    temp.set( coordinates[2][0] - coordinates[0][0],
              coordinates[2][1] - coordinates[0][1],
              coordinates[2][2] - coordinates[0][2]);
    double diag02 = temp.length_squared();

    temp.set( coordinates[3][0] - coordinates[1][0],
              coordinates[3][1] - coordinates[1][1],
              coordinates[3][2] - coordinates[1][2]);
    double diag13 = temp.length_squared();
    
    static const double QUAD_STRETCH_FACTOR = sqrt(2.0);

    // 'diag02' is now the max diagonal of the quad
    diag02 = VERDICT_MAX( diag02, diag13 );

    if( diag02 < VERDICT_DBL_MIN )
      metric_vals->stretch = VERDICT_DBL_MAX; 
    else
      metric_vals->stretch =  QUAD_STRETCH_FACTOR *
                              VERDICT_MIN(
                                VERDICT_MIN( lengths[0], lengths[1] ),
                                VERDICT_MIN( lengths[2], lengths[3] ) ) /
                              sqrt(diag02);
  }

  if(metrics_request_flag & (V_QUAD_CONDITION | V_QUAD_SHAPE | V_QUAD_SHAPE_AND_SIZE ) )
  {
    double lengths_squared[4];
    lengths_squared[0] = edges[0].length_squared();
    lengths_squared[1] = edges[1].length_squared();
    lengths_squared[2] = edges[2].length_squared();
    lengths_squared[3] = edges[3].length_squared();

    if( areas[0] < VERDICT_DBL_MIN ||
        areas[1] < VERDICT_DBL_MIN ||
        areas[2] < VERDICT_DBL_MIN ||
        areas[3] < VERDICT_DBL_MIN )
    {
      metric_vals->condition = VERDICT_DBL_MAX;
      metric_vals->shape= VERDICT_DBL_MAX;
    }
    else
    {
      double max_condition = 0.0, condition;

      condition = (lengths_squared[0] + lengths_squared[3])/areas[0];
      max_condition = VERDICT_MAX( max_condition, condition ); 

      condition = (lengths_squared[1] + lengths_squared[0])/areas[1];
      max_condition = VERDICT_MAX( max_condition, condition ); 
     
      condition = (lengths_squared[2] + lengths_squared[1])/areas[2];
      max_condition = VERDICT_MAX( max_condition, condition ); 

      condition = (lengths_squared[3] + lengths_squared[2])/areas[3];
      max_condition = VERDICT_MAX( max_condition, condition ); 

      metric_vals->condition = 0.5*max_condition;
      metric_vals->shape =  2/max_condition;
    }
  } 

  if(metrics_request_flag & V_QUAD_AREA )
  {
    if( metric_vals->area > 0 ) 
      metric_vals->area = (VERDICT_REAL) VERDICT_MIN( metric_vals->area, VERDICT_DBL_MAX );
    metric_vals->area = (VERDICT_REAL) VERDICT_MAX( metric_vals->area, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_ASPECT )
  {
    if( metric_vals->aspect > 0 ) 
      metric_vals->aspect = (VERDICT_REAL) VERDICT_MIN( metric_vals->aspect, VERDICT_DBL_MAX );
    metric_vals->aspect = (VERDICT_REAL) VERDICT_MAX( metric_vals->aspect, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_CONDITION )
  {
    if( metric_vals->condition > 0 ) 
      metric_vals->condition = (VERDICT_REAL) VERDICT_MIN( metric_vals->condition, VERDICT_DBL_MAX );
    metric_vals->condition = (VERDICT_REAL) VERDICT_MAX( metric_vals->condition, -VERDICT_DBL_MAX );
  }

  // calculate distortion
  if(metrics_request_flag & V_QUAD_DISTORTION)
  {
    metric_vals->distortion = v_quad_distortion(num_nodes, coordinates);

    if( metric_vals->distortion > 0 ) 
      metric_vals->distortion = (VERDICT_REAL) VERDICT_MIN( metric_vals->distortion, VERDICT_DBL_MAX );
    metric_vals->distortion = (VERDICT_REAL) VERDICT_MAX( metric_vals->distortion, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_JACOBIAN )
  {
    if( metric_vals->jacobian > 0 ) 
      metric_vals->jacobian = (VERDICT_REAL) VERDICT_MIN( metric_vals->jacobian, VERDICT_DBL_MAX );
    metric_vals->jacobian = (VERDICT_REAL) VERDICT_MAX( metric_vals->jacobian, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_MAXIMUM_ANGLE )
  {
    if( metric_vals->maximum_angle > 0 ) 
      metric_vals->maximum_angle = (VERDICT_REAL) VERDICT_MIN( metric_vals->maximum_angle, VERDICT_DBL_MAX );
    metric_vals->maximum_angle = (VERDICT_REAL) VERDICT_MAX( metric_vals->maximum_angle, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_MINIMUM_ANGLE )
  {
    if( metric_vals->minimum_angle > 0 ) 
      metric_vals->minimum_angle = (VERDICT_REAL) VERDICT_MIN( metric_vals->minimum_angle, VERDICT_DBL_MAX );
    metric_vals->minimum_angle = (VERDICT_REAL) VERDICT_MAX( metric_vals->minimum_angle, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_ODDY )
  {
    if( metric_vals->oddy > 0 ) 
      metric_vals->oddy = (VERDICT_REAL) VERDICT_MIN( metric_vals->oddy, VERDICT_DBL_MAX );
    metric_vals->oddy = (VERDICT_REAL) VERDICT_MAX( metric_vals->oddy, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_RELATIVE_SIZE_SQUARED )
  {
    if( metric_vals->relative_size_squared> 0 ) 
      metric_vals->relative_size_squared = (VERDICT_REAL) VERDICT_MIN( metric_vals->relative_size_squared, VERDICT_DBL_MAX );
    metric_vals->relative_size_squared = (VERDICT_REAL) VERDICT_MAX( metric_vals->relative_size_squared, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_SCALED_JACOBIAN )
  {
    if( metric_vals->scaled_jacobian> 0 ) 
      metric_vals->scaled_jacobian = (VERDICT_REAL) VERDICT_MIN( metric_vals->scaled_jacobian, VERDICT_DBL_MAX );
    metric_vals->scaled_jacobian = (VERDICT_REAL) VERDICT_MAX( metric_vals->scaled_jacobian, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_SHEAR )
  {
    if( metric_vals->shear > 0 ) 
      metric_vals->shear = (VERDICT_REAL) VERDICT_MIN( metric_vals->shear, VERDICT_DBL_MAX );
    metric_vals->shear = (VERDICT_REAL) VERDICT_MAX( metric_vals->shear, -VERDICT_DBL_MAX );
  }

  // calculate shear and size
  // reuse values from above
  if(metrics_request_flag & V_QUAD_SHEAR_AND_SIZE)
  {
    metric_vals->shear_and_size = metric_vals->shear * metric_vals->relative_size_squared;

    if( metric_vals->shear_and_size > 0 ) 
      metric_vals->shear_and_size = (VERDICT_REAL) VERDICT_MIN( metric_vals->shear_and_size, VERDICT_DBL_MAX );
    metric_vals->shear_and_size = (VERDICT_REAL) VERDICT_MAX( metric_vals->shear_and_size, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_SHAPE )
  {
    if( metric_vals->shape > 0 ) 
      metric_vals->shape = (VERDICT_REAL) VERDICT_MIN( metric_vals->shape, VERDICT_DBL_MAX );
    metric_vals->shape = (VERDICT_REAL) VERDICT_MAX( metric_vals->shape, -VERDICT_DBL_MAX );
  }

  // calculate shape and size
  // reuse values from above
  if(metrics_request_flag & V_QUAD_SHAPE_AND_SIZE)
  {
    metric_vals->shape_and_size = metric_vals->shape * metric_vals->relative_size_squared;

    if( metric_vals->shape_and_size > 0 ) 
      metric_vals->shape_and_size = (VERDICT_REAL) VERDICT_MIN( metric_vals->shape_and_size, VERDICT_DBL_MAX );
    metric_vals->shape_and_size = (VERDICT_REAL) VERDICT_MAX( metric_vals->shape_and_size, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_SKEW )
  {
    if( metric_vals->skew > 0 ) 
      metric_vals->skew = (VERDICT_REAL) VERDICT_MIN( metric_vals->skew, VERDICT_DBL_MAX );
    metric_vals->skew = (VERDICT_REAL) VERDICT_MAX( metric_vals->skew, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_STRETCH )
  {
    if( metric_vals->stretch > 0 ) 
      metric_vals->stretch = (VERDICT_REAL) VERDICT_MIN( metric_vals->stretch, VERDICT_DBL_MAX );
    metric_vals->stretch = (VERDICT_REAL) VERDICT_MAX( metric_vals->stretch, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_TAPER )
  {
    if( metric_vals->taper > 0 ) 
      metric_vals->taper = (VERDICT_REAL) VERDICT_MIN( metric_vals->taper, VERDICT_DBL_MAX );
    metric_vals->taper = (VERDICT_REAL) VERDICT_MAX( metric_vals->taper, -VERDICT_DBL_MAX );
  }

  if(metrics_request_flag & V_QUAD_WARPAGE )
  {
    if( metric_vals->warpage > 0 ) 
      metric_vals->warpage = (VERDICT_REAL) VERDICT_MIN( metric_vals->warpage, VERDICT_DBL_MAX );
    metric_vals->warpage = (VERDICT_REAL) VERDICT_MAX( metric_vals->warpage, -VERDICT_DBL_MAX );
  }

}