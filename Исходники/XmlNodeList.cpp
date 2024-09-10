result_t XmlNodeList::insertAfter(XmlNode_base *newChild, XmlNode_base *refChild,
                                  obj_ptr<XmlNode_base> &retVal)
{
    XmlNodeImpl *pNew = checkChild(newChild);
    XmlNodeImpl *pRef = checkChild(refChild);
    if (!pNew || !pRef)
        return CHECK_ERROR(CALL_E_INVALIDARG);

    if (pRef->m_parent != m_this)
        return CHECK_ERROR(Runtime::setError("The node after which the new node is to be inserted is not a child of this node."));

    if (pNew == pRef)
    {
        retVal = newChild;
        return 0;
    }

    if (!checkNew(pNew))
        return CHECK_ERROR(Runtime::setError("The new child element contains the parent."));

    int32_t sz = (int32_t)m_childs.size();
    int32_t idx = pRef->m_index + 1;
    int32_t i;

    m_childs.resize(sz + 1);

    for (i = sz; i > idx; i --)
    {
        XmlNodeImpl *pTmp = m_childs[i - 1];
        m_childs[i] = pTmp;
        pTmp->m_index ++;
    }

    pNew->setParent(m_this, idx);
    m_childs[idx] = pNew;

    retVal = newChild;
    return 0;
}