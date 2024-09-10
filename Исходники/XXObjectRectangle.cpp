XBOOL XXObjectRectangle::SysCallMethod(int id,XSWFCONTEXT*pCnt,XXVARLIST&list)
{
	switch(id)
	{
	case _SYSID(clone):
		 pCnt->pStack->Push(Clone());
		 return XTRUE;
	case _SYSID(contains):
		 contains(*pCnt,list);
		 return XTRUE;
	case _SYSID(containsPoint):
		 containsPoint(*pCnt,list);
		 return XTRUE;
	case _SYSID(containsRectangle):
		 containsRectangle(*pCnt,list);
		 return XTRUE;
	case _SYSID(equals):
		 equalsRect(*pCnt,list);
		 return XTRUE;
	case _SYSID(inflate):
		 inflate(*pCnt,list);
		 return XTRUE;
	case _SYSID(inflatePoint):
		 inflatePoint(*pCnt,list);
		 return XTRUE;
	case _SYSID(intersection):
		 intersection(*pCnt,list);
		 return XTRUE;
	case _SYSID(intersects):
		 intersects(*pCnt,list);return XTRUE;
	case _SYSID(isEmpty):
		 pCnt->pStack->PushBool((width==0&&height==0));
		 return XTRUE;
	case _SYSID(offset):
		 offsetRect(*pCnt,list);
		 return XTRUE;
	case _SYSID(offsetPoint):
		 offsetPoint(*pCnt,list);
		 return XTRUE;
	case _SYSID(setEmpty):
		 left=top=0;
		 width=height=0;
		 pCnt->pStack->PushConst(XOCT_UNDEFINE);
		 return XTRUE;
	case _SYSID(toString):
		{
			XXVar var;
			GetString(var);
			pCnt->pStack->Push(var);
		}return XTRUE;
	case _SYSID(union):
		unionRect(*pCnt,list);
		return XTRUE;
	}
	return XXObject::SysCallMethod(id,pCnt,list);
}