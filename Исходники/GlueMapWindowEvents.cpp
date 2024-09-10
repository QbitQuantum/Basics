bool
GlueMapWindow::OnMouseUp(PixelScalar x, PixelScalar y)
{
    if (drag_mode != DRAG_NONE)
        ReleaseCapture();

    // Ignore single click event if double click detected
    if (ignore_single_click) {
        ignore_single_click = false;
        return true;
    }

    int click_time = mouse_down_clock.Elapsed();
    mouse_down_clock.Reset();

    DragMode old_drag_mode = drag_mode;
    drag_mode = DRAG_NONE;

    switch (old_drag_mode) {
    case DRAG_NONE:
        /* skip the arm_mapitem_list check below */
        return false;

#ifdef HAVE_MULTI_TOUCH
    case DRAG_MULTI_TOUCH_PAN:
        follow_mode = FOLLOW_SELF;
        ::PanTo(visible_projection.GetGeoScreenCenter());
        return true;
#endif

    case DRAG_PAN:
#ifndef ENABLE_OPENGL
        /* allow the use of the stretched last buffer for the next two
           redraws */
        scale_buffer = 2;
#endif

#ifdef ENABLE_OPENGL
        kinetic_x.MouseUp(x);
        kinetic_y.MouseUp(y);
        kinetic_timer.Schedule(30);
#endif
        break;

    case DRAG_SIMULATOR:
        if (click_time > 50 &&
                compare_squared(drag_start.x - x, drag_start.y - y,
                                Layout::Scale(36)) == 1) {
            GeoPoint location = visible_projection.ScreenToGeo(x, y);

            double distance = hypot(drag_start.x - x, drag_start.y - y);

            // This drag moves the aircraft (changes speed and direction)
            const Angle old_bearing = CommonInterface::Basic().track;
            const auto min_speed = fixed(1.1) *
                                   CommonInterface::GetComputerSettings().polar.glide_polar_task.GetVMin();
            const Angle new_bearing = drag_start_geopoint.Bearing(location);
            if (((new_bearing - old_bearing).AsDelta().AbsoluteDegrees() < fixed(30)) ||
                    (CommonInterface::Basic().ground_speed < min_speed))
                device_blackboard->SetSpeed(Clamp(fixed(distance) / Layout::FastScale(3),
                                                  min_speed, fixed(100)));

            device_blackboard->SetTrack(new_bearing);
            // change bearing without changing speed if direction change > 30
            // 20080815 JMW prevent dragging to stop glider

            return true;
        }

        break;

    case DRAG_GESTURE:
        const TCHAR* gesture = gestures.Finish();
        if (gesture && OnMouseGesture(gesture))
            return true;

        break;
    }

    if (arm_mapitem_list) {
        map_item_timer.Schedule(200);
        return true;
    }

    return false;
}