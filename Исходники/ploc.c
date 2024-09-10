node *PPLOCat( node *arg_node, info *arg_info)
{
  DBUG_ENTER("PPLOCat");

  int loc;
  node *temp;
  node *top = NULL;
  node *ref;

  if(INFO_TOP(arg_info) != NULL) {
    top = INFO_TOP(arg_info);

    ref = TBmakeNetrefs(top, NULL);
    NODE_ERRCODE(ref) = STRcpy(NODE_ERRCODE(arg_node));

    NETREFS_LOCATION(ref) = AT_LOCATION(arg_node);

    temp = TBmakeNetbody(NULL, ref);

    NODE_ERRCODE(temp) = STRcpy(NODE_ERRCODE(arg_node));

    temp = TBmakeNetdef(STRcpy(NETDEF_NAME(top)),
           NULL,
           FALSE, FALSE, NULL,
           temp,
           NULL);

    NODE_ERRCODE(temp) = STRcpy(NODE_ERRCODE(arg_node));

    top = temp;

    INFO_TOP(arg_info) = NULL;
  }

  loc = INFO_LOC(arg_info);

  INFO_LOC(arg_info) = AT_LOCATION(arg_node);

  AT_LEFT(arg_node) = TRAVdo(AT_LEFT(arg_node), arg_info);

  INFO_LOC(arg_info) = loc;

  temp = AT_LEFT(arg_node);

  AT_LEFT(arg_node) = NULL;

  FREEdoFreeTree(arg_node);

  arg_node = temp;

  INFO_TOP(arg_info) = top;

  DBUG_RETURN(arg_node);
}