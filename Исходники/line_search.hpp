        void make_step_size() //default
        {
            auto const& interpolate = []( value_type x1, value_type y1, value_type x2, value_type y2, value_type x3, value_type y3 )
            {
                matrix<value_type> A( 3, 3 );
                matrix<value_type> x( 3, 1 );
                matrix<value_type> B( 3, 1 );
                A[0][0] = x1 * x1; A[0][1] = x1; A[0][2] = value_type{1}; B[0][0] = y1;
                A[1][0] = x2 * x2; A[1][1] = x2; A[1][2] = value_type{1}; B[1][0] = y2;
                A[2][0] = x3 * x3; A[2][1] = x3; A[2][2] = value_type{1}; B[2][0] = y3;

                int const status = lu_solver( A, x, B );
                if ( 1 == status ) conjugate_gradient_squared( A, x, B );

                return x[1][0] / ( x[0][0]+x[0][0] ); 
            };

            auto const& phi = [this]( value_type alpha ) 
            { 
                (*this).current_solution += alpha * (*this).direction;
                auto const ans = (*this).merit_function( (*this).current_solution.data() );
                (*this).current_solution -= alpha * (*this).direction;
                return ans;
            };
            //auto const& d_phi = make_derivative( phi, 0 );
            auto const& d_phi = make_derivative<0>( phi );

            value_type const c_1 = 0.00186744273170798882; // e^{-2pi}
            //value_type const c_2 = value_type{1} - c_1;
            value_type const c_2 = 0.9;
            value_type const alpha_max = 1.4142135623730950488; // sqrt(2)
            value_type const ratio = 0.6180339887498948482;
            value_type const alpha_next = alpha_max * ratio;

            value_type const phi_0 = phi( value_type{0} );
            value_type const d_phi_0 = d_phi( value_type{0} );
            value_type const phi_alpha_max = phi( alpha_max );

            value_type alpha = interpolate( value_type{0}, phi_0, alpha_next, phi(alpha_next), alpha_max, phi_alpha_max );

            if ( std::isnan( alpha ) || std::isinf( alpha ) ) alpha = alpha_next;
            if ( alpha > alpha_max || alpha <= value_type{0} ) alpha = alpha_next;

            value_type phi_last_alpha = phi_0;
            value_type last_alpha = 0;
            value_type phi_alpha = phi( alpha );

            auto const& zoom = [interpolate, ratio, c_1, c_2, phi_0, d_phi_0, phi, d_phi]( value_type alpha_low, value_type phi_alpha_low, value_type alpha_high, value_type phi_alpha_high  )
            {
                auto recurser = [interpolate, ratio, c_1, c_2, phi_0, d_phi_0, phi, d_phi]( value_type alpha_low, value_type phi_alpha_low, value_type alpha_high, value_type phi_alpha_high, auto recur )
                {
                    value_type const alpha_se = alpha_low + ( alpha_high - alpha_low ) * ratio;
                    if ( std::abs( alpha_low - alpha_high ) < value_type( 1.0e-10 ) ) return alpha_se;

                    value_type const phi_alpha_se = phi( alpha_se );
                    value_type alpha_j = interpolate( alpha_low, phi_alpha_low, alpha_se, phi_alpha_se, alpha_high, phi_alpha_high );
                    if ( alpha_j > std::max( alpha_low, alpha_high ) || alpha_j < std::min( alpha_low, alpha_high ) ) alpha_j = alpha_se;
                    if ( std::isinf( alpha_j ) || std::isnan( alpha_j ) ) alpha_j = alpha_se;
                    value_type const phi_alpha_j = phi( alpha_j );

                    value_type const d_phi_alpha_j = d_phi( alpha_j );
                    if ( std::abs(d_phi_alpha_j) <= -c_2 * d_phi_0 ) 
                        return alpha_j;

                    if ( ( phi_alpha_j > phi_0 + c_1 * alpha_j * d_phi_0 ) | ( phi_alpha_j >= phi_alpha_low ) )
                        return recur( alpha_low, phi_alpha_low, alpha_j, phi_alpha_j, recur );

                    if ( d_phi_alpha_j * ( alpha_high - alpha_low ) >= value_type{0} )
                        return recur( alpha_j, phi_alpha_j, alpha_low, phi_alpha_low, recur );

                    return recur( alpha_j, phi_alpha_j, alpha_high, phi_alpha_high, recur );
                };

                return recurser( alpha_low, phi_alpha_low, alpha_high, phi_alpha_high, recurser );
            };

            for ( size_type index = 0; true; ++index )
            {
                if ( index != 0 ) 
                    phi_alpha = phi( alpha );

                if ( ( ( phi_alpha > phi_0 + c_1 * alpha * d_phi_0 ) && ( phi_alpha < phi_0 ) ) || ( index != 0  && phi_alpha >= phi_last_alpha ) )
                {
                    step_size = zoom( last_alpha, phi_last_alpha, alpha, phi_alpha );
                    break;
                }

                value_type const d_phi_alpha = d_phi( alpha );
                if ( ( std::abs(d_phi_alpha) <= -c_2 * d_phi_0 ) && ( phi_alpha < phi_0 ) )
                {
                    step_size = alpha;
                    break;
                }

                if ( d_phi_alpha >= 0 )
                {
                    step_size = zoom( alpha, phi_alpha, last_alpha, phi_last_alpha );
                    break;
                }

                value_type const alpha_se = alpha + ( alpha_max - alpha ) * ratio;
                value_type const phi_alpha_se = phi( alpha_se );
                alpha = interpolate( alpha, phi_alpha, alpha_se, phi_alpha_se, alpha_max, phi_alpha_max );
                phi_last_alpha = phi_alpha;
            }

            //current_solution += step_size * direction;
            current_solution -= step_size * direction;
            current_residual = merit_function( current_solution.data() );

            std::cerr << "\n\nstep is set to " << step_size;
            std::cerr << "\nresidual is  " << current_residual << "\n";
            std::cerr << "direction is " << direction.transpose() << "\n";
            std::cerr << "solution is " << current_solution.transpose() << "\n";
        }