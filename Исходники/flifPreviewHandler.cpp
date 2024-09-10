void flifPreviewHandler::destroyPreviewWindowData()
{
    if (_preview_window)
    {
        _preview_window = 0;
        _image_window = 0;
        _play_button = 0;
        _frame_scrollbar = 0;
    }

    if (_registered_class)
    {
        UnregisterClassW(PREVIEW_WINDOW_CLASSNAME, getInstanceHandle());
        _registered_class = 0;
    }

    _frame_width = 0;
    _frame_height = 0;
    _num_loops = 0;
    _frame_bitmaps.clear();
    _frame_delays.clear();
    _loop_time = std::chrono::milliseconds(0);

    _play_state = PS_STOP;
    _play_start_time = std::chrono::time_point<std::chrono::high_resolution_clock>();
    _current_frame = -1;
}