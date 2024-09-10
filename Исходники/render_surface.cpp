bool
render_surface::on_motion_notify_event( GdkEventMotion* event)
{
	python::gil_lock L;
	mouse_event( event );
	return true;
}