long fx_numeric_field::change_on_digit(int sign)
{
    FXString txt = getText();
    int pos = getCursorPos();

    int pow_exp, dot_pos;
    int norm = get_normalized_int (txt.text(), pow_exp, dot_pos);

    if (dot_pos < 0) return 0;

    int pos_exp = dot_pos - pos;
    if (pos_exp < 0)
        pos_exp ++;
    int inc_abs = ipow10 (pos_exp + pow_exp);

    norm += sign * inc_abs;

    FXString new_txt = denormalize (norm, pow_exp, dot_pos);
    int new_pos = dot_pos - pos_exp;
    if (pos_exp < 0)
        new_pos ++;

    setText(new_txt);
    setCursorPos(new_pos);

    if (target)
        target->tryHandle(this, FXSEL(SEL_CHANGED,message), (void*)new_txt.text());

    return 1;
}