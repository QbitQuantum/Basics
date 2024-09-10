/// Function name  : compareAVLTreeNodeWithValues
// Description     : Compares a node in an AVLTree against a specified set of values
///                           The number of values must match the number of tree sort keys
// 
// CONST AVL_TREE*  pTree     : [in] AVLTree containing the nodes
// CONST LPARAM     pNodeData : [in] Data of the node to compare
// ...              ...       : [in] Value to compare node against
// 
// Return Value   : CR_LESSER  : The value is less than the node
//                  CR_EQUAL   : The value is equal to the node
//                  CR_GREATER : The value is more than the node
// 
COMPARISON_RESULT  compareAVLTreeNodeWithValues(CONST AVL_TREE*  pTree, CONST LPARAM  pNodeData, LPARAM  xValue1, LPARAM  xValue2, LPARAM  xValue3)
{
   COMPARISON_RESULT    eResult;         // Comparison result
   CONST AVL_TREE_KEY*  pCurrentKey;     // Convenience pointer
   LPARAM               xNodeProperty,   // Extracted property of the input node
                        xSearchValues[3] = {xValue1, xValue2, xValue3};    // Input values
   // Prepare
   eResult = CR_EQUAL;

   /// Iterate through sort keys
   for (UINT  iKey = 0; (eResult == CR_EQUAL) AND (iKey < pTree->iKeyCount); iKey++)
   {
      // Prepare
      pCurrentKey = pTree->pSortKeys[iKey];

      // Extract appropriate property value from node
      xNodeProperty = extractObjectProperty(pTree, pNodeData, pCurrentKey->eSorting);

      /// [COMPARISON] Compare property against current search value
      switch (pCurrentKey->eType)
      {
      case AP_STRING_CASE: eResult = (COMPARISON_RESULT)StrCmp((TCHAR*)xNodeProperty, (TCHAR*)xSearchValues[iKey]);        break;
      case AP_STRING:      eResult = (COMPARISON_RESULT)StrCmpI((TCHAR*)xNodeProperty, (TCHAR*)xSearchValues[iKey]);        break;
      case AP_INTEGER:     eResult = (COMPARISON_RESULT)utilCompareIntegers((INT)xSearchValues[iKey], (INT)xNodeProperty);  break;
      }

      /// [DIRECTION] Flip the result for descending ordering
      if (pCurrentKey->eDirection == AO_DESCENDING)
         eResult = (COMPARISON_RESULT)(eResult * -1);
   }

   // Return result
   return eResult;
}