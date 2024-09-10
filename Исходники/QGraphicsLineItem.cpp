QTCEXPORT(void,qtc_QGraphicsLineItem_line_qth)(void* x0, double* _ret_x1, double* _ret_y1, double* _ret_x2, double* _ret_y2) {
  QLineF tc = ((QGraphicsLineItem*)x0)->line();
  *_ret_x1 = tc.x1(); *_ret_y1 = tc.y1(); *_ret_x2 = tc.x2(); *_ret_y2 = tc.y2();
  return;
}