uint2048& operator-=(uint2048& operand_a, const uint2048& operand_b){
	uint64_t a, b;
	uint64_t* c;
	uint8_t borrow_flag = 0u;

	for (auto i = 0u; i < 32u; ++i){
		a = operand_a.parts_[i];
		b = operand_b.parts_[i];
		c = &(operand_a.parts_[i]);

		// intrinsic function
		// sbb instruction
		// *c = a - (b + borrow)
		// borrow_flag is set to 1 if (a < (b + borrow))
		borrow_flag = _subborrow_u64(borrow_flag, a, b, c);
	}
	return operand_a;
}