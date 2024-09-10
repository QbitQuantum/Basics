    int TreeInertialParameters::dynamicsRegressor( const JntArray &q, 
                                                    const JntArray &q_dot,
                                                    const JntArray &q_dotdot,  
                                                    const Twist& base_velocity, 
                                                    const Twist& base_acceleration,
                                                    Eigen::MatrixXd & dynamics_regressor)
    {
        if(q.rows()!=nj || q_dot.rows()!=nj || q_dotdot.rows()!=nj || dynamics_regressor.cols()!=10*ns || dynamics_regressor.rows()!=(6+nj))
            return -1;
        
        unsigned int i;
        unsigned int j=0;
        
        //Kinematic propagation copied by RNE   
        for(unsigned int l = 0; l < recursion_order.size(); l++ ) {
            
            unsigned int curr_index = recursion_order[l];
        
			const Segment& seg = seg_vector[curr_index]->second.segment;
			const Joint& jnt = seg.getJoint();
			
            double q_,qdot_,qdotdot_;
            if(jnt.getType() !=Joint::None){
				int idx = link2joint[curr_index];
                q_=q(idx);
                qdot_=q_dot(idx);
                qdotdot_=q_dotdot(idx);
            }else
                q_=qdot_=qdotdot_=0.0;
                
            Frame& eX  = X[curr_index];
            Twist& eS  = S[curr_index];
            Twist& ev  = v[curr_index];
            Twist& ea  = a[curr_index];
            Wrench& ef = f[curr_index];
            Frame& eX_b = X_b[curr_index];

            assert(X.size() == ns);
            //Calculate segment properties: X,S,vj,cj
            X[curr_index] = seg.pose(q_);
            //eX=seg.pose(q_);
                            //Remark this is the inverse of the 
                            //frame for transformations from 
                            //the parent to the current coord frame
            //Transform velocity and unit velocity to segment frame
            Twist vj=eX.M.Inverse(seg.twist(q_,qdot_));
            eS=eX.M.Inverse(seg.twist(q_,1.0));
            //We can take cj=0, see remark section 3.5, page 55 since the unit velocity vector S of our joints is always time constant
            //calculate velocity and acceleration of the segment (in segment coordinates)
            
            int parent_index = lambda[curr_index];
            
            if( parent_index == -1 ) {
                eX_b = eX;
            } else {
                eX_b = X_b[parent_index]*eX;
            }
            
            
  
            Twist parent_a, parent_v;
            
            if( parent_index == -1 ) {
                parent_a = base_acceleration;
                parent_v = base_velocity;
            } else {
                parent_a = a[parent_index];
                parent_v = v[parent_index];
            }
            
            ev=eX.Inverse(parent_v)+vj;
            ea=eX.Inverse(parent_a)+eS*qdotdot_+ev*vj;
            
        }      
        //end kinematic phase
        
        dynamics_regressor.setZero();
        
        //just for design, then the loop can be put together
        Eigen::Matrix<double, 6, 10> netWrenchRegressor_i;

        for(i=0;i<ns;i++) {
                        
            netWrenchRegressor_i = netWrenchRegressor(v[i],a[i]);
            
            dynamics_regressor.block(0,(int)(10*i),6,10) = WrenchTransformationMatrix(X_b[i])*netWrenchRegressor_i;

            Frame X_j_i;
            for(j=0;j<ns;j++) {
                X_j_i = X_b[j].Inverse()*X_b[i];
                
                if( seg_vector[j]->second.segment.getJoint().getType() != Joint::None ) {
                    if( indicator_function[i][link2joint[j]] ) {
                        dynamics_regressor.block(6+link2joint[j],10*i,1,10) = 
                            toEigen(S[j]).transpose()*WrenchTransformationMatrix(X_j_i)*netWrenchRegressor_i;
                    }
                }
            }
        
            
        }

        return 0;
        
    }