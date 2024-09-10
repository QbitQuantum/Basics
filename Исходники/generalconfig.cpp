GeneralConfiguration::GeneralConfiguration(bool save_on_destroy)
/*
 This version of the general configuration uses a fast, in-memory system 
 for storing and retrieving the data.
 It loads the values from file only when needed. 
 Once the values have been loaded in memory, they remain there,
 and the next times the values are queried, they are taken from memory,
 instead of loading them from disk again. This speeds the system up greatly.
 It has "getters" and "setters" to facilitate this system.
 On object destruction, it saves the values if they were modified.
 */
{
  // Save parameters.
  my_save_on_destroy = save_on_destroy;

  // Function definition for initializing variables.
#define INITIALIZE(parameter) parameter##_loaded = false

  // Initialize variables.
  INITIALIZE(screen_width);
  INITIALIZE(screen_height);
  INITIALIZE(window_width);
  INITIALIZE(window_height);
  INITIALIZE(window_x_position);
  INITIALIZE(window_y_position);
  INITIALIZE(window_maximized);
  INITIALIZE(window_widths);
  INITIALIZE(window_heights);
  INITIALIZE(window_x_positions);
  INITIALIZE(window_y_positions);
  INITIALIZE(window_ids);
  INITIALIZE(window_titles);
  INITIALIZE(window_shows);
  INITIALIZE(project);
  INITIALIZE(book);
  INITIALIZE(chapter);
  INITIALIZE(verse);
  INITIALIZE(stylesheet);
  INITIALIZE(references_file);
  INITIALIZE(export_to_bibleworks_filename);
  INITIALIZE(export_to_sword_module_path);
  INITIALIZE(export_to_sword_install_path);
  INITIALIZE(paper_format);
  INITIALIZE(paper_width);
  INITIALIZE(paper_height);
  INITIALIZE(paper_inside_margin);
  INITIALIZE(paper_outside_margin);
  INITIALIZE(paper_top_margin);
  INITIALIZE(paper_bottom_margin);
  INITIALIZE(column_spacing);
  INITIALIZE(printdate);
  INITIALIZE(printdraft);
  INITIALIZE(header_font_size);
  INITIALIZE(print_engine_use_intermediate_text);
  INITIALIZE(print_changes_only);
  INITIALIZE(project_to_compare_with);
  INITIALIZE(notes_selection_reference);
  INITIALIZE(notes_selection_edited);
  INITIALIZE(notes_selection_date_from);
  INITIALIZE(notes_selection_date_to);
  INITIALIZE(notes_selection_category);
  INITIALIZE(notes_selection_current_project);
  INITIALIZE(notes_display_project);
  INITIALIZE(notes_display_category);
  INITIALIZE(notes_display_date_created);
  INITIALIZE(notes_display_created_by);
  INITIALIZE(notes_display_summary);
  INITIALIZE(notes_display_reference_text);
  INITIALIZE(check_markers_compare_project);
  INITIALIZE(check_markers_compare_all_markers);
  INITIALIZE(check_markers_compare_include_only);
  INITIALIZE(check_markers_compare_ignore);
  INITIALIZE(check_markers_compare_ignore_verse_zero);
  INITIALIZE(check_capitalization_punctuation);
  INITIALIZE(check_capitalization_ignore);
  INITIALIZE(check_capitalization_allow_any_prefixes);
  INITIALIZE(check_repetition_ignore_case);
  INITIALIZE(check_repetition_show_only_these);
  INITIALIZE(check_repetition_ignore_these);
  INITIALIZE(check_matching_pairs_ignore);
  INITIALIZE(check_words_inventory_not_include_words_count);
  INITIALIZE(check_words_inventory_word_forming_characters);
  INITIALIZE(check_markers_spacing_include);
  INITIALIZE(styles_category_expanded);
  INITIALIZE(insert_footnote_template);
  INITIALIZE(insert_endnote_template);
  INITIALIZE(insert_xref_template);
  INITIALIZE(parallel_bible_keep_verses_together);
  INITIALIZE(parallel_bible_chapters_verses);
  INITIALIZE(parallel_bible_include_verse_zero);
  INITIALIZE(printing_fonts);
  INITIALIZE(parallel_bible_projects);
  INITIALIZE(parallel_bible_enabled);
  INITIALIZE(use_outpost);
  INITIALIZE(mychecks);
  INITIALIZE(tidy_translate);
  INITIALIZE(tidy_books);
  INITIALIZE(tidy_texts);
  INITIALIZE(tidy_normalize_hyphens);
  INITIALIZE(tidy_space_between_chapter_verse);
  INITIALIZE(tidy_space_series_verses);
  INITIALIZE(tidy_full_stop_ends_text);
  INITIALIZE(tidy_ampersand_semicolon);
  INITIALIZE(tidy_space_before_punctuation);
  INITIALIZE(wordlist_process_general);
  INITIALIZE(wordlist_general_asterisk);
  INITIALIZE(wordlist_general_asterisk_first);
  INITIALIZE(wordlist_process_hebrew);
  INITIALIZE(wordlist_hebrew_asterisk);
  INITIALIZE(wordlist_hebrew_asterisk_first);
  INITIALIZE(wordlist_process_greek);
  INITIALIZE(wordlist_greek_asterisk);
  INITIALIZE(wordlist_greek_asterisk_first);
  INITIALIZE(wordlist_process_index);
  INITIALIZE(wordlist_index_asterisk);
  INITIALIZE(wordlist_index_asterisk_first);
  INITIALIZE(text_editor_font_default);
  INITIALIZE(text_editor_font_name);
  INITIALIZE(text_editor_default_color);
  INITIALIZE(text_editor_normal_text_color);
  INITIALIZE(text_editor_background_color);
  INITIALIZE(text_editor_selected_text_color);
  INITIALIZE(text_editor_selection_color);
  INITIALIZE(encoding);
  INITIALIZE(features_mode);
  INITIALIZE(features_list);
  INITIALIZE(remember_verse_per_chapter);
  INITIALIZE(start_program_maximized);
  INITIALIZE(administration_password);
  INITIALIZE(print_references_projects);
  INITIALIZE(dialogpositions_x);
  INITIALIZE(dialogpositions_y);
  INITIALIZE(text_replacement);
  INITIALIZE(text_replacement_originals);
  INITIALIZE(text_replacement_replacements);
  INITIALIZE(pdf_viewer_automatic);
  INITIALIZE(pdf_viewer_path);
  INITIALIZE(pdf_viewer_arguments);
  INITIALIZE(project_tasks_names);
  INITIALIZE(project_tasks_durations);
  INITIALIZE(print_job);
  INITIALIZE(projects_displaying_verses);
  INITIALIZE(compare_disregard_notes);
  INITIALIZE(source_language_names);
  INITIALIZE(reference_window_show_verse_text);
  INITIALIZE(reference_window_show_relevant_bits);
  INITIALIZE(consultation_notes_git_use_remote_repository);
  INITIALIZE(consultation_notes_git_remote_repository_url);
  INITIALIZE(bibledit_web_url);
  INITIALIZE(bibledit_web_user);
}