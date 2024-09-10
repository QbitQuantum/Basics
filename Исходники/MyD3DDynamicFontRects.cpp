	bool MyDynamicFontRects::UpdateVertexBufferByString(ID3D11DeviceContext* pDeviceContext, LPCWSTR pString,
		MyMath::Vector2F posInPixels,
		const MyMath::Vector4F& upperColor, const MyMath::Vector4F& lowerColor,
		long fontHeight, bool usesFixedFeed,
		uint32_t fontTexWidth, uint32_t fontTexHeight,
		const MyMath::TCharCodeUVMap& codeUVMap)
	{
		_ASSERTE(pString != nullptr);
		m_stringLength = 0;
		float offsetX = 0;
		TVertex* pVertexArray = &m_vertexArray[0]; // ローカル変数にキャッシュして高速化。
		for (int i = 0; pString[i] != 0 && i < MaxCharacterCount; ++i, ++m_stringLength)
		{
			// HACK: このアルゴリズム（というか単一の wchar_t キー）だと、サロゲート ペアにはどうしても対応不可能。
			const size_t charCode = static_cast<size_t>(pString[i]);
			if (charCode < codeUVMap.size())
			{
				const auto codeUV = codeUVMap[charCode];
				const float uvLeft   = static_cast<float>(codeUV.X) / fontTexWidth;
				const float uvTop    = static_cast<float>(codeUV.Y) / fontTexHeight;
				const float uvRight  = static_cast<float>(codeUV.GetRight()) / fontTexWidth;
				const float uvBottom = static_cast<float>(codeUV.GetBottom()) / fontTexHeight;
				const float uvWidth   = codeUV.Width;
				const float uvHeight  = codeUV.Height;
				// LT, RT, LB, RB.（0, 1, 2 は左手系の定義順）
				const size_t index0 = i * 4 + 0;
				// 文字の水平方向送り（カーニングは考慮しないが、プロポーショナルの場合は文字幅）。
				// スペースの文字送りも考慮する。
				// HUD 系は常にモノスペースのほうがいいこともある。
				// 非 ASCII はテクスチャ作成時にフォント メトリックから取得した文字幅にする。
				// ヨーロッパ言語など、非 ASCII でもモノスペース時は半角幅のほうがいい文字もあるが、それは考慮しない。
				// したがって、メソッドのフラグで等幅指定されたら、ASCII のみ半角幅とし、
				// 非 ASCII はフォント メトリックから取得した文字幅を使うようにする。
				const float feed = (usesFixedFeed && iswascii(pString[i])) ? (fontHeight / 2) : uvWidth;
				pVertexArray[index0].Position.x = posInPixels.x + offsetX;
				pVertexArray[index0].Position.y = posInPixels.y;
				pVertexArray[index0].Position.z = 0;
				//pVertexArray[index0].Position.w = 1;
				pVertexArray[index0].Color = upperColor;
				pVertexArray[index0].TexCoord.x = uvLeft;
				pVertexArray[index0].TexCoord.y = uvTop;
				const size_t index1 = i * 4 + 1;
				pVertexArray[index1].Position.x = posInPixels.x + offsetX + uvWidth;
				pVertexArray[index1].Position.y = posInPixels.y;
				pVertexArray[index1].Position.z = 0;
				//pVertexArray[index1].Position.w = 1;
				pVertexArray[index1].Color = upperColor;
				pVertexArray[index1].TexCoord.x = uvRight;
				pVertexArray[index1].TexCoord.y = uvTop;
				const size_t index2 = i * 4 + 2;
				pVertexArray[index2].Position.x = posInPixels.x + offsetX;
				pVertexArray[index2].Position.y = posInPixels.y + uvHeight;
				pVertexArray[index2].Position.z = 0;
				//pVertexArray[index2].Position.w = 1;
				pVertexArray[index2].Color = lowerColor;
				pVertexArray[index2].TexCoord.x = uvLeft;
				pVertexArray[index2].TexCoord.y = uvBottom;
				const size_t index3 = i * 4 + 3;
				pVertexArray[index3].Position.x = posInPixels.x + offsetX + uvWidth;
				pVertexArray[index3].Position.y = posInPixels.y + uvHeight;
				pVertexArray[index3].Position.z = 0;
				//pVertexArray[index3].Position.w = 1;
				pVertexArray[index3].Color = lowerColor;
				pVertexArray[index3].TexCoord.x = uvRight;
				pVertexArray[index3].TexCoord.y = uvBottom;

				// ボールド体の場合はもう少しオフセットしたほうがいいかも。
				// フォントによっては、強制的に半角幅分送るだけ、というのは問題あり。
				// 特にプロポーショナル フォントは英数字であっても文字幅が異なる。
				// モノスペースであっても、半角幅分とはかぎらない。
				offsetX += feed + 1;
			}
		}
		if (m_stringLength > 0)
		{
			return this->ReplaceVertexData(pDeviceContext, &m_vertexArray[0]);
		}
		else
		{
			return true;
		}
	}