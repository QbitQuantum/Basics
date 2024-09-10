/*! 
  tri_quality for calculating multiple tri functions at once

  using this method is generally faster than using the individual 
  method multiple times.

*/
C_FUNC_DEF void v_tri_quality( int num_nodes, double coordinates[][3], 
    unsigned int metrics_request_flag, TriMetricVals *metric_vals ) 
{

  memset( metric_vals, 0, sizeof(TriMetricVals) );

  // for starts, lets set up some basic and common information

  /*  node numbers and side numbers used below

             2
             ++
            /  \ 
         2 /    \ 1
          /      \
         /        \
       0 ---------+ 1
             0
  */
  
  // vectors for each side
  VerdictVector sides[3];
  sides[0].set(
      coordinates[1][0] - coordinates[0][0],
      coordinates[1][1] - coordinates[0][1],
      coordinates[1][2] - coordinates[0][2]
      );
  sides[1].set(
      coordinates[2][0] - coordinates[1][0],
      coordinates[2][1] - coordinates[1][1],
      coordinates[2][2] - coordinates[1][2]
      );
  sides[2].set(
      coordinates[2][0] - coordinates[0][0],
      coordinates[2][1] - coordinates[0][1],
      coordinates[2][2] - coordinates[0][2]
      );
  VerdictVector tri_normal = sides[0] * sides[2];
    //if we have access to normal information, check to see if the
    //element is inverted.  If we don't have the normal information
    //that we need for this, assume the element is not inverted.
    //This flag will be used for condition number, jacobian, shape,
    //and size and shape.
  bool is_inverted = false;
  if( compute_normal )
  {
      //center of tri
    double point[3], surf_normal[3];
    point[0] =  (coordinates[0][0] + coordinates[1][0] + coordinates[2][0]) / 3;
    point[1] =  (coordinates[0][1] + coordinates[1][1] + coordinates[2][1]) / 3;
    point[2] =  (coordinates[0][2] + coordinates[1][2] + coordinates[2][2]) / 3;
      //dot product
    compute_normal( point, surf_normal ); 
    if( (tri_normal.x()*surf_normal[0] + 
         tri_normal.y()*surf_normal[1] +
         tri_normal.z()*surf_normal[2] ) < 0 )
      is_inverted=true; 
  }
  
  // lengths squared of each side
  double sides_lengths_squared[3];
  sides_lengths_squared[0] = sides[0].length_squared();
  sides_lengths_squared[1] = sides[1].length_squared();
  sides_lengths_squared[2] = sides[2].length_squared();
 

  // if we are doing angle calcuations
  if( metrics_request_flag & (V_TRI_MINIMUM_ANGLE | V_TRI_MAXIMUM_ANGLE) )
  {
    // which is short and long side
    int short_side=0, long_side=0;

    if(sides_lengths_squared[1] < sides_lengths_squared[0])
      short_side = 1;
    if(sides_lengths_squared[2] < sides_lengths_squared[short_side])
      short_side = 2;
  
    if(sides_lengths_squared[1] > sides_lengths_squared[0])
      long_side = 1;
    if(sides_lengths_squared[2] > sides_lengths_squared[long_side])
      long_side = 2;


    // calculate the minimum angle of the tri
    if( metrics_request_flag & V_TRI_MINIMUM_ANGLE )
    {
      if(sides_lengths_squared[0] == 0.0 || 
        sides_lengths_squared[1] == 0.0 ||
        sides_lengths_squared[2] == 0.0)
      {
        metric_vals->minimum_angle = 0.0;
      }        
      else if(short_side == 0)
        metric_vals->minimum_angle = (double)sides[2].interior_angle(sides[1]);
      else if(short_side == 1)
        metric_vals->minimum_angle = (double)sides[0].interior_angle(sides[2]);
      else
        metric_vals->minimum_angle = (double)sides[0].interior_angle(-sides[1]);
    }
    
    // calculate the maximum angle of the tri
    if( metrics_request_flag & V_TRI_MAXIMUM_ANGLE )
    {
      if(sides_lengths_squared[0] == 0.0 || 
        sides_lengths_squared[1] == 0.0 ||
        sides_lengths_squared[2] == 0.0)
      {
        metric_vals->maximum_angle = 0.0;
      }        
      else if(long_side == 0)
        metric_vals->maximum_angle = (double)sides[2].interior_angle(sides[1]);
      else if(long_side == 1)
        metric_vals->maximum_angle = (double)sides[0].interior_angle(sides[2]);
      else
        metric_vals->maximum_angle = (double)sides[0].interior_angle(-sides[1]);
    }
  }


  // calculate the area of the tri
  // the following functions depend on area
  if( metrics_request_flag & (V_TRI_AREA | V_TRI_SCALED_JACOBIAN | 
    V_TRI_SHAPE | V_TRI_RELATIVE_SIZE_SQUARED | V_TRI_SHAPE_AND_SIZE ) )
  {
    metric_vals->area = (double)((sides[0] * sides[2]).length() * 0.5);
  }

  // calculate the aspect ratio
  if(metrics_request_flag & V_TRI_ASPECT_FROBENIUS)
  {
    // sum the lengths squared
    double srms = 
      sides_lengths_squared[0] +
      sides_lengths_squared[1] +
      sides_lengths_squared[2] ;

    // calculate once and reuse
    static const double twoTimesRootOf3 = 2*sqrt(3.0);

    double div = (twoTimesRootOf3 * 
      ( (sides[0] * sides[2]).length() ));

    if(div == 0.0)
      metric_vals->aspect_frobenius = (double)VERDICT_DBL_MAX;
    else
      metric_vals->aspect_frobenius = (double)(srms / div);
  }

  // calculate the radius ratio of the triangle
  if( metrics_request_flag & V_TRI_RADIUS_RATIO )
  {
  double a1 = sqrt( sides_lengths_squared[0] );
  double b1 = sqrt( sides_lengths_squared[1] );
  double c1 = sqrt( sides_lengths_squared[2] );

  VerdictVector ab = sides[0] * sides[1];

  metric_vals->radius_ratio = (double) .25 * a1 * b1 * c1 * ( a1 + b1 + c1 ) / ab.length_squared();
  }

  // calculate the scaled jacobian
  if(metrics_request_flag & V_TRI_SCALED_JACOBIAN)
  {
    // calculate once and reuse
    static const double twoOverRootOf3 = 2/sqrt(3.0);
    // use the area from above
    
    double tmp = tri_normal.length() * twoOverRootOf3;
      
    // now scale it by the lengths of the sides
    double min_scaled_jac = VERDICT_DBL_MAX;
    double temp_scaled_jac;
    for(int i=0; i<3; i++)
    {
      if(sides_lengths_squared[i%3] == 0.0 || sides_lengths_squared[(i+2)%3] == 0.0)
        temp_scaled_jac = 0.0;
      else
        temp_scaled_jac = tmp / sqrt(sides_lengths_squared[i%3]) / sqrt(sides_lengths_squared[(i+2)%3]);
      if( temp_scaled_jac < min_scaled_jac )
        min_scaled_jac = temp_scaled_jac;
    }
      //multiply by -1 if the normals are in opposite directions
    if( is_inverted )
    {
      min_scaled_jac *= -1; 
    }
    metric_vals->scaled_jacobian = (double)min_scaled_jac;

  }

  // calculate the condition number
  if(metrics_request_flag & V_TRI_CONDITION)
  {
    // calculate once and reuse
    static const double rootOf3 = sqrt(3.0);
      //if it is inverted, the condition number is considered to be infinity.
    if(is_inverted){
      metric_vals->condition = VERDICT_DBL_MAX;
    }
    else{
      double area2x = (sides[0] * sides[2]).length();
      if(area2x == 0.0 ) 
        metric_vals->condition = (double)(VERDICT_DBL_MAX);
      else
        metric_vals->condition = (double) ( (sides[0]%sides[0] +
                                                   sides[2]%sides[2] -
                                                   sides[0]%sides[2])  /
                                                  (area2x*rootOf3) );
    }
    
  }

  // calculate the shape
  if(metrics_request_flag & V_TRI_SHAPE || metrics_request_flag & V_TRI_SHAPE_AND_SIZE)
  {
      //if element is inverted, shape is zero.  We don't need to
      //calculate anything.
    if(is_inverted ){
      metric_vals->shape = 0.0;
    }
    else{//otherwise, we calculate the shape
        // calculate once and reuse
      static const double rootOf3 = sqrt(3.0);
        // reuse area from before
      double area2x = metric_vals->area * 2;
        // dot products
      double dots[3] = { 
        sides[0] % sides[0],
          sides[2] % sides[2],
          sides[0] % sides[2]
          };

        // add the dots
      double sum_dots = dots[0] + dots[1] - dots[2];

        // then the finale
      if( sum_dots == 0.0 ) 
        metric_vals->shape = 0.0;
      else
        metric_vals->shape = (double)(rootOf3 * area2x / sum_dots);
    }
    
  }

  // calculate relative size squared
  if(metrics_request_flag & V_TRI_RELATIVE_SIZE_SQUARED || metrics_request_flag & V_TRI_SHAPE_AND_SIZE)
  {
    // get weights
    double w11, w21, w12, w22;
    v_tri_get_weight(w11,w21,w12,w22);
    // get the determinant
    double detw = v_determinant(w11,w21,w12,w22);
    // use the area from above and divide with the determinant
    if( metric_vals->area == 0.0  || detw == 0.0 )
      metric_vals->relative_size_squared = 0.0;
    else
    {
      double size = metric_vals->area * 2.0 / detw;
      // square the size
      size *= size;
      // value ranges between 0 to 1
      metric_vals->relative_size_squared = (double)VERDICT_MIN(size, 1.0/size );
    }
  }

  // calculate shape and size
  if(metrics_request_flag & V_TRI_SHAPE_AND_SIZE)
  {
    metric_vals->shape_and_size = 
      metric_vals->relative_size_squared * metric_vals->shape;
  }

  // calculate distortion
  if(metrics_request_flag & V_TRI_DISTORTION)
    metric_vals->distortion = v_tri_distortion(num_nodes, coordinates);

  //take care of any over-flow problems
  if( metric_vals->aspect_frobenius > 0 )
    metric_vals->aspect_frobenius = (double) VERDICT_MIN( metric_vals->aspect_frobenius, VERDICT_DBL_MAX );\
  else
    metric_vals->aspect_frobenius = (double) VERDICT_MAX( metric_vals->aspect_frobenius, -VERDICT_DBL_MAX );

  if( metric_vals->area > 0 )
    metric_vals->area = (double) VERDICT_MIN( metric_vals->area, VERDICT_DBL_MAX );
  else
    metric_vals->area = (double) VERDICT_MAX( metric_vals->area, -VERDICT_DBL_MAX );

  if( metric_vals->minimum_angle > 0 )
    metric_vals->minimum_angle = (double) VERDICT_MIN( metric_vals->minimum_angle, VERDICT_DBL_MAX );
  else
    metric_vals->minimum_angle = (double) VERDICT_MAX( metric_vals->minimum_angle, -VERDICT_DBL_MAX );

  if( metric_vals->maximum_angle > 0 )
    metric_vals->maximum_angle = (double) VERDICT_MIN( metric_vals->maximum_angle, VERDICT_DBL_MAX );
  else
    metric_vals->maximum_angle = (double) VERDICT_MAX( metric_vals->maximum_angle , -VERDICT_DBL_MAX );

  if( metric_vals->condition > 0 )
    metric_vals->condition = (double) VERDICT_MIN( metric_vals->condition, VERDICT_DBL_MAX );
  else
    metric_vals->condition = (double) VERDICT_MAX( metric_vals->condition, -VERDICT_DBL_MAX );

  if( metric_vals->shape > 0 )
    metric_vals->shape = (double) VERDICT_MIN( metric_vals->shape, VERDICT_DBL_MAX );
  else
    metric_vals->shape = (double) VERDICT_MAX( metric_vals->shape, -VERDICT_DBL_MAX );

  if( metric_vals->radius_ratio > 0 )
    metric_vals->radius_ratio = (double) VERDICT_MIN( metric_vals->radius_ratio, VERDICT_DBL_MAX );\
  else
    metric_vals->radius_ratio = (double) VERDICT_MAX( metric_vals->radius_ratio, -VERDICT_DBL_MAX );

  if( metric_vals->scaled_jacobian > 0 )
    metric_vals->scaled_jacobian = (double) VERDICT_MIN( metric_vals->scaled_jacobian, VERDICT_DBL_MAX );
  else
    metric_vals->scaled_jacobian = (double) VERDICT_MAX( metric_vals->scaled_jacobian, -VERDICT_DBL_MAX );

  if( metric_vals->relative_size_squared > 0 )
    metric_vals->relative_size_squared = (double) VERDICT_MIN( metric_vals->relative_size_squared, VERDICT_DBL_MAX );
  else
    metric_vals->relative_size_squared = (double) VERDICT_MAX( metric_vals->relative_size_squared, -VERDICT_DBL_MAX );

  if( metric_vals->shape_and_size > 0 )
    metric_vals->shape_and_size = (double) VERDICT_MIN( metric_vals->shape_and_size, VERDICT_DBL_MAX );
  else
    metric_vals->shape_and_size = (double) VERDICT_MAX( metric_vals->shape_and_size, -VERDICT_DBL_MAX );

  if( metric_vals->distortion > 0 )
    metric_vals->distortion = (double) VERDICT_MIN( metric_vals->distortion, VERDICT_DBL_MAX );
  else
    metric_vals->distortion = (double) VERDICT_MAX( metric_vals->distortion, -VERDICT_DBL_MAX );
}