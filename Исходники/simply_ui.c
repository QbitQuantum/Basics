void simply_ui_set_text(SimplyUi *self, SimplyUiTextfieldId textfield_id, const char *str) {
  SimplyUiTextfield *textfield = &self->ui_layer.textfields[textfield_id];
  char **str_field = &textfield->text;
  strset(str_field, str);
  mark_dirty(self);
}