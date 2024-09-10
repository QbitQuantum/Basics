void screen_refresh() {
    window_set_caption(room_caption);
    enigma::update_mouse_variables();
    SwapBuffers(enigma::window_hDC);
}