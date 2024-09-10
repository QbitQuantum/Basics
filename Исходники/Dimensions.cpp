//----------------------------------------------------------------------------//
float UnifiedDim::getValue(const Window&, const Rectf& container) const
{
    switch (d_what)
    {
        case DT_LEFT_EDGE:
        case DT_RIGHT_EDGE:
        case DT_X_POSITION:
        case DT_X_OFFSET:
        case DT_WIDTH:
            return CoordConverter::asAbsolute(d_value, container.getWidth());
            break;

        case DT_TOP_EDGE:
        case DT_BOTTOM_EDGE:
        case DT_Y_POSITION:
        case DT_Y_OFFSET:
        case DT_HEIGHT:
            return CoordConverter::asAbsolute(d_value, container.getHeight());
            break;

        default:
            CEGUI_THROW(InvalidRequestException(
                "unknown or unsupported DimensionType encountered."));
            break;
    }
}