const wxString& tcNumberEditControl::GetEditValue() const
{
    static wxString convertedValue;
    convertedValue = "";

    double x = 0;
    if (editValue.ToDouble(&x))
    {
        x *= displayToDatabase;
        convertedValue.Printf("%f", x);
    }

    return convertedValue;
}