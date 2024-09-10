void
nsTextBoxFrame::GetTextSize(nsPresContext* aPresContext, nsIRenderingContext& aRenderingContext,
                                const nsString& aString, nsSize& aSize, nscoord& aAscent)
{
    nsCOMPtr<nsIFontMetrics> fontMet;
    nsLayoutUtils::GetFontMetricsForFrame(this, getter_AddRefs(fontMet));
    fontMet->GetHeight(aSize.height);
    aRenderingContext.SetFont(fontMet);
    aSize.width =
      nsLayoutUtils::GetStringWidth(this, &aRenderingContext, aString.get(), aString.Length());
    fontMet->GetMaxAscent(aAscent);
}