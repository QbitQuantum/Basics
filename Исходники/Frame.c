static operand pslot_to_operand( struct frame* f, int nr_locals, int pidx, bool stackonly ){
	assert( f );
	assert( f->m );

	if( stackonly || pidx >= NR_SPARE_REGS( f ) ){
#if 0
		operand r = OP_TARGETDADDR( f->m->sp, 4 * INVERSE( pidx,  2 * nr_locals ) );
#else
		operand r = OP_TARGETDADDR( f->m->fp, -(8 + 4 * pidx) );
#endif
		return r;
	} else {
		operand r = OP_TARGETREG( vreg_to_physical_reg( f, pidx ) );
		return r;
	}
			
} 