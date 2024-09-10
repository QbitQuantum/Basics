// 创建TF
IDWriteTextFormat*	TextFormatCache::CreateTextFormat(const TextFormatParameter* pParameter){
	IDWriteTextFormat* pTextFormat(nullptr);
#ifdef _DEBUG
	if (!s_ppDWriteFactory){
		_cwprintf(L"s_ppDWriteFactory未初始化.\n");
		return NULL;
	}
	if (!(*s_ppDWriteFactory)){
		_cwprintf(L"DWriteFactory未初始化.\n");
		return NULL;
	}
#endif
	(*s_ppDWriteFactory)->CreateTextFormat(
		pParameter->font_name,
		s_pCollection,
		pParameter->font_weight,
		pParameter->font_style,
		pParameter->font_stretch,
		pParameter->font_size * (96.0f / 72.f),
		L"", //locale
		&pTextFormat
		);
	if (pTextFormat){
#ifdef _DEBUG
		HRESULT hr(S_OK);
		// 设置行对齐
		if (SUCCEEDED(hr))
			hr = pTextFormat->SetTextAlignment(pParameter->text_alignmen);
		// 设置列对齐
		if (SUCCEEDED(hr))
			hr = pTextFormat->SetParagraphAlignment(pParameter->paragraph_alignment);
		// 设置自动换行
		if (SUCCEEDED(hr))
			hr = pTextFormat->SetWordWrapping(pParameter->word_wrapping);
		// 设置制表符宽度
		if (SUCCEEDED(hr))
			hr = pTextFormat->SetIncrementalTabStop(pParameter->incremental_tabstop);
		// 段落排列方向
		//if (SUCCEEDED(hr))
			//hr = pTextFormat->SetFlowDirection(DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP);
		// 设置行距
		if (SUCCEEDED(hr))
			hr = pTextFormat->SetLineSpacing(pParameter->line_spacing_method, pParameter->line_spacing,
			pParameter->baseline);
		if (FAILED(hr)){
			MessageBoxW(nullptr, L"<TextFormatCache::CreateTextFormat>: OK to created but failed to set\n"
				L"创建成功但是设置失败", L"Error", MB_OK);
			SafeRelease(pTextFormat);
			return nullptr;
		}
#else
		// 设置行对齐
		pTextFormat->SetTextAlignment(pParameter->text_alignmen);
		// 设置列对齐
		pTextFormat->SetParagraphAlignment(pParameter->paragraph_alignment);
		// 设置自动换行
		pTextFormat->SetWordWrapping(pParameter->word_wrapping);
		// 设置制表符宽度
		pTextFormat->SetIncrementalTabStop(pParameter->incremental_tabstop);
		// 段落排列方向
		//pTextFormat->SetFlowDirection(pParameter->flow_direction);
		// 设置行距
		pTextFormat->SetLineSpacing(pParameter->line_spacing_method, pParameter->line_spacing,
			pParameter->baseline);
#endif
		return pTextFormat;
	}
	return nullptr;
	//s_aryTextFormat[idx]->SetTrimming();
}