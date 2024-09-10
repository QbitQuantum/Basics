static SECStatus DecodeItem(void* dest,
                     const SEC_ASN1Template* templateEntry,
                     SECItem* src, PLArenaPool* arena, PRBool checkTag)
{
    SECStatus rv = SECSuccess;
    SECItem temp;
    SECItem mark;
    PRBool pop = PR_FALSE;
    PRBool decode = PR_TRUE;
    PRBool save = PR_FALSE;
    unsigned long kind;
    PRBool match = PR_TRUE;
    PRBool optional = PR_FALSE;

    PR_ASSERT(src && dest && templateEntry && arena);
#if 0
    if (!src || !dest || !templateEntry || !arena)
    {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        rv = SECFailure;
    }
#endif

    if (SECSuccess == rv)
    {
        /* do the template validation */
        kind = templateEntry->kind;
        optional = (0 != (kind & SEC_ASN1_OPTIONAL));
        if (!kind)
        {
            PORT_SetError(SEC_ERROR_BAD_TEMPLATE);
            rv = SECFailure;
        }
    }

    if (SECSuccess == rv)
    {
#ifdef DEBUG
        if (kind & SEC_ASN1_DEBUG_BREAK)
        {
            /* when debugging the decoder or a template that fails to
            decode, put SEC_ASN1_DEBUG in the component that gives you
            trouble. The decoder will then get to this block and assert.
            If you want to debug the rest of the code, you can set a
            breakpoint and set dontassert to PR_TRUE, which will let
            you skip over the assert and continue the debugging session
            past it. */
            PRBool dontassert = PR_FALSE;
            PR_ASSERT(dontassert); /* set bkpoint here & set dontassert*/
        }
#endif

        if ((kind & SEC_ASN1_SKIP) ||
            (kind & SEC_ASN1_SAVE))
        {
            /* if skipping or saving this component, don't decode it */
            decode = PR_FALSE;
        }
    
        if (kind & (SEC_ASN1_SAVE | SEC_ASN1_OPTIONAL))
        {
            /* if saving this component, or if it is optional, we may not want to
               move past it, so save the position in case we have to rewind */
            mark = *src;
            if (kind & SEC_ASN1_SAVE)
            {
                save = PR_TRUE;
                if (0 == (kind & SEC_ASN1_SKIP))
                {
                    /* we will for sure have to rewind when saving this
                       component and not skipping it. This is true for all
                       legacy uses of SEC_ASN1_SAVE where the following entry
                       in the template would causes the same component to be
                       processed again */
                    pop = PR_TRUE;
                }
            }
        }

        rv = GetItem(src, &temp, PR_TRUE);
    }

    if (SECSuccess == rv)
    {
        /* now check if the component matches what we expect in the template */

        if (PR_TRUE == checkTag)

        {
            rv = MatchComponentType(templateEntry, &temp, &match, dest);
        }

        if ( (SECSuccess == rv) && (PR_TRUE != match) )
        {
            if (kind & SEC_ASN1_OPTIONAL)
            {

                /* the optional component is missing. This is not fatal. */
                /* Rewind, don't decode, and don't save */
                pop = PR_TRUE;
                decode = PR_FALSE;
                save = PR_FALSE;
            }
            else
            {
                /* a required component is missing. abort */
                PORT_SetError(SEC_ERROR_BAD_DER);
                rv = SECFailure;
            }
        }
    }

    if ((SECSuccess == rv) && (PR_TRUE == decode))
    {
        /* the order of processing here is is the tricky part */
        /* we start with our special cases */
        /* first, check the component class */
        if (kind & SEC_ASN1_INLINE)
        {
            /* decode inline template */
            rv = DecodeInline(dest, templateEntry, &temp , arena, PR_TRUE);
        }

        else
        if (kind & SEC_ASN1_EXPLICIT)
        {
            rv = DecodeExplicit(dest, templateEntry, &temp, arena);
        }
        else
        if ( (SEC_ASN1_UNIVERSAL != (kind & SEC_ASN1_CLASS_MASK)) &&

              (!(kind & SEC_ASN1_EXPLICIT)))
        {

            /* decode implicitly tagged components */
            rv = DecodeImplicit(dest, templateEntry, &temp , arena);
        }
        else
        if (kind & SEC_ASN1_POINTER)
        {
            rv = DecodePointer(dest, templateEntry, &temp, arena, PR_TRUE);
        }
        else
        if (kind & SEC_ASN1_CHOICE)
        {
            rv = DecodeChoice(dest, templateEntry, &temp, arena);
        }
        else
        if (kind & SEC_ASN1_ANY)
        {
            /* catch-all ANY type, don't decode */
            save = PR_TRUE;
            if (kind & SEC_ASN1_INNER)
            {
                /* skip the tag and length */
                SECItem newtemp = temp;
                rv = GetItem(&newtemp, &temp, PR_FALSE);
            }
        }
        else
        if (kind & SEC_ASN1_GROUP)
        {
            if ( (SEC_ASN1_SEQUENCE == (kind & SEC_ASN1_TAGNUM_MASK)) ||
                 (SEC_ASN1_SET == (kind & SEC_ASN1_TAGNUM_MASK)) )
            {
                rv = DecodeGroup(dest, templateEntry, &temp , arena);
            }
            else
            {
                /* a group can only be a SET OF or SEQUENCE OF */
                PORT_SetError(SEC_ERROR_BAD_TEMPLATE);
                rv = SECFailure;
            }
        }
        else
        if (SEC_ASN1_SEQUENCE == (kind & SEC_ASN1_TAGNUM_MASK))
        {
            /* plain SEQUENCE */
            rv = DecodeSequence(dest, templateEntry, &temp , arena);
        }
        else
        {
            /* handle all other types as "save" */
            /* we should only get here for primitive universal types */
            SECItem newtemp = temp;
            rv = GetItem(&newtemp, &temp, PR_FALSE);
            save = PR_TRUE;
            if ((SECSuccess == rv) &&
                SEC_ASN1_UNIVERSAL == (kind & SEC_ASN1_CLASS_MASK))
            {
                unsigned long tagnum = kind & SEC_ASN1_TAGNUM_MASK;
                if ( temp.len == 0 && (tagnum == SEC_ASN1_BOOLEAN ||
                                       tagnum == SEC_ASN1_INTEGER ||
                                       tagnum == SEC_ASN1_BIT_STRING ||
                                       tagnum == SEC_ASN1_OBJECT_ID ||
                                       tagnum == SEC_ASN1_ENUMERATED ||
                                       tagnum == SEC_ASN1_UTC_TIME ||
                                       tagnum == SEC_ASN1_GENERALIZED_TIME) )
                {
                    /* these types MUST have at least one content octet */
                    PORT_SetError(SEC_ERROR_BAD_DER);
                    rv = SECFailure;
                }
                else
                switch (tagnum)
                {
                /* special cases of primitive types */
                case SEC_ASN1_INTEGER:
                    {
                        /* remove leading zeroes if the caller requested
                           siUnsignedInteger
                           This is to allow RSA key operations to work */
                        SECItem* destItem = (SECItem*) ((char*)dest +
                                            templateEntry->offset);
                        if (destItem && (siUnsignedInteger == destItem->type))
                        {
                            while (temp.len > 1 && temp.data[0] == 0)
                            {              /* leading 0 */
                                temp.data++;
                                temp.len--;
                            }
                        }
                        break;
                    }

                case SEC_ASN1_BIT_STRING:
                    {
                        /* change the length in the SECItem to be the number
                           of bits */
                        temp.len = (temp.len-1)*8 - (temp.data[0] & 0x7);
                        temp.data++;
                        break;
                    }

                default:
                    {
                        break;
                    }
                }
            }
        }
    }

    if ((SECSuccess == rv) && (PR_TRUE == save))
    {
        SECItem* destItem = (SECItem*) ((char*)dest + templateEntry->offset);
        if (destItem)
        {
            /* we leave the type alone in the destination SECItem.
               If part of the destination was allocated by the decoder, in
               cases of POINTER, SET OF and SEQUENCE OF, then type is set to
               siBuffer due to the use of PORT_ArenaZAlloc*/
            destItem->data = temp.len ? temp.data : NULL;
            destItem->len = temp.len;
        }
        else
        {
            PORT_SetError(SEC_ERROR_INVALID_ARGS);
            rv = SECFailure;
        }
    }

    if (PR_TRUE == pop)
    {
        /* we don't want to move ahead, so restore the position */
        *src = mark;
    }
    return rv;
}