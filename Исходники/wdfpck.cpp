void update_datafile(const char *dataname,const char *lstname)
{
	int old_number,new_number;
	std::vector<FILE_LST> old_list(c_MaxFile);
	old_number=read_lst(dataname,old_list);
	if (old_number<0) {
		printf("[%s] is Bad\n",dataname);
		return;
	}
	FILE *f;
	FileList list;
	FileHeader header;
	int i;
	new_number=list.ReadList(lstname);
	f=fopen(dataname,"rb+");
	if (f==0) {
		printf("[%s] can't update",dataname);
		return;
	}
	list.ReadHeader(f,&header);
	header.number=new_number;
	int s;
	for (s=i=0;i<old_number;i++) {
		if (list.FindFile(old_list[i].uid)==-1) {
			printf("A file[%x] (%d bytes) is deleted\n",old_list[i].uid,old_list[i].size);
			delete_file(f,old_number,old_list,i);
			++s;
		}
	}
	if (s>0) {
		printf("%d files deleted\n",s);
	}
	for (i=0;i<old_number;i++) {
		int n;
		if (old_list[i].uid==0) continue;
		n=list.FindFile(old_list[i].uid);
		assert(n>=0);
		int space=old_list[i].size+old_list[i].space;
		int size=file_size(list.GetName(n));
		if (size>space) {
			delete_file(f,old_number,old_list,i);
			printf("[%s] deleted\n",list.GetName(n));
		}
		else if (size==old_list[i].size) {
			if (list.NeedUpdate(f,n,old_list,i)) {
				list.UpdateFile(f,n,old_list,i);
			}
		}
		else if (size<=space) {
			list.UpdateFile(f,n,old_list,i);
		}
	}
// 寻找文件尾
	for (i=0;i<old_number;i++) {
		if (old_list[i].uid==0) 
			continue;
		if (old_list[i].offset+old_list[i].size+old_list[i].space==header.offset) 
			break;
	}
	if (i<old_number) {
		header.offset=old_list[i].offset+old_list[i].size;
		old_list[i].space=0;
		list.ClearTail(old_list[i].uid);
	}
	fseek(f,header.offset,SEEK_SET);
	for (i=0;i<new_number;i++) {
		if (list.WriteFile(f,i,true)) 
			printf("Added\n");	// 添加文件(见缝插针)
	}
	header.offset=ftell(f);
	list.WriteList(f);
	write_header(f,&header);
	fclose(f);
}