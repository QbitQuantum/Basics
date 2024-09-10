PixmapSource SkinContext::getPixmapSource(const QDomNode& pixmapNode) const {
    PixmapSource source;

    const SvgParser svgParser(*this);

    if (!pixmapNode.isNull()) {
        QDomNode svgNode = selectNode(pixmapNode, "svg");
        if (!svgNode.isNull()) {
            // inline svg
            const QByteArray rslt = svgParser.saveToQByteArray(
                svgParser.parseSvgTree(svgNode, m_xmlPath));
            source.setSVG(rslt);
        } else {
            // filename
            QString pixmapName = nodeToString(pixmapNode);
            if (!pixmapName.isEmpty()) {
                source.setPath(getSkinPath(pixmapName));
                if (source.isSVG()) {
                    const QByteArray rslt = svgParser.saveToQByteArray(
                            svgParser.parseSvgFile(source.getPath()));
                    source.setSVG(rslt);
                }
            }
        }
    }

    return source;
}