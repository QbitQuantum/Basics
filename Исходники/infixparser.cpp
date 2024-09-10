void ParsedObject::ReadExpression(LispInt depth)
{
    ReadAtom();

    for (;;) {
        //Handle special case: a[b]. a is matched with lowest precedence!!
        if (iLookAhead == iParser.iEnvironment.iProgOpen->String()) {
            // Match opening bracket
            MatchToken(iLookAhead);
            // Read "index" argument
            ReadExpression(KMaxPrecedence);
            // Match closing bracket
            if (iLookAhead != iParser.iEnvironment.iProgClose->String())
                throw LispErrGeneric(std::string("Expecting a ] close bracket for program block, but got ") + *iLookAhead + std::string(" instead"));

            MatchToken(iLookAhead);
            // Build into Ntn(...)
            const LispString* theOperator = iParser.iEnvironment.iNth->String();
            InsertAtom(theOperator);
            Combine(2);
        } else {
            LispOperators::const_iterator opi = iParser.iInfixOperators.find(iLookAhead);
            
            if (opi == iParser.iInfixOperators.end()) {
                if (!IsSymbolic((*iLookAhead)[0]))
                    return;
                
                const std::size_t origlen = iLookAhead->size();
                std::size_t len = origlen;

                while (len > 1) {
                    len -= 1;
                    const LispString* lookUp =
                            iParser.iEnvironment.HashTable().LookUp(iLookAhead->substr(0, len));

                    opi = iParser.iInfixOperators.find(lookUp);

                    if (opi != iParser.iInfixOperators.end()) {

                        const LispString* lookUpRight =
                                iParser.iEnvironment.HashTable().LookUp(iLookAhead->substr(len, origlen - len));

                        if (iParser.iPrefixOperators.find(lookUpRight) != iParser.iPrefixOperators.end()) {
                            iLookAhead = lookUp;
                            LispInput& input = iParser.iInput;
                            LispInt newPos = input.Position() - (origlen - len);
                            input.SetPosition(newPos);
                            break;
                        }

                        opi = iParser.iInfixOperators.end();
                    }
                }

                if (opi == iParser.iInfixOperators.end())
                    return;
            }

            
            if (depth < opi->second.iPrecedence)
                return;
            LispInt upper = opi->second.iPrecedence;
            if (!opi->second.iRightAssociative)
                upper--;
            GetOtherSide(2, upper);
        }
    }
}