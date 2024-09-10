void InputOutputLinControl::computeRelativeTransformation(tf::StampedTransform start, tf::StampedTransform current, tf::Transform& relative_transform)
{
	relative_transform = start.inverse() * current;
}