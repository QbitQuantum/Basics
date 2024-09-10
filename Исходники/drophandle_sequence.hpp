 static ws_uint_t drag_query_file(HDROP hdrop, ws_uint_t index, ws_char_w_t* buffer, ws_uint_t cchBuffer)
 {
     return DragQueryFileW(hdrop, index, buffer, cchBuffer);
 }