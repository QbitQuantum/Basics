bool OTASCIIArmor::WriteArmoredString(OTString & strOutput,
                                      const // for "-----BEGIN OT LEDGER-----", str_type would contain "LEDGER"
                                        std::string str_type, // There's no default, to force you to enter the right string.
                                      bool bEscaped/*=false*/)
{   
    const char * szEscape = "- ";
    
    OTString strTemp;
    strTemp.Format("%s%s %s-----\n"    // "%s-----BEGIN OT ARMORED %s-----\n"
                   "Version: Open Transactions %s\n"
                   "Comment: http://github.com/FellowTraveler/Open-Transactions/wiki\n\n" // todo hardcoding.
                   "%s"                // Should already have a newline at the bottom.
                   "%s%s %s-----\n\n", // "%s-----END OT ARMORED %s-----\n"
                   bEscaped ? szEscape : "",
                   OT_BEGIN_ARMORED, 
                   str_type.c_str(),   // "%s%s %s-----\n"
                   OTLog::Version(),   // "Version: Open Transactions %s\n"
                   /* No variable */   // "Comment: http://github.com/FellowTraveler/Open-Transactions/wiki\n\n", 
                   this->Get(),        //  "%s"     <==== CONTENTS OF THIS OBJECT BEING WRITTEN...
                   bEscaped ? szEscape : "", 
                   OT_END_ARMORED, 
                   str_type.c_str());  // "%s%s %s-----\n"
    // -----------------------
    strOutput.Concatenate("%s", strTemp.Get());    
    // -----------------------
    return true;
}