void vm_floor_float_to_int(const ScriptArguments& args)
{
	/// @todo Not sure if this might round to zero
	*args[0].globalInteger = floorf(*args[1].globalReal);
}