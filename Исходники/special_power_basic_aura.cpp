//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerBasicAura::apply()
{
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerBasicAura::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable auras
	actor->setForbidAuraUseDates(CTickEventHandler::getGameCycle(), CTickEventHandler::getGameCycle() + _DisablePowerTime);

	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();

	// create effect and apply it on target
	CAuraRootEffect *effect = new CAuraRootEffect(_ActorRowId, endDate, _RootEffectFamily, _CreatedEffectFamily, _PowerType, _ParamValue, _AffectGuild);
	if (!effect)
	{		
		nlwarning("<CSpecialPowerBasicAura::apply> Failed to allocate new CShieldingEffect");
		return;
	}
	effect->setRadius(_AuraRadius);
	effect->setTargetDisableTime(_TargetsDisableAuraTime);
	actor->addSabrinaEffect(effect);

	// add aura FX on the actor
	CMirrorPropValue<TYPE_VISUAL_FX> visualFx( TheDataset, _ActorRowId, DSPropertyVISUAL_FX );
	CVisualFX fx;
	fx.unpack(visualFx.getValue());
	
	switch(_PowerType)
	{
	case POWERS::LifeAura:
		fx.Aura = MAGICFX::AuraHp;
		break;
	case POWERS::StaminaAura:
		fx.Aura = MAGICFX::AuraSta;
		break;
	case POWERS::SapAura:
		fx.Aura = MAGICFX::AuraSap;
		break;
	case POWERS::MeleeProtection:
		fx.Aura = MAGICFX::ProtectionMelee;
		break;
	case POWERS::Umbrella:
		fx.Aura = MAGICFX::ProtectionRange;
		break;
	case POWERS::AntiMagicShield:
		fx.Aura = MAGICFX::ProtectionMagic;
		break;
	case POWERS::WarCry:
		fx.Aura = MAGICFX::WarCry;
		break;
	case POWERS::FireWall:
		fx.Aura = MAGICFX::FireWall;
		break;
	case POWERS::ThornWall:
		fx.Aura = MAGICFX::ThornWall;
		break;
	case POWERS::WaterWall:
		fx.Aura = MAGICFX::WaterWall;
		break;
	case POWERS::LightningWall:
		fx.Aura = MAGICFX::LightningWall;
		break;
	default:
		return;
	};
	
	sint64 prop;
	fx.pack(prop);
	visualFx = (sint16)prop;
} // apply //