/** Updates Exif thumnail after conversion and (if required) rotates this thumbnail.
  * New thumbnail will set as \a exifThumbnail in metadata object.\n
  * If setting thumbnail fails, this function will print error using printError()
  * function.\n
  * This function is available if SIR_METADATA_SUPPORT is defined only.
  */
void ConvertThread::updateThumbnail(const QImage &image) {
    // update thumbnail
    if (saveMetadata && shared.updateThumbnail) {
        MetadataUtils::ExifStruct *exifStruct = metadata.exifStruct();
        int w = exifStruct->thumbnailWidth.split(' ').first().toInt();
        int h = exifStruct->thumbnailHeight.split(' ').first().toInt();
        QImage tmpImg = image.scaled(w,h, Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation);
        bool specialRotate = (rotate && (int)angle%90 != 0);
        QImage *thumbnail = &exifStruct->thumbnailImage;
        if (specialRotate) {
            w = tmpImg.width();
            h = tmpImg.height();
            *thumbnail = tmpImg;
        }
        else {
            if (shared.backgroundColor.isValid())
                thumbnail->fill(shared.backgroundColor.rgb());
            else
                thumbnail->fill(Qt::black);
            QPoint begin ( (w-tmpImg.width())/2, (h-tmpImg.height())/2 );
            for (int i=0, y=begin.y(); i<tmpImg.height(); i++, y++) {
                for (int j=0, x=begin.x(); j<tmpImg.width(); j++, x++)
                    thumbnail->setPixel(x, y, tmpImg.pixel(j,i));
            }
        }
        // rotate thumbnail
        if (shared.rotateThumbnail && !specialRotate) {
            QTransform transform;
            int flip;
            transform.rotate(MetadataUtils::Exif::rotationAngle(
                                 exifStruct->orientation, &flip));
            if (flip == MetadataUtils::Vertical)
                transform.scale(1.0,-1.0);
            else if (flip == MetadataUtils::Horizontal)
                transform.scale(-1.0,1.0);
            *thumbnail = thumbnail->transformed(transform);
        }
        if (!metadata.setExifThumbnail(thumbnail,tid))
            printError();
    }
}