 void CreateDigitFormatStr() {
    if (range > 1)
       digits = (int)ceil(log10(range-1.0));
    else
       digits = 5; // hack: default
    if (zeropad && range>1)
       formatStr.Printf(wxT("%%0%dd"), digits); // ex. "%03d" if digits is 3
    else {
       formatStr.Printf(wxT("%%0%dd"), digits);
    }
 }