void CEmoticon::OnRender()
{
	if(!m_Active)
	{
		if(m_WasActive)
		{
            if (m_SelectedEmote != -1)
                Emote(m_SelectedEmote);
            else if (Client()->IsServerType("ddrace") && m_SelectedEyes != -1)
                Eyes(m_SelectedEyes);
        }
		m_WasActive = false;
		return;
	}

	if(m_pClient->m_Snap.m_SpecInfo.m_Active)
	{
		m_Active = false;
		m_WasActive = false;
		return;
	}

	m_WasActive = true;

	if (length(m_SelectorMouse) > 170.0f)
		m_SelectorMouse = normalize(m_SelectorMouse) * 170.0f;

	float SelectedAngle = GetAngle(m_SelectorMouse) + 2*pi/24;
	if (SelectedAngle < 0)
		SelectedAngle += 2*pi;

    float mouselen = length(m_SelectorMouse);
	if (mouselen > 110.0f)
	{
        m_SelectedEyes = -1;
		m_SelectedEmote = (int)(SelectedAngle / (2*pi) * NUM_EMOTICONS);
    } else if (Client()->IsServerType("ddrace") && mouselen > 50.0f && mouselen < 110.0f) // H-Client
    {
        m_SelectedEmote = -1;
		m_SelectedEyes = (int)(SelectedAngle / (2*pi) * NUM_EMOTES);
    } else
    {
        m_SelectedEyes = -1;
        m_SelectedEmote = -1;
    }

	CUIRect Screen = *UI()->Screen();

	Graphics()->MapScreen(Screen.x, Screen.y, Screen.w, Screen.h);

	Graphics()->BlendNormal();

	Graphics()->TextureSet(-1);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(0,0,0,0.3f);
	DrawCircle(Screen.w/2, Screen.h/2, 190.0f, 64);
	Graphics()->QuadsEnd();

    // H-Client
    if (Client()->IsServerType("ddrace"))
    {
        Graphics()->TextureSet(-1);
        Graphics()->QuadsBegin();
        Graphics()->SetColor(60,60,60,0.3f);
        DrawCircle(Screen.w/2, Screen.h/2, 110.0f, 64);
        Graphics()->QuadsEnd();
	}
	//

	Graphics()->TextureSet(g_pData->m_aImages[IMAGE_EMOTICONS].m_Id);
	Graphics()->QuadsBegin();

	for (int i = 0; i < NUM_EMOTICONS; i++)
	{
		float Angle = 2*pi*i/NUM_EMOTICONS;
		if (Angle > pi)
			Angle -= 2*pi;

		bool Selected = m_SelectedEmote == i;

		float Size = Selected ? 80.0f : 50.0f;

		float NudgeX = 150.0f * cosf(Angle);
		float NudgeY = 150.0f * sinf(Angle);
		RenderTools()->SelectSprite(SPRITE_OOP + i);
		IGraphics::CQuadItem QuadItem(Screen.w/2 + NudgeX, Screen.h/2 + NudgeY, Size, Size);
		Graphics()->QuadsDraw(&QuadItem, 1);
	}
    Graphics()->QuadsEnd();

    if (Client()->IsServerType("ddrace"))
    {
        for (int i = 0; i < NUM_EMOTES; i++)
        {
            float Angle = 2*pi*i/NUM_EMOTES;
            if (Angle > pi)
                Angle -= 2*pi;

            bool Selected = m_SelectedEyes == i;

            float Size = Selected ? 80.0f : 50.0f;

            float NudgeX = 80.0f * cosf(Angle);
            float NudgeY = 80.0f * sinf(Angle);

            CTeeRenderInfo teeRenderInfo = m_pClient->m_aClients[m_pClient->m_Snap.m_LocalClientID].m_RenderInfo;
            teeRenderInfo.m_Size = Size;

            Graphics()->TextureSet(teeRenderInfo.m_Texture);
            Graphics()->QuadsBegin();
            Graphics()->SetColor(teeRenderInfo.m_ColorBody.r, teeRenderInfo.m_ColorBody.g, teeRenderInfo.m_ColorBody.b, teeRenderInfo.m_ColorBody.a);

            switch (i)
            {
                case EMOTE_PAIN:
                    RenderTools()->SelectSprite(SPRITE_TEE_EYE_PAIN, 0, 0, 0);
                    break;
                case EMOTE_HAPPY:
                    RenderTools()->SelectSprite(SPRITE_TEE_EYE_HAPPY, 0, 0, 0);
                    break;
                case EMOTE_SURPRISE:
                    RenderTools()->SelectSprite(SPRITE_TEE_EYE_SURPRISE, 0, 0, 0);
                    break;
                case EMOTE_ANGRY:
                    RenderTools()->SelectSprite(SPRITE_TEE_EYE_ANGRY, 0, 0, 0);
                    break;
                default:
                    RenderTools()->SelectSprite(SPRITE_TEE_EYE_NORMAL, 0, 0, 0);
                    break;
            }

            vec2 Direction = vec2(-1,0);
            float BaseSize = teeRenderInfo.m_Size;
            float EyeScale = BaseSize*0.40f;
            float h = i == EMOTE_BLINK ? BaseSize*0.15f : EyeScale;
            float EyeSeparation = (0.075f - 0.010f*absolute(Direction.x))*BaseSize;
            vec2 Offset = vec2(Direction.x*0.125f, -0.05f+Direction.y*0.10f)*BaseSize;
            vec2 BodyPos = vec2(Screen.w/2 + NudgeX, Screen.h/2 + NudgeY);
            IGraphics::CQuadItem Array[2] = {
                IGraphics::CQuadItem(BodyPos.x-EyeSeparation+Offset.x, BodyPos.y+Offset.y, EyeScale, h),
                IGraphics::CQuadItem(BodyPos.x+EyeSeparation+Offset.x, BodyPos.y+Offset.y, -EyeScale, h)};
            Graphics()->QuadsDraw(Array, 2);

            Graphics()->QuadsEnd();
        }
	}

	//Graphics()->QuadsEnd();

	Graphics()->TextureSet(g_pData->m_aImages[IMAGE_CURSOR].m_Id);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(1,1,1,1);
	IGraphics::CQuadItem QuadItem(m_SelectorMouse.x+Screen.w/2,m_SelectorMouse.y+Screen.h/2,24,24);
	Graphics()->QuadsDrawTL(&QuadItem, 1);
	Graphics()->QuadsEnd();
}