/********************
 * dres_free_field
 ********************/
void
dres_free_field(dres_field_t *f)
{
    FREE(f->name);
    dres_free_value(&f->value);
}