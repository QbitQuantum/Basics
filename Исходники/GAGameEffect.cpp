void FGAGameEffectContainer::RemoveEffect(FGAGameEffectHandle& HandleIn)
{
	EGAEffectAggregation aggregatiopn = HandleIn.GetEffectRef().GameEffect->EffectAggregation;
	UObject* Instigator = HandleIn.GetContextRef().Instigator.Get();
	TSharedPtr<FGAGameEffect> effect = ActiveEffects.FindAndRemoveChecked(HandleIn);

	if (effect.IsValid())
	{
		switch (aggregatiopn)
		{
		case EGAEffectAggregation::AggregateByInstigator:
		{
			TMap<FGAGameEffectHandle, TSharedPtr<FGAGameEffect>>* effects = InstigatorEffects.Find(Instigator);
			TMap<UClass*, FGAGameEffectHandle>* EffectByClass = InstigatorEffectHandles.Find(Instigator);
			if (EffectByClass)
			{
				EffectByClass->Remove(HandleIn.GetEffectSpec()->StaticClass());
			}
			if (effects)
			{
				effects->FindAndRemoveChecked(HandleIn);
				if (effects->Num() == 0)
				{
					InstigatorEffects.Remove(Instigator);
				}
			}
			break;
		}
		case EGAEffectAggregation::AggregateByTarget:
		{
			TargetEffects.FindAndRemoveChecked(HandleIn);
			break;
		}
		}
		for (FGAGameEffectModifier& Modifier : effect->GameEffect->Modifiers)
		{
			if (Modifier.Attribute.IsValid())
			{
				FGAAttributeBase* Attribute = OwningComp->GetAttribute(Modifier.Attribute);
				if (Attribute)
				{
					Attribute->RemoveBonus(HandleIn);
				}
			}
		}
		UE_LOG(GameAttributesEffects, Log, TEXT("FGAGameEffectContainer:: Removing Effect"))
			effect.Reset();
	}
}