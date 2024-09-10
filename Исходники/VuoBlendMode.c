/**
 * @ingroup VuoBlendMode
 * Same as @c %VuoBlendMode_getString()
 */
char * VuoBlendMode_getSummary(const VuoBlendMode value)
{
	char *valueAsString = "";

	switch (value)
	{
		case VuoBlendMode_Normal:
			valueAsString = "Normal — Alpha";
			break;
		case VuoBlendMode_Multiply:
			valueAsString = "Multiply — b•f";
			break;
		case VuoBlendMode_DarkerComponent:
			valueAsString = "Darker Component — min(b,f)";
			break;
		case VuoBlendMode_DarkerColor:
			valueAsString = "Darker Color — min(b,f)";
			break;
		case VuoBlendMode_LinearBurn:
			valueAsString = "Linear Burn — b+f-1";
			break;
		case VuoBlendMode_ColorBurn:
			valueAsString = "Color Burn — 1-(1-b)/f";
			break;
		case VuoBlendMode_Screen:
			valueAsString = "Screen — 1-(1-b)•(1-f)";
			break;
		case VuoBlendMode_LighterComponent:
			valueAsString = "Lighter Component — max(b,f)";
			break;
		case VuoBlendMode_LighterColor:
			valueAsString = "Lighter Color — max(b,f)";
			break;
		case VuoBlendMode_LinearDodge:
			valueAsString = "Linear Dodge (Add) — b+f";
			break;
		case VuoBlendMode_ColorDodge:
			valueAsString = "Color Dodge — b/(1-f)";
			break;
		case VuoBlendMode_Overlay:
			valueAsString = "Overlay";
			break;
		case VuoBlendMode_SoftLight:
			valueAsString = "Soft Light";
			break;
		case VuoBlendMode_HardLight:
			valueAsString = "Hard Light";
			break;
		case VuoBlendMode_VividLight:
			valueAsString = "Vivid Light";
			break;
		case VuoBlendMode_LinearLight:
			valueAsString = "Linear Light";
			break;
		case VuoBlendMode_PinLight:
			valueAsString = "Pin Light";
			break;
		case VuoBlendMode_HardMix:
			valueAsString = "Hard Mix";
			break;
		case VuoBlendMode_Difference:
			valueAsString = "Difference — abs(b-f)";
			break;
		case VuoBlendMode_Exclusion:
			valueAsString = "Exclusion — b+f-2•b•f";
			break;
		case VuoBlendMode_Subtract:
			valueAsString = "Subtract — b-f";
			break;
		case VuoBlendMode_Divide:
			valueAsString = "Divide — b/f";
			break;
		case VuoBlendMode_Hue:
			valueAsString = "Hue";
			break;
		case VuoBlendMode_Saturation:
			valueAsString = "Saturation";
			break;
		case VuoBlendMode_Color:
			valueAsString = "Color";
			break;
		case VuoBlendMode_Luminosity:
			valueAsString = "Luminosity";
			break;
	}
	return strdup(valueAsString);
}