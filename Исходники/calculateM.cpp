/**
 * @function Residual 
 */
void Residual( Eigen::MatrixXd _M, std::vector<Eigen::VectorXi> _points2D, 
                                   std::vector<Eigen::VectorXd> _points3D,
                                   std::vector<Eigen::VectorXd> _normPoints2D, 
                                   std::vector<Eigen::VectorXd> _normPoints3D,
                                   Eigen::MatrixXd T2 )
{
   int N = _points2D.size();
   Eigen::VectorXd uvh;
   double u; double v;
   std::vector<Eigen::VectorXd> uv_normPredicted;
   std::vector<Eigen::VectorXd> uv_predicted;
   std::vector<Eigen::VectorXd> normResidual;
   std::vector<Eigen::VectorXd> residual;
   Eigen::MatrixXd T2inv;

   for( int i = 0; i < N; i++ )
   {
      Eigen::VectorXd normPoint3D_h(4);
      normPoint3D_h << _normPoints3D[i](0), _normPoints3D[i](1), _normPoints3D[i](2), 1; 
      uvh = _M*normPoint3D_h;
      u = uvh(0) / uvh(2);  v = uvh(1) / uvh(2);

      uv_normPredicted.push_back( Eigen::Vector2d( u, v ) );
      double nru = u - _normPoints2D[i](0); 
      double nrv = v - _normPoints2D[i](1);
      double nrd = sqrt( nru*nru + nrv*nrv );
      normResidual.push_back( Eigen::Vector3d( nru, nrv, nrd) );

      T2inv = T2.inverse();
      Eigen::VectorXd uvp = T2inv*Eigen::Vector3d( u, v, 1 );
      double ru = uvp(0) - _points2D[i](0); 
      double rv = uvp(1) - _points2D[i](1);
      double rd = sqrt( ru*ru + rv*rv );
      uv_predicted.push_back( Eigen::Vector2d( uvp(0), uvp(1) ) );
      residual.push_back( Eigen::Vector3d( ru, rv, rd ) );

   }


   /** Display */
   printf("Residual!! \n");
   for( unsigned int i = 0; i < N; i++ )
   {
      printf("[%d] P2D: (%d , %d) -- Predicted: (%.4f , %.4f) - Residual: (%.4f %.4f) Mod: %.4f \n",i, _points2D[i](0), _points2D[i](1), uv_predicted[i](0), uv_predicted[i](1), residual[i](0), residual[i](1), residual[i](2));
   }

}