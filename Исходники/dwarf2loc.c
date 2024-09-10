static void
dwarf2_tracepoint_var_ref (struct symbol *symbol, struct agent_expr *ax,
			   struct axs_value *value, gdb_byte *data,
			   int size)
{
  if (size == 0)
    error (_("Symbol \"%s\" has been optimized out."),
	   SYMBOL_PRINT_NAME (symbol));

  if (size == 1
      && data[0] >= DW_OP_reg0
      && data[0] <= DW_OP_reg31)
    {
      value->kind = axs_lvalue_register;
      value->u.reg = data[0] - DW_OP_reg0;
    }
  else if (data[0] == DW_OP_regx)
    {
      ULONGEST reg;
      read_uleb128 (data + 1, data + size, &reg);
      value->kind = axs_lvalue_register;
      value->u.reg = reg;
    }
  else if (data[0] == DW_OP_fbreg)
    {
      /* And this is worse than just minimal; we should honor the frame base
	 as above.  */
      int frame_reg;
      LONGEST frame_offset;
      gdb_byte *buf_end;

      buf_end = read_sleb128 (data + 1, data + size, &frame_offset);
      if (buf_end != data + size)
	error (_("Unexpected opcode after DW_OP_fbreg for symbol \"%s\"."),
	       SYMBOL_PRINT_NAME (symbol));

      gdbarch_virtual_frame_pointer (current_gdbarch, 
				     ax->scope, &frame_reg, &frame_offset);
      ax_reg (ax, frame_reg);
      ax_const_l (ax, frame_offset);
      ax_simple (ax, aop_add);

      value->kind = axs_lvalue_memory;
    }
  else if (data[0] >= DW_OP_breg0
	   && data[0] <= DW_OP_breg31)
    {
      unsigned int reg;
      LONGEST offset;
      gdb_byte *buf_end;

      reg = data[0] - DW_OP_breg0;
      buf_end = read_sleb128 (data + 1, data + size, &offset);
      if (buf_end != data + size)
	error (_("Unexpected opcode after DW_OP_breg%u for symbol \"%s\"."),
	       reg, SYMBOL_PRINT_NAME (symbol));

      ax_reg (ax, reg);
      ax_const_l (ax, offset);
      ax_simple (ax, aop_add);

      value->kind = axs_lvalue_memory;
    }
  else
    error (_("Unsupported DWARF opcode 0x%x in the location of \"%s\"."),
	   data[0], SYMBOL_PRINT_NAME (symbol));
}