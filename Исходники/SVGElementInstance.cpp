SVGElementInstance::~SVGElementInstance()
{
    for (RefPtr<SVGElementInstance> child = m_firstChild; child; child = child->m_nextSibling)
        child->setParent(0);

    // Deregister as instance for passed element.
    m_element->document()->accessSVGExtensions()->removeInstanceMapping(this, m_element.get());
}