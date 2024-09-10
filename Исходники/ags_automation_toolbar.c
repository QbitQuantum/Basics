/**
 * ags_automation_toolbar_load_port:
 * @automation_toolbar: an #AgsAutomationToolbar
 * @control_name: the specifier as string
 *
 * Applies all port to appropriate #AgsMachine.
 *
 * Since: 0.4.3
 */
void
ags_automation_toolbar_apply_port(AgsAutomationToolbar *automation_toolbar,
				  gchar *control_name)
{
  AgsAutomationEditor *automation_editor;
  AgsMachine *machine;

  GtkTreeModel *model;
  GtkTreeIter iter;

  gchar **specifier, *current;
  guint length;
  gboolean is_active;
  
  automation_editor = gtk_widget_get_ancestor(automation_toolbar,
					      AGS_TYPE_AUTOMATION_EDITOR);
  machine = automation_editor->selected_machine;

  model = gtk_combo_box_get_model(automation_toolbar->port);

  /* create specifier array */
  specifier = NULL;
  length = 0;
  
  if(gtk_tree_model_get_iter_first(model,
				   &iter)){
    do{
      gtk_tree_model_get(model,
			 &iter,
			 0, &is_active,
			 -1);

      if(is_active){
	if(length == 0){
	  specifier = (gchar **) malloc(2 * sizeof(gchar *));
	}else{
	  specifier = (gchar **) realloc(specifier,
					 (length + 2) * sizeof(gchar *));
	}
      
	gtk_tree_model_get(model,
			   &iter,
			   1, &current,
			   -1);
	specifier[length] = current;

	length++;
      }
    }while(gtk_tree_model_iter_next(model,
				    &iter));
    specifier[length] = NULL;
  }

  if(machine->automation_port != NULL){
    free(machine->automation_port);
  }

  /* apply */
  machine->automation_port = specifier;
  
  if(g_strv_contains(specifier,
		     control_name)){
    AgsScaleArea *scale_area;
    AgsAutomationArea *automation_area;

    AgsAudio *audio;
    AgsAutomation *automation;

    GList *list;

    gboolean found_audio, found_output, found_input;
    
    audio = machine->audio;
    list = audio->automation;
    
    /* add port */
    found_audio = FALSE;
    found_output = FALSE;
    found_input = FALSE;
    
    while((list = ags_automation_find_specifier(list,
						control_name)) != NULL &&
	  (!found_audio || !found_output || !found_input)){
      if(AGS_AUTOMATION(list->data)->channel_type == G_TYPE_NONE &&
	 !found_audio){
	scale_area = ags_scale_area_new(automation_editor->audio_scale,
					control_name,
					AGS_AUTOMATION(list->data)->lower,
					AGS_AUTOMATION(list->data)->upper,
					AGS_AUTOMATION(list->data)->steps);
	ags_scale_add_area(automation_editor->audio_scale,
			   scale_area);
	gtk_widget_queue_draw(automation_editor->audio_scale);
	
	automation_area = ags_automation_area_new(automation_editor->audio_automation_edit->drawing_area,
						  audio,
						  G_TYPE_NONE,
						  control_name);
	ags_automation_edit_add_area(automation_editor->audio_automation_edit,
				     automation_area);
	gtk_widget_queue_draw(automation_editor->audio_automation_edit->drawing_area);

	found_audio = TRUE;
      }

      if(AGS_AUTOMATION(list->data)->channel_type == AGS_TYPE_OUTPUT &&
	 !found_output){
	scale_area = ags_scale_area_new(automation_editor->output_scale,
					control_name,
					AGS_AUTOMATION(list->data)->lower,
					AGS_AUTOMATION(list->data)->upper,
					AGS_AUTOMATION(list->data)->steps);
	ags_scale_add_area(automation_editor->output_scale,
			   scale_area);
	gtk_widget_queue_draw(automation_editor->output_scale);
	
	automation_area = ags_automation_area_new(automation_editor->output_automation_edit->drawing_area,
						  audio,
						  AGS_TYPE_OUTPUT,
						  control_name);
	ags_automation_edit_add_area(automation_editor->output_automation_edit,
				     automation_area);
	gtk_widget_queue_draw(automation_editor->output_automation_edit->drawing_area);
	
	found_output = TRUE;
      }

      if(AGS_AUTOMATION(list->data)->channel_type == AGS_TYPE_INPUT &&
	 !found_input){
	scale_area = ags_scale_area_new(automation_editor->input_scale,
					control_name,
					AGS_AUTOMATION(list->data)->lower,
					AGS_AUTOMATION(list->data)->upper,
					AGS_AUTOMATION(list->data)->steps);
	ags_scale_add_area(automation_editor->input_scale,
			   scale_area);
	gtk_widget_queue_draw(automation_editor->input_scale);
	
	automation_area = ags_automation_area_new(automation_editor->input_automation_edit->drawing_area,
						  audio,
						  AGS_TYPE_INPUT,
						  control_name);
	ags_automation_edit_add_area(automation_editor->input_automation_edit,
				     automation_area);
	gtk_widget_queue_draw(automation_editor->input_automation_edit->drawing_area);
	
	found_input = TRUE;
      }
      
      list = list->next;
    }
  }else{
    AgsAutomationEdit *automation_edit;
    AgsScale *scale;
    
    GList *scale_area;
    GList *automation_area;

    /* remove audio port */
    automation_edit = automation_editor->audio_automation_edit;
    scale = automation_editor->audio_scale;

    scale_area = ags_scale_area_find_specifier(scale->scale_area,
					       control_name);
    
    if(scale_area != NULL){
      automation_area = ags_automation_area_find_specifier(automation_edit->automation_area,
							   control_name);

      ags_scale_remove_area(scale,
			    scale_area->data);
      gtk_widget_queue_draw(scale);

      ags_automation_edit_remove_area(automation_edit,
				      automation_area->data);
      gtk_widget_queue_draw(automation_edit->drawing_area);
    }
    
    /* remove output port */
    automation_edit = automation_editor->output_automation_edit;
    scale = automation_editor->output_scale;
    
    scale_area = ags_scale_area_find_specifier(scale->scale_area,
					       control_name);

    if(scale_area != NULL){
      automation_area = ags_automation_area_find_specifier(automation_edit->automation_area,
							   control_name);

      ags_scale_remove_area(scale,
			    scale_area->data);
      gtk_widget_queue_draw(scale);

      ags_automation_edit_remove_area(automation_edit,
				      automation_area->data);
      gtk_widget_queue_draw(automation_edit->drawing_area);
    }

    /* remove input port */
    automation_edit = automation_editor->input_automation_edit;
    scale = automation_editor->input_scale;
    
    scale_area = ags_scale_area_find_specifier(scale->scale_area,
					       control_name);

    if(scale_area != NULL){
      automation_area = ags_automation_area_find_specifier(automation_edit->automation_area,
							   control_name);

      ags_scale_remove_area(scale,
			    scale_area->data);
      gtk_widget_queue_draw(scale);

      ags_automation_edit_remove_area(automation_edit,
				      automation_area->data);
      gtk_widget_queue_draw(automation_edit->drawing_area);
    }
  }
}