			static void qsort_list(s_object_field_definition (&list)[_SizeOfArray])
			{
				qsort_s(list, _SizeOfArray, sizeof(s_object_field_definition), qsort_proc, NULL);
			}