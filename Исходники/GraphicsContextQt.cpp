void GraphicsContext::concatCTM(const TransformationMatrix& transform)
{
    if (paintingDisabled())
        return;

    m_data->p()->setMatrix(transform, true);

    // Transformations to the context shouldn't transform the currentPath. 
    // We have to undo every change made to the context from the currentPath to avoid wrong drawings.
    if (!m_data->currentPath.isEmpty() && transform.isInvertible()) {
        QMatrix matrix = transform.inverse();
        m_data->currentPath = m_data->currentPath * matrix;
        m_common->state.pathTransform.multiply(transform);
    }
}