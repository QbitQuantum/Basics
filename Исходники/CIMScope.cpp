String CIMScope::toString () const
{
    String tmp;

    if (this->hasScope (CIMScope::CLASS))
	tmp.append("CLASS ");

    if (this->hasScope (CIMScope::ASSOCIATION))
	tmp.append("ASSOCIATION ");

    if (this->hasScope (CIMScope::INDICATION))
	tmp.append("INDICATION ");

    if (this->hasScope (CIMScope::PROPERTY))
	tmp.append("PROPERTY ");

    if (this->hasScope (CIMScope::REFERENCE))
	tmp.append("REFERENCE ");

    if (this->hasScope (CIMScope::METHOD))
	tmp.append("METHOD ");

    if (this->hasScope (CIMScope::PARAMETER))
	tmp.append("PARAMETER ");

    if (tmp.size())
	tmp.remove(tmp.size() - 1);

    return tmp;
}