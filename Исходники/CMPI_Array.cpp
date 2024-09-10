    PEGASUS_STATIC CMPIArray* arrayClone(
        const CMPIArray* eArray,
        CMPIStatus* rc)
    {
        PEG_METHOD_ENTER(
            TRC_CMPIPROVIDERINTERFACE,
            "CMPI_Array:arrayClone()");
        CMPI_Array *arr = (CMPI_Array*)eArray->hdl;
        if (!arr)
        {
            CMSetStatus(rc, CMPI_RC_ERR_INVALID_HANDLE);
            PEG_METHOD_EXIT();
            return NULL;
        }
        CMPIData* dta=(CMPIData*)arr->hdl;
        if (!dta)
        {
            CMSetStatus(rc, CMPI_RC_ERR_INVALID_HANDLE);
            PEG_METHOD_EXIT();
            return NULL;
        }
        CMPIData* nDta = new CMPIData[dta->value.uint32+1];
        CMPI_Array* nArr = new CMPI_Array(nDta, true);
        CMPI_Object* obj = new CMPI_Object(nArr);
        obj->unlink();
        CMPIArray* nArray = reinterpret_cast<CMPIArray*>(obj);
        CMPIStatus rrc = {CMPI_RC_OK,NULL};

        if (dta->type & CMPI_ENC)
        {
            for (unsigned int i=1; i<=dta->value.uint32; i++)
            {
                nDta[i].state=CMPI_nullValue;
            }
        }

        for (unsigned int i=0; i<=dta->value.uint32; i++)
        {
            nDta[i]=dta[i];
            if (i == 0)
            {
                continue;
            }
            if (dta->type & CMPI_ENC && dta[i].state==CMPI_goodValue)
            {
                switch (dta[i].type)
                {
                    case CMPI_instance:
                        if (dta[i].value.inst)
                        {
                            nDta[i].value.inst =
                                (dta[i].value.inst)->ft->clone(
                                    dta[i].value.inst,
                                    &rrc);
                        }
                        break;

                    case CMPI_ref:
                        if (dta[i].value.ref)
                        {
                            nDta[i].value.ref = (dta[i].value.ref)->ft->clone(
                                dta[i].value.ref,
                                &rrc);
                        }
                        break;

                    case CMPI_args:
                        if (dta[i].value.args)
                        {
                            nDta[i].value.args =
                                (dta[i].value.args)->ft->clone(
                                    dta[i].value.args,
                                    &rrc);
                        }
                        break;

                    case CMPI_dateTime:
                        if (dta[i].value.dateTime)
                        {
                            nDta[i].value.dateTime =
                                (dta[i].value.dateTime)->ft->clone(
                                    dta[i].value.dateTime,
                                    &rrc);
                        }
                        break;

                    case CMPI_enumeration:
                        if (dta[i].value.Enum)
                        {
                            nDta[i].value.Enum =
                                (dta[i].value.Enum)->ft->clone(
                                    dta[i].value.Enum,
                                    &rrc);
                        }
                        break;

                    case CMPI_filter:
                        if (dta[i].value.filter)
                        {
                            nDta[i].value.filter =
                                (dta[i].value.filter)->ft->clone(
                                    dta[i].value.filter,
                                    &rrc);
                        }
                        break;

                    case CMPI_charsptr:
                        if (dta[i].value.dataPtr.length>0)
                        {
                            nDta[i].value.dataPtr.length =
                                dta[i].value.dataPtr.length;
                            nDta[i].value.dataPtr.ptr =
                                malloc(nDta[i].value.dataPtr.length);
                            if (nDta[i].value.dataPtr.ptr == NULL)
                            {
                                arrayRelease(nArray);
                                if (rc)
                                {
                                    *rc=rrc;
                                }
                                return NULL;
                            }
                            memcpy(
                                nDta[i].value.dataPtr.ptr,
                                dta[i].value.dataPtr.ptr,
                                dta[i].value.dataPtr.length);
                        }
                        break;

                    case CMPI_string:
                        if (dta[i].value.string)
                        {
                            nDta[i].value.string =
                                (dta[i].value.string)->ft->clone(
                                    dta[i].value.string,
                                    &rrc);
                        }
                        break;
                }
                if (rrc.rc)
                {
                    arrayRelease(nArray);
                    if (rc)
                    {
                        *rc=rrc;
                    }
                    PEG_METHOD_EXIT();
                    return NULL;
                }
            }
        }

        CMSetStatus(rc,CMPI_RC_OK);
        PEG_METHOD_EXIT();
        return nArray;
    }