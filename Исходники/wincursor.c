void
UpdateCursor(void)
{
  xcb_xfixes_get_cursor_image_cookie_t cookie = xcb_xfixes_get_cursor_image(xcwm_context_get_connection(context));
  xcb_xfixes_get_cursor_image_reply_t* reply = xcb_xfixes_get_cursor_image_reply(xcwm_context_get_connection(context), cookie, NULL);

  // DEBUG("Got cursor image, serial %d\n", reply->cursor_serial);

  WMUTIL_CURSOR cursor;
  memset(&cursor, 0, sizeof(cursor));
  cursor.width = reply->width;
  cursor.height = reply->height;
  cursor.xhot = reply->xhot;
  cursor.yhot = reply->yhot;
  cursor.argb = xcb_xfixes_get_cursor_image_cursor_image(reply);

  hCursor = winXCursorToHCURSOR(&cursor);

  // XXX: We should only change the cursor if the cursor is within one of our windows...
  // it's hard to notice this as a problem, as windows don't normally try to change the cursor except in response to something being clicked...
  HCURSOR hPreviousCursor = SetCursor(hCursor);

  // DEBUG("cursor 0x%08x, previous cursor 0x%08x\n", hCursor, hPreviousCursor);

  DestroyCursor(hPreviousCursor);

  free(reply);
}