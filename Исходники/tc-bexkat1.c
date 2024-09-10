/* Convert the instructions into frags and bytes */
void
md_assemble(char *str)
{
  char *op_start;
  char *op_end;
  char op_name[10];
  const bexkat1_opc_info_t *opcode;
  char *p;
  char pend;
  unsigned int iword;
  int nlen = 0;
  int regnum;
  expressionS arg;
  int offset;

  while (*str == ' ')
    str++;
  
  // mark opcode
  op_start = str;
  for (op_end = str;
       *op_end && !is_end_of_line[*op_end & 0xff] && *op_end != ' ';
       op_end++)
    nlen++;
  
  pend = *op_end;
  *op_end = 0;
  strncpy(op_name, op_start, 10);
  *op_end = pend;

  if (nlen == 0)
    as_bad(_("can't find opcode "));
  
  while (ISSPACE(*op_end))
    op_end++;
  
  opcode = (bexkat1_opc_info_t *) hash_find(opcode_hash_control, op_name);
  if (opcode == NULL) {
    as_bad(_("unknown opcode %s"), op_name);
    return;
  }

  iword = (opcode->type << 28) | (opcode->opcode << 24) | opcode->size;

  p = frag_more(4);

  switch (opcode->type) {
  case BEXKAT1_INH:
    if (opcode->args == 0) {
      md_number_to_chars(p, iword, 4);
    }
    if (opcode->args == 1) {
      op_end = parse_exp_save_ilp(op_end, &arg);
      if (opcode->size) {
	md_number_to_chars(p, iword, 4);
	p = frag_more(4);
	fix_new_exp(frag_now,
		    (p - frag_now->fr_literal),
		    4,
		    &arg,
		    0,
		    BFD_RELOC_32);
      } else {
	if (arg.X_op != O_constant) {
	  as_bad(_("offset is not a constant expression"));
	  ignore_rest_of_line();
	  return;
	}
	offset = arg.X_add_number;
	if (offset < -16384 || offset > 16383) {
	  as_bad(_("offset is out of range: %d\n"), offset);
	  ignore_rest_of_line();
	  return;
	}
	
	md_number_to_chars(p, iword, 4);
	fix_new_exp(frag_now,
		    (p - frag_now->fr_literal),
		    4,
		    &arg,
		    0,
		    BFD_RELOC_BEXKAT1_15);
      }
    }
    break;
  case BEXKAT1_PUSH:
    if (opcode->args == 1 && opcode->opcode == 2) // bsr
      goto branch;
    if (opcode->args == 1) {
      if (opcode->size) {
	op_end = parse_exp_save_ilp(op_end, &arg);
	md_number_to_chars(p, iword, 4);
	p = frag_more(4);
	fix_new_exp(frag_now,
		    (p - frag_now->fr_literal),
		    4,
		    &arg,
		    0,
		    BFD_RELOC_32);
      } else {
	regnum = parse_regnum(&op_end);
	if (regnum == -1)
	  return; 
	while (ISSPACE(*op_end))
	  op_end++;
	iword |= (regnum & 0xf) << 20; // A
	md_number_to_chars(p, iword, 4);
      }
    }
    if (opcode->args == 2) {
      if (*op_end != '(')
	op_end = parse_exp_save_ilp(op_end, &arg);
      else { // Implicit 0 offset to allow for indirect
	arg.X_op = O_constant;
	arg.X_add_number = 0;
      }
      
      if (*op_end != '(') {
	as_bad(_("missing open paren: %s"), op_end);
	ignore_rest_of_line();
	return;
      }
      op_end++; // burn paren
      while (ISSPACE(*op_end))
	op_end++;
      
      regnum = parse_regnum(&op_end);
      if (regnum == -1)
	return; 
      while (ISSPACE(*op_end))
	op_end++;
      iword |= (regnum & 0xf) << 20; // A
      
      if (*op_end != ')') {
	as_bad(_("missing close paren: %s"), op_end);
	ignore_rest_of_line();
	return;
      }
      op_end++;
      
      if (arg.X_op != O_constant) {
	as_bad(_("offset is not a constant expression"));
	ignore_rest_of_line();
	return;
      }
      offset = arg.X_add_number;
      if (offset < -16384 || offset > 16383) {
	as_bad(_("offset is out of range: %d\n"), offset);
	ignore_rest_of_line();
	return;
      }

      md_number_to_chars(p, iword, 4);
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  0,
		  BFD_RELOC_BEXKAT1_15);
    }
    break;
  case BEXKAT1_POP:
    if (opcode->args == 0) {
      md_number_to_chars(p, iword, 4);
    }
    if (opcode->args == 1) {
      regnum = parse_regnum(&op_end);
      if (regnum == -1)
	return; 
      while (ISSPACE(*op_end))
	op_end++;
      iword |= (regnum & 0xf) << 20; // A
      md_number_to_chars(p, iword, 4);
    }
    break;
  case BEXKAT1_MOV:
    if (opcode->opcode == 0) {
      regnum = parse_regnum(&op_end);
      if (regnum == -1)
        return; 
      while (ISSPACE(*op_end))
        op_end++;
      iword |= (regnum & 0xf) << 20; // A
      md_number_to_chars(p, iword, 4);
      break;
    }
    /* __attribute__((fallthrough)); */
  case BEXKAT1_CMP:
  case BEXKAT1_FPU:
  case BEXKAT1_FP:
  case BEXKAT1_ALU:
  case BEXKAT1_INT:
  case BEXKAT1_INTU:
    if (opcode->args > 1) {
      regnum = parse_regnum(&op_end);
      if (regnum == -1)
        return; 
      while (ISSPACE(*op_end))
        op_end++;
      iword |= (regnum & 0xf) << 20; // A

      if (*op_end != ',') {
        as_bad(_("missing comma: %s"), op_end);
        return;
      }
      op_end++;
      while (ISSPACE(*op_end))
        op_end++;
    
    }

    regnum = parse_regnum(&op_end);
    if (regnum == -1)
      return; 
    while (ISSPACE(*op_end))
      op_end++;
    iword |= (regnum & 0xf) << 16; // B

    if (opcode->args > 2) {

      if (*op_end != ',') {
	as_bad(_("missing comma: %s"), op_end);
	return;
      }
      op_end++;
      while (ISSPACE(*op_end))
	op_end++;
      
      if (opcode->opcode < 8) {
	regnum = parse_regnum(&op_end);
	if (regnum == -1)
	  return; 
	while (ISSPACE(*op_end))
	  op_end++;
	iword |= (regnum & 0xf) << 12; // C
	md_number_to_chars(p, iword, 4);
      } else {
	op_end = parse_exp_save_ilp(op_end, &arg);
	if (arg.X_op != O_constant) {
	  as_bad(_("offset is not a constant expression"));
	  ignore_rest_of_line();
	  return;
	}
	offset = arg.X_add_number;
	if (offset < -16384 || offset > 16383) {
	  as_bad(_("offset is out of range: %d\n"), offset);
	  ignore_rest_of_line();
	  return;
	}
	md_number_to_chars(p, iword, 4);
	fix_new_exp(frag_now,
		    (p - frag_now->fr_literal),
		    4,
		    &arg,
		    0,
		    BFD_RELOC_BEXKAT1_15);
      }
    } else {
      md_number_to_chars(p, iword, 4);
    }
    break;
branch:
  case BEXKAT1_BRANCH:
    md_number_to_chars(p, iword, 4);
    op_end = parse_exp_save_ilp(op_end, &arg);
    if (target_big_endian)
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  TRUE,
		  BFD_RELOC_BEXKAT1_15_PCREL);
    else
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  TRUE,
		  BFD_RELOC_BEXKAT1_15_PCREL);
    break;
  case BEXKAT1_LOAD:
  case BEXKAT1_STORE:
    // A, 
    regnum = parse_regnum(&op_end);
    if (regnum == -1)
      return; 
    while (ISSPACE(*op_end))
      op_end++;
    iword |= (regnum & 0xf) << 20; // A
    
    if (*op_end != ',') {
      as_bad(_("missing comma: %s"), op_end);
      return;
    }
    op_end++;
    while (ISSPACE(*op_end))
      op_end++;
    /* __attribute__((fallthrough)); */
  case BEXKAT1_JUMP:
    if (opcode->size) { // big address
      md_number_to_chars(p, iword, 4);
      op_end = parse_exp_save_ilp(op_end, &arg);
      p = frag_more(4);
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  0,
		  BFD_RELOC_32);
    } else { // exp(B)
      if (*op_end != '(')
	op_end = parse_exp_save_ilp(op_end, &arg);
      else { // Implicit 0 offset to allow for indirect
	arg.X_op = O_constant;
	arg.X_add_number = 0;
      }
      
      if (*op_end != '(') {
	as_bad(_("missing open paren: %s"), op_end);
	ignore_rest_of_line();
	return;
      }
      op_end++; // burn paren
      while (ISSPACE(*op_end))
	op_end++;
      
      regnum = parse_regnum(&op_end);
      if (regnum == -1)
	return; 
      while (ISSPACE(*op_end))
	op_end++;
      iword |= (regnum & 0xf) << 16; // B
      
      if (*op_end != ')') {
	as_bad(_("missing close paren: %s"), op_end);
	ignore_rest_of_line();
	return;
      }
      op_end++;
      
      if (arg.X_op != O_constant) {
	as_bad(_("offset is not a constant expression"));
	ignore_rest_of_line();
	return;
      }
      offset = arg.X_add_number;
      if (offset < -16384 || offset > 16383) {
	as_bad(_("offset is out of range: %d\n"), offset);
	ignore_rest_of_line();
	return;
      }

      md_number_to_chars(p, iword, 4);
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  0,
		  BFD_RELOC_BEXKAT1_15);
    }
    break;
  case BEXKAT1_LDI:
    regnum = parse_regnum(&op_end);
    if (regnum == -1)
      return; 
    while (ISSPACE(*op_end))
      op_end++;
    iword |= (regnum & 0xf) << 20; // A
    
    if (*op_end != ',') {
      as_bad(_("missing comma: %s"), op_end);
      return;
    }
    op_end++;
    while (ISSPACE(*op_end))
      op_end++;
    op_end = parse_exp_save_ilp(op_end, &arg);
    if (opcode->size) {
      md_number_to_chars(p, iword, 4);
      p = frag_more(4);
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  0,
		  BFD_RELOC_32);
    } else {
      if (arg.X_op != O_constant) {
	as_bad(_("offset is not a constant expression"));
	ignore_rest_of_line();
	return;
      }
      offset = arg.X_add_number;
      if (offset >= 32768) {
	as_bad(_("offset is out of range: %d\n"), offset);
	ignore_rest_of_line();
	return;
      }

      md_number_to_chars(p, iword, 4);
      fix_new_exp(frag_now,
		  (p - frag_now->fr_literal),
		  4,
		  &arg,
		  0,
		  BFD_RELOC_BEXKAT1_15);
    }
    break;
  }

  while (ISSPACE(*op_end))
    op_end++;
  if (*op_end != 0)
    as_warn("extra stuff on line ignored %s %c", op_start, *op_end);
  if (pending_reloc)
    as_bad("Something forgot to clean up\n");
  return;
}