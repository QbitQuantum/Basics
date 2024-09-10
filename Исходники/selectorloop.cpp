    EBTStatus SelectorLoopTask::update(Agent* pAgent, EBTStatus childStatus) {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(childStatus);
        int idx = -1;

        if (childStatus != BT_RUNNING) {
            BEHAVIAC_ASSERT(this->m_activeChildIndex != CompositeTask::InvalidChildIndex);

            if (childStatus == BT_SUCCESS) {
                return BT_SUCCESS;
            } else if (childStatus == BT_FAILURE) {
                //the next for starts from (idx + 1), so that it starts from next one after this failed one
                idx = this->m_activeChildIndex;
            } else {
                BEHAVIAC_ASSERT(false);
            }
        }

        //checking the preconditions and take the first action tree
        uint32_t index = (uint32_t) - 1;

        for (uint32_t i = (idx + 1); i < this->m_children.size(); ++i) {
            WithPreconditionTask* pSubTree = (WithPreconditionTask*)this->m_children[i];
            BEHAVIAC_ASSERT(WithPreconditionTask::DynamicCast(pSubTree));
            BehaviorTask* pre = pSubTree->PreconditionNode();

            EBTStatus status = pre->exec(pAgent);

            if (status == BT_SUCCESS) {
                index = i;
                break;
            }
        }

        //clean up the current ticking action tree
        if (index != (uint32_t) - 1) {
            if (this->m_activeChildIndex != CompositeTask::InvalidChildIndex &&
                this->m_activeChildIndex != (int)index) {
                WithPreconditionTask* pCurrentSubTree = (WithPreconditionTask*)this->m_children[this->m_activeChildIndex];
                BEHAVIAC_ASSERT(WithPreconditionTask::DynamicCast(pCurrentSubTree));
                BehaviorTask* action = pCurrentSubTree->ActionNode();
                BEHAVIAC_UNUSED_VAR(action);
                pCurrentSubTree->abort(pAgent);
            }

            for (uint32_t i = index; i < this->m_children.size(); ++i) {
                WithPreconditionTask* pSubTree = (WithPreconditionTask*)this->m_children[i];
                BEHAVIAC_ASSERT(WithPreconditionTask::DynamicCast(pSubTree));

                if (i > index) {
                    BehaviorTask* pre = pSubTree->PreconditionNode();
                    EBTStatus status = pre->exec(pAgent);

                    //to search for the first one whose precondition is success
                    if (status != BT_SUCCESS) {
                        continue;
                    }
                }

                BehaviorTask* action = pSubTree->ActionNode();
                EBTStatus s = action->exec(pAgent);

                if (s == BT_RUNNING) {
                    this->m_activeChildIndex = i;
                    pSubTree->m_status = BT_RUNNING;
                } else {
                    //pActionTree->reset(pAgent);
                    pSubTree->m_status = s;

                    if (s == BT_FAILURE) {
                        //THE ACTION failed, to try the next one
                        continue;
                    }
                }

                BEHAVIAC_ASSERT(s == BT_RUNNING || s == BT_SUCCESS);

                return s;
            }
        }

        return BT_FAILURE;
    }