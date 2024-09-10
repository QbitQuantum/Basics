SkOSWindow::SkOSWindow(void* hWnd) : fHWND(hWnd), fAGLCtx(NULL)
{
	OSStatus    result;
    WindowRef   wr = (WindowRef)hWnd;

    HIViewRef imageView, parent;
    HIViewRef rootView = HIViewGetRoot(wr);
    HIViewFindByID(rootView, kHIViewWindowContentID, &parent);
    result = HIImageViewCreate(NULL, &imageView);
	SkASSERT(result == noErr);

    result = HIViewAddSubview(parent, imageView);
	SkASSERT(result == noErr);

    fHVIEW = imageView;

    HIViewSetVisible(imageView, true);
    HIViewPlaceInSuperviewAt(imageView, 0, 0);

    if (true) {
        HILayoutInfo layout;
        layout.version = kHILayoutInfoVersionZero;
        set_bindingside(&layout.binding.left, parent, kHILayoutBindLeft);
        set_bindingside(&layout.binding.top, parent, kHILayoutBindTop);
        set_bindingside(&layout.binding.right, parent, kHILayoutBindRight);
        set_bindingside(&layout.binding.bottom, parent, kHILayoutBindBottom);
        set_axisscale(&layout.scale.x, parent);
        set_axisscale(&layout.scale.y, parent);
        set_axisposition(&layout.position.x, parent, kHILayoutPositionLeft);
        set_axisposition(&layout.position.y, rootView, kHILayoutPositionTop);
        HIViewSetLayoutInfo(imageView, &layout);
    }

    HIImageViewSetOpaque(imageView, true);
    HIImageViewSetScaleToFit(imageView, false);

	static const EventTypeSpec  gTypes[] = {
		{ kEventClassKeyboard,  kEventRawKeyDown			},
        { kEventClassKeyboard,  kEventRawKeyUp              },
		{ kEventClassMouse,		kEventMouseDown				},
		{ kEventClassMouse,		kEventMouseDragged			},
		{ kEventClassMouse,		kEventMouseMoved			},
		{ kEventClassMouse,		kEventMouseUp				},
		{ kEventClassTextInput, kEventTextInputUnicodeForKeyEvent   },
		{ kEventClassWindow,	kEventWindowBoundsChanged	},
//		{ kEventClassWindow,	kEventWindowDrawContent		},
		{ SK_MacEventClass,		SK_MacEventKind				}
	};

	EventHandlerUPP handlerUPP = NewEventHandlerUPP(SkOSWindow::EventHandler);
	int				count = SK_ARRAY_COUNT(gTypes);

	result = InstallEventHandler(GetWindowEventTarget(wr), handlerUPP,
						count, gTypes, this, nil);
	SkASSERT(result == noErr);

	gCurrOSWin = this;
	gCurrEventQ = GetCurrentEventQueue();
	gEventTarget = GetWindowEventTarget(wr);

	static bool gOnce = true;
	if (gOnce) {
		gOnce = false;
		gPrevNewHandler = set_new_handler(sk_new_handler);
	}
}