const QList<PlastiQCandidateMethod> PlastiQMetaObject::candidates(const QByteArray &name, int argc, PlastiQMethod::Type type, PlastiQMethod::Access filter, bool ignoreCase) const
{
#ifdef PQDEBUG
    PQDBG_LVL_START(__FUNCTION__);
    PQDBGLPUP(QString("PlastiQMetaObject::d.className = %1").arg(d.className));
    PQDBGLPUP(QString("find candidates for `%1`").arg(name.constData()));
#endif

    QList<PlastiQCandidateMethod> candidateList;

    const PlastiQMetaObject *m = this;
    int offset = 0;
    bool maxArgs = argc == -1;
    QByteArray lowerName = name.toLower();

    do {
        QHashIterator<QByteArray, PlastiQMethod> *i;
        const QHash<QByteArray, PlastiQMethod> *hash;

        switch(type) {
        case PlastiQMethod::Method:
            i = new QHashIterator<QByteArray, PlastiQMethod>(*(m->d.pq_methods));
            hash = m->d.pq_methods;
            break;

        case PlastiQMethod::Constructor:
            i = new QHashIterator<QByteArray, PlastiQMethod>(*(m->d.pq_constructors));
            hash = m->d.pq_constructors;
            break;

        case PlastiQMethod::Signal:
            i = new QHashIterator<QByteArray, PlastiQMethod>(*(m->d.pq_signals));
            hash = m->d.pq_signals;
            break;

        default:
            PQDBG_LVL_DONE();
            return candidateList;
        }

        while(i->hasNext()) {
            i->next();


            if(ignoreCase) {
                if(i->value().name.toLower() != lowerName) continue;
            }
            else {
                if(i->value().name != name) continue;
            }

            int idx = i->key().indexOf("(");
            QString methodSignature = i->key().mid(idx + 1, i->key().size() - idx - 2);

            QStringList argTypes = methodSignature.split(",");
            int candidateArgc = methodSignature.length() ? argTypes.size() : 0;

            if(type == PlastiQMethod::Signal && maxArgs) {
                if(argc < candidateArgc) {
                    argc = candidateArgc;
                    candidateList.clear();
                    candidateList.append({ i->value().name, argc, argTypes, i->value().index + offset });
                    continue;
                }
            }
            else {
                if(!maxArgs && candidateArgc != argc) {
                    continue;
                }
            }

            if(filter == PlastiQMethod::None || filter == i->value().access) {
                if(maxArgs) {
                    if(argc < candidateArgc) {
                        PQDBGLPUP(QString("reappend candidate: %1(%2)").arg(name.constData()).arg(methodSignature));
                        argc = candidateArgc;
                        candidateList.clear();
                        candidateList.append({ i->value().name, argc, argTypes, i->value().index + offset });
                        continue;
                    }
                }
                else {
                    PQDBGLPUP(QString("append candidate: %1(%2)").arg(name.constData()).arg(methodSignature));
                    candidateList.append({ i->value().name, argc, argTypes, i->value().index + offset });
                }
            }
        }

        if(type == PlastiQMethod::Constructor) {
            delete i;
            break;
        }
        else {
            offset += hash->size();
            delete i;
        }
    } while(m = m->d.superdata);

    PQDBG_LVL_DONE();
    return candidateList;
}