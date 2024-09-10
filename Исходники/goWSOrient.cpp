/**
 * @function balancePath
 * @brief Builds a straight path -- easy
 */
bool goWSOrient::balancePath( const Eigen::VectorXd &_startConfig, 
		     	      const Eigen::Transform<double, 3, Eigen::Affine> &_goalPose,
	          	      std::vector<Eigen::VectorXd> &path )
{

  srand( time(NULL) );
  //-- Copy input 
  startConfig = _startConfig;
  goalPose = _goalPose;
  goalPos = _goalPose.translation();

  //-- Create needed variables
  Eigen::VectorXd q; Eigen::VectorXd wsPos;
  Eigen::Transform<double, 3, Eigen::Affine> T;
  Eigen::MatrixXd Jc(3, 7); Eigen::MatrixXd Jcinv(7, 3);

  Eigen::MatrixXd delta_q;
  double ws_dist;

  //-- Initialize variables
  q = startConfig; path.push_back( q );
  ws_dist = DBL_MAX;

  //-- Loop
  int trials = 0;
    //-- Get ws position
    robinaLeftArm_fk( q, TWBase, Tee, T );
    wsPos = T.translation();

    Eigen::VectorXd wsOrient(3); 
    getRPY( T, wsOrient(0), wsOrient(1), wsOrient(2) );


    Eigen::VectorXd phi(7);
    Eigen::VectorXd dq(7);   
    Eigen::VectorXd qorig = q;   

      //-- Get the Jacobian
      robinaLeftArm_j( q, TWBase, Tee, Jc );

      //-- Get the pseudo-inverse(easy way)
      pseudoInv( 3, 7, Jc, Jcinv );
    int count = 0;
    for( int i = 0; i < 1000; i++ )
    {

     for( int j = 0; j < 7; j++ )
     { phi[j] = rand()%6400 / 10000.0 ; }

      //-- Get a null space projection displacement that does not affect the thing
      dq = ( Eigen::MatrixXd::Identity(7,7) - Jcinv*Jc )*phi;

      //-- Add to q 
      //q = qorig + dq;
      Eigen::VectorXd newq;
      newq = qorig + dq;

     //-- Calculate distance
     Eigen::Transform<double, 3, Eigen::Affine> Torig;
     Eigen::Transform<double, 3, Eigen::Affine> Tphi;
     robinaLeftArm_fk( newq, TWBase, Tee, Tphi );
     robinaLeftArm_fk( qorig, TWBase, Tee, Torig );
     double dist = ( Tphi.translation() - Torig.translation() ).norm();

     if( dist < 0.015 )
     { 
       count++;
       q = newq;
       printf("--> [%d] Distance to the original xyz is: %.3f \n", count, dist );
       //-- Push it 
       path.push_back( q );
     }

    }

  return true;
}