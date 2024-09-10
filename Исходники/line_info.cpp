/** Update this line.
 * @param linfo new info to consume
 * This also updates moving averages for all fields.
 */
void TrackedLineInfo::update(LineInfo &linfo)
{
  if (visibility_history <= 0)
    visibility_history = 1;
  else
    visibility_history += 1;

  this->raw = linfo;
  fawkes::tf::Stamped<fawkes::tf::Point> bp_new(
	  fawkes::tf::Point(
	      linfo.base_point[0], linfo.base_point[1], linfo.base_point[2]
	  ), fawkes::Time(0,0), input_frame_id);
  try {
    transformer->transform_point(tracking_frame_id, bp_new, this->base_point_odom);
  } catch (fawkes::tf::TransformException &e) {
    logger->log_warn(plugin_name.c_str(), "Can't transform to %s. Attempting to track in %s.",
										 tracking_frame_id.c_str(), input_frame_id.c_str());
    this->base_point_odom = bp_new;
  }
  this->history.push_back(linfo);

  Eigen::Vector3f base_point_sum(0,0,0), end_point_1_sum(0,0,0),
	  end_point_2_sum(0,0,0), line_direction_sum(0,0,0), point_on_line_sum(0,0,0);
  float length_sum(0);
  for (LineInfo &l : this->history) {
	base_point_sum += l.base_point;
	end_point_1_sum += l.end_point_1;
	end_point_2_sum += l.end_point_2;
	line_direction_sum += l.line_direction;
	point_on_line_sum += l.point_on_line;
	length_sum += l.length;
  }

  size_t sz = this->history.size();
  this->smooth.base_point = base_point_sum / sz;
  this->smooth.cloud = linfo.cloud;
  this->smooth.end_point_1 = end_point_1_sum / sz;
  this->smooth.end_point_2 = end_point_2_sum / sz;
  this->smooth.length = length_sum / sz;
  this->smooth.line_direction = line_direction_sum / sz;
  this->smooth.point_on_line = point_on_line_sum / sz;

  Eigen::Vector3f x_axis(1,0,0);

  Eigen::Vector3f ld_unit = this->smooth.line_direction / this->smooth.line_direction.norm();
  Eigen::Vector3f pol_invert = Eigen::Vector3f(0,0,0) - this->smooth.point_on_line;
  Eigen::Vector3f P = this->smooth.point_on_line + pol_invert.dot(ld_unit) * ld_unit;
  this->smooth.bearing = std::acos(x_axis.dot(P) / P.norm());
  // we also want to encode the direction of the angle
  if (P[1] < 0)
    this->smooth.bearing = std::abs(this->smooth.bearing) * -1.;

  Eigen::Vector3f l_diff = raw.end_point_2 - raw.end_point_1;
  Eigen::Vector3f l_ctr = raw.end_point_1 + l_diff / 2.;
  this->bearing_center = std::acos(x_axis.dot(l_ctr) / l_ctr.norm());
  if (l_ctr[1] < 0)
    this->bearing_center = std::abs(this->bearing_center) * -1.;
}