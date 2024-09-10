//procustres
inline void ICP::minimize(const Pair& init_f){
	
	Eigen::Vector3d centroide_model(0.0,0.0,0.0), centroide_data(0.0,0.0,0.0);
	Eigen::Matrix3d M;
	
	unsigned int N = data_indices.size() + init_f.size();
	
	Eigen::MatrixXd model(3,N);
	Eigen::MatrixXd  data(3,N);
	
		
	//calcula os centroides
	int k=0;
	for(unsigned int i=0; i<N; i++){
		
		if (i<data_indices.size()){
			model(0,i) = cloud_m->points[ model_indices[i] ].x;
			model(1,i) = cloud_m->points[ model_indices[i] ].y;
			model(2,i) = cloud_m->points[ model_indices[i] ].z;
		
			data(0,i) = cloud_d->points[ data_indices[i] ].x*T(0,0) + cloud_d->points[ data_indices[i] ].y*T(0,1) + cloud_d->points[ data_indices[i] ].z*T(0,2) + T(0,3);
			data(1,i) = cloud_d->points[ data_indices[i] ].x*T(1,0) + cloud_d->points[ data_indices[i] ].y*T(1,1) + cloud_d->points[ data_indices[i] ].z*T(1,2) + T(1,3);
			data(2,i) = cloud_d->points[ data_indices[i] ].x*T(2,0) + cloud_d->points[ data_indices[i] ].y*T(2,1) + cloud_d->points[ data_indices[i] ].z*T(2,2) + T(2,3);
		}else{

			model(0,i) = cloud_m->points[ init_f[k].first ].x;
			model(1,i) = cloud_m->points[ init_f[k].first ].y;
			model(2,i) = cloud_m->points[ init_f[k].first ].z;
		
			data(0,i) = cloud_d->points[ init_f[k].second ].x*T(0,0) + cloud_d->points[ init_f[k].second ].y*T(0,1) + cloud_d->points[ init_f[k].second ].z*T(0,2) + T(0,3);
			data(1,i) = cloud_d->points[ init_f[k].second ].x*T(1,0) + cloud_d->points[ init_f[k].second ].y*T(1,1) + cloud_d->points[ init_f[k].second ].z*T(1,2) + T(1,3);
			data(2,i) = cloud_d->points[ init_f[k].second ].x*T(2,0) + cloud_d->points[ init_f[k].second ].y*T(2,1) + cloud_d->points[ init_f[k].second ].z*T(2,2) + T(2,3);	
			k++;
		}
		
		centroide_model += model.block(0,i,3,1);
		centroide_data  +=  data.block(0,i,3,1);
	}
	
	centroide_data = centroide_data/N;
	centroide_model = centroide_model/N;
	
	
  //subtrai os centroides aos dados
	for (unsigned int i=0; i<N; i++){
		model.block(0,i,3,1) -= centroide_model;
		data.block(0,i,3,1) -= centroide_data;
	}
	
	
	//Determina a transformacao
	M = data*model.transpose();
	
	Eigen::JacobiSVD<Eigen::Matrix3d> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);
	
	Eigen::Matrix3d U = svd.matrixU();
	Eigen::Matrix3d V = svd.matrixV();
	
	if (U.determinant()*V.determinant()<0) {
		for (int i=0; i<3; ++i) 
			V(i,2) *=-1;
	}
	
		
	Eigen::Matrix3d r = V * U.transpose();
	Eigen::Vector3d t = centroide_model - r * centroide_data;
	
	//~ T.block<3,3>(0,0) =  r*T.block<3,3>(0,0);
	//~ T.block<3,1>(0,3) += t; 
	T.block<3,1>(0,3) = T.block<3,3>(0,0)*t + T.block<3,1>(0,3); 
	T.block<3,3>(0,0) = T.block<3,3>(0,0)*r;
	
	
} 