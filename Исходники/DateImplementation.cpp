void
DateImplementation::GetDateComponent(CompoundString *bs, DateData componentType, int adjust)
{
    double value = this->GetDateData(componentType, true /* fUTC */, m_scriptContext);
    if(Js::NumberUtilities::IsFinite(value))
    {
        const int ival = (int)value + adjust;
        const int ivalAbs = ival < 0 ? -ival : ival;

        switch(componentType)
        {
        case DateData::FullYear:
            if(ival < 0 || ival > 9999)
            {
                // ES5 spec section 15.9.1.15.1 states that for years outside the range 0-9999, the expanded year
                // representation should:
                //     - always include the sign
                //     - have 2 extra digits (6 digits total)
                bs->AppendChars(ival < 0 ? _u('-') : _u('+'));
                if(ivalAbs < 100000)
                {
                    bs->AppendChars(_u('0'));
                    if(ivalAbs < 10000)
                    {
                        bs->AppendChars(_u('0'));
                    }
                }
            }

            // Years are zero-padded to at least 4 digits in ES5
            if(ivalAbs < 1000)
            {
                bs->AppendChars(_u('0'));
                // will fall through to next case for additional padding
            }
            else
            {
                break;
            }
        // fall through

        case DateData::Milliseconds:
            if (ivalAbs < 100)
            {
                bs->AppendChars(_u('0'));
                // will fall through to next case for additional padding
            }
            else
            {
                break;
            }
        // fall through

        default:
            if (ivalAbs < 10)
            {
                bs->AppendChars(_u('0'));
            }
        }

        // _itow_s makes use of max 12 bytes for a base-10 32-bit int (_u("-2147483648\0")), although we don't need the sign
        // and our numbers shouldn't be that big anyway
        bs->AppendChars(
            ivalAbs,
            10,
            [](const int value, char16 *const buffer, const CharCount charCapacity)
        {
            errno_t err = _itow_s(value, buffer, charCapacity, 10);
            Assert(err == 0);
        });
    }
}