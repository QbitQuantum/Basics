void Opl2::initialize(
	const int sample_rate)
{
	uninitialize();

	sample_rate_ = std::max(sample_rate, get_min_sample_rate());

	emulator_ = DBOPL::Handler{};
	emulator_.Init(sample_rate_);

	is_initialized_ = true;
}