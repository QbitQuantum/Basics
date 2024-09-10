Status InitMeasurementTable(MeasurementTable* measurementTable, const char* name, byte columns, byte rows)
{
    Status status = FindTable(name, &(measurementTable->table));
    if (status != OK)
    {
        status = CreateTable(name, columns, rows, &(measurementTable->table));
    }
    measurementTable->name = name;
    return status;
}