static void draw_device_area(
	GDSpecPtr device_spec,
	GDHandle selected_device,
	Rect *frame)
{
	Point offset;
	GDHandle device;

	get_device_area_offset(frame, &offset);
	
	EraseRect(frame);
	FrameRect(frame);
	
	for (device= GetDeviceList(); device; device= GetNextDevice(device))
	{
		if (TestDeviceAttribute(device, screenDevice) && TestDeviceAttribute(device, screenActive))
		{
			GDSpec spec;
			Rect bounds;
			
			BuildExplicitGDSpec(&spec, device, device_spec->flags, device_spec->bit_depth, 0, 0);
			
			get_device_area_frame(device, &bounds, offset);
			
			RGBForeColor(HasDepthGDSpec(&spec) ? &rgb_dark_gray : &rgb_white);
			PaintRect(&bounds);
			RGBForeColor(&rgb_black);
			
			if (device==selected_device) PenSize(2, 2);
			FrameRect(&bounds);
			PenSize(1, 1);
			
			if (device==GetMainDevice())
			{
				bounds.bottom= bounds.top + DEVICE_AREA_MENU_BAR_HEIGHT;
				EraseRect(&bounds);
				FrameRect(&bounds);
			}
		}
	}
	
	return;
}