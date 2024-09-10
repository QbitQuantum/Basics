//--------------------------------------------------------------------------------
// get target look at
//--------------------------------------------------------------------------------
bool zz_camera_follow::get_target_dir (vec3& dir)
{
	if (!target_) {
		dir.set(0, 1, 0);
		return false;
	}
	dir = target_->get_look_at();
	dir.normalize();
	return true;
}