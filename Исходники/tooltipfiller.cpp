QString ToolTipFiller::filterActionTipContents(const FilterAction& action)
{
    if (action.isNull())
    {
        return QString();
    }

    QString            str;
    DToolTipStyleSheet cnt(ApplicationSettings::instance()->getToolTipsFont());
    QString            tip = cnt.tipHeader;

    tip += cnt.headBeg + i18n("Filter") + cnt.headEnd;

    // Displayable name
    tip += cnt.cellBeg + i18n("Name:") + cnt.cellMid
        + DImgFilterManager::instance()->i18nDisplayableName(action) + cnt.cellEnd;

    // Category
    QString reproducible("---");

    switch (action.category())
    {
        case FilterAction::ReproducibleFilter:
            reproducible = i18nc("Image filter reproducible: Yes", "Yes");
            break;
        case FilterAction::ComplexFilter:
            reproducible = i18nc("Image filter reproducible: Partially", "Partially");
            break;
        case FilterAction::DocumentedHistory:
            reproducible = i18nc("Image filter reproducible: No", "No");
            break;
        default:
            break;
    };

    tip += cnt.cellBeg + i18n("Reproducible:") + cnt.cellMid
         + reproducible + cnt.cellEnd;

    // Description

    str = action.description();

    if (str.isEmpty())
    {
        str = QString("---");
    }

    tip += cnt.cellSpecBeg + i18nc("Image filter description", "Description:") + cnt.cellSpecMid
        + cnt.breakString(str) + cnt.cellSpecEnd;

    // Identifier + version
    tip += cnt.cellBeg + i18n("Identifier:") + cnt.cellMid
        + action.identifier() + " (v" + QString::number(action.version()) + ") " + cnt.cellEnd;

    if (action.hasParameters())
    {
        tip += cnt.headBeg + i18n("Technical Parameters") + cnt.headEnd;

        const QHash<QString, QVariant>& params = action.parameters();
        QList<QString> keys                    = params.keys();
        qSort(keys);

        foreach(const QString& key, keys)
        {
            QHash<QString, QVariant>::const_iterator it;

            for (it = params.find(key); it != params.end() && it.key() == key; ++it)
            {
                if (it.key().isEmpty() || !it.value().isValid())
                {
                    continue;
                }

                if (it.key().startsWith(QLatin1String("curveData")))
                {
                    str = i18n("<i>Binary Data</i>");
                }
                else
                {
                    str = it.value().toString();
                }

                if (str.length() > cnt.maxStringLength)
                {
                    str = cnt.elidedText(str, Qt::ElideRight);
                }

                QString key = it.key();
                QChar first = key.at(0);

                if (first.isLower())
                {
                    key.replace(0, 1, first.toUpper());
                }

                tip += cnt.cellBeg + key + cnt.cellMid
                    + str + cnt.cellEnd;
            }
        }