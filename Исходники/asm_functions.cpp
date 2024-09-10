int asm_cmd_in(FILE* strin, double* codes, int* cur_code)
{
	if (strin == NULL) return ASM_STRIN_BAD;
	if (codes == NULL) return ASM_BAD_CODES_POINTER;
	if (cur_code == NULL) return ASM_BAD_CUR_CODE_POINTER;

	char in_word[CMD_MAXLEN] = {};
	int cond = fscanf_s(strin, "%s", in_word, CMD_MAXLEN);
	if (cond <= 0) return ASM_SCAN_FAILED;
		
	double reg = 0;
	int ret = asm_str_convert(_strlwr(in_word), &reg);
	if (ret != ASM_OK) return ASM_BAD_IN_STR_TOKEN;

	SEC_RUN_(asm_push_code(codes, cur_code, reg));
	return ASM_OK;
}