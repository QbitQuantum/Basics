void		THIS::init(parent_t * const & p)
{
	printv_func(DEBUG);

	setParent(p);

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	neb::gfx::environ::single<neb::gfx::camera::view::Base>::init(p);
	neb::gfx::environ::three::init(p);

	//programs_.reset(new neb::gfx::glsl::program::threed("3d"));
	//programs_->init();
	
	
	
	// camera
	/*
	if(!getParent()->view_) {
		getParent()->view_.reset(new neb::gfx::camera::view::Free(self));
	}
	*/
}