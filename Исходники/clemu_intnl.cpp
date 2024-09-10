int
clemuGPU :: initDevice(void)
{
int ret = CL_EMU_SUCCESS;
   if ( !IsInit())
   {


 char  *env_root;
 size_t var_len;
 char root_location[512];
 char propert_file_location[512];
 FILE * property_file;



      _dupenv_s(&env_root,&var_len, "CLEMU_ROOT");
 
	  assert(var_len > 0);
	  if ( !var_len )
	  {
        return(CL_EMU_FAILURE);
	  }
	  strcpy_s(root_location, 512,env_root);
      if ( root_location[var_len-1] != '\\' )
	  {
         root_location[var_len-1] = '\\';
         root_location[var_len] = 0;
	  }
    
      sprintf_s(propert_file_location,512,"%s%s\\%s.txt", root_location, DEFAULTE_PROPERTY_FOLDER, DEFAULT_EMULATOR_PROPERTIES_NM);
	  property_file = fopen( propert_file_location,"rt");
	  if ( property_file )
	  {
char in_buffer[512];
char data_buffer[512];
char format_buffer[512];
int class_len = strlen("class=");
int found_class, found_device;

          fgets( in_buffer, 512, property_file);
          sscanf(in_buffer, "emu_class=%s\n",  data_buffer);
		  SetDevClass( (const char * )data_buffer);

          fgets( in_buffer, 512, property_file);
          sscanf(in_buffer, "emu_name=%s\n",  data_buffer);
		  SetDevNm( (const char * )data_buffer);

          found_class = 0;
		  while(fgets( in_buffer, 512, property_file))
		  {
             sscanf(in_buffer, "class=%s\n",  data_buffer);
			 if  (!strcmp(data_buffer, m_class))
			 {
                    found_class = 1;
				    break;
			 }
		  }

		  if ( found_class )
		  {
               found_device = 0;
		       while(fgets( in_buffer, 512, property_file))
		       {
                    sscanf(in_buffer, "name=%s\n",  data_buffer);
			        if  (!strcmp(data_buffer, m_name))
			        {
                         found_device = 1;
				         break;
			        }
		       }
			   if ( found_device )
			   {
		    int propery;
/*
   m_nbr_groupsperSIMD = 2;
   m_nbr_SE = 1;
   m_nbr_SIMD = 1;
   m_wavefront_size = 64;
   m_local_mem_sz = (1 << 15);
*/

				   for(int p = 0; emulator_device_properties_nm[p]; p++)
				   {
				      sprintf_s(format_buffer,512,"%s.%s=%%d\n", m_name,emulator_device_properties_nm[p]);
                      fscanf(property_file, format_buffer,  &propery);
                      if ( !strcmp(emulator_device_properties_nm[p], "se" ) )
					  {
                          m_nbr_SE = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "SIMD" ) )
					  {
						  m_nbr_SIMD = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "width" ) )
					  {
						  m_wavefront_size = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "local_memory" ) )
					  {
						  m_local_mem_sz = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "groups_per_SIMD" ) )
					  {
						  m_nbr_groupsperSIMD = propery;
					  }

				   }
				   

// ALIGNED??
                    m_localMem = new __int64*[GetNbrSIMD()];
	                assert(m_localMem);
	                for(int i = 0; i < GetNbrSIMD(); i++)
	                {
                        m_localMem[i] = (__int64*)new __int64[GetTotalLclSz()];
	                    assert(m_localMem[i]);
	                }
	                m_init = 1;
			   }
		  }
		fclose(property_file);
	  }
   }
   return(ret);
}