/*
 * @implemented
 */
ULONG APIENTRY
CLIPOBJ_cEnumStart(
    IN CLIPOBJ* ClipObj,
    IN BOOL ShouldDoAll,
    IN ULONG ClipType,
    IN ULONG BuildOrder,
    IN ULONG MaxRects)
{
    CLIPGDI *ClipGDI = ObjToGDI(ClipObj, CLIP);
    SORTCOMP CompareFunc;

    ClipGDI->EnumPos = 0;
    ClipGDI->EnumMax = (MaxRects > 0) ? MaxRects : ClipGDI->EnumRects.c;

    if (CD_ANY != BuildOrder && ClipGDI->EnumOrder != BuildOrder)
    {
        switch (BuildOrder)
        {
            case CD_RIGHTDOWN:
                CompareFunc = (SORTCOMP) CompareRightDown;
                break;

            case CD_RIGHTUP:
                CompareFunc = (SORTCOMP) CompareRightUp;
                break;

            case CD_LEFTDOWN:
                CompareFunc = (SORTCOMP) CompareLeftDown;
                break;

            case CD_LEFTUP:
                CompareFunc = (SORTCOMP) CompareLeftUp;
                break;

            default:
                DPRINT1("Invalid BuildOrder %d\n", BuildOrder);
                BuildOrder = ClipGDI->EnumOrder;
                CompareFunc = NULL;
                break;
        }

        if (NULL != CompareFunc)
        {
            EngSort((PBYTE) ClipGDI->EnumRects.arcl, sizeof(RECTL), ClipGDI->EnumRects.c, CompareFunc);
        }

        ClipGDI->EnumOrder = BuildOrder;
    }

    /* Return the number of rectangles enumerated */
    if ((MaxRects > 0) && (ClipGDI->EnumRects.c > MaxRects))
    {
        return 0xFFFFFFFF;
    }

    return ClipGDI->EnumRects.c;
}