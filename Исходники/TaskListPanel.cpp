void
TaskListPanel::Show(const PixelRect &rc)
{
  if (serial != task_list_serial) {
    serial = task_list_serial;
    // Scan XCSoarData for available tasks
    task_store->Scan(more);
  }

  dialog.ShowTaskView(get_cursor_task());

  GetList().SetCursorIndex(0); // so Save & Declare are always available
  RefreshView();
  ListWidget::Show(rc);
}