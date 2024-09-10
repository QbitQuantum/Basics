std::shared_ptr<StartEndRenderState> ParabolaPointer::buildRenderState(const QVariantMap& propMap) {
    QUuid startID;
    if (propMap["start"].isValid()) {
        QVariantMap startMap = propMap["start"].toMap();
        if (startMap["type"].isValid()) {
            startMap.remove("visible");
            startID = qApp->getOverlays().addOverlay(startMap["type"].toString(), startMap);
        }
    }

    glm::vec3 color = glm::vec3(RenderState::ParabolaRenderItem::DEFAULT_PARABOLA_COLOR);
    float alpha = RenderState::ParabolaRenderItem::DEFAULT_PARABOLA_COLOR.a;
    float width = RenderState::ParabolaRenderItem::DEFAULT_PARABOLA_WIDTH;
    bool isVisibleInSecondaryCamera = RenderState::ParabolaRenderItem::DEFAULT_PARABOLA_ISVISIBLEINSECONDARYCAMERA;
    bool drawInFront = RenderState::ParabolaRenderItem::DEFAULT_PARABOLA_DRAWINFRONT;
    bool enabled = false;
    if (propMap["path"].isValid()) {
        enabled = true;
        QVariantMap pathMap = propMap["path"].toMap();
        if (pathMap["color"].isValid()) {
            color = toGlm(u8vec3FromVariant(pathMap["color"]));
        }

        if (pathMap["alpha"].isValid()) {
            alpha = pathMap["alpha"].toFloat();
        }

        if (pathMap["width"].isValid()) {
            width = pathMap["width"].toFloat();
        }

        if (pathMap["isVisibleInSecondaryCamera"].isValid()) {
            isVisibleInSecondaryCamera = pathMap["isVisibleInSecondaryCamera"].toBool();
        }

        if (pathMap["drawInFront"].isValid()) {
            drawInFront = pathMap["drawInFront"].toBool();
        }
    }

    QUuid endID;
    if (propMap["end"].isValid()) {
        QVariantMap endMap = propMap["end"].toMap();
        if (endMap["type"].isValid()) {
            endMap.remove("visible");
            endID = qApp->getOverlays().addOverlay(endMap["type"].toString(), endMap);
        }
    }

    return std::make_shared<RenderState>(startID, endID, color, alpha, width, isVisibleInSecondaryCamera, drawInFront, enabled);
}