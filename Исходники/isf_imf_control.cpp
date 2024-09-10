EAPI int _isf_imf_context_input_panel_layout_set (Ecore_IMF_Input_Panel_Layout layout)
{
    int layout_temp = layout;

    connect_panel ();
    _imcontrol_client.prepare ();
    _imcontrol_client.set_layout (layout_temp);
    _imcontrol_client.send ();
    return 0;
}