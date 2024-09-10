void SampleScene01::Render(Dx11Context* context, Dx11Camera* camera, Dx11Lens* lens)
{
	wchar_t buf[32]; 
	wsprintf(buf, L"カウント: %d", left); 
	float w = text->SetText(context, buf); 

	EffectGUIStandardInfo info = {0, 0, 0.125f * w, 0.125f, 
		1.0f, 0.5f, 0, 0}; // 完全不透明（1.0f), 色半反転(0,5f)

	effect->Update(context, text, &info); 
	if(_heapchk()!=_HEAPOK) {
		DebugBreak();
	}
	osd_fps->Render(context, camera, lens); 
}