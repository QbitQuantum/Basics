/** <!--******************************************************************-->
 *
 * @fn COPYerror
 *
 * @brief Copies the node and its sons/attributes
 *
 * @param arg_node Error node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
COPYerror (node * arg_node, info * arg_info)
{
  node *result = TBmakeError (NULL, PH_initial, NULL);
  DBUG_ENTER ("COPYerror");
  LUTinsertIntoLutP (INFO_LUT (arg_info), arg_node, result);
  /* Copy attributes */
  ERROR_MESSAGE (result) = STRcpy (ERROR_MESSAGE (arg_node));
  ERROR_ANYPHASE (result) = ERROR_ANYPHASE (arg_node);
  /* Copy sons */
  ERROR_NEXT (result) = COPYTRAV (ERROR_NEXT (arg_node), arg_info);
  /* Return value */
  DBUG_RETURN (result);
}