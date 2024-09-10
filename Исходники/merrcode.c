/** <!--******************************************************************-->
 *
 * @fn MERRCODEboxtypes
 *
 * @brief Sets error code for the node and its sons
 *
 * @param arg_node BoxTypes node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *MERRCODEboxtypes( node *arg_node, info *arg_info ){
  DBUG_ENTER("MERRCODEboxtypes");

  /* Set error code */
  NODE_ERRCODE(arg_node)= STRcpy(INFO_ERRCODE(arg_info));

  /* Visit sons */
  if(BOXTYPES_ENTRIES( arg_node)!= NULL){
    BOXTYPES_ENTRIES( arg_node)= TRAVdo( BOXTYPES_ENTRIES( arg_node), arg_info);
  }
  if(BOXTYPES_NEXT( arg_node)!= NULL){
    BOXTYPES_NEXT( arg_node)= TRAVdo( BOXTYPES_NEXT( arg_node), arg_info);
  }

  /* Return value */
  DBUG_RETURN(arg_node);
}