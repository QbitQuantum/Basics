wxString DescriptorFrame::edit_partit(wxString partit)
{
	
	int erase_s=partit.Replace("<partitioning>","");
	int erase_e=partit.Replace("</partitioning>","");


	int erase_start=partit.find("<hostcollocation>");
		while (erase_start>0)
		{
			erase_start=partit.find("<hostcollocation>");
			int erase_end=partit.find("</hostcollocation>")+18;
			if (erase_end>18) 
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}

		} 

		

	erase_start=0;
	erase_start=partit.find("<processcollocation");
		while (erase_start>0)
		{
			erase_start=partit.find("<processcollocation");
			int erase_end=partit.find("</processcollocation>")+21;

			if (erase_end>21)
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}
			
		}	

		
	erase_start=0;
	erase_start=partit.find("<homeplacement");
		while (erase_start>0)
		{
			erase_start=1;
			erase_start=partit.find("<homeplacement");
			int erase_end=partit.find("</homeplacement>")+16;
			if (erase_end>16)
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}
						
		}
		
	
	return partit;

}