	_FORCE_INLINE_ int32_tMULSHIFT_S32 (
		int32_t Factor1,
		int32_t Factor2,
		uint8_t Bits
					) {

			return __ll_rshift (
					__emul ( Factor1, Factor2 ),
			Bits
						);
					}