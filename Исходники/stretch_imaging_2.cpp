Eigen::Vector2d final_ray_scene_intersection( const Eigen::Vector2d &scene_point, const Eigen::Vector2d &final_ray_normalized, const Eigen::Vector2d &intersection_point_on_curved_surface)
{
	double d = (scene_point-intersection_point_on_curved_surface).dot(Eigen::Vector2d(0,-1))/(final_ray_normalized.dot(Eigen::Vector2d(0,-1)));
	return final_ray_normalized*d+intersection_point_on_curved_surface;
}