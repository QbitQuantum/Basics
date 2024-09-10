auto_ptr<IInputWidgetProxy> EntityEditor::create_boolean_input_widgets(const Dictionary& metadata)
{
    QCheckBox* checkbox = new QCheckBox(m_parent);

    if (should_be_focused(metadata))
        checkbox->setFocus();

    m_form_layout->addRow(create_label(metadata), checkbox);

    auto_ptr<IInputWidgetProxy> widget_proxy(new CheckBoxProxy(checkbox));
    widget_proxy->set(metadata.strings().get<string>("value"));

    return widget_proxy;
}