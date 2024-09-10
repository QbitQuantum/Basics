static void showSensorsPage(void)
{
    uint8_t rowIndex = PAGE_TITLE_LINE_COUNT;
    static const char *format = "%s %5d %5d %5d";

    i2c_OLED_set_line(bus, rowIndex++);
    i2c_OLED_send_string(bus, "        X     Y     Z");

    if (sensors(SENSOR_ACC)) {
        tfp_sprintf(lineBuffer, format, "ACC", lrintf(acc.accADC[X]), lrintf(acc.accADC[Y]), lrintf(acc.accADC[Z]));
        padLineBuffer();
        i2c_OLED_set_line(bus, rowIndex++);
        i2c_OLED_send_string(bus, lineBuffer);
    }

    if (sensors(SENSOR_GYRO)) {
        tfp_sprintf(lineBuffer, format, "GYR", lrintf(gyro.gyroADCf[X]), lrintf(gyro.gyroADCf[Y]), lrintf(gyro.gyroADCf[Z]));
        padLineBuffer();
        i2c_OLED_set_line(bus, rowIndex++);
        i2c_OLED_send_string(bus, lineBuffer);
    }

#ifdef USE_MAG
    if (sensors(SENSOR_MAG)) {
        tfp_sprintf(lineBuffer, format, "MAG", lrintf(mag.magADC[X]), lrintf(mag.magADC[Y]), lrintf(mag.magADC[Z]));
        padLineBuffer();
        i2c_OLED_set_line(bus, rowIndex++);
        i2c_OLED_send_string(bus, lineBuffer);
    }
#endif

    tfp_sprintf(lineBuffer, format, "I&H", attitude.values.roll, attitude.values.pitch, DECIDEGREES_TO_DEGREES(attitude.values.yaw));
    padLineBuffer();
    i2c_OLED_set_line(bus, rowIndex++);
    i2c_OLED_send_string(bus, lineBuffer);

    /*
    uint8_t length;

    ftoa(EstG.A[X], lineBuffer);
    length = strlen(lineBuffer);
    while (length < HALF_SCREEN_CHARACTER_COLUMN_COUNT) {
        lineBuffer[length++] = ' ';
        lineBuffer[length+1] = 0;
    }
    ftoa(EstG.A[Y], lineBuffer + length);
    padLineBuffer();
    i2c_OLED_set_line(bus, rowIndex++);
    i2c_OLED_send_string(bus, lineBuffer);

    ftoa(EstG.A[Z], lineBuffer);
    length = strlen(lineBuffer);
    while (length < HALF_SCREEN_CHARACTER_COLUMN_COUNT) {
        lineBuffer[length++] = ' ';
        lineBuffer[length+1] = 0;
    }
    ftoa(smallAngle, lineBuffer + length);
    padLineBuffer();
    i2c_OLED_set_line(bus, rowIndex++);
    i2c_OLED_send_string(bus, lineBuffer);
    */

}