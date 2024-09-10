TunUdata::TunUdata(TunUdata &&src_obj)
	:TunUdata() {

	swap(*this, src_obj);
}