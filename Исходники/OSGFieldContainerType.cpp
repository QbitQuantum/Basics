bool FieldContainerType::setPrototype(FieldContainer *pPrototype)
{
    bool returnValue = false;

    if(this->isAbstract() == false)
    {
        if(pPrototype != NULL)
        {
            TypePredicates::IsBaseOf baseTypePred(pPrototype->getType());

            if(baseTypePred(this) == true)
            {
                pPrototype->addReferenceUnrecorded();
            
                _pPrototype->subReferenceUnrecorded();

                _pPrototype = pPrototype;

                BitVector bCurrent = 0x0002;

                for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
                {
                    FieldDescriptionBase *pDesc = this->getFieldDesc(i);

                    if(pDesc == NULL)
                        continue;

                    if(0x0000 == (bCurrent & 
                                _pPrototype->_pFieldFlags->_bThreadLocalFlags))
                    {
                        pDesc->setFlags(pDesc->getFlags()  | 
                                        Field::FThreadLocal);
                    }
                    else
                    {
                        pDesc->setFlags(pDesc->getFlags()   & 
                                        ~Field::FThreadLocal);
                    }

                    if(0x0000 == (bCurrent & 
                                _pPrototype->_pFieldFlags->_bClusterLocalFlags))
                    {
                        pDesc->setFlags(pDesc->getFlags()   | 
                                        Field::FClusterLocal);
                    }
                    else
                    {
                        pDesc->setFlags(pDesc->getFlags()    & 
                                        ~Field::FClusterLocal);
                    }

                    bCurrent <<= 1;
                }

                returnValue = true;
            }
            else
            {
                FWARNING(("can not set unrelated container of type %s "
                          "as prototype for type %s\n",
                          pPrototype->getType().getCName(),
                          this->getCName()));
            }
        }
        else
        {
            FWARNING(("can not delete prototype of a concrete object\n"));
        }
    }
    else
    {
        FWARNING(("can not set prototype of an abstract object\n"));
    }

    return returnValue;
}