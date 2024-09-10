rt_public EIF_BOOLEAN eiso(EIF_REFERENCE target, EIF_REFERENCE source)
{
	/* Compare `source ' and `target' in term of their structure:
	 * 1/ direct instances should be equal.
	 * 2/ references should be of the same dynamic type.
	 * It assumes that dynamic types of `source' and `target' are the
	 * same.
	 * Return a boolean.
	 */

	if (target == source)
		return EIF_TRUE;

#ifdef DEBUG
	dprintf(2)("eiso: source = 0x%lx [%s] target = 0x%lx [%s]\n",
		source, System(Dtype(source)).cn_generator,
		target, System(Dtype(target)).cn_generator);
#endif

		/* Check if the dynamic types are the same */
	if (Dftype(source) != Dftype(target)) {
		return EIF_FALSE;
	} else {
			/* Check iomorphism */
		return e_field_iso(target, source);
	}
}