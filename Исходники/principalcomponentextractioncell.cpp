		int process(const tendrils& inputs, const tendrils& outputs,
					boost::shared_ptr<const ::pcl::PointCloud<Point> >& input)
		{
      eigenVectors_->clear();
      centroids_->clear();
      ::pcl::ExtractIndices<Point> filter;
      filter.setInputCloud(input);

      rectangles_->resize(static_cast<std::size_t>(clusters_->size()));
      for(std::size_t i = 0; i < clusters_->size(); ++i)
      {
        rectangles_->at(i).resize(4);
      }

      for(std::size_t i = 0; i < clusters_->size(); ++i)
      {
        if(clusters_->at(i).indices.size() < 3)
          continue;

        boost::shared_ptr< ::pcl::PointCloud<Point> > cloud;
        cloud = boost::make_shared< ::pcl::PointCloud<Point> > ();
        // extract indices into a cloud
        filter.setIndices( ::pcl::PointIndicesPtr(
        new ::pcl::PointIndices ((*clusters_)[i])) );
        filter.filter(*cloud);

        // extract the eigen vectors
        ::pcl::PointCloud< ::pcl::PointXYZ> proj;
        pcl::PCA <Point > pca;
        pca.setInputCloud(cloud);
        eigenVectors_->push_back(pca.getEigenVectors());
        centroids_->push_back(pca.getMean());

        //generate the rectangles
        Eigen::Vector3f center = Eigen::Vector3f(pca.getMean().x(),
                                                 pca.getMean().y(),
                                                 pca.getMean().z());
        Eigen::Vector3f longAxis = Eigen::Vector3f(pca.getEigenVectors()(0,0),
                                                 pca.getEigenVectors()(1,0),
                                                 pca.getEigenVectors()(2,0));
        Eigen::Vector3f shortAxis = Eigen::Vector3f(pca.getEigenVectors()(0,1),
                                                 pca.getEigenVectors()(1,1),
                                                 pca.getEigenVectors()(2,1));
        longAxis.normalize();
        longAxis = (*length_rectangles_)*longAxis;        
        shortAxis.normalize();
        shortAxis = (*width_rectangles_)*shortAxis;        
        
        rectangles_->at(i)[0] = center - longAxis/2 - shortAxis/2;
        rectangles_->at(i)[1] = center + longAxis/2 - shortAxis/2;
        rectangles_->at(i)[2] = center + longAxis/2 + shortAxis/2;
        rectangles_->at(i)[3] = center - longAxis/2 + shortAxis/2;

      }
      
			return ecto::OK;
		}