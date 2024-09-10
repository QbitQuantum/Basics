  void writeFloat(JsonFloat value, int digits = 2) {
    if (Polyfills::isNaN(value)) return writeRaw("NaN");

    if (value < 0.0) {
      writeRaw('-');
      value = -value;
    }

    if (Polyfills::isInfinity(value)) return writeRaw("Infinity");

    short powersOf10;
    if (value > 1000 || value < 0.001) {
      powersOf10 = Polyfills::normalize(value);
    } else {
      powersOf10 = 0;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    JsonFloat rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i) rounding /= 10.0;

    value += rounding;

    // Extract the integer part of the value and print it
    JsonUInt int_part = static_cast<JsonUInt>(value);
    JsonFloat remainder = value - static_cast<JsonFloat>(int_part);
    writeInteger(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
      writeRaw('.');
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0) {
      remainder *= 10.0;
      JsonUInt toPrint = JsonUInt(remainder);
      writeInteger(JsonUInt(remainder));
      remainder -= static_cast<JsonFloat>(toPrint);
    }

    if (powersOf10 < 0) {
      writeRaw("e-");
      writeInteger(-powersOf10);
    }

    if (powersOf10 > 0) {
      writeRaw('e');
      writeInteger(powersOf10);
    }
  }