// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  snprintf(yup, 2, "%c", all_answers[cell_index->row*2+1]);
  menu_cell_basic_draw(ctx, cell_layer, itoa(all_answers[cell_index->row*2]), yup, NULL);
}