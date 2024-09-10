inline bool MtgCard::operator==(const MtgCard& rhs) {
    return GetLayout() == rhs.GetLayout() &&
            GetManacost() == rhs.GetManacost() &&
            GetCmc() == rhs.GetCmc() &&
            CompareStringList(GetColors(), rhs.GetColors()) &&
            type == rhs.type &&
            CompareStringList(GetSupertypes(), rhs.GetSupertypes()) &&
            CompareStringList(GetTypes(), rhs.GetTypes()) &&
            CompareStringList(GetSubtypes(), rhs.GetSubtypes()) &&
            GetRarity() == rhs.GetRarity() &&
            text == rhs.GetText() &&
            GetFlavor() == rhs.GetFlavor() &&
            GetArtist() == rhs.GetArtist() &&
            GetNumber() == rhs.GetNumber() &&
            GetPower() == rhs.GetPower() &&
            GetToughness() == rhs.GetToughness() &&
            GetLoyalty() == rhs.GetLoyalty() &&
            GetMultiverseid() == rhs.GetMultiverseid() &&
            CompareIntList(GetVariations(), rhs.GetVariations()) &&
            GetImageName() == rhs.GetImageName() &&
            GetWatermark() == rhs.GetWatermark() &&
            GetBorder() == rhs.GetBorder() &&
            IsTimeshifted() == rhs.IsTimeshifted() &&
            GetHand() == rhs.GetHand() &&
            GetLife() == rhs.GetLife() &&
            IsReserved() == rhs.IsReserved() &&
            GetReleasedate() == rhs.GetReleasedate() &&
            IsStarter() == rhs.IsStarter() &&
            CompareStringPairList(GetRulings(), rhs.GetRulings()) &&
            CompareStringPairList(GetForeignNames(), rhs.GetForeignNames()) &&
            GetOriginalText() == rhs.GetOriginalText() &&
            GetOriginalType() == rhs.GetOriginalType() &&
            CompareStringPairList(GetLegalities(), rhs.GetLegalities()) &&
            GetEdition() == rhs.GetEdition();
}