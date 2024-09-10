int RegisterField(char *name,int Length,int Pos,FieldType *&Field)
{
//   char name[256];in>>name;
   if (Stricmp(name,"String")==0) Field=new FieldString;
   else
	   if (Stricmp(name,"Real")==0) Field=new FieldReal;

	else
	   if (Stricmp(name,"Long")==0) Field=new FieldLong;

	   else
		   if (Stricmp(name,"Int")==0) Field=new FieldInt;
		   else
    { cout<<" RegisterField; There is no such function \n"<<name<<"\n";return 0; }
//   Func->ReadIni(in);
	Field->Pos=Pos;Field->Length=Length;
	return 1;
  };