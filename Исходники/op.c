// TODO: use esil here?
R_API char *r_anal_op_to_string(RAnal *anal, RAnalOp *op) {
	RAnalFunction *f;
	char ret[128];
	char *cstr;
	char *r0 = r_anal_value_to_string (op->dst);
	char *a0 = r_anal_value_to_string (op->src[0]);
	char *a1 = r_anal_value_to_string (op->src[1]);

	switch (op->type) {
	case R_ANAL_OP_TYPE_MOV:
		snprintf (ret, sizeof (ret), "%s = %s", r0, a0);
		break;
	case R_ANAL_OP_TYPE_CJMP:
		{
		RAnalBlock *bb = r_anal_bb_from_offset (anal, op->addr);
		if (bb) {
			cstr = r_anal_cond_to_string (bb->cond);
			snprintf (ret, sizeof (ret), "if (%s) goto 0x%"PFMT64x, cstr, op->jump);
			free (cstr);
		} else snprintf (ret, sizeof (ret), "if (%s) goto 0x%"PFMT64x, "unk", op->jump);
		}
		break;
	case R_ANAL_OP_TYPE_JMP:
		snprintf (ret, sizeof (ret), "goto 0x%"PFMT64x, op->jump);
		break;
	case R_ANAL_OP_TYPE_UJMP:
		snprintf (ret, sizeof (ret), "goto %s", r0);
		break;
	case R_ANAL_OP_TYPE_PUSH:
	case R_ANAL_OP_TYPE_UPUSH:
		snprintf (ret, sizeof (ret), "push %s", a0);
		break;
	case R_ANAL_OP_TYPE_POP:
		snprintf (ret, sizeof (ret), "pop %s", r0);
		break;
	case R_ANAL_OP_TYPE_UCALL:
		snprintf (ret, sizeof (ret), "%s()", r0);
		break;
	case R_ANAL_OP_TYPE_CALL:
		f = r_anal_get_fcn_in (anal, op->jump, R_ANAL_FCN_TYPE_NULL);
		if (f) snprintf (ret, sizeof (ret), "%s()", f->name);
		else  snprintf (ret, sizeof (ret), "0x%"PFMT64x"()", op->jump);
		break;
	case R_ANAL_OP_TYPE_CCALL:
		f = r_anal_get_fcn_in (anal, op->jump, R_ANAL_FCN_TYPE_NULL);
		{
		RAnalBlock *bb = r_anal_bb_from_offset (anal, op->addr);
		if (bb) {
			cstr = r_anal_cond_to_string (bb->cond);
			if (f) snprintf (ret, sizeof (ret), "if (%s) %s()", cstr, f->name);
			else snprintf (ret, sizeof (ret), "if (%s) 0x%"PFMT64x"()", cstr, op->jump);
			free (cstr);
		} else {
			if (f) snprintf (ret, sizeof (ret), "if (unk) %s()", f->name);
			else snprintf (ret, sizeof (ret), "if (unk) 0x%"PFMT64x"()", op->jump);
		}
		}
		break;
	case R_ANAL_OP_TYPE_ADD:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s += %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s + %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_SUB:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s -= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s - %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_MUL:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s *= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s * %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_DIV:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s /= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s / %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_AND:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s &= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s & %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_OR:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s |= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s | %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_XOR:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s ^= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s ^ %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_LEA:
		snprintf (ret, sizeof (ret), "%s -> %s", r0, a0);
		break;
	case R_ANAL_OP_TYPE_CMP:
		memcpy (ret, ";", 2);
		break;
	case R_ANAL_OP_TYPE_NOP:
		memcpy (ret, "nop", 4);
		break;
	case R_ANAL_OP_TYPE_RET:
		memcpy (ret, "ret", 4);
		break;
	case R_ANAL_OP_TYPE_CRET:
		{
		RAnalBlock *bb = r_anal_bb_from_offset (anal, op->addr);
		if (bb) {
			cstr = r_anal_cond_to_string (bb->cond);
			snprintf (ret, sizeof (ret), "if (%s) ret", cstr);
			free (cstr);
		} else memcpy (ret, "if (unk) ret", 13);
		}
		break;
	case R_ANAL_OP_TYPE_LEAVE:
		memcpy (ret, "leave", 6);
		break;
	case R_ANAL_OP_TYPE_MOD:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "%s %%= %s", r0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s %% %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_XCHG:
		if (a1 == NULL || !strcmp (a0, a1))
			snprintf (ret, sizeof (ret), "tmp = %s; %s = %s; %s = tmp", r0, r0, a0, a0);
		else snprintf (ret, sizeof (ret), "%s = %s ^ %s", r0, a0, a1);
		break;
	case R_ANAL_OP_TYPE_ROL:
	case R_ANAL_OP_TYPE_ROR:
	case R_ANAL_OP_TYPE_SWITCH:
	case R_ANAL_OP_TYPE_CASE:
		eprintf ("Command not implemented.\n");
		free (r0);
		free (a0);
		free (a1);
		return NULL;
	default:
		free (r0);
		free (a0);
		free (a1);
		return NULL;
	}
	free (r0);
	free (a0);
	free (a1);
	return strdup (ret);
}