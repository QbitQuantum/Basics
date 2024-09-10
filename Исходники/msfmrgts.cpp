void MessageFormatRegressionTest::Test4031438() 
{
    UErrorCode status = U_ZERO_ERROR;
    
    UnicodeString pattern1("Impossible {1} has occurred -- status code is {0} and message is {2}.");
    UnicodeString pattern2("Double '' Quotes {0} test and quoted '{1}' test plus 'other {2} stuff'.");

    MessageFormat *messageFormatter = new MessageFormat("", status);
    failure(status, "new MessageFormat");
    
    const UBool possibleDataError = TRUE;

    //try {
        logln("Apply with pattern : " + pattern1);
        messageFormatter->applyPattern(pattern1, status);
        failure(status, "messageFormat->applyPattern");
        //Object[] params = {new Integer(7)};
        Formattable params []= {
            Formattable((int32_t)7)
        };
        UnicodeString tempBuffer;
        FieldPosition pos(FieldPosition::DONT_CARE);
        tempBuffer = messageFormatter->format(params, 1, tempBuffer, pos, status);
        if(tempBuffer != "Impossible {1} has occurred -- status code is 7 and message is {2}." || failure(status, "MessageFormat::format"))
            dataerrln("Tests arguments < substitution failed");
        logln("Formatted with 7 : " + tempBuffer);
        ParsePosition pp(0);
        int32_t count = 0;
        Formattable *objs = messageFormatter->parse(tempBuffer, pp, count);
        //if(objs[7/*params.length*/] != NULL)
        //    errln("Parse failed with more than expected arguments");

        NumberFormat *fmt = 0;
        UnicodeString temp, temp1;
        
        for (int i = 0; i < count; i++) {
            
            // convert to string if not already
            Formattable obj = objs[i];
            temp.remove();
            if(obj.getType() == Formattable::kString)
                temp = obj.getString(temp);
            else {
                fmt = NumberFormat::createInstance(status);
                switch (obj.getType()) {
                case Formattable::kLong: fmt->format(obj.getLong(), temp); break;
                case Formattable::kInt64: fmt->format(obj.getInt64(), temp); break;
                case Formattable::kDouble: fmt->format(obj.getDouble(), temp); break;
                default: break;
                }
            }

            // convert to string if not already
            Formattable obj1 = params[i];
            temp1.remove();
            if(obj1.getType() == Formattable::kString)
                temp1 = obj1.getString(temp1);
            else {
                fmt = NumberFormat::createInstance(status);
                switch (obj1.getType()) {
                case Formattable::kLong: fmt->format(obj1.getLong(), temp1); break;
                case Formattable::kInt64: fmt->format(obj1.getInt64(), temp1); break;
                case Formattable::kDouble: fmt->format(obj1.getDouble(), temp1); break;
                default: break;
                }
            }

            //if (objs[i] != NULL && objs[i].getString(temp1) != params[i].getString(temp2)) {
            if (temp != temp1) {
                errln("Parse failed on object " + objs[i].getString(temp1) + " at index : " + i);
            }       
        }

        delete fmt;
        delete [] objs;

        // {sfb} does this apply?  no way to really pass a null Formattable, 
        // only a null array

        /*tempBuffer = messageFormatter->format(null, tempBuffer, FieldPosition(FieldPosition::DONT_CARE), status);
        if (tempBuffer != "Impossible {1} has occurred -- status code is {0} and message is {2}." || failure(status, "messageFormat->format"))
            errln("Tests with no arguments failed");
        logln("Formatted with null : " + tempBuffer);*/
        logln("Apply with pattern : " + pattern2);
        messageFormatter->applyPattern(pattern2, status);
        failure(status, "messageFormatter->applyPattern", possibleDataError);
        tempBuffer.remove();
        tempBuffer = messageFormatter->format(params, 1, tempBuffer, pos, status);
        if (tempBuffer != "Double ' Quotes 7 test and quoted {1} test plus other {2} stuff.")
            dataerrln("quote format test (w/ params) failed. - %s", u_errorName(status));
        logln("Formatted with params : " + tempBuffer);
        
        /*tempBuffer = messageFormatter->format(null);
        if (!tempBuffer.equals("Double ' Quotes {0} test and quoted {1} test plus other {2} stuff."))
            errln("quote format test (w/ null) failed.");
        logln("Formatted with null : " + tempBuffer);
        logln("toPattern : " + messageFormatter.toPattern());*/
    /*} catch (Exception foo) {
        errln("Exception when formatting in bug 4031438. "+foo.getMessage());
    }*/
        delete messageFormatter;
}