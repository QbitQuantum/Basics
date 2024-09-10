void LcdStateRunning::drawKwhStats()
{
    Settings settings;
    EepromSettings::load(settings);

    lcd.setBacklight(LCD16x2::WHITE);

    lcd.move(0,0);
    lcd.write_P(STR_STATS_KWH);

    lcd.move(0,1);
    uint16_t *p = 0;
    switch (page)
    {
        case PAGE_KWH_WEEK:
            lcd.write_P(STR_STATS_WEEK);
            p = &settings.kwh_week;
            break;

        case PAGE_KWH_MONTH:
            lcd.write_P(STR_STATS_MONTH);
            p = &settings.kwh_month;
            break;

        case PAGE_KWH_YEAR:
            lcd.write_P(STR_STATS_YEAR);
            p = &settings.kwh_year;
            break;

        case PAGE_KWH_TOTAL:
            lcd.write_P(STR_STATS_TOTAL);
            p = &settings.kwh_total;
            break;

        default:
            break;
    }

    char buffer[10] = {0};
    ltoa(p ? *p : 0, buffer, 10);

    lcd.write(": ");
    lcd.write(buffer);
    spaces(lcd, 5);
}