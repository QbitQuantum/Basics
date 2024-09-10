__RELIABILITY_CONTRACT
const char * type_info::_Name_base(const type_info *_This,__type_info_node* __ptype_info_node)
{
        void *pTmpUndName;
        size_t len;

        if (_This->_m_data == NULL) {
            if ((pTmpUndName = __unDNameHelper(NULL,
                                               (_This->_m_d_name)+1,
                                               0,
                                               0)) == NULL)
                return NULL;

            /*
             * Pad all the trailing spaces with null. Note that len-- > 0 is used
             * at left side which depends on operator associativity. Also note
             * that len will be used later so don't trash.
             */
            for (len=strlen((char *)pTmpUndName); len-- > 0 && ((char *)pTmpUndName)[len] == ' ';) {
                ((char *)pTmpUndName)[len] = '\0';
            }

            bool _MustReleaseLock = false;
            __PREPARE_CONSTRAINED_REGION
            __TRY
                __BEGIN_CONSTRAINED_REGION
                    System::Threading::Thread::BeginThreadAffinity();
                    _mlock(_TYPEINFO_LOCK);
                    _MustReleaseLock = true;
                __END_CONSTRAINED_REGION
                /*
                 * We need to check if this->_m_data is still NULL, this will
                 * prevent the memory leak.
                 */
                if (_This->_m_data == NULL) {
                    /*
                     * allocate a node which will store the pointer to the memory
                     * allocated for this->_m_data. We need to store all this in
                     * linklist so that we can free them as process exit. Note
                     * that __clean_type_info_names is freeing this memory.
                     */
                    __type_info_node *pNode = (__type_info_node *)_malloc_base(sizeof(__type_info_node));
                    if (pNode != NULL) {

                        /*
                         * We should be doing only if we are sucessful in allocating
                         * node pointer. Note that we need to add 2 to len, this
                         * is because len = strlen(pTmpUndName)-1.
                         */
                        if ((((type_info *)_This)->_m_data = _malloc_base(len+2)) != NULL) {
                            _ERRCHECK(strcpy_s ((char *)((type_info *)_This)->_m_data, len+2, (char *)pTmpUndName));
                            pNode->memPtr = _This->_m_data;

                            /*
                             * Add this to global linklist. Note that we always
                             * add this as second element in linklist.
                             */
                            pNode->next = __ptype_info_node->next;
                            __ptype_info_node->next = pNode;
                        } else {
                            /*
                             * Free node pointer as there is no allocation for
                             * this->_m_data, this means that we don't really
                             * need this in the link list.
                             */
                            _free_base(pNode);
                        }
                    }
                }
                /*
                 * Free the temporary undecorated name.
                 */
                _free_base (pTmpUndName);
            __FINALLY
                if (_MustReleaseLock)
                {
                    _munlock(_TYPEINFO_LOCK);
                    System::Threading::Thread::EndThreadAffinity();
                }
            __END_TRY_FINALLY


        }

        return (char *) _This->_m_data;
}