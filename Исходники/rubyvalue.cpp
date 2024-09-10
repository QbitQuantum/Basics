template <> RubyValue Conversion<QDateTime>::to(const QDateTime &dateTime)
{
    RubyValue sec = rb_rational_new(RubyValue::from(dateTime.toMSecsSinceEpoch()), RubyValue::from(1000));
    RubyValue time = rb_time_num_new(sec, RubyValue::from(dateTime.offsetFromUtc()));
    return time.send(RUBYQML_INTERN("to_datetime"));
}