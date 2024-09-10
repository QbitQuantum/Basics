bool ImageDiffer::Diff(const Image& ref, const Image& target) {
    SAFE_DELETE(m_diffData);
    SAFE_DELETE(m_displayData);

    if (ref.GetWidth() != target.GetWidth() ||
        ref.GetHeight() != target.GetHeight()) {
        ApolloException::NotYetImplemented();
    }

    m_ref = &ref;
    m_target = &target;
    m_diffData = new Image(ref.GetWidth(), ref.GetHeight());
    m_displayData = new Image(ref.GetWidth(), ref.GetHeight());

    bool identical = true;

    for (UINT32 row = 0; row < ref.GetHeight(); row++) {
        for (UINT32 col = 0; col < ref.GetWidth(); col++) {
            Color4f diff = ref.GetPixel(row, col) - target.GetPixel(row, col);
            diff.Abs();
            m_diffData->SetPixel(diff, row, col);

            diff *= m_magnify;
            if (diff.MaxChannel() > m_threshold) {
                Color4f c1 = ref.GetPixel(row, col);
                Color4f c2 = target.GetPixel(row, col);
                identical = false;
            }
        }
    }

    m_displayDirty = true;

    return identical;
}