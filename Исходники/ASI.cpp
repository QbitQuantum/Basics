void ASI::SetPosition(CRef cref, const QPointF& pos)
{
    Component* pComponent = cref.GetInstance();
    if (pComponent != NULL)
    {
        if (!pComponent->m_pData->inLayout)
        {
            GuiRequest request;

            request.cref = cref;
            request.data.point.x = pos.x();
            request.data.point.y = pos.y();
            request.type = GuiRequest::RequestType_SetPosition;

            m_pGuiRequestHandler->PostRequest(&request);
        }

        cref.ReleaseInstance();
    }
}