bool MetadataThumbnail::writeThumbnail(bool isMetadataEnabled)
{
    isThumbnailSavedSuccessfully = false;

#ifdef SIR_METADATA_SUPPORT
    if (isMetadataEnabled) {
        MetadataUtils::Metadata metadata;
        if (metadata.read(imagePath, true)) {
            exifStruct_ = metadata.exifStruct()->copy();
            iptcStruct_ = metadata.iptcStruct()->copy();
            Exiv2::Image::AutoPtr image = metadata.imageAutoPtr();
            imageSize = QSize(image->pixelWidth(), image->pixelHeight());
            Exiv2::PreviewManager previewManager (*image);
            Exiv2::PreviewPropertiesList previewList = previewManager.
                    getPreviewProperties();
            if (previewList.empty()) {
                return isThumbnailSavedSuccessfully;
            }
            else { // read from metadata thumnail
                Exiv2::PreviewImage preview = previewManager.getPreviewImage(
                            previewList[0]);
                preview.writeFile(thumbPath.toStdString());
                thumbPath += preview.extension().c_str();
                thumbSize.setWidth(preview.width());
                thumbSize.setHeight(preview.height());
            }
            isThumbnailSavedSuccessfully = true;
            return isThumbnailSavedSuccessfully;
        }
        else {
            return isThumbnailSavedSuccessfully;
        }
    }
#endif // SIR_METADATA_SUPPORT

    return isThumbnailSavedSuccessfully;
}