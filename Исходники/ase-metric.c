static inline Lisp_Object
_ase_metric_euclidean_1dim_fast(Lisp_Object a, Lisp_Object b)
{
	return Fabs(ent_binop(ASE_BINARY_OP_DIFF, a, b));
}