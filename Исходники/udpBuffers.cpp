/*------------------------------------ convertBufferToAtoms ---*/
t_atom *
convertBufferToAtoms(void *        xx,
                     t_handle      aBuffer,
                     sockaddr_in & sender,
                     long &        numAtoms,
                     const long    numBytes,
                     const bool    rawMode)
{
    long            outputSize;
    t_atom *        result = NULL;
    unsigned char * walker = reinterpret_cast<unsigned char *>(*aBuffer);

    if (rawMode)
    {
        outputSize = numBytes + 2;
        result = GET_BYTES(outputSize, t_atom);
        if (result)
        {
            t_atom * thisAtom = result;
            char     hostAddr[NI_MAXHOST + 1];

            getnameinfo(reinterpret_cast<sockaddr *>(&sender), sizeof(sender), hostAddr,
                        sizeof(hostAddr), NULL, 0, NI_NUMERICHOST);
            atom_setsym(thisAtom, gensym(hostAddr));
            ++thisAtom;
            atom_setlong(thisAtom, TO_INT(sender.sin_port));
            ++thisAtom;
            for (short ii = 0; ii < numBytes; ++ii, ++thisAtom, ++walker)
            {
                atom_setlong(thisAtom, TO_INT(*walker));
            }
        }
    }
    else
    {
        short numElements;
        short sanityCheck;
        long  calcBytes;
        bool  okSoFar = true;

        memcpy(&numElements, walker, sizeof(numElements));
        numElements = ntohs(numElements);
        memcpy(&sanityCheck, walker + sizeof(numElements), sizeof(sanityCheck));
        sanityCheck = ntohs(sanityCheck);
        calcBytes = -(numElements + sanityCheck);
        walker += (sizeof(numElements) + sizeof(sanityCheck));
        outputSize = numElements + 2;
        result = GET_BYTES(outputSize, t_atom);
        if (result)
        {
            t_atom *        thisAtom = result;
            unsigned char * lastByteInBuffer = walker + calcBytes;
            short           chunkSize;
            unsigned char   baseElementType = *walker; // !!!
            unsigned char   elementType = baseElementType;
            long            dummy;
            char            hostAddr[NI_MAXHOST + 1];

            getnameinfo(reinterpret_cast<sockaddr *>(&sender), sizeof(sender), hostAddr,
                        sizeof(hostAddr), NULL, 0, NI_NUMERICHOST);
            atom_setsym(thisAtom, gensym(hostAddr));
            ++thisAtom;
            atom_setlong(thisAtom, TO_INT(sender.sin_port));
            ++thisAtom;
            ++walker;
            for (long element_index = 0; okSoFar && (element_index < numElements);
                 ++element_index, ++thisAtom)
            {
                if (walker > lastByteInBuffer)
                {
                    /* We should never get here, but just in case: */
                    LOG_ERROR_1(xx, OUTPUT_PREFIX "ran off end of receive buffer!")
                    okSoFar = false;
                }
                if (A_GIMME == baseElementType)
                {
                    /* A mixed vector: get the type */
                    elementType = *walker;
                    ++walker;
                }
                switch (elementType)
                {
                    case A_FLOAT:
                        if ((walker + sizeof(float)) > lastByteInBuffer)
                        {
                            LOG_ERROR_1(xx, OUTPUT_PREFIX "ran off end of receive buffer!")
                            okSoFar = false;
                        }
                        else
                        {
                            memcpy(&dummy, walker, sizeof(dummy));
                            atom_setfloat(thisAtom, ntohl(*reinterpret_cast<float *>(&dummy)));
                            walker += sizeof(float);
                        }
                        break;

                    case A_LONG:
                        if ((walker + sizeof(long)) > lastByteInBuffer)
                        {
                            LOG_ERROR_1(xx, OUTPUT_PREFIX "ran off end of receive buffer!")
                            okSoFar = false;
                        }
                        else
                        {
                            memcpy(&dummy, walker, sizeof(long));
                            atom_setlong(thisAtom, ntohl(dummy));
                            walker += sizeof(long);
                        }
                        break;

                    case A_SYM:
                        if ((walker + sizeof(chunkSize)) > lastByteInBuffer)
                        {
                            LOG_ERROR_1(xx, OUTPUT_PREFIX "ran off end of receive buffer!")
                            okSoFar = false;
                        }
                        else
                        {
                            memcpy(&chunkSize, walker, sizeof(chunkSize));
                            chunkSize = ntohs(chunkSize);
                            walker += sizeof(chunkSize);
                            if ((walker + chunkSize) > lastByteInBuffer)
                            {
                                LOG_ERROR_1(xx, OUTPUT_PREFIX "ran off end of receive buffer!")
                                okSoFar = false;
                            }
                            else
                            {
                                atom_setsym(thisAtom, gensym(reinterpret_cast<char *>(walker)));
                                walker += chunkSize;
                            }
                        }
                        break;

                    case A_SEMI:
                    case A_COMMA:
                    case A_DOLLAR:
                    case A_DOLLSYM:
                        thisAtom->a_type = elementType;
                        break;

                    default:
                        LOG_ERROR_2(xx, OUTPUT_PREFIX "unexpected atom type seen - atom %d",
                                    static_cast<int>(element_index))
                        okSoFar = false;
                        break;
                        
                }
            }
            if (! okSoFar)
            {
                FREE_BYTES(result);
                outputSize = 0;
            }
        }
        *aBuffer = reinterpret_cast<char *>(walker);
    }
    numAtoms = outputSize;
    return result;
} // convertBufferToAtoms