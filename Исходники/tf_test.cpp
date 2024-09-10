static void print_transform(tf::Transform transform)
{	
	carmen_orientation_3D_t orientation = get_carmen_orientation_from_tf_transform(transform);
	printf("y:% lf p:% lf r:% lf\n", orientation.yaw, orientation.pitch, orientation.roll);
	printf("x:% lf y:% lf z:% lf\n", transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z());
	printf("\n");
}