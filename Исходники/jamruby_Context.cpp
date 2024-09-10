jamruby_context::~jamruby_context()
{
	std::for_each(classes.begin(), classes.end(), destruct_class(getEnv()));
	classes.clear();
}