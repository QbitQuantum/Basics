asn_enc_rval_t
NativeEnumerated_encode_uper(asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po) {
	asn_INTEGER_specifics_t *specs = (asn_INTEGER_specifics_t *)td->specifics;
	asn_enc_rval_t er;
	long native, value;
	asn_per_constraint_t *ct;
	int inext = 0;
	asn_INTEGER_enum_map_t key;
	asn_INTEGER_enum_map_t *kf;

	if(!sptr) _ASN_ENCODE_FAILED;
	if(!specs) _ASN_ENCODE_FAILED;

	if(constraints) ct = &constraints->value;
	else if(td->per_constraints) ct = &td->per_constraints->value;
	else _ASN_ENCODE_FAILED;	/* Mandatory! */

	ASN_DEBUG("Encoding %s as NativeEnumerated", td->name);

	er.encoded = 0;

	native = *(long *)sptr;
	if(native < 0) _ASN_ENCODE_FAILED;

	key.nat_value = native;
	kf = bsearch(&key, specs->value2enum, specs->map_count,
		sizeof(key), NativeEnumerated__compar_value2enum);
	if(!kf) {
		ASN_DEBUG("No element corresponds to %ld", native);
		_ASN_ENCODE_FAILED;
	}
	value = kf - specs->value2enum;

	if(ct->range_bits >= 0) {
		int cmpWith = specs->extension
				? specs->extension - 1 : specs->map_count;
		if(value >= cmpWith)
			inext = 1;
	}
	if(ct->flags & APC_EXTENSIBLE) {
		if(per_put_few_bits(po, inext, 0))
			_ASN_ENCODE_FAILED;
		ct = 0;
	} else if(inext) {
		_ASN_ENCODE_FAILED;
	}

	if(ct && ct->range_bits >= 0) {
		if(per_put_few_bits(po, value, ct->range_bits))
			_ASN_ENCODE_FAILED;
		_ASN_ENCODED_OK(er);
	}

	if(!specs->extension)
		_ASN_ENCODE_FAILED;

	/*
	 * X.691, #10.6: normally small non-negative whole number;
	 */
	if(uper_put_nsnnwn(po, value - (specs->extension - 1)))
		_ASN_ENCODE_FAILED;

	_ASN_ENCODED_OK(er);
}