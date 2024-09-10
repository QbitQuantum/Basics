void
ControllerHelpWindow::draw()
{
  const Controller& controller = InputManagerSDL::current()->get_controller();

  Vector2f pos(static_cast<float>(Display::get_width())  - 350.0f - 16.0f, 
               static_cast<float>(Display::get_height()) - 200.0f - 16.0f);

  Display::fill_rounded_rect(Rectf(pos, Sizef(350, 200)), 10.0f, Color(0.0f, 0.0f, 0.25f, 0.9f));
  Display::draw_rounded_rect(Rectf(pos, Sizef(350, 200)), 10.0f, Color(1.0f, 1.0f, 1.0f,  0.5f));

  draw_stick(pos + Vector2f(50, 75),
             controller.get_button_state(LEFT_STICK_BUTTON),
             controller.get_axis_state(X_AXIS),
             controller.get_axis_state(Y_AXIS));

  draw_stick(pos + Vector2f(250, 150),
             controller.get_button_state(RIGHT_STICK_BUTTON),
             controller.get_axis_state(X2_AXIS),
             controller.get_axis_state(Y2_AXIS));

  draw_trigger(pos + Vector2f(45,  20), controller.get_trigger_state(LEFT_TRIGGER_AXIS));
  draw_trigger(pos + Vector2f(305, 20), controller.get_trigger_state(RIGHT_TRIGGER_AXIS));

  draw_button(pos + Vector2f(125, 75), controller.get_button_state(SELECT_BUTTON));
  draw_button(pos + Vector2f(225, 75), controller.get_button_state(START_BUTTON));

  draw_button(pos + Vector2f(100, 22), controller.get_button_state(LEFT_SHOULDER_BUTTON));
  draw_button(pos + Vector2f(250, 22), controller.get_button_state(RIGHT_SHOULDER_BUTTON));

  Vector2f face_pos(300, 75);
  draw_button(pos + face_pos + Vector2f(  0,  25), controller.get_button_state(PRIMARY_BUTTON));
  draw_button(pos + face_pos + Vector2f (25,   0), controller.get_button_state(SECONDARY_BUTTON));
  draw_button(pos + face_pos + Vector2f(-25,   0), controller.get_button_state(TERTIARY_BUTTON));
  draw_button(pos + face_pos + Vector2f(  0, -25), controller.get_button_state(QUATERNARY_BUTTON));

  Vector2f dpad_pos(100, 150);
  draw_button(pos + dpad_pos + Vector2f(  0,  25), controller.get_button_state(MENU_DOWN_BUTTON));
  draw_button(pos + dpad_pos + Vector2f (25,   0), controller.get_button_state(MENU_RIGHT_BUTTON));
  draw_button(pos + dpad_pos + Vector2f(-25,   0), controller.get_button_state(MENU_LEFT_BUTTON));
  draw_button(pos + dpad_pos + Vector2f(  0, -25), controller.get_button_state(MENU_UP_BUTTON));
}