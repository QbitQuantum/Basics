// Construtor of JoystickConfiguration
JoystickConfiguration::JoystickConfiguration(int pad, bool left, wxWindow *parent)
    : wxDialog(
          parent,                      // Parent
          wxID_ANY,                    // ID
          _T("Gamepad configuration"), // Title
          wxDefaultPosition,           // Position
          wxSize(400, 200),            // Width + Lenght
          // Style
          wxSYSTEM_MENU |
              wxCAPTION |
              wxCLOSE_BOX |
              wxCLIP_CHILDREN)
{
    m_init_reverse_Lx = false;
    m_init_reverse_Ly = false;
    m_init_reverse_Rx = false;
    m_init_reverse_Ry = false;
    m_init_mouse_Ljoy = false;
    m_init_mouse_Rjoy = false;

    m_pad_id = pad;
    m_isForLeftJoystick = left;
    m_pan_joystick_config = new wxPanel(
        this,              // Parent
        wxID_ANY,          // ID
        wxDefaultPosition, // Prosition
        wxSize(300, 200)   // Size
        );

    if (m_isForLeftJoystick) {
        m_cb_reverse_Lx = new wxCheckBox(
            m_pan_joystick_config, // Parent
            wxID_ANY,              // ID
            _T("Reverse Lx"),      // Label
            wxPoint(20, 20)        // Position
            );

        m_cb_reverse_Ly = new wxCheckBox(
            m_pan_joystick_config, // Parent
            wxID_ANY,              // ID
            _T("Reverse Ly"),      // Label
            wxPoint(20, 40)        // Position
            );

        m_cb_mouse_Ljoy = new wxCheckBox(
            m_pan_joystick_config,                    // Parent
            wxID_ANY,                                 // ID
            _T("Use mouse for left analog joystick"), // Label
            wxPoint(20, 60)                           // Position
            );

        m_cb_reverse_Rx = nullptr;
        m_cb_reverse_Ry = nullptr;
        m_cb_mouse_Rjoy = nullptr;
    } else {
        m_cb_reverse_Rx = new wxCheckBox(
            m_pan_joystick_config, // Parent
            wxID_ANY,              // ID
            _T("Reverse Rx"),      // Label
            wxPoint(20, 20)        // Position
            );

        m_cb_reverse_Ry = new wxCheckBox(
            m_pan_joystick_config, // Parent
            wxID_ANY,              // ID
            _T("Reverse Ry"),      // Label
            wxPoint(20, 40)        // Position
            );

        m_cb_mouse_Rjoy = new wxCheckBox(
            m_pan_joystick_config,                     // Parent
            wxID_ANY,                                  // ID
            _T("Use mouse for right analog joystick"), // Label
            wxPoint(20, 60)                            // Position
            );

        m_cb_reverse_Lx = nullptr;
        m_cb_reverse_Ly = nullptr;
        m_cb_mouse_Ljoy = nullptr;
    }

    m_bt_ok = new wxButton(
        m_pan_joystick_config, // Parent
        wxID_ANY,              // ID
        _T("&OK"),             // Label
        wxPoint(250, 130),     // Position
        wxSize(60, 25)         // Size
        );

    m_bt_cancel = new wxButton(
        m_pan_joystick_config, // Parent
        wxID_ANY,              // ID
        _T("&Cancel"),         // Label
        wxPoint(320, 130),     // Position
        wxSize(60, 25)         // Size
        );

    Bind(wxEVT_BUTTON, &JoystickConfiguration::OnButtonClicked, this);
    Bind(wxEVT_CHECKBOX, &JoystickConfiguration::OnCheckboxChange, this);
}