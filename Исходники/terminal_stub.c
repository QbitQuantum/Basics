static PWSTR get_title(void)
{
	size_t max_length = 256;
	PWSTR result = malloc(max_length * sizeof(WCHAR));
	while(GetConsoleTitleW(result, max_length) > 0){
		max_length *= 2;
		PWSTR new_result = realloc(result, max_length * sizeof(WCHAR));
		if(new_result == NULL){
			free(result);
			caml_raise_out_of_memory();
		}
		result = new_result;
	}
	return result;
}