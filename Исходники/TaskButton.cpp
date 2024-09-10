TaskButton::TaskButton(IPane *parent, IPainter *backgroundPainter, IPainter *textPainter,
    IEventHandler *eventHandler, HWND window, TaskData &taskData)
  : mEventHandler(eventHandler)
  , mIconPainter(nullptr)
  , mMenu(nullptr)
  , mMenuWindow(nullptr)
  , mOverlayIconPainter(nullptr)
  , mTaskData(taskData)
  , mFlashInterval(0)
  , mWindow(window)
{
  mIconPosition = NRECT(NLENGTH(0, 0, 0), NLENGTH(0, 0, 0), NLENGTH(0, 0, 32), NLENGTH(0, 0, 32));
  mIconPainter = nCore::CreateImagePainter();
  mIconPainter->SetPosition(mIconPosition, nullptr);
  mIconPainter->SetImage(nCore::GetWindowIcon(window, 32));

  mOverlayIconPosition =
    NRECT(NLENGTH(0, 0, 16), NLENGTH(0, 0, 16), NLENGTH(0, 0, 32), NLENGTH(0, 0, 32));
  mOverlayIconPainter = nCore::CreateImagePainter();
  mOverlayIconPainter->SetPosition(mOverlayIconPosition, nullptr);

  PaneInitData initData;
  ZeroMemory(&initData, sizeof(PaneInitData));
  initData.cbSize = sizeof(PaneInitData);
  initData.messageHandler = this;
  IPainter *painters[] = { backgroundPainter, textPainter, mIconPainter, mOverlayIconPainter };
  initData.painters = painters;
  initData.numPainters = _countof(painters);
  initData.states = gButtonStates;
  initData.numStates = gNumButtonStates;
  mPane = parent->CreateChild(&initData);

  if (IsIconic(window)) {
    ActivateState(State::Minimized);
  }
  if (window == gActiveWindow) {
    ActivateState(State::Active);
  }

  wchar_t windowText[256];
  GetWindowText(window, windowText, 256);
  mPane->SetText(windowText);

  // Reset the system menu for the window
  mMenu = GetSystemMenu(mWindow, FALSE);
  if (!IsMenu(mMenu)) {
    GetSystemMenu(mWindow, TRUE);
    mMenu = GetSystemMenu(mWindow, FALSE);
  }
}