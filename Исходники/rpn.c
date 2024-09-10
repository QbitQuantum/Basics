stackDataT evaluateExpression(FILE *infile, Stack *S) {
    int next_char, read_ahead_char;
    int string_position = 0;
    char temp_string[MAXDIGITS];
    stackDataT data;

    while ((next_char = fgetc(infile)) != EOF) {

        // If the character is a minus, it might be an operator or it might 
        // be a negative sign
        if (next_char == MINUS) {
            // Get the next char from the stream for testing
            if ((read_ahead_char = fgetc(infile)) != EOF) {
                // Push the next char back onto the stream so it is correctly
                // processed on the next loop iteration
                if (ungetc(read_ahead_char, infile) != read_ahead_char) {
                    fprintf(stderr, "Error: Unable to parse the expression.\n");
                }
                // If the next char in the stream is a number, this minus is a
                // negative sign, add it to the number string and end this loop
                // iteration
                if (charIsANumber(read_ahead_char)) {
                    temp_string[string_position] = next_char;
                    string_position++;
                    continue;
                }
            }
        }

        // If the character is a number, add it to the temp string
        if (charIsANumber(next_char)) {
            temp_string[string_position] = next_char;
            string_position++;
        }

        // Test if the next char is whitespace between chars
        else if (charIsWhitespace(next_char)) {

            // Test if we have a number string to convert
            if (string_position > 0) {
                // Terminate the string and convert it to data
                temp_string[string_position] = '\0';
                data = atoi(temp_string);
                if (errno) {
                    // Handle number convert error
                    fprintf(
                        stderr,
                        "Error: unable to convert %s to an integer\n",
                        temp_string
                    );
                    exit(3);
                }
                // Push the data onto the stack
                push(S, data);
                // Finally, clear counter to reset temp string
                string_position = 0;
            }
        }

        // Test if the next char is an operator
        else if (charIsOperator(next_char)) {
            doSingleCalculation(S, next_char);
        }
        
        // Handle unexptected characters here
        else {
            fprintf(
                stderr, 
                "Error: the character %c is not valid.\n", 
                next_char
            );
            exit(2);
        }
    }

    // Pop the final value off the stack - that's our answer
    data = pop(S);
    
    // If there is anything left on the stack, that's an error - handle here
    if (!isEmpty(S)) {
        fprintf(
            stderr, 
            "Error: Not enough operators for the number of operands\n"
        );
        exit(4);
    }  

    return data;
}