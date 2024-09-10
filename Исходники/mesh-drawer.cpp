void
MeshDrawer::setMesh(const cv::Mat &mesh)
{
	current_mesh = mesh;
		
	int number_of_points = (int)point_items.size();
	int number_of_lines  = (int)line_items.size();
	
	bool hide_mesh = ((mesh.rows == 0) || (mesh.cols == 0));
	
	// update lines
	for (int line_index = 0; line_index < number_of_lines; line_index++) {
		QGraphicsLineItem *line = line_items[line_index];
		
		if (hide_mesh) {
			line->setVisible(false);
		} else {
			QPointF	from_point(mesh.at<double>(current_connections.at<int>(0,line_index),0),
						   mesh.at<double>(current_connections.at<int>(0,line_index)+number_of_points,0));
			QPointF to_point(mesh.at<double>(current_connections.at<int>(1,line_index),0),
						 mesh.at<double>(current_connections.at<int>(1,line_index)+number_of_points,0));
			QLineF line_position(from_point,to_point);			
			line->setLine(line_position);
			line->setVisible(true);
		}
	}
	
	// update points
	for (int point_index = 0; point_index < number_of_points; point_index++) {
		QGraphicsEllipseItem *point = point_items[point_index];
		
		if (hide_mesh) {
			point->setVisible(false);
		} else {
			QPointF position(mesh.at<double>(point_index,0), mesh.at<double>(point_index+number_of_points,0));
		
			QRectF ellipse_rect(position.x() - point_radius,
								position.y() - point_radius,
								2*point_radius,
								2*point_radius);
		
			point->setRect(ellipse_rect);
			point->setVisible(true);
		}
	}
}