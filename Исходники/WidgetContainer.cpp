void WidgetContainer::OnInputPointerPress(const EventInputPointer *ev)
{
	ASSERT_NULL(ev);

	WidgetIterator it = vWidget.begin();
	WidgetIterator end = vWidget.end();

	for (; it != end; ++it)
	{
		IWidget *w = (*it);
		ASSERT_NULL(w);

		bEventConsumed = FALSE;

		if (w->IsDisabled())
			continue;

		f32 cX = ev->GetX();
		f32 cY = ev->GetY();

		if (!w->ContainsPoint(cX, cY))
			continue;

		if (w->GetObjectType() == Seed::ObjectGuiWidgetContainer)
		{
			WidgetContainer *wc = reinterpret_cast<WidgetContainer *>(w);
			wc->OnInputPointerPress(ev);

			bEventConsumed = wc->IsEventConsumed();
			if (bEventConsumed)
				break;
		}

		if (!(w->GetTrigger() & ev->GetPressed()))
			continue;

		u32 j = ev->GetJoystick();

		//LOG("> PRESS [%d, %f, %f]", j, cX, cY);

		if (w->GetState() == Seed::WidgetStateDrag)
		{
			continue;
		}

		const EventWidget newEvent(w, NULL, WidgetEventPressed, j, cX, cY, ev->GetPressed(), ev->GetHold(), ev->GetReleased());

		LOG(">PRESSED_OVER [id: %d]", w->GetId());
		// GetState eh o baseado em prioridade a partir de todos os inputs.
		if (w->GetState() != Seed::WidgetStatePressedOver && w->GetPlayerState(j) != Seed::WidgetStatePressedOver)
		{
			// muda apenas o estado interno do widget
			LOG("\tEstado WIDGET");
			w->OnWidgetPress(&newEvent);
		}

		w->SetState(Seed::WidgetStatePressed);
		w->SetPlayerState(Seed::WidgetStatePressedOver, j);
		LOG("\tEstado PLAYER");

		w->SendOnPress(&newEvent);
		LOG("\tEvento");
		//if (newEvent.IsConsumed())
		bEventConsumed = newEvent.IsConsumed();
		if (bEventConsumed)
			break;
	}
}