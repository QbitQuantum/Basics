static void zend_accel_function_hash_copy(HashTable *target, HashTable *source)
{
	zend_function *function1, *function2;
	uint idx;
	Bucket *p;
	zval *t;

	for (idx = 0; idx < source->nNumUsed; idx++) {
		p = source->arData + idx;
		if (Z_TYPE(p->val) == IS_UNDEF) continue;
		ZEND_ASSERT(p->key);
		t = zend_hash_add(target, p->key, &p->val);
		if (UNEXPECTED(t == NULL)) {
			if (p->key->len > 0 && p->key->val[0] == 0) {
				/* Mangled key */
				t = zend_hash_update(target, p->key, &p->val);
			} else {
				t = zend_hash_find(target, p->key);
				goto failure;
			}
		}
	}
	target->nInternalPointer = target->nNumOfElements ? 0 : INVALID_IDX;
	return;

failure:
	function1 = Z_PTR(p->val);
	function2 = Z_PTR_P(t);
	CG(in_compilation) = 1;
	zend_set_compiled_filename(function1->op_array.filename);
	CG(zend_lineno) = function1->op_array.opcodes[0].lineno;
	if (function2->type == ZEND_USER_FUNCTION
		&& function2->op_array.last > 0) {
		zend_error(E_ERROR, "Cannot redeclare %s() (previously declared in %s:%d)",
				   function1->common.function_name->val,
				   function2->op_array.filename->val,
				   (int)function2->op_array.opcodes[0].lineno);
	} else {
		zend_error(E_ERROR, "Cannot redeclare %s()", function1->common.function_name->val);
	}
}