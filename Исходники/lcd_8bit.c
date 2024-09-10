void lcd_value_int(uint8_t var)
{
    char temp[10];
    itoa(var,temp,10);
    lcd_puts(temp);
}