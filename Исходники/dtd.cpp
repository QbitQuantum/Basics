void DTD::parseTagAttributeValues(QString name, QString *value) {
    AttributeList *attributes = new AttributeList();

    QStringList attrLines = QStringList::split("\\end",*value);
    QStringList::Iterator lineIt = attrLines.begin();
    while (lineIt != attrLines.end()) //iterate through the attribute lines
    {
        //split the attribute line
        QStringList all = QStringList::split(" ", *lineIt);
        QStringList::Iterator it = all.begin();
        while(it != all.end())
        {
            Attribute *attr = new Attribute();
            attr->name = *it;
            //kdDebug() << "Inserting for tag " << name << ": " << *it << endl;
            ++it;

            QString values = *it;
            //list of possible values
            if ( values.startsWith("(") && values.endsWith(")") )
            {
                values.remove(0,1);
                values.remove(values.length()-1,1);
                attr->values = QStringList::split("|", values);
                QString s = (attr->values[0]+attr->values[1]).lower();
                stripSpaces(&s);
                if ((s == "truefalse") || (s == "falsetrue"))
                {
                    attr->type = "check";
                } else
                {
                    attr->type = "list";
                }
            } else
            {
                attr->values = values;
                attr->type = "input";
            }

            //kdDebug() << " --- values: " << *it << endl;
            if (it != all.end())
            {
                ++it;
                QString s=*it;
                if (s.startsWith("\"") && s.endsWith("\"") && it!=all.end())
                {
                    s.remove(0,1);
                    s.remove(s.length()-1,1);
                    attr->defaultValue = s;
                }
                if (s.startsWith("#") && it != all.end())
                {
                    s.remove(0,1);
                    attr->status = s.lower();
                }
                if (*it == "#FIXED" && it != all.end())
                {
                    ++it;
                    attr->values.append(*it);
                }
            }

            if (it != all.end())
            {
                ++it;
            }
            attributes->append(attr);
        }
        ++lineIt;
    }
    tagAttributes.insert(name, attributes);
}