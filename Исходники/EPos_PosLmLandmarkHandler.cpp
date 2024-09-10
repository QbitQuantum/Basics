// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void PosLmLandmarkHandler::RemoveNonExistingCategoriesL(
    CPosLmLocalDbAccess& aDbAccess,
    RArray<TPosLmItemId>& aCategoryIdArray)
    {
    RArray<TPosLmItemId> categoriesInDatabase;
    CleanupClosePushL(categoriesInDatabase);

    PosLmCategoryHandler::GetAllCategoryIdsL(aDbAccess,
        CPosLmCategoryManager::ECategorySortOrderNone, categoriesInDatabase);

    if (categoriesInDatabase.Count() == 0)
        {
        aCategoryIdArray.Reset();
        }

    for (TInt i = 0; i < aCategoryIdArray.Count();)
        {
        if (categoriesInDatabase.Find(aCategoryIdArray[i]) == KErrNotFound)
            {
            aCategoryIdArray.Remove(i);
            }
        else
            {
            i++;
            }
        }

    CleanupStack::PopAndDestroy(&categoriesInDatabase);
    }