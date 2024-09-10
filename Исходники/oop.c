/** see http://lxr.php.net/xref/PHP_7_0/Zend/zend_vm_def.h#2892 */
static int oop_method_call_handler(zend_execute_data *execute_data)
{
    const zend_op *opline = execute_data->opline;
    zend_free_op free_op1, free_op2;
    zval *obj = NULL, *method = NULL;
    zend_class_entry *ce = NULL;
    zend_function *fbc = NULL;
    zend_execute_data *call = NULL;

    obj = zend_get_zval_ptr(opline->op1_type, &opline->op1, execute_data, &free_op1, BP_VAR_R);
    method = zend_get_zval_ptr(opline->op2_type, &opline->op2, execute_data, &free_op2, BP_VAR_R);

    if (Z_TYPE_P(obj) == IS_STRING) {
        ce = OOP_G(oop_handlers)[Z_TYPE_P(obj)];

        if (!ce) {
            return ZEND_USER_OPCODE_DISPATCH;
        }

        fbc = zend_std_get_static_method(ce, Z_STR_P(method), NULL);
        if (UNEXPECTED(fbc == NULL)) {
           php_error(E_ERROR, "Call to undefined method %s::%s()", ZSTR_VAL(ce->name), Z_STRVAL_P(method));
        }
        fbc = oop_get_indirection_func(ce, fbc, method, obj);

        call = zend_vm_stack_push_call_frame(ZEND_CALL_NESTED_FUNCTION, fbc, opline->extended_value, ce, NULL);
        call->prev_execute_data = EX(call);
        EX(call) = call;

        FREE_OP(free_op2);
        FREE_OP_IF_VAR(free_op1);

        execute_data->opline++;

        return ZEND_USER_OPCODE_CONTINUE;
    }

    return ZEND_USER_OPCODE_DISPATCH;
}