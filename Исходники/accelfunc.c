double handle_op_power(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = atof(front, cgc_strlen(front) + 1, is_bad_formula);
    free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = atof(front, cgc_strlen(front) + 1, is_bad_formula);
    free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand2 == 0.0)
        result = 1.0;
    else if (operand2 == 1.0)
        result = operand1;
    else if (isnan(operand2))
        result = operand2;
    else if (operand1 == 0 && operand2 > 0)
        result = 0.0;
    else if (operand1 < 0 && remainder(operand2, 1) == 0.0)
        result = pow(-operand1, operand2) * (remainder(operand2, 2) == 0 ? 1 : -1);
    else
        result = pow(operand1, operand2);
    goto done;

error:
    clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}