void XimIM_impl::set_ic_focus(C16 icid)
{
    XimIC *ic = get_ic_by_id(icid);
    if (ic)
	ic->setFocus();
}