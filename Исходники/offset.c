/* Size of a simple object. */
rt_public size_t eif_objsiz(size_t nb_ref, size_t nb_char, size_t nb_int16, size_t nb_int32, size_t nb_r32, size_t nb_ptr, size_t nb_int64, size_t nb_r64)
{
	size_t to_add = eif_r64off(nb_ref,nb_char, nb_int16,nb_int32,nb_r32,nb_ptr, nb_int64) + R64ACS(nb_r64);
	return to_add + REMAINDER(to_add);
}