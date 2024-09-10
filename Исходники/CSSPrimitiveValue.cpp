CSSPrimitiveValue::CSSPrimitiveValue(const Length& length, float zoom)
    : CSSValue(PrimitiveClass)
{
    switch (length.type()) {
    case Auto:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueAuto;
        break;
    case Intrinsic:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueIntrinsic;
        break;
    case MinIntrinsic:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueMinIntrinsic;
        break;
    case MinContent:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueMinContent;
        break;
    case MaxContent:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueMaxContent;
        break;
    case FillAvailable:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueWebkitFillAvailable;
        break;
    case FitContent:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueWebkitFitContent;
        break;
    case ExtendToZoom:
        init(UnitType::ValueID);
        m_value.valueID = CSSValueInternalExtendToZoom;
        break;
    case Percent:
        init(UnitType::Percentage);
        ASSERT(std::isfinite(length.percent()));
        m_value.num = length.percent();
        break;
    case Fixed:
        init(UnitType::Pixels);
        m_value.num = length.value() / zoom;
        break;
    case Calculated: {
        const CalculationValue& calc = length.calculationValue();
        if (calc.pixels() && calc.percent()) {
            init(CSSCalcValue::create(
                CSSCalcValue::createExpressionNode(calc.pixels() / zoom, calc.percent()),
                calc.isNonNegative() ? ValueRangeNonNegative : ValueRangeAll));
            break;
        }
        if (calc.percent()) {
            init(UnitType::Percentage);
            m_value.num = calc.percent();
        } else {
            init(UnitType::Pixels);
            m_value.num = calc.pixels() / zoom;
        }
        if (m_value.num < 0 && calc.isNonNegative())
            m_value.num = 0;
        break;
    }
    case DeviceWidth:
    case DeviceHeight:
    case MaxSizeNone:
        ASSERT_NOT_REACHED();
        break;
    }
}