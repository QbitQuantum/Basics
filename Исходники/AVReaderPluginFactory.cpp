/**
 * @brief Function called to describe the plugin controls and features.
 * @param[in, out]   desc       Effect descriptor
 * @param[in]        context    Application context
 */
void AVReaderPluginFactory::describeInContext(OFX::ImageEffectDescriptor& desc, OFX::EContext context)
{
    // Create the mandated output clip
    OFX::ClipDescriptor* dstClip = desc.defineClip(kOfxImageEffectOutputClipName);
    dstClip->addSupportedComponent(OFX::ePixelComponentRGBA);
    dstClip->addSupportedComponent(OFX::ePixelComponentRGB);
    dstClip->addSupportedComponent(OFX::ePixelComponentAlpha);
    dstClip->setSupportsTiles(kSupportTiles);

    describeReaderParamsInContext(desc, context);

    // Groups
    OFX::GroupParamDescriptor* formatGroup = desc.defineGroupParam(kParamFormatGroup);
    OFX::GroupParamDescriptor* videoGroup = desc.defineGroupParam(kParamVideoGroup);
    OFX::GroupParamDescriptor* metaGroup = desc.defineGroupParam(kParamMetaGroup);

    formatGroup->setLabel("Format");
    videoGroup->setLabel("Video");
    metaGroup->setLabel("Metadata");

    formatGroup->setAsTab();
    videoGroup->setAsTab();
    metaGroup->setAsTab();

    /// FORMAT PARAMETERS
    avtranscoder::FormatContext formatContext(AV_OPT_FLAG_DECODING_PARAM);
    avtranscoder::OptionArray formatOptions = formatContext.getOptions();
    common::addOptionsToGroup(desc, formatGroup, formatOptions, common::kPrefixFormat);

    OFX::GroupParamDescriptor* formatDetailedGroup = desc.defineGroupParam(kParamFormatDetailedGroup);
    formatDetailedGroup->setLabel("Detailed");
    formatDetailedGroup->setAsTab();
    formatDetailedGroup->setParent(formatGroup);

    avtranscoder::OptionArrayMap formatDetailedGroupOptions = avtranscoder::getAvailableOptionsPerOutputFormat();
    common::addOptionsToGroup(desc, formatDetailedGroup, formatDetailedGroupOptions, common::kPrefixFormat);

    /// VIDEO PARAMETERS
    AVCodecContext* videoContext = avcodec_alloc_context3(NULL);
    avtranscoder::OptionArray videoOptions;
    avtranscoder::loadOptions(videoOptions, videoContext, AV_OPT_FLAG_DECODING_PARAM | AV_OPT_FLAG_VIDEO_PARAM);
    common::addOptionsToGroup(desc, videoGroup, videoOptions, common::kPrefixVideo);
    av_free(videoContext);

    OFX::BooleanParamDescriptor* useCustomSAR = desc.defineBooleanParam(kParamUseCustomSAR);
    useCustomSAR->setLabel("Override SAR");
    useCustomSAR->setDefault(false);
    useCustomSAR->setHint("Override the file SAR (Storage Aspect Ratio) with a custom SAR value.");
    useCustomSAR->setParent(videoGroup);

    OFX::DoubleParamDescriptor* customSAR = desc.defineDoubleParam(kParamCustomSAR);
    customSAR->setLabel("Custom SAR");
    customSAR->setDefault(1.0);
    customSAR->setDisplayRange(0., 3.);
    customSAR->setRange(0., 10.);
    customSAR->setHint("Choose a custom value to override the file SAR (Storage Aspect Ratio). Maximum value: 10.");
    customSAR->setParent(videoGroup);

    OFX::IntParamDescriptor* streamIndex = desc.defineIntParam(kParamVideoStreamIndex);
    streamIndex->setLabel(kParamVideoStreamIndexLabel);
    streamIndex->setDefault(0);
    streamIndex->setDisplayRange(0., 16.);
    streamIndex->setRange(0., 100.);
    streamIndex->setHint("Choose a custom value to decode the video stream you want. Maximum value: 100.");
    streamIndex->setParent(videoGroup);

    OFX::GroupParamDescriptor* videoDetailedGroup = desc.defineGroupParam(kParamVideoDetailedGroup);
    videoDetailedGroup->setLabel("Detailed");
    videoDetailedGroup->setAsTab();
    videoDetailedGroup->setParent(videoGroup);

    avtranscoder::OptionArrayMap videoDetailedGroupOptions = avtranscoder::getAvailableOptionsPerVideoCodec();
    common::addOptionsToGroup(desc, videoDetailedGroup, videoDetailedGroupOptions, common::kPrefixVideo);

    /// METADATA PARAMETERS
    AVCodecContext* metaDataContext = avcodec_alloc_context3(NULL);
    avtranscoder::OptionArray metaDataOptions;
    avtranscoder::loadOptions(metaDataOptions, metaDataContext, AV_OPT_FLAG_DECODING_PARAM | AV_OPT_FLAG_METADATA);
    common::addOptionsToGroup(desc, metaGroup, metaDataOptions, common::kPrefixMetaData);
    av_free(metaDataContext);

    OFX::StringParamDescriptor* metaDataWrapper = desc.defineStringParam(kParamMetaDataWrapper);
    metaDataWrapper->setLabel(kParamMetaDataWrapperLabel);
    metaDataWrapper->setEnabled(false);
    metaDataWrapper->setStringType(OFX::eStringTypeMultiLine);
    metaDataWrapper->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataVideo = desc.defineStringParam(kParamMetaDataVideo);
    metaDataVideo->setLabel(kParamMetaDataVideoLabel);
    metaDataVideo->setEnabled(false);
    metaDataVideo->setStringType(OFX::eStringTypeMultiLine);
    metaDataVideo->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataAudio = desc.defineStringParam(kParamMetaDataAudio);
    metaDataAudio->setLabel(kParamMetaDataAudioLabel);
    metaDataAudio->setEnabled(false);
    metaDataAudio->setStringType(OFX::eStringTypeMultiLine);
    metaDataAudio->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataData = desc.defineStringParam(kParamMetaDataData);
    metaDataData->setLabel(kParamMetaDataDataLabel);
    metaDataData->setEnabled(false);
    metaDataData->setStringType(OFX::eStringTypeMultiLine);
    metaDataData->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataSubtitle = desc.defineStringParam(kParamMetaDataSubtitle);
    metaDataSubtitle->setLabel(kParamMetaDataSubtitleLabel);
    metaDataSubtitle->setEnabled(false);
    metaDataSubtitle->setStringType(OFX::eStringTypeMultiLine);
    metaDataSubtitle->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataAttachement = desc.defineStringParam(kParamMetaDataAttachement);
    metaDataAttachement->setLabel(kParamMetaDataAttachementLabel);
    metaDataAttachement->setEnabled(false);
    metaDataAttachement->setStringType(OFX::eStringTypeMultiLine);
    metaDataAttachement->setParent(metaGroup);

    OFX::StringParamDescriptor* metaDataUnknown = desc.defineStringParam(kParamMetaDataUnknown);
    metaDataUnknown->setLabel(kParamMetaDataUnknownLabel);
    metaDataUnknown->setEnabled(false);
    metaDataUnknown->setStringType(OFX::eStringTypeMultiLine);
    metaDataUnknown->setParent(metaGroup);

    /// VERBOSE
    OFX::BooleanParamDescriptor* useVerbose = desc.defineBooleanParam(kParamVerbose);
    useVerbose->setLabel("Set to verbose");
    useVerbose->setDefault(false);
    useVerbose->setHint("Set plugin to verbose to get debug informations.");
}