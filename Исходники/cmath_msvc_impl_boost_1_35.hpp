inline float do_hypot(const Float& v1,const Float& v2, mpl::false_)
{
    mpl::bool_<(sizeof(hypotf_impl::has_hypot(_hypotf(v1, v2)))==sizeof(hypotf_impl::yes))> condition;
    return hypotf_impl::do_hypot_(v1,v2, condition);
}