void
TaskManagerDialog::Create(SingleWindow &parent)
{
  WndForm::Create(parent, parent.GetClientRect(), _("Task Manager"));

  task = protected_task_manager->TaskClone();

  /* create the controls */

  ContainerWindow &client_area = GetClientAreaWindow();
  const TaskManagerLayout layout =
    CalculateTaskManagerLayout(client_area.GetClientRect());

  task_view_position = layout.task_view;

  WindowStyle hidden;
  hidden.Hide();
  task_view = new TaskMapWindow(UIGlobals::GetMapLook(), *this, MAP);
  task_view->Create(client_area, layout.task_view, hidden);

  ButtonWindowStyle button_style(hidden);
  button_style.TabStop();
  target_button = new WndButton(client_area, GetLook(), _("Target"),
                                layout.target_button, button_style,
                                *this, TARGET);

  WindowStyle tab_style;
  tab_style.ControlParent();
  tab_bar = new TabBarControl(client_area, GetLook(), layout.tab_bar,
                              tab_style, layout.vertical);
  tab_bar->SetPageFlippedCallback([this]() { UpdateCaption(); });

  /* create pages */

  TaskPropertiesPanel *wProps =
    new TaskPropertiesPanel(*this, &task, &modified);

  TaskClosePanel *wClose = new TaskClosePanel(*this, &modified);

  TaskCalculatorPanel *wCalculator =
    new TaskCalculatorPanel(UIGlobals::GetDialogLook(), &modified);
  wCalculator->SetTargetButton(target_button);

  const MapLook &look = UIGlobals::GetMapLook();
  Widget *wEdit = CreateTaskEditPanel(*this, look.task, look.airspace,
                                      &task, &modified);

  TaskMiscPanel *list_tab = new TaskMiscPanel(*this, &task, &modified);

  const bool enable_icons =
    CommonInterface::GetUISettings().dialog.tab_style
    == DialogSettings::TabStyle::Icon;
  const IconLook &icons = UIGlobals::GetIconLook();
  const Bitmap *CalcIcon = enable_icons ? &icons.hBmpTabCalculator : NULL;
  const Bitmap *TurnPointIcon = enable_icons ? &icons.hBmpTabTask : NULL;
  const Bitmap *BrowseIcon = enable_icons ? &icons.hBmpTabWrench : NULL;
  const Bitmap *PropertiesIcon = enable_icons ? &icons.hBmpTabSettings : NULL;

  tab_bar->AddTab(wCalculator, _("Calculator"), CalcIcon);

  if (layout.vertical) {
    tab_bar->AddTab(wEdit, _("Turn Points"), TurnPointIcon);
    TurnpointTab = 1;

    tab_bar->AddTab(list_tab, _("Manage"), BrowseIcon);

    tab_bar->AddTab(wProps, _("Rules"), PropertiesIcon);
    PropertiesTab = 3;

    tab_bar->AddTab(wClose, _("Close"));

    tab_bar->SetCurrentPage(0);
  } else {
    tab_bar->AddTab(wClose, _("Close"));

    tab_bar->AddTab(wEdit, _("Turn Points"), TurnPointIcon);
    TurnpointTab = 2;

    tab_bar->AddTab(list_tab, _("Manage"), BrowseIcon);

    tab_bar->AddTab(wProps, _("Rules"), PropertiesIcon);
    PropertiesTab = 4;

    tab_bar->SetCurrentPage(0);
  }

  UpdateCaption();
}