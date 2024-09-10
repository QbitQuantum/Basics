    static CMPIEnumeration* enumClone(
        const CMPIEnumeration* eEnumObj,
        CMPIStatus* rc)
    {
        PEG_METHOD_ENTER(
            TRC_CMPIPROVIDERINTERFACE,
            "CMPI_Enumeration:enumClone()");
        const CMPIEnumeration* eEnum = (CMPIEnumeration*)eEnumObj->hdl;

        CMSetStatus(rc, CMPI_RC_OK);
        if (eEnum->hdl)
        {
            if ((void*)eEnum->ft == (void*)CMPI_InstEnumeration_Ftab)
            {
                Array<SCMOInstance>* enm = (Array<SCMOInstance>*)eEnum->hdl;
                CMPI_Object *obj = new CMPI_Object(
                    new CMPI_InstEnumeration(new Array<SCMOInstance>(*enm)));
                obj->unlink(); // remove from current thread context.
                CMPIEnumeration* cmpiEnum =
                    reinterpret_cast<CMPIEnumeration*>(obj);
                PEG_METHOD_EXIT();
                return cmpiEnum;
            }
            else if ((void*)eEnum->ft == (void*)CMPI_ObjEnumeration_Ftab)
            {
                Array<SCMOInstance>* enm = (Array<SCMOInstance>*)eEnum->hdl;
                CMPI_Object *obj = new CMPI_Object(
                    new CMPI_ObjEnumeration(new Array<SCMOInstance>(*enm)));
                obj->unlink(); // remove from current thread context.
                CMPIEnumeration* cmpiEnum =
                    reinterpret_cast<CMPIEnumeration*>(obj);
                PEG_METHOD_EXIT();
                return cmpiEnum;
            }
            else if ((void*)eEnum->ft == (void*)CMPI_OpEnumeration_Ftab)
            {
                Array<SCMOInstance>* enm = (Array<SCMOInstance>*)eEnum->hdl;
                CMPI_Object *obj = new CMPI_Object(
                    new CMPI_OpEnumeration(new Array<SCMOInstance>(*enm)));
                obj->unlink(); // remove from current thread context.
                CMPIEnumeration* cmpiEnum =
                    reinterpret_cast<CMPIEnumeration*>(obj);
                PEG_METHOD_EXIT();
                return cmpiEnum;
            }
        }
        PEG_TRACE_CSTRING(
            TRC_CMPIPROVIDERINTERFACE,
            Tracer::LEVEL1,
            "Received invalid Handle - eEnum->hdl...");
        CMSetStatus(rc, CMPI_RC_ERR_INVALID_HANDLE);
        PEG_METHOD_EXIT();
        return NULL;
    }