static zend_bool class_name_type_hint(const zend_op_array *op_array, uint32_t arg_num)
{
	zend_arg_info *arg_info;

	if (arg_num > 0) {
		if (op_array->fn_flags & ZEND_ACC_HAS_TYPE_HINTS) {
			if (EXPECTED(arg_num <= op_array->num_args)) {
				arg_info = &op_array->arg_info[arg_num-1];
			} else if (UNEXPECTED(op_array->fn_flags & ZEND_ACC_VARIADIC)) {
				arg_info = &op_array->arg_info[op_array->num_args];
			} else {
				return 0;
			}
			return ZEND_TYPE_IS_CLASS(arg_info->type);
		}
	} else {
		arg_info = op_array->arg_info - 1;
		return ZEND_TYPE_IS_CLASS(arg_info->type);
	}
	return 0;
}