/**
 *   Read the current temperature in degrees F.
 *
 *   @return temperature in units of 0.1 degrees F
 */
int32_t LM92::ReadTempC()
{
    int32_t value;

    if ((value = ReadRaw()) == -999)
        return -999;
    
    // Convert from degC to degF.
    // See the LM72_92.xls Spreadsheet in the .../unit_test directory for additional information.    
    return ((5 * value) / 64);
}