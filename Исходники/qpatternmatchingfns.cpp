QString ReplaceFN::parseReplacement(const int,
                                    const DynamicContext::Ptr &context) const
{
    // TODO what if there is no groups, can one rewrite to the replacement then?
    const QString input(m_operands.at(2)->evaluateSingleton(context).stringValue());

    QString retval;
    retval.reserve(input.size());
    const int len = input.length();

    for(int i = 0; i < len; ++i)
    {
        const QChar ch(input.at(i));
        switch(ch.toAscii())
        {
            case '$':
            {
                /* QRegExp uses '\' as opposed to '$' for marking sub groups. */
                retval.append(QLatin1Char('\\'));

                ++i;
                if(i == len)
                {
                    context->error(errorAtEnd('$'), ReportContext::FORX0004, this);
                    return QString();
                }

                const QChar nextCh(input.at(i));
                if(nextCh.isDigit())
                    retval.append(nextCh);
                else
                {
                    context->error(QtXmlPatterns::tr("In the replacement string, %1 must be "
                                                     "followed by at least one digit when not escaped.")
                                                     .arg(formatKeyword(QLatin1Char('$'))),
                                                ReportContext::FORX0004, this);
                    return QString();
                }

                break;
            }
            case '\\':
            {
                ++i;
                if(i == len)
                {
                    /* error, we've reached the end. */;
                    context->error(errorAtEnd('\\'), ReportContext::FORX0004, this);
                }

                const QChar nextCh(input.at(i));
                if(nextCh == QLatin1Char('\\') || nextCh == QLatin1Char('$'))
                {
                    retval.append(ch);
                    break;
                }
                else
                {
                    context->error(QtXmlPatterns::tr("In the replacement string, %1 can only be used to "
                                                     "escape itself or %2, not %3")
                                                     .arg(formatKeyword(QLatin1Char('\\')))
                                                     .arg(formatKeyword(QLatin1Char('$')))
                                                     .arg(formatKeyword(nextCh)),
                                               ReportContext::FORX0004, this);
                    return QString();
                }
            }
            default:
                retval.append(ch);
        }
    }

    return retval;
}