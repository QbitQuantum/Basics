// -----------------------------------------------------------------------------
// CSecModUIModel::LoadTokenLabelsL(CEikTextListBox& aListBox)
// -----------------------------------------------------------------------------
//
void CSecModUIModel::LoadTokenLabelsL(CEikTextListBox& aListBox)
    {
    LOG_ENTERFN("CSecModUIModel::LoadTokenLabelsL()");

    TInt keyStoreCount = iAOKeyStores.Count();

    if (0 == keyStoreCount)
        {
        LOG_WRITE_FORMAT("keyStoreCount == %i",keyStoreCount);
        LOG_LEAVEFN("CSecModUIModel::LoadTokenLabelsL()");
        //disable the scrollbar if no keystore
        aListBox.ScrollBarFrame()->SetScrollBarVisibilityL(
	    CEikScrollBarFrame::EOff,CEikScrollBarFrame::EOff);
        return;
        }
    TBuf<KItemLength> item;
    TBuf<KItemLength> label;

    CDesCArray* itemArray =
        STATIC_CAST(CDesCArray*, aListBox.Model()->ItemTextArray());
    for (TInt i = 0; i < keyStoreCount; i++)
        {
        if (iAOKeyStores[i]->Token().TokenType().Type().iUid 
            == KTokenTypeFileKeystore)
            {
            AppendResourceL(label, R_QTN_KEYSTORE_LIST_TEXT_PHONE_KEYSTORE);
            }
        else 
            {                
            label = iAOKeyStores[i]->Token().Label();
            }
        item += KTab;
        item += label;
        item += KTab;
        AppendLocationL(item, iAOKeyStores[i]->Token().TokenType().Type());
        item.SetLength(item.Length() - 1); // Remove \n from the end
        itemArray->AppendL(item);
        label.Zero();
        item.Zero();
        }

    LOG_LEAVEFN("CSecModUIModel::LoadTokenLabelsL()");
    }