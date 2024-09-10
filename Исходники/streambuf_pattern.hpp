			virtual void puts(const _Elem* str,streamsize size){
				for(std::streamsize i=0;i<size;i++)putc(str[i]);
			}