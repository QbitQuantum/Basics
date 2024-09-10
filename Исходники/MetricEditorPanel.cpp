void MetricEditorPanel::loadFWObject(libfwbuilder::FWObject *obj)
{
    RoutingRule *r=RoutingRule::cast(obj);
    if (r==nullptr) return;
    rule=r;

    FWObject *o = r;
    while (o!=nullptr && Firewall::cast(o)==nullptr) o=o->getParent();
    assert(o!=nullptr);

    m_widget->spin_box->setMinimum( 0);
    m_widget->spin_box->setMaximum( 255);
    m_widget->spin_box->setValue( r->getMetric());
}