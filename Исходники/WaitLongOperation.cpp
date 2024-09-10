// -----------------------------------------------------------------------
// WaitLongOperation
// -----------------------------------------------------------------------
WaitLongOperation::WaitLongOperation(RLMachine& machine)
    : machine_(machine),
      wait_until_target_time_(false),
      target_time_(0),
      break_on_clicks_(false), button_pressed_(0),
      break_on_event_(false),
      has_sleep_time_provider_(false),
      break_on_ctrl_pressed_(machine.system().text().ctrlKeySkip()),
      ctrl_pressed_(false),
      mouse_moved_(false),
      save_click_location_(false) {
}