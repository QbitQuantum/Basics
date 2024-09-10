SummaryInspectorWidget::SummaryInspectorWidget(const IdentifiedObjectAbstract* obj,
        std::set<const ConstraintModel*> constraints,
        std::set<const TimeNodeModel*> timenodes,
        std::set<const EventModel*> events,
        std::set<const StateModel*> states,
        const iscore::DocumentContext& context,
        QWidget* parent):
    InspectorWidgetBase {*obj, context, parent}
{
    setObjectName("SummaryInspectorWidget");
    setParent(parent);

    auto cSection = new Inspector::InspectorSectionWidget{tr("Constraints"), false, this};
    m_properties.push_back(cSection);

    for(auto c : constraints)
    {
        cSection->addContent(new ConstraintSummaryWidget{*c, context, this});
    }

    auto tnSection = new Inspector::InspectorSectionWidget{tr("TimeNodes"), false, this};
    m_properties.push_back(tnSection);
    for(auto t : timenodes)
    {
        tnSection->addContent(new TimeNodeSummaryWidget{*t, context, this});
    }

    auto evSection = new Inspector::InspectorSectionWidget{tr("Events"), false, this};
    m_properties.push_back(evSection);
    for(auto ev : events)
    {
        evSection->addContent(new EventSummaryWidget{*ev, context, this});
    }

    updateAreaLayout(m_properties);
}