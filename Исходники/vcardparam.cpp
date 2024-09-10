QByteArray vCardParam::toByteArray(vCardVersion version) const
{
    QByteArray buffer;

    switch (version)
    {
        case VC_VER_2_1:
        {
            switch (m_group)
            {
                case vCardParam::Charset:
                    buffer.append(QString(VC_GROUP_TOKEN).arg(VC_CHARSET_TOKEN).arg(m_value));
                    break;

                case vCardParam::Encoding:
                    buffer.append(QString(VC_GROUP_TOKEN).arg(VC_ENCODING_TOKEN).arg(m_value));
                    break;

                default:
                    buffer.append(m_value);
                    break;
            }
            break;
        }
        break;

        case VC_VER_3_0:
        {
            switch (m_group)
            {
                case vCardParam::Type:
                    buffer.append(QString(VC_GROUP_TOKEN).arg(VC_TYPE_TOKEN).arg(m_value));
                    break;

                case vCardParam::Charset:
                    buffer.append(QString(VC_GROUP_TOKEN).arg(VC_CHARSET_TOKEN).arg(m_value));
                    break;

                case vCardParam::Encoding:
                    buffer.append(QString(VC_GROUP_TOKEN).arg(VC_ENCODING_TOKEN).arg(m_value));
                    break;

                default:
                    buffer.append(m_value);
                    break;
            }
        }
        break;

        default:
            break;
    }

    return buffer.toUpper();
}