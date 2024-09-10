int str9xpec_handle_part_id_command(struct command_context_s *cmd_ctx, char *cmd, char **args, int argc)
{
	flash_bank_t *bank;
	scan_field_t field;
	u8 *buffer = NULL;
	jtag_tap_t *tap;
	u32 idcode;
	str9xpec_flash_controller_t *str9xpec_info = NULL;

	if (argc < 1)
	{
		return ERROR_COMMAND_SYNTAX_ERROR;
	}

	bank = get_flash_bank_by_num(strtoul(args[0], NULL, 0));
	if (!bank)
	{
		command_print(cmd_ctx, "flash bank '#%s' is out of bounds", args[0]);
		return ERROR_OK;
	}

	str9xpec_info = bank->driver_priv;
	tap = str9xpec_info->tap;

	buffer = calloc(CEIL(32, 8), 1);

	str9xpec_set_instr(tap, ISC_IDCODE, TAP_IRPAUSE);

	field.tap = tap;
	field.num_bits = 32;
	field.out_value = NULL;
	field.out_mask = NULL;
	field.in_value = buffer;
	field.in_check_value = NULL;
	field.in_check_mask = NULL;
	field.in_handler = NULL;
	field.in_handler_priv = NULL;

	jtag_add_dr_scan(1, &field, TAP_IDLE);
	jtag_execute_queue();

	idcode = buf_get_u32(buffer, 0, 32);

	command_print(cmd_ctx, "str9xpec part id: 0x%8.8x", idcode);

	free(buffer);

	return ERROR_OK;
}