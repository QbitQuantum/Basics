static void ui_window_win32_set_droppable(void *data, bool droppable)
{
   /* Minimum supported client: Windows XP, minimum supported server: Windows 2000 Server */
   ui_window_win32_t *window = (ui_window_win32_t*)data;
   DragAcceptFiles(window->hwnd, droppable);
}