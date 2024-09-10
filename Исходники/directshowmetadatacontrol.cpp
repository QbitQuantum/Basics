void DirectShowMetaDataControl::updateMetadata(IFilterGraph2 *graph, IBaseFilter *source, const QString &fileSrc)
{
    m_metadata.clear();

#ifndef QT_NO_SHELLITEM
    if (!sHCreateItemFromParsingName) {
        QSystemLibrary lib(QStringLiteral("shell32"));
        sHCreateItemFromParsingName = (q_SHCreateItemFromParsingName)(lib.resolve("SHCreateItemFromParsingName"));
    }

    if (!fileSrc.isEmpty() && sHCreateItemFromParsingName) {
        IShellItem2* shellItem = 0;
        if (sHCreateItemFromParsingName(reinterpret_cast<const WCHAR*>(fileSrc.utf16()),
                                        0, IID_PPV_ARGS(&shellItem)) == S_OK) {

            IPropertyStore *pStore = 0;
            if (shellItem->GetPropertyStore(GPS_DEFAULT, IID_PPV_ARGS(&pStore)) == S_OK) {
                DWORD cProps;
                if (SUCCEEDED(pStore->GetCount(&cProps))) {
                    for (DWORD i = 0; i < cProps; ++i)
                    {
                        PROPERTYKEY key;
                        PROPVARIANT var;
                        PropVariantInit(&var);
                        if (FAILED(pStore->GetAt(i, &key)))
                            continue;
                        if (FAILED(pStore->GetValue(key, &var)))
                            continue;

                        if (IsEqualPropertyKey(key, PKEY_Author)) {
                            m_metadata.insert(QMediaMetaData::Author, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Title)) {
                            m_metadata.insert(QMediaMetaData::Title, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_SubTitle)) {
                            m_metadata.insert(QMediaMetaData::SubTitle, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_ParentalRating)) {
                            m_metadata.insert(QMediaMetaData::ParentalRating, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Comment)) {
                            m_metadata.insert(QMediaMetaData::Description, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Copyright)) {
                            m_metadata.insert(QMediaMetaData::Copyright, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_ProviderStyle)) {
                            m_metadata.insert(QMediaMetaData::Genre, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_Year)) {
                            m_metadata.insert(QMediaMetaData::Year, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_DateEncoded)) {
                            m_metadata.insert(QMediaMetaData::Date, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Rating)) {
                            m_metadata.insert(QMediaMetaData::UserRating,
                                              int((convertValue(var).toUInt() - 1) / qreal(98) * 100));
                        } else if (IsEqualPropertyKey(key, PKEY_Keywords)) {
                            m_metadata.insert(QMediaMetaData::Keywords, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Language)) {
                            m_metadata.insert(QMediaMetaData::Language, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_Publisher)) {
                            m_metadata.insert(QMediaMetaData::Publisher, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_Duration)) {
                            m_metadata.insert(QMediaMetaData::Duration,
                                              (convertValue(var).toLongLong() + 10000) / 10000);
                        } else if (IsEqualPropertyKey(key, PKEY_Audio_EncodingBitrate)) {
                            m_metadata.insert(QMediaMetaData::AudioBitRate, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_AverageLevel)) {
                            m_metadata.insert(QMediaMetaData::AverageLevel, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Audio_ChannelCount)) {
                            m_metadata.insert(QMediaMetaData::ChannelCount, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Audio_PeakValue)) {
                            m_metadata.insert(QMediaMetaData::PeakValue, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Audio_SampleRate)) {
                            m_metadata.insert(QMediaMetaData::SampleRate, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_AlbumTitle)) {
                            m_metadata.insert(QMediaMetaData::AlbumTitle, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_AlbumArtist)) {
                            m_metadata.insert(QMediaMetaData::AlbumArtist, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Artist)) {
                            m_metadata.insert(QMediaMetaData::ContributingArtist, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Composer)) {
                            m_metadata.insert(QMediaMetaData::Composer, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Conductor)) {
                            m_metadata.insert(QMediaMetaData::Conductor, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Lyrics)) {
                            m_metadata.insert(QMediaMetaData::Lyrics, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Mood)) {
                            m_metadata.insert(QMediaMetaData::Mood, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_TrackNumber)) {
                            m_metadata.insert(QMediaMetaData::TrackNumber, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Music_Genre)) {
                            m_metadata.insert(QMediaMetaData::Genre, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_ThumbnailStream)) {
                            m_metadata.insert(QMediaMetaData::ThumbnailImage, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Video_FrameHeight)) {
                            QSize res;
                            res.setHeight(convertValue(var).toUInt());
                            if (SUCCEEDED(pStore->GetValue(PKEY_Video_FrameWidth, &var)))
                                res.setWidth(convertValue(var).toUInt());
                            m_metadata.insert(QMediaMetaData::Resolution, res);
                        } else if (IsEqualPropertyKey(key, PKEY_Video_HorizontalAspectRatio)) {
                            QSize aspectRatio;
                            aspectRatio.setWidth(convertValue(var).toUInt());
                            if (SUCCEEDED(pStore->GetValue(PKEY_Video_VerticalAspectRatio, &var)))
                                aspectRatio.setHeight(convertValue(var).toUInt());
                            m_metadata.insert(QMediaMetaData::PixelAspectRatio, aspectRatio);
                        } else if (IsEqualPropertyKey(key, PKEY_Video_FrameRate)) {
                            m_metadata.insert(QMediaMetaData::VideoFrameRate,
                                              convertValue(var).toReal() / 1000);
                        } else if (IsEqualPropertyKey(key, PKEY_Video_EncodingBitrate)) {
                            m_metadata.insert(QMediaMetaData::VideoBitRate, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Video_Director)) {
                            m_metadata.insert(QMediaMetaData::Director, convertValue(var));
                        } else if (IsEqualPropertyKey(key, PKEY_Media_Writer)) {
                            m_metadata.insert(QMediaMetaData::Writer, convertValue(var));
                        }

                        PropVariantClear(&var);
                    }
                }

                pStore->Release();
            }

            shellItem->Release();
        }
    }

    if (!m_metadata.isEmpty())
        goto send_event;
#endif

#ifndef QT_NO_WMSDK
    IWMHeaderInfo *info = com_cast<IWMHeaderInfo>(source, IID_IWMHeaderInfo);

    if (info) {
        Q_FOREACH (const QWMMetaDataKey &key, *qt_wmMetaDataKeys()) {
            QVariant var = getValue(info, key.wmName);
            if (var.isValid()) {
                if (key.qtName == QMediaMetaData::Duration) {
                    // duration is provided in 100-nanosecond units, convert to milliseconds
                    var = (var.toLongLong() + 10000) / 10000;
                } else if (key.qtName == QMediaMetaData::Resolution) {
                    QSize res;
                    res.setHeight(var.toUInt());
                    res.setWidth(getValue(info, L"WM/VideoWidth").toUInt());
                    var = res;
                } else if (key.qtName == QMediaMetaData::VideoFrameRate) {
                    var = var.toReal() / 1000.f;
                } else if (key.qtName == QMediaMetaData::PixelAspectRatio) {
                    QSize aspectRatio;
                    aspectRatio.setWidth(var.toUInt());
                    aspectRatio.setHeight(getValue(info, L"AspectRatioY").toUInt());
                    var = aspectRatio;
                } else if (key.qtName == QMediaMetaData::UserRating) {
                    var = (var.toUInt() - 1) / qreal(98) * 100;
                }

                m_metadata.insert(key.qtName, var);
            }
        }

        info->Release();
    }

    if (!m_metadata.isEmpty())
        goto send_event;
#endif
    {
        IAMMediaContent *content = 0;

        if ((!graph || graph->QueryInterface(
                 IID_IAMMediaContent, reinterpret_cast<void **>(&content)) != S_OK)
                && (!source || source->QueryInterface(
                        IID_IAMMediaContent, reinterpret_cast<void **>(&content)) != S_OK)) {
            content = 0;
        }

        if (content) {
            BSTR string = 0;

            if (content->get_AuthorName(&string) == S_OK)
                m_metadata.insert(QMediaMetaData::Author, convertBSTR(&string));

            if (content->get_Title(&string) == S_OK)
                m_metadata.insert(QMediaMetaData::Title, convertBSTR(&string));

            if (content->get_Description(&string) == S_OK)
                m_metadata.insert(QMediaMetaData::Description, convertBSTR(&string));

            if (content->get_Rating(&string) == S_OK)
                m_metadata.insert(QMediaMetaData::UserRating, convertBSTR(&string));

            if (content->get_Copyright(&string) == S_OK)
                m_metadata.insert(QMediaMetaData::Copyright, convertBSTR(&string));

            content->Release();
        }
    }

send_event:
    // DirectShowMediaPlayerService holds a lock at this point so defer emitting signals to a later
    // time.
    QCoreApplication::postEvent(this, new QEvent(QEvent::Type(MetaDataChanged)));
}