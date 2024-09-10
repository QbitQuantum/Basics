 static bool type_to_text(const void* value_in, quan::dynarray<char> & text_out)
 {
    if ( ! value_in) return false;
    char buf[100];
    // convert to typed value in
    quan::three_d::vect<int32_t> const * tvi = (quan::three_d::vect<int32_t> const*) value_in;
    int const result = sprintf (buf,"[%i,%i,%i]"
       ,static_cast<int>(tvi->x)
       ,static_cast<int>(tvi->y)
       ,static_cast<int>(tvi->z));
    if ( (result <= 0) || (result >= 100)) {
       quan::error(fn_any, quan::detail::bad_int_range);
       return false;
    }
    if (!text_out.realloc (result +1)) {
       symbol_table::on_malloc_failed();
       return false;
    }
    strcpy (text_out.get(), buf);
    return true;
 }