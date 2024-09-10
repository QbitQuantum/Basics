void SkMultiPictureDraw::DrawData::Reset(SkTDArray<DrawData>& data) {
    for (int i = 0; i < data.count(); ++i) {
        data[i].fPicture->unref();
        data[i].fCanvas->unref();
        delete data[i].fPaint;
    }
    data.rewind();
}