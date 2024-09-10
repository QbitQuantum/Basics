/**
*	Calling "checkNewInput", which takes keyboard input, and returning
*   it if "checkNewInput" returns 'true'. Otherwise displays error message
*   and calling the function again.
*
*	@param  char*
*
*	@return bool
*/
char* IOcontrol::getLineInput(const char* errorMessage) {
    char input[MAX_INPUT_LENG];
    bool correctInput = false;
    int i = 0;

    while (true) {
        cin.getline(input, MAX_INPUT_LENG);

        if (checkNewInput(input)) {
            break;
        }
        cout << errorMessage;
    }
    char output[MAX_INPUT_LENG];
    strcpy(output, input);

    return output;
}