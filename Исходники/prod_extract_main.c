/**
	LB_notification callback - updates the status of each client
	@param lb_fd(in) - FD that event occcurred on
	@param msg_id(in) - message id that has changed
	@param msg_len(in) - message length
	@param user_data - user data, should be NULL

 */
void on_lb_change(int lb_fd, LB_id_t msg_id, int msg_len, void* user_data)
{

	int retval;
	Prod_header* product;
	static char* file_name = NULL;
	char text[100];
	struct tm* time;
	float elevation;
	int i;
	int rda_elev_indx;
	prod_count++;
        retval = LB_read(lb_fd, (void*)&product, LB_ALLOC_BUF, msg_id);
        if (retval >= 0)
	{
		LE_send_msg(GL_INFO, "Generated product id %d, msg id = %d\n", product->g.prod_id, msg_id);
		LE_send_msg(GL_INFO, "Product code = %d\n", ORPGPAT_get_code(product->g.prod_id));
		LE_send_msg(GL_INFO, "Prod desc = %s\n", ORPGPAT_get_description(product->g.prod_id, STRIP_MNEMONIC));
		LE_send_msg(GL_INFO, "Prod count = %d\n", prod_count);

                if (!select_product(ORPGPAT_get_code(product->g.prod_id)))
                {
                   LE_send_msg(GL_INFO, "Product code %d not selected for extraction", ORPGPAT_get_code(product->g.prod_id));
                   return;
                }
                else
                   LE_send_msg(GL_INFO, "Product code %d is selected for extraction", ORPGPAT_get_code(product->g.prod_id));

		file_name = STR_copy(file_name, ORPGPAT_get_description(product->g.prod_id, STRIP_MNEMONIC));
		for (i = 0; (i < strlen(file_name)); i++)
		{
		    if ((isspace((int)file_name[i])) || (file_name[i] == ':')
			|| (file_name[i] == '/'))
			file_name[i] = '_';
		    else if (file_name[i] == '.')
			file_name[i] = '.';
		    else if (!isalnum((int)file_name[i]))
		    {
		     	file_name[i] = '\0';
		        break;
		    }
		}

                rda_elev_indx = ORPGVST_get_rda_index(product->g.elev_ind);
		elevation = ((float)ORPGVST_get_elevation(rda_elev_indx)) / 10.0;
		LE_send_msg(GL_INFO, "Elev index = %d, rda elev indx = %d, elevation = %f", rda_elev_indx, product->g.elev_ind, elevation); 
		if (ORPGPAT_get_type(product->g.prod_id) == 0)
		    elevation = 0.0;
		sprintf(text, "_%2.1f", elevation);
		file_name = STR_cat(file_name, text);

		time = gmtime((const time_t*)&product->elev_t);
		sprintf(text, "_%4.4d%2.2d%2.2d_%2.2d%2.2d%2.2d",
		   time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
		   time->tm_hour, time->tm_min, time->tm_sec);

		file_name = STR_cat(file_name, text);

		LE_send_msg(GL_INFO, "File_name=%s\n", file_name);
		LE_send_msg(GL_INFO, "Size of msg=%d, size of product=%d\n", retval, product->g.len);

		if (product->g.len > 0)
		{
		   LE_send_msg(GL_INFO, "Writing %s format\n", orpg_format?"ORPG":"ICD");
		   if (orpg_format)
		      generate_output_file(file_name, ((char*)product), product->g.len);
		   else
		      generate_output_file(file_name, ((char*)product) + sizeof(Prod_header), product->g.len - sizeof(Prod_header));

		   if (index_name != NULL)
		      generate_xml_string(product, file_name);
		}
		else
		   LE_send_msg(GL_INFO, "Skip writing file %s because size is %d\n", file_name, product->g.len);

		free(product);
	}
	else
	   LE_send_msg(GL_INFO, "Read error %d on msg id %d\n", retval, msg_id);
}