std::pair<TrieNode::Ptr,int> TrieNode::intersectF(
    const TrieNode::Ptr &v1, const TrieNode::Ptr &v2, int index1)
{
    typedef TrieNode::Ptr P;
    typedef QMap<QString,int>::const_iterator MapIterator;
    if (v1.isNull() || v2.isNull())
        return std::make_pair(P(0), ((v1.isNull()) ? 1 : 0) | ((v2.isNull()) ? 2 : 0));
    QString::const_iterator i = v1->prefix.constBegin()+index1, iEnd = v1->prefix.constEnd();
    QString::const_iterator j = v2->prefix.constBegin(), jEnd = v2->prefix.constEnd();
    while (i != iEnd && j != jEnd) {
        if (i->isSpace()) {
            if (! j->isSpace())
                break;
            do {
                ++j;
            } while (j != jEnd && j->isSpace());
            do {
                ++i;
            } while (i != iEnd && i->isSpace());
        } else {
            if (*i != *j)
                break;
            ++i;
            ++j;
        }
    }
    if (i == iEnd) {
        if (j == jEnd) {
            if (v1->postfixes.isEmpty() || v2->postfixes.isEmpty()) {
                if (v1->postfixes.isEmpty() && v2->postfixes.isEmpty())
                    return std::make_pair(v1, 3);
                foreach (P t1, v1->postfixes)
                    if (t1->prefix.isEmpty()) {
                        if (index1 == 0)
                            return std::make_pair(v2, 2);
                        else
                            return std::make_pair(TrieNode::create(
                                v1->prefix.left(index1).append(v2->prefix), v2->postfixes),0);
                    }
                foreach (P t2, v2->postfixes)
                    if (t2->prefix.isEmpty())
                        return std::make_pair(v1,1);
                return std::make_pair(P(0), 0);
            }
            QMap<QString,int> p1, p2;
            QList<P> p3;
            int ii = 0;
            foreach (P t1, v1->postfixes)
                p1[t1->prefix] = ii++;
            ii = 0;
            foreach (P t2, v2->postfixes)
                p2[t2->prefix] = ii++;
            MapIterator p1Ptr = p1.constBegin(), p2Ptr = p2.constBegin(),
                p1End = p1.constEnd(), p2End = p2.constEnd();
            int sameV1V2 = 3;
            while (p1Ptr != p1End && p2Ptr != p2End) {
                if (p1Ptr.key().isEmpty()) {
                    if (p2Ptr.key().isEmpty()) {
                        if (sameV1V2 == 0)
                            p3.append(v1->postfixes.at(p1Ptr.value()));
                        ++p1Ptr;
                        ++p2Ptr;
                    } else {
                        if (sameV1V2 == 1)
                            for (MapIterator p1I = p1.constBegin();p1I != p1Ptr; ++p1I)
                                p3.append(v1->postfixes.at(p1I.value()));
                        ++p1Ptr;
                        sameV1V2 &= 2;
                    }
                } else if (p2Ptr.key().isEmpty()) {
                    if (sameV1V2 == 2)
                        for (MapIterator p2I = p2.constBegin(); p2I != p2Ptr; ++p2I)
                                p3.append(v2->postfixes.at(p2I.value()));
                    ++p2Ptr;
                    sameV1V2 &= 1;
                } else {
                    QChar c1 = p1Ptr.key().at(0);
                    QChar c2 = p2Ptr.key().at(0);
                    if (c1 < c2) {
                        if (sameV1V2 == 1)
                            for (MapIterator p1I = p1.constBegin(); p1I != p1Ptr; ++p1I)
                                p3.append(v1->postfixes.at(p1I.value()));
                        ++p1Ptr;
                        sameV1V2 &= 2;
                    } else if (c1 > c2) {
                        if (sameV1V2 == 2)
                            for (MapIterator  p2I = p2.constBegin(); p2I != p2Ptr; ++p2I)
                                    p3.append(v2->postfixes.at(p2I. value()));
                        ++p2Ptr;
                        sameV1V2 &= 1;
                    } else {
                        std::pair<P,int> res = intersectF(v1->postfixes.at(p1Ptr.value()),
                            v2->postfixes.at(p2Ptr.value()));
                        if (sameV1V2 !=0 && (sameV1V2 & res.second) == 0) {
                            if ((sameV1V2 & 1) == 1)
                                for (MapIterator p1I = p1.constBegin(); p1I != p1Ptr; ++p1I)
                                    p3.append(v1->postfixes.at(p1I.value()));
                            if (sameV1V2 == 2)
                                for (MapIterator p2I = p2.constBegin(); p2I != p2Ptr; ++p2I)
                                    p3.append(v2->postfixes.at(p2I.value()));
                        }
                        sameV1V2 &= res.second;
                        if (sameV1V2 == 0 && !res.first.isNull())
                            p3.append(res.first);
                        ++p1Ptr;
                        ++p2Ptr;
                    }
                }
            }
            if (p1Ptr != p1End) {
                if (sameV1V2 == 1)
                    for (MapIterator p1I = p1.constBegin(); p1I != p1Ptr; ++p1I)
                        p3.append(v1->postfixes.at(p1I.value()));
                sameV1V2 &= 2;
            } else if (p2Ptr != p2End) {
                if (sameV1V2 == 2) {
                    for (MapIterator  p2I = p2.constBegin(); p2I != p2Ptr; ++p2I)
                        p3.append(v2->postfixes.at(p2I. value()));
                }
                sameV1V2 &= 1;
            }
            switch (sameV1V2) {
            case 0:
                if (p3.isEmpty())
                   return std::make_pair(P(0),0);
                else
                    return std::make_pair(TrieNode::create(v1->prefix,p3),0);
            case 2:
                if (index1 == 0)
                    return std::make_pair(v2,2);
                else
                    return std::make_pair(TrieNode::create(
                            v1->prefix.left(index1).append(v2->prefix), v2->postfixes), 0);
            default:
                return std::make_pair(v1,sameV1V2);
            }
        }
       // i == iEnd && j != jEnd
        foreach (const P &t1, v1->postfixes)
            if ((!t1->prefix.isEmpty()) && t1->prefix.at(0) == *j) {
                std::pair<P,int> res = intersectF(v2,t1,j-v2->prefix.constBegin());
                if (index1 == 0)
                    return std::make_pair(res.first, (((res.second & 1)==1) ? 2 : 0));
                else
                    return std::make_pair(TrieNode::create(
                        v1->prefix.left(index1).append(res.first->prefix),
                        res.first->postfixes), 0);
            }
        return std::make_pair(P(0), 0);
    } else {