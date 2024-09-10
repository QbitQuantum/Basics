U_CAPI void U_EXPORT2
umsg_vparse(const UMessageFormat *fmt,
            const UChar    *source,
            int32_t        sourceLength,
            int32_t        *count,
            va_list        ap,
            UErrorCode     *status)
{
    //check arguments
    if(status==NULL||U_FAILURE(*status))
    {
        return;
    }
    if(fmt==NULL||source==NULL || sourceLength<-1 || count==NULL){
        *status=U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }
    if(sourceLength==-1){
        sourceLength=u_strlen(source);
    }

    UnicodeString srcString(source,sourceLength);
    Formattable *args = ((const MessageFormat*)fmt)->parse(source,*count,*status);
    UDate *aDate;
    double *aDouble;
    UChar *aString;
    int32_t* aInt;
    int64_t* aInt64;
    UnicodeString temp;
    int len =0;
    // assign formattables to varargs
    for(int32_t i = 0; i < *count; i++) {
        switch(args[i].getType()) {

        case Formattable::kDate:
            aDate = va_arg(ap, UDate*);
            if(aDate){
                *aDate = args[i].getDate();
            }else{
                *status=U_ILLEGAL_ARGUMENT_ERROR;
            }
            break;

        case Formattable::kDouble:
            aDouble = va_arg(ap, double*);
            if(aDouble){
                *aDouble = args[i].getDouble();
            }else{
                *status=U_ILLEGAL_ARGUMENT_ERROR;
            }
            break;

        case Formattable::kLong:
            aInt = va_arg(ap, int32_t*);
            if(aInt){
                *aInt = (int32_t) args[i].getLong();
            }else{
                *status=U_ILLEGAL_ARGUMENT_ERROR;
            }
            break;

        case Formattable::kInt64:
            aInt64 = va_arg(ap, int64_t*);
            if(aInt64){
                *aInt64 = args[i].getInt64();
            }else{
                *status=U_ILLEGAL_ARGUMENT_ERROR;
            }
            break;

        case Formattable::kString:
            aString = va_arg(ap, UChar*);
            if(aString){
                args[i].getString(temp);
                len = temp.length();
                temp.extract(0,len,aString);
                aString[len]=0;
            }else{
                *status= U_ILLEGAL_ARGUMENT_ERROR;
            }
            break;

        case Formattable::kObject:
            // This will never happen because MessageFormat doesn't
            // support kObject.  When MessageFormat is changed to
            // understand MeasureFormats, modify this code to do the
            // right thing. [alan]
            U_ASSERT(FALSE);
            break;

        // better not happen!
        case Formattable::kArray:
            U_ASSERT(FALSE);
            break;
        }
    }

    // clean up
    delete [] args;
}