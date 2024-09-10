//-------- Begin of function ButtonCustom::set_help_code -------//
//
void ButtonCustom::set_help_code(const char* helpCode)
{
	strncpy( help_code, helpCode, HELP_CODE_LEN );

	help_code[HELP_CODE_LEN] = NULL;
}