static inline VALUE
vm_call_method(rb_thread_t *th, rb_control_frame_t *cfp,
               int num, const rb_block_t *blockptr, VALUE flag,
               ID id, const rb_method_entry_t *me, VALUE recv)
{
    VALUE val;

start_method_dispatch:

    if (me != 0) {
        if ((me->flag == 0)) {
normal_method_dispatch:
            switch (me->def->type) {
            case VM_METHOD_TYPE_ISEQ: {
                vm_setup_method(th, cfp, recv, num, blockptr, flag, me);
                return Qundef;
            }
            case VM_METHOD_TYPE_NOTIMPLEMENTED:
            case VM_METHOD_TYPE_CFUNC: {
                val = vm_call_cfunc(th, cfp, num, recv, blockptr, me);
                break;
            }
            case VM_METHOD_TYPE_ATTRSET: {
                if (num != 1) {
                    rb_raise(rb_eArgError, "wrong number of arguments (%d for 1)", num);
                }
                val = rb_ivar_set(recv, me->def->body.attr.id, *(cfp->sp - 1));
                cfp->sp -= 2;
                break;
            }
            case VM_METHOD_TYPE_IVAR: {
                if (num != 0) {
                    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0)", num);
                }
                val = rb_attr_get(recv, me->def->body.attr.id);
                cfp->sp -= 1;
                break;
            }
            case VM_METHOD_TYPE_MISSING: {
                VALUE *argv = ALLOCA_N(VALUE, num+1);
                argv[0] = ID2SYM(me->def->original_id);
                MEMCPY(argv+1, cfp->sp - num, VALUE, num);
                cfp->sp += - num - 1;
                val = rb_funcall2(recv, rb_intern("method_missing"), num+1, argv);
                break;
            }
            case VM_METHOD_TYPE_BMETHOD: {
                VALUE *argv = ALLOCA_N(VALUE, num);
                MEMCPY(argv, cfp->sp - num, VALUE, num);
                cfp->sp += - num - 1;
                val = vm_call_bmethod(th, recv, num, argv, blockptr, me);
                break;
            }
            case VM_METHOD_TYPE_ZSUPER: {
                VALUE klass = RCLASS_SUPER(me->klass);
                me = rb_method_entry(klass, id);

                if (me != 0) {
                    goto normal_method_dispatch;
                }
                else {
                    goto start_method_dispatch;
                }
            }
            case VM_METHOD_TYPE_OPTIMIZED: {
                switch (me->def->body.optimize_type) {
                case OPTIMIZED_METHOD_TYPE_SEND: {
                    rb_control_frame_t *reg_cfp = cfp;
                    rb_num_t i = num - 1;
                    VALUE sym;

                    if (num == 0) {
                        rb_raise(rb_eArgError, "no method name given");
                    }

                    sym = TOPN(i);
                    id = SYMBOL_P(sym) ? SYM2ID(sym) : rb_to_id(sym);
                    /* shift arguments */
                    if (i > 0) {
                        MEMMOVE(&TOPN(i), &TOPN(i-1), VALUE, i);
                    }
                    me = rb_method_entry(CLASS_OF(recv), id);
                    num -= 1;
                    DEC_SP(1);
                    flag |= VM_CALL_FCALL_BIT | VM_CALL_OPT_SEND_BIT;

                    goto start_method_dispatch;
                }
                case OPTIMIZED_METHOD_TYPE_CALL: {
                    rb_proc_t *proc;
                    int argc = num;
                    VALUE *argv = ALLOCA_N(VALUE, num);
                    GetProcPtr(recv, proc);
                    MEMCPY(argv, cfp->sp - num, VALUE, num);
                    cfp->sp -= num + 1;

                    val = rb_vm_invoke_proc(th, proc, proc->block.self, argc, argv, blockptr);
                    break;
                }
                default:
                    rb_bug("eval_invoke_method: unsupported optimized method type (%d)",
                           me->def->body.optimize_type);
                }
                break;
            }
            default: {
                rb_bug("eval_invoke_method: unsupported method type (%d)", me->def->type);
                break;
            }
            }
        }
        else {
            int noex_safe;

            if (!(flag & VM_CALL_FCALL_BIT) &&
                    (me->flag & NOEX_MASK) & NOEX_PRIVATE) {
                int stat = NOEX_PRIVATE;

                if (flag & VM_CALL_VCALL_BIT) {
                    stat |= NOEX_VCALL;
                }
                val = vm_method_missing(th, id, recv, num, blockptr, stat);
            }
            else if (!(flag & VM_CALL_OPT_SEND_BIT) && (me->flag & NOEX_MASK) & NOEX_PROTECTED) {
                VALUE defined_class = me->klass;

                if (RB_TYPE_P(defined_class, T_ICLASS)) {
                    defined_class = RBASIC(defined_class)->klass;
                }

                if (!rb_obj_is_kind_of(cfp->self, defined_class)) {
                    val = vm_method_missing(th, id, recv, num, blockptr, NOEX_PROTECTED);
                }
                else {
                    goto normal_method_dispatch;
                }
            }
            else if ((noex_safe = NOEX_SAFE(me->flag)) > th->safe_level &&
                     (noex_safe > 2)) {
                rb_raise(rb_eSecurityError, "calling insecure method: %s", rb_id2name(id));
            }
            else {
                goto normal_method_dispatch;
            }
        }
    }
    else {
        /* method missing */
        int stat = 0;
        if (flag & VM_CALL_VCALL_BIT) {
            stat |= NOEX_VCALL;
        }
        if (flag & VM_CALL_SUPER_BIT) {
            stat |= NOEX_SUPER;
        }
        if (id == idMethodMissing) {
            VALUE *argv = ALLOCA_N(VALUE, num);
            vm_method_missing_args(th, argv, num - 1, 0, stat);
            rb_raise_method_missing(th, num, argv, recv, stat);
        }
        else {
            val = vm_method_missing(th, id, recv, num, blockptr, stat);
        }
    }

    RUBY_VM_CHECK_INTS();
    return val;
}