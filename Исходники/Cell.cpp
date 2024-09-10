XLNT_FUNCTION void cell::set_value(time t)
{
    d_->type_ = type::numeric;
    d_->value_numeric_ = t.to_number();
    set_number_format(number_format::date_time6());
}