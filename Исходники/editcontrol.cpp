void CMainFrame::SetEditControl()
{
	CWndControl* editCtrl = null;
	if (CWndControl::s_selection.GetSize() >= 1)
		editCtrl = CWndControl::s_selection[0];

	if (editCtrl)
	{
		CWndControl::s_selection[0] = null;

		WindowData* wndData = null;
		ControlData* ctrlData = null;

		if (editCtrl->GetType() == WTYPE_GUI_EDITOR_WND)
			wndData = ((CWndWindow*)editCtrl)->Data();
		else
		{
			wndData = ((CWndWindow*)editCtrl->GetParent())->Data();

			for (int i = 0; i < wndData->controls.GetSize(); i++)
			{
				if (wndData->controls[i]->ID == editCtrl->GetID())
				{
					ctrlData = wndData->controls[i];
					break;
				}
			}

			wndData = null;
		}

		ui.dockEdit->setEnabled(true);
		if (wndData)
		{
			ui.editControlID->setEditable(true);
			ui.editControlID->setCurrentText(((CWndWindow*)editCtrl)->Data()->define);
			ui.editControlID->setEnabled(false);
			ui.editControlWidth->setValue(wndData->size.width());
			ui.editControlHeight->setValue(wndData->size.height());
			ui.editControlText->setText(wndData->title);
			ui.editControlTexture->setText(wndData->texture);
			ui.editControlTooltip->setText(wndData->tooltip);
			ui.btnAdaptSizeToTexture->setEnabled(false);
			ui.editControlNoDrawFrame->setChecked((wndData->flags & WBS_NODRAWFRAME) != 0);
			ui.editControlNoDrawFrame->setEnabled(true);
			ui.editControlTiles->setChecked(wndData->tiles);

			ui.groupEditControl->setEnabled(false);
			ui.editControlEnabled->setChecked(false);
			ui.editControlVisible->setChecked(false);
			ui.editControlGroup->setChecked(false);
			ui.editControlTabStop->setChecked(false);
			ui.editControlScrollBar->setChecked(false);
			ui.editControlX->setValue(0);
			ui.editControlY->setValue(0);
			ui.editVAlignTop->setChecked(true);
			ui.editHAlignLeft->setChecked(true);

			ui.groupEditWindow->setEnabled(true);
			ui.editWindowCaption->setChecked((wndData->flags & WBS_CAPTION) != 0);
			ui.editWindowNoFrame->setChecked((wndData->flags & WBS_NOFRAME) != 0);

			if (wndData->format == D3DFMT_A4R4G4B4)
				ui.editWindowD3DFormat->setCurrentText("A4R4G4B4");
			else if (wndData->format == D3DFMT_A8R8G8B8)
				ui.editWindowD3DFormat->setCurrentText("A8R8G8B8");

#if __VER >= 19
			ui.editWindowIcon->setEnabled(true);
			ui.editWindowIcon->setText(wndData->icon);

			ui.editControlColor->setEnabled(false);
			ui.editControlViewColor->setStyleSheet("background-color: #7f7f7f;");
#endif
		}
		else
		{
			ui.editControlID->setEditable(false);
			ui.editControlID->setCurrentText(ctrlData->define);
			ui.editControlID->setEnabled(true);
			ui.editControlWidth->setValue(ctrlData->rect.width());
			ui.editControlHeight->setValue(ctrlData->rect.height());
			ui.editControlText->setText(ctrlData->text);
			ui.editControlTexture->setText(ctrlData->texture);
			ui.editControlTooltip->setText(ctrlData->tooltip);
			ui.editControlTiles->setChecked(ctrlData->tiles);
			if (ctrlData->type == WTYPE_BUTTON)
				ui.btnAdaptSizeToTexture->setEnabled(true);
			else
				ui.btnAdaptSizeToTexture->setEnabled(false);
			ui.editControlNoDrawFrame->setChecked((ctrlData->flags & WBS_NODRAWFRAME) != 0);
			if (ctrlData->type == WTYPE_TABCTRL)
				ui.editControlNoDrawFrame->setEnabled(false);
			else
				ui.editControlNoDrawFrame->setEnabled(true);

			ui.groupEditControl->setEnabled(true);
			ui.editControlEnabled->setChecked(!ctrlData->disabled);
			ui.editControlVisible->setChecked(ctrlData->visible);
			ui.editControlGroup->setChecked(ctrlData->group);
			ui.editControlTabStop->setChecked(ctrlData->tabStop);
			ui.editControlScrollBar->setChecked((ctrlData->flags & WBS_VSCROLL) != 0);
			ui.editControlX->setValue(ctrlData->rect.left());
			ui.editControlY->setValue(ctrlData->rect.top());

			if (ctrlData->type == WTYPE_STATIC)
			{
				ui.groupEditHAlign->setEnabled(true);
				ui.groupEditVAlign->setEnabled(true);

				if ((ctrlData->flags & WSS_ALIGNHRIGHT) != 0)
					ui.editHAlignRight->setChecked(true);
				else if ((ctrlData->flags & WSS_ALIGNHCENTER) != 0)
					ui.editHAlignCenter->setChecked(true);
				else
					ui.editHAlignLeft->setChecked(true);

				if ((ctrlData->flags & WSS_ALIGNVBOTTOM) != 0)
					ui.editVAlignBottom->setChecked(true);
				else if ((ctrlData->flags & WSS_ALIGNVCENTER) != 0)
					ui.editVAlignMiddle->setChecked(true);
				else
					ui.editVAlignTop->setChecked(true);
			}
			else
			{
				ui.editVAlignTop->setChecked(true);
				ui.editHAlignLeft->setChecked(true);
				ui.groupEditHAlign->setEnabled(false);
				ui.groupEditVAlign->setEnabled(false);
			}

			ui.groupEditWindow->setEnabled(false);
			ui.editWindowCaption->setChecked(false);
			ui.editWindowNoFrame->setChecked(false);
			ui.editWindowD3DFormat->setCurrentText("A4R4G4B4");

#if __VER >= 19
			ui.editWindowIcon->setEnabled(false);
			ui.editWindowIcon->setText("");

			ui.editControlColor->setEnabled(true);
			ui.editControlViewColor->setStyleSheet("background-color: " % ctrlData->color.name() % ';');
#endif
		}

		CWndControl::s_selection[0] = editCtrl;
	}
	else
	{
		ui.editControlID->setEditable(true);
		ui.editControlID->setCurrentText("");
		ui.editControlWidth->setValue(1);
		ui.editControlHeight->setValue(1);
		ui.editControlText->setText("");
		ui.editControlTexture->setText("");
		ui.editControlTooltip->setText("");
		ui.btnAdaptSizeToTexture->setEnabled(false);
		ui.editControlNoDrawFrame->setChecked(false);
		ui.editControlNoDrawFrame->setEnabled(true);
		ui.editControlTiles->setChecked(false);
		ui.dockEdit->setEnabled(false);

		ui.groupEditControl->setEnabled(false);
		ui.editControlEnabled->setChecked(false);
		ui.editControlVisible->setChecked(false);
		ui.editControlGroup->setChecked(false);
		ui.editControlTabStop->setChecked(false);
		ui.editControlScrollBar->setChecked(false);
		ui.editControlX->setValue(0);
		ui.editControlY->setValue(0);
		ui.editVAlignTop->setChecked(true);
		ui.editHAlignLeft->setChecked(true);

		ui.groupEditWindow->setEnabled(false);
		ui.editWindowCaption->setChecked(false);
		ui.editWindowNoFrame->setChecked(false);
		ui.editWindowD3DFormat->setCurrentText("A4R4G4B4");

#if __VER >= 19
		ui.editWindowIcon->setEnabled(false);
		ui.editWindowIcon->setText("");

		ui.editControlColor->setEnabled(false);
		ui.editControlViewColor->setStyleSheet("background-color: #7f7f7f;");
#endif
	}

	m_editor->RenderEnvironment();
}