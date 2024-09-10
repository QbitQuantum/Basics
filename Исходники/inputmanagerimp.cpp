    InputImpl(OEngine::Render::OgreRenderer &_ogre,
                   MWWorld::Player &_player,
                   MWBase::WindowManager &_windows,
                   bool debug,
                   OMW::Engine& engine)
      : ogre(_ogre),
        input(ogre.getWindow(), !debug),
        poller(input),
        player(_player),
        windows(_windows),
        mEngine (engine),
        mDragDrop(false),
        mPreviewPOVDelay(0.f),
        mTimeIdle(0.f)
    {
      using namespace OEngine::Input;
      using namespace OEngine::Render;
      using namespace OEngine::GUI;
      using namespace Mangle::Input;
      using namespace OIS;

      disp = DispatcherPtr(new Dispatcher(A_LAST));

      // Bind MW-specific functions
      disp->funcs.bind(A_Quit, boost::bind(&InputImpl::exitNow, this),
                      "Quit program");
      disp->funcs.bind(A_Screenshot, boost::bind(&InputImpl::screenshot, this),
                      "Screenshot");
      disp->funcs.bind(A_Inventory, boost::bind(&InputImpl::toggleInventory, this),
                       "Toggle inventory screen");
      disp->funcs.bind(A_Console, boost::bind(&InputImpl::toggleConsole, this),
                       "Toggle console");
      disp->funcs.bind(A_Journal, boost::bind(&InputImpl::toggleJournal, this),
                       "Toggle journal");
      disp->funcs.bind(A_Activate, boost::bind(&InputImpl::activate, this),
                       "Activate");
      disp->funcs.bind(A_AutoMove, boost::bind(&InputImpl::toggleAutoMove, this),
                      "Auto Move");
      disp->funcs.bind(A_ToggleWalk, boost::bind(&InputImpl::toggleWalking, this),
                      "Toggle Walk/Run");
      disp->funcs.bind(A_ToggleWeapon,boost::bind(&InputImpl::toggleWeapon,this),
                      "Draw Weapon");
      disp->funcs.bind(A_ToggleSpell,boost::bind(&InputImpl::toggleSpell,this),
                      "Ready hands");
      disp->funcs.bind(A_GameMenu, boost::bind(&InputImpl::toggleMainMenu, this),
                      "Toggle main menu");

      mouse = MouseLookEventPtr(new MouseLookEvent());

      // This event handler pumps events into MyGUI
      guiEvents = EventInjectorPtr(new EventInjector(windows.getGui()));

      // Hook 'mouse' and 'disp' up as event handlers into 'input'
      // (the OIS driver and event source.) We do this through an
      // EventList which dispatches the event to multiple handlers for
      // us.
      {
        EventList *lst = new EventList;
        input.setEvent(EventPtr(lst));
        lst->add(mouse,Event::EV_MouseMove);
        lst->add(disp,Event::EV_KeyDown);
        lst->add(guiEvents,Event::EV_ALL);
      }

      mControlSwitch["playercontrols"]      = true;
      mControlSwitch["playerfighting"]      = true;
      mControlSwitch["playerjumping"]       = true;
      mControlSwitch["playerlooking"]       = true;
      mControlSwitch["playermagic"]         = true;
      mControlSwitch["playerviewswitch"]    = true;
      mControlSwitch["vanitymode"]          = true;

      changeInputMode(false);

      /**********************************
        Key binding section

        The rest of this function has hard coded key bindings, and is
        intended to be replaced by user defined bindings later.
       **********************************/

      // Key bindings for keypress events
      // NOTE: These keys do not require constant polling - use in conjuction with variables in loops.

      disp->bind(A_Quit, KC_Q);
      disp->bind(A_GameMenu, KC_ESCAPE);
      disp->bind(A_Screenshot, KC_SYSRQ);
      disp->bind(A_Inventory, KC_I);
      disp->bind(A_Console, KC_F1);
      disp->bind(A_Journal, KC_J);
      disp->bind(A_Activate, KC_SPACE);
      disp->bind(A_AutoMove, KC_Z);
      disp->bind(A_ToggleSneak, KC_X);
      disp->bind(A_ToggleWalk, KC_C);
      disp->bind(A_ToggleWeapon,KC_F);
      disp->bind(A_ToggleSpell,KC_R);

      // Key bindings for polled keys
      // NOTE: These keys are constantly being polled. Only add keys that must be checked each frame.

      // Arrow keys
      poller.bind(A_MoveLeft, KC_LEFT);
      poller.bind(A_MoveRight, KC_RIGHT);
      poller.bind(A_MoveForward, KC_UP);
      poller.bind(A_MoveBackward, KC_DOWN);

      // WASD keys
      poller.bind(A_MoveLeft, KC_A);
      poller.bind(A_MoveRight, KC_D);
      poller.bind(A_MoveForward, KC_W);
      poller.bind(A_MoveBackward, KC_S);

      poller.bind(A_Jump, KC_E);
      poller.bind(A_Crouch, KC_LCONTROL);

      poller.bind(A_TogglePOV, KC_TAB);
    }