static BaseLayerAndroid* nativeDeserializeViewState(JNIEnv* env, jobject, jint version,
                                                    jobject jstream, jbyteArray jstorage)
{
    SkStream* stream = CreateJavaInputStreamAdaptor(env, jstream, jstorage);
    if (!stream)
        return 0;
    Color color = stream->readU32();
    SkPicture* picture = new SkPicture(stream);
    PictureLayerContent* content = new PictureLayerContent(picture);

    BaseLayerAndroid* layer = new BaseLayerAndroid(content);
    layer->setBackgroundColor(color);

    SkRegion dirtyRegion;
    dirtyRegion.setRect(0, 0, content->width(), content->height());
    layer->markAsDirty(dirtyRegion);

    SkSafeUnref(content);
    SkSafeUnref(picture);
    int childCount = stream->readS32();
    for (int i = 0; i < childCount; i++) {
        LayerAndroid* childLayer = deserializeLayer(version, stream);
        if (childLayer)
            layer->addChild(childLayer);
    }
    delete stream;
    return layer;
}