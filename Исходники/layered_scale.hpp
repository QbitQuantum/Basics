	/** @param[in] i_scale 線形補間scale値。
	    @param[in] i_super 上位階層scale。最上位の場合は空を指定する。
	 */
	public: explicit layered_scale(
		typename this_type::lerp const&       i_scale = lerp(1),
		typename this_type::shared_ptr const& i_super = shared_ptr()):
	super_scale_(i_super),
	lerp_scale_(i_scale),
	last_scale_(i_scale.current()),
	last_count_(this_type::counter())
	{
		this_type* const a_super(i_super.get());
		if (NULL != a_super)
		{
			this->last_scale_ *= a_super->get_current();
		}
	}