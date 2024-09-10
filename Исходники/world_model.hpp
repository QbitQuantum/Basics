void 
pcl::kinfuLS::WorldModel<PointT>::getExistingData(const double previous_origin_x, const double previous_origin_y, const double previous_origin_z, const double offset_x, const double offset_y, const double offset_z, const double volume_x, const double volume_y, const double volume_z, pcl::PointCloud<PointT> &existing_slice)
{
  double newOriginX = previous_origin_x + offset_x; 
  double newOriginY = previous_origin_y + offset_y; 
  double newOriginZ = previous_origin_z + offset_z;
  double newLimitX = newOriginX + volume_x; 
  double newLimitY = newOriginY + volume_y; 
  double newLimitZ = newOriginZ + volume_z;
	
  // filter points in the space of the new cube
  PointCloudPtr newCube (new pcl::PointCloud<PointT>);
  // condition
  ConditionAndPtr range_condAND (new pcl::ConditionAnd<PointT> ());
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("x", pcl::ComparisonOps::GE, newOriginX)));
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("x", pcl::ComparisonOps::LT, newLimitX)));
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("y", pcl::ComparisonOps::GE, newOriginY)));
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("y", pcl::ComparisonOps::LT, newLimitY)));
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("z", pcl::ComparisonOps::GE, newOriginZ)));
  range_condAND->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("z", pcl::ComparisonOps::LT, newLimitZ))); 
  
  // build the filter
  pcl::ConditionalRemoval<PointT> condremAND (true);
  condremAND.setCondition (range_condAND);
  condremAND.setInputCloud (world_);
  condremAND.setKeepOrganized (false);
  
  // apply filter
  condremAND.filter (*newCube);
	
  // filter points that belong to the new slice
  ConditionOrPtr range_condOR (new pcl::ConditionOr<PointT> ());
  
  if(offset_x >= 0)
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("x", pcl::ComparisonOps::GE,  previous_origin_x + volume_x - 1.0 )));
  else
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("x", pcl::ComparisonOps::LT,  previous_origin_x )));
	
  if(offset_y >= 0)
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("y", pcl::ComparisonOps::GE,  previous_origin_y + volume_y - 1.0 )));
  else
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("y", pcl::ComparisonOps::LT,  previous_origin_y )));
	
  if(offset_z >= 0)
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("z", pcl::ComparisonOps::GE,  previous_origin_z + volume_z - 1.0 )));
  else
	range_condOR->addComparison (FieldComparisonConstPtr (new pcl::FieldComparison<PointT> ("z", pcl::ComparisonOps::LT,  previous_origin_z )));
  
  // build the filter
  pcl::ConditionalRemoval<PointT> condrem (true);
  condrem.setCondition (range_condOR);
  condrem.setInputCloud (newCube);
  condrem.setKeepOrganized (false);
  // apply filter
  condrem.filter (existing_slice);  
 
  if(existing_slice.points.size () != 0)
  {
	//transform the slice in new cube coordinates
	Eigen::Affine3f transformation; 
	transformation.translation ()[0] = newOriginX;
	transformation.translation ()[1] = newOriginY;
	transformation.translation ()[2] = newOriginZ;
		
	transformation.linear ().setIdentity ();

	transformPointCloud (existing_slice, existing_slice, transformation.inverse ());
	
  }
}