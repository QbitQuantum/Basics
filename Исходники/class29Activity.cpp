void String::setString(const char *string2)
{
    sPtr = new char[length + 1];
    
    if (string2 != 0)
        strcpy(sPtr, string2);
    else 
        sPtr[0] = '\0'; 
}