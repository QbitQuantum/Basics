void PsychicDominatorStateMachine::Update()
{
	// waiting. lurking in the shadows.
	if(this->Deferment > 0) {
		if(--this->Deferment) {
			return;
		}
	}

	SWTypeExt::ExtData *pData = SWTypeExt::ExtMap.Find(this->Super->Type);

	switch(PsyDom::Status) {
	case PsychicDominatorStatus::FirstAnim:
		{
			// here are the contents of PsyDom::Start().
			CellClass *pTarget = MapClass::Instance->GetCellAt(this->Coords);
			CoordStruct coords = pTarget->GetCoords();
			coords.Z += pData->Dominator_FirstAnimHeight;

			AnimClass* pAnim = nullptr;
			if(AnimTypeClass* pAnimType = pData->Dominator_FirstAnim.Get(RulesClass::Instance->DominatorFirstAnim)) {
				pAnim = GameCreate<AnimClass>(pAnimType, coords);
			}
			PsyDom::Anim = pAnim;
		
			auto sound = pData->SW_ActivationSound.Get(RulesClass::Instance->PsychicDominatorActivateSound);
			if(sound != -1) {
				VocClass::PlayAt(sound, coords, nullptr);
			}

			pData->PrintMessage(pData->Message_Activate, this->Super->Owner);
			
			PsyDom::Status = PsychicDominatorStatus::Fire;

			// most likely LightUpdateTimer
			ScenarioClass::Instance->AmbientTimer.Start(1);
			ScenarioClass::UpdateLighting();

			return;
		}
	case PsychicDominatorStatus::Fire:
		{
			// wait for some percentage of the first anim to be
			// played until we strike.
			AnimClass* pAnim = PsyDom::Anim;
			if(pAnim) {
				int currentFrame = pAnim->Animation.Value;
				short frameCount = pAnim->Type->GetImage()->Frames;
				int percentage = pData->Dominator_FireAtPercentage.Get(RulesClass::Instance->DominatorFireAtPercentage);
				if(frameCount * percentage / 100 > currentFrame) {
					return;
				}
			}

			PsyDom::Fire();

			PsyDom::Status = PsychicDominatorStatus::SecondAnim;
			return;
		}
	case PsychicDominatorStatus::SecondAnim:
		{
			// wait for the second animation to finish. (there may be up to
			// 10 frames still to be played.)
			AnimClass* pAnim = PsyDom::Anim;
			if(pAnim) {
				int currentFrame = pAnim->Animation.Value;
				short frameCount = pAnim->Type->GetImage()->Frames;

				if(frameCount - currentFrame > 10) {
					return;
				}
			}

			PsyDom::Status = PsychicDominatorStatus::Reset;
			return;
		}
	case PsychicDominatorStatus::Reset:
		{
			// wait for the last frame... WTF? 
			AnimClass* pAnim = PsyDom::Anim;
			if(pAnim) {
				int currentFrame = pAnim->Animation.Value;
				short frameCount = pAnim->Type->GetImage()->Frames;

				if(frameCount - currentFrame > 1) {
					return;
				}
			}

			PsyDom::Status = PsychicDominatorStatus::Over;

			PsyDom::Coords = CellStruct::Empty;
			PsyDom::Anim = nullptr;
			ScenarioClass::UpdateLighting();

			return;
		}
	case PsychicDominatorStatus::Over:
		{
			// wait for the light to go away.
			if(ScenarioClass::Instance->AmbientCurrent != ScenarioClass::Instance->AmbientTarget) {
				return;
			}

			// clean up
			SW_PsychicDominator::CurrentPsyDom = nullptr;
			PsyDom::Status = PsychicDominatorStatus::Inactive;
			ScenarioClass::UpdateLighting();
			this->Clock.TimeLeft = 0;
		}
	}
}