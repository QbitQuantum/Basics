void Wms::getMap( const QString &image_format, const QString &layers, const QSize &image_size, const BoundingBox &bbox) {

  // check the validity of the input parameters
  
  // bbox
  // TODO
  qDebug() << /*"BBOX : "  <<*/ bbox;


  // layers
  if (layers.isEmpty()) {
    serviceException(
      "noLayers",
      "no layers specified");
    return;
  }
  QStringList layer_names = layers.split(",");
  QStringList layer_names_cleaned;
  for (int i=0; i<layer_names.size(); ++i) {
    QString layer_name = layer_names.at(i).trimmed();
    
    if (!layer_name.isEmpty()) {
      if (renderer.map.hasLayer(layer_name)) {
        layer_names_cleaned.append(layer_name);  
      }
      else {
        serviceException(
          "layerDoesNotExist",
          "one of the layers does not exist");
        return;       
      }
    }
  }

  // format
  QByteArray renderformat;
  QList<QByteArray> supported_formats = renderer.getImageFormats();
  if (image_format == MIMETYPE_PNG) {
    renderformat = "png";  
  }
  else if (image_format == MIMETYPE_JPG) {
    renderformat = "jpeg";  
  }
  else if (image_format == MIMETYPE_TIF) {
    renderformat = "tiff";  
  };

  if (renderformat.isEmpty() || !supported_formats.contains(renderformat.data())) {
    serviceException(
      "formatNotsupported",
      "the imageformat is not supported");
    return;
  }


  // render
  renderer.map.setVisibleLayers(layer_names_cleaned);

  QByteArray bytes;
  QBuffer buffer(&bytes); // write binary data
  buffer.open(QIODevice::WriteOnly);

  if (renderer.render( buffer, renderformat.toUpper(), image_size)) {

    m_request->setHeader(HTTP_CONTENT_TYPE, image_format.toUtf8());
    QByteArray content_length = QByteArray::number(bytes.length());
    m_request->setHeader(HTTP_CONTENT_LEN, content_length );
    m_request->write(bytes);
  }
  else {
    serviceException(
      "renderError",
      "could not render the image - this should realy not happen, sorry");
    return;
  }
}