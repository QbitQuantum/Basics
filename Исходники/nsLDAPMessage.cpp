// if getP is true, we get the attributes by recursing once
// (without getP set) in order to fill in *attrCount, then allocate
// and fill in the *aAttributes.  
// 
// if getP is false, just fill in *attrCount and return
// 
nsresult
nsLDAPMessage::IterateAttributes(PRUint32 *aAttrCount, char** *aAttributes, 
                 bool getP)
{
    BerElement *position;
    nsresult rv;

    if (!aAttrCount || !aAttributes ) {
        return NS_ERROR_INVALID_POINTER;
    }

    // if we've been called from GetAttributes, recurse once in order to
    // count the elements in this message.
    //
    if (getP) {
        *aAttributes = 0;
        *aAttrCount = 0;

        rv = IterateAttributes(aAttrCount, aAttributes, false);
        if (NS_FAILED(rv))
            return rv;

        // create an array of the appropriate size
        //
        *aAttributes = static_cast<char **>(nsMemory::Alloc(*aAttrCount *
                                                      sizeof(char *)));
        if (!*aAttributes) {
            return NS_ERROR_OUT_OF_MEMORY;
        }
    } 

    // get the first attribute
    //
    char *attr = ldap_first_attribute(mConnectionHandle, 
                                      mMsgHandle, 
                                      &position);
    if (!attr) {
        return IterateAttrErrHandler(ldap_get_lderrno(mConnectionHandle, 0, 0),
                                     aAttrCount, aAttributes, position);
    }

    // if we're getting attributes, try and fill in the first field
    //
    if (getP) {
        (*aAttributes)[0] = nsCRT::strdup(attr);
        if (!(*aAttributes)[0]) {
            ldap_memfree(attr);
            nsMemory::Free(*aAttributes);
            return NS_ERROR_OUT_OF_MEMORY;
        }

        // note that we start counting again, in order to keep our place in 
        // the array so that we can unwind gracefully and avoid leakage if
        // we hit an error as we're filling in the array
        //
        *aAttrCount = 1;
    } else {

        // otherwise just update the count
        //
        *aAttrCount = 1;
    }
    ldap_memfree(attr);

    while (1) {
    
        // get the next attribute
        //
        attr = ldap_next_attribute(mConnectionHandle, mMsgHandle, position);

        // check to see if there is an error, or if we're just done iterating
        //
        if (!attr) {
            
            // bail out if there's an error
            //
            PRInt32 lderrno = ldap_get_lderrno(mConnectionHandle, 0, 0);
            if (lderrno != LDAP_SUCCESS) {
                return IterateAttrErrHandler(lderrno, aAttrCount, aAttributes, 
                                             position);
            }

            // otherwise, there are no more attributes; we're done with
            // the while loop
            //
            break;

        } else if (getP) {

            // if ldap_next_attribute did return successfully, and 
            // we're supposed to fill in a value, do so.
            //
            (*aAttributes)[*aAttrCount] = nsCRT::strdup(attr);
            if (!(*aAttributes)[*aAttrCount]) {
                ldap_memfree(attr);
                return IterateAttrErrHandler(LDAP_NO_MEMORY, aAttrCount, 
                                             aAttributes, position);
            }
       
        }
        ldap_memfree(attr);

        // we're done using *aAttrCount as a c-style array index (ie starting
        // at 0).  update it to reflect the number of elements now in the array
        //
        *aAttrCount += 1;
    }

    // free the position pointer, if necessary
    //
    if (position) {
        ldap_ber_free(position, 0);
    }

    return NS_OK;
}