/** ***********************************************************************************
  * it-edit the Integrated Terminal Editor: a text editor with severals               *
  * integrated functionnalities.                                                      *
  *                                                                                   *
  * Copyright (C) 2015,2016 Brüggemann Eddie.                                         *
  *                                                                                   *
  * This file is part of it-edit.                                                     *
  * it-edit is free software: you can redistribute it and/or modify                   *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * it-edit is distributed in the hope that it will be useful,                        *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with it-edit. If not, see <http://www.gnu.org/licenses/>                    *
  *                                                                                   *
  ************************************************************************************/

#include "./configuration_dialog.h"



void add_a_new_item_to_files_manager(GtkWidget *widget, GtkWidget *files_manager_vbox) {
  /** Display a dialog to add a new entry to the "File Handler" fubnctionnality. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *add_a_file_to_files_manager_dialog  = gtk_dialog_new_with_buttons( _("Add a new file to files manager"),
                                                  GTK_WINDOW(gui->main_window),
                                                  GTK_DIALOG_USE_HEADER_BAR | GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  _("Add file"),
                                                  GTK_RESPONSE_OK,
                                                  _("Cancel"),
                                                  GTK_RESPONSE_CANCEL,
                                                  NULL);

  gtk_window_set_transient_for(GTK_WINDOW(add_a_file_to_files_manager_dialog), GTK_WINDOW(gui->main_window)) ;

  gtk_window_set_title(GTK_WINDOW(add_a_file_to_files_manager_dialog), _("Adding a file") );

  gtk_window_set_resizable(GTK_WINDOW(add_a_file_to_files_manager_dialog), FALSE) ;

  gtk_container_set_border_width(GTK_CONTAINER(add_a_file_to_files_manager_dialog), 15) ;

  GtkWidget *new_entry_title_label = gtk_label_new( _("Title") ) ;

  GtkWidget *new_entry_file_label  = gtk_label_new( _("File") )  ;

  GtkWidget *new_entry_title_entry = gtk_entry_new() ;

  gtk_entry_set_width_chars(GTK_ENTRY(new_entry_title_entry), 35) ;

  gtk_entry_set_max_length(GTK_ENTRY(new_entry_title_entry),  35) ;

  GtkWidget *new_entry_file_button = gtk_file_chooser_button_new(NULL, GTK_FILE_CHOOSER_ACTION_OPEN);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(new_entry_file_button), g_get_home_dir() );

  GtkWidget *main_add_file_hbox    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *new_entry_title_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL,   5) ;

  GtkWidget *new_entry_data_vbox   = gtk_box_new(GTK_ORIENTATION_VERTICAL,   5) ;

  gtk_box_set_homogeneous(GTK_BOX(new_entry_title_vbox), TRUE) ;
  gtk_box_set_homogeneous(GTK_BOX(new_entry_data_vbox),  TRUE) ;

  gtk_box_pack_start(GTK_BOX(new_entry_title_vbox), new_entry_title_label, FALSE, FALSE,0) ;
  gtk_box_pack_start(GTK_BOX(new_entry_title_vbox), new_entry_file_label, FALSE, FALSE,0) ;

  gtk_box_pack_start(GTK_BOX(new_entry_data_vbox), new_entry_title_entry, FALSE, FALSE,0) ;
  gtk_box_pack_start(GTK_BOX(new_entry_data_vbox), new_entry_file_button, FALSE, FALSE,0) ;

  gtk_box_pack_start(GTK_BOX(main_add_file_hbox), new_entry_title_vbox, FALSE, FALSE,0) ;
  gtk_box_pack_start(GTK_BOX(main_add_file_hbox), new_entry_data_vbox, FALSE, FALSE,0) ;

  gtk_box_set_spacing(GTK_BOX(new_entry_title_vbox), 5) ;
  gtk_box_set_spacing(GTK_BOX(new_entry_data_vbox), 5) ;
  gtk_box_set_spacing(GTK_BOX(main_add_file_hbox), 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(new_entry_title_vbox), 5) ;
  gtk_container_set_border_width(GTK_CONTAINER(new_entry_data_vbox), 5) ;
  gtk_container_set_border_width(GTK_CONTAINER(main_add_file_hbox), 5) ;

  GtkWidget *dialog_content_area = gtk_dialog_get_content_area(GTK_DIALOG(add_a_file_to_files_manager_dialog)) ;

  GtkWidget *add_file_button = gtk_dialog_get_widget_for_response (GTK_DIALOG(add_a_file_to_files_manager_dialog), GTK_RESPONSE_OK) ;

  GtkWidget *add_file_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "list-add.png");

  g_object_set(G_OBJECT(add_file_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(add_file_button), add_file_image);

  GtkWidget *cancel_button   = gtk_dialog_get_widget_for_response (GTK_DIALOG(add_a_file_to_files_manager_dialog), GTK_RESPONSE_CANCEL) ;

  GtkWidget *cancel_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "dialog-cancel.png");

  g_object_set(G_OBJECT(cancel_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(cancel_button), cancel_image);

  gtk_container_add(GTK_CONTAINER(dialog_content_area), main_add_file_hbox) ;

  gtk_widget_show_all(add_a_file_to_files_manager_dialog) ;

  gint result = gtk_dialog_run (GTK_DIALOG(add_a_file_to_files_manager_dialog));
  switch (result) {

      case GTK_RESPONSE_OK :

        if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(new_entry_title_entry)), "") == 0 || gtk_entry_get_text(GTK_ENTRY(new_entry_title_entry)) == NULL || gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(new_entry_file_button)) == NULL ) {
          gtk_widget_destroy(add_a_file_to_files_manager_dialog) ;
          return ;
        }

        Files_Manager *file_item = g_malloc(sizeof(Files_Manager)) ;
        file_item->label = g_strdup(gtk_entry_get_text(GTK_ENTRY(new_entry_title_entry)) ) ;
        file_item->uri   = g_strdup(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(new_entry_file_button)) )   ;

        FILE *fp = fopen(PATH_TO_LINKS_FILE, "a") ;

        fputs(file_item->label, fp) ;
        fputc('\n', fp) ;
        fputs(file_item->uri, fp) ;
        fputc('\n', fp) ;

        fclose(fp) ;


        GtkWidget *files_checkbutton = gtk_check_button_new_with_label(file_item->label) ;

        g_object_set_data(G_OBJECT(files_checkbutton), "item", file_item) ;

        gtk_box_pack_start(GTK_BOX(files_manager_vbox), files_checkbutton, FALSE, FALSE, 0) ;

        gtk_widget_show_all(GTK_WIDGET(files_manager_vbox)) ;

        gtk_widget_destroy(add_a_file_to_files_manager_dialog) ;
        return ;

      case GTK_RESPONSE_CANCEL :

        gtk_widget_destroy(add_a_file_to_files_manager_dialog) ;
        return ;


     default :

        gtk_widget_destroy(add_a_file_to_files_manager_dialog) ;
        return ;

  }


}

void add_a_new_item_to_applications(GtkWidget *widget, gpointer user_data) {

  /** Add a new application as shortcut for starting it. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif





  GtkWidget *file_dialog = gtk_file_chooser_dialog_new( _("Add a new aplication."), GTK_WINDOW(gui->main_window), GTK_FILE_CHOOSER_ACTION_OPEN, _("Add"), GTK_RESPONSE_OK, _("Cancel"), GTK_RESPONSE_CANCEL, NULL) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_dialog), PATH_TO_BIN_FOLDER) ;

  gtk_widget_show_all(file_dialog) ;

  int ret = gtk_dialog_run(GTK_DIALOG(file_dialog)) ;

  switch (ret) {

    case GTK_RESPONSE_OK : {

      GKeyFile *conf_file = g_key_file_new() ;

      GError *error = NULL ;

      g_key_file_load_from_file(conf_file, PATH_TO_APP_FILE, G_KEY_FILE_NONE, &error) ;

      if (error != NULL) {

        gchar *msg = g_strdup_printf( _("Configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

        display_message_dialog( _("Cannot register new application !"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        g_free(msg) ;

        g_error_free(error) ;

        return ;

      }

      MenuItem *menu_item = g_malloc(sizeof(MenuItem)) ;

      gchar *gui_new_app =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_dialog)) ;

      gchar *text = g_strdup_printf("  %s  ", g_path_get_basename(gui_new_app)) ;

      setup_menu_item(menu_item, text, NULL, "applications-system.png", NULL, 0, 0, 0) ;

      g_free(text) ;

      gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->app_others_menu), menu_item->menuitem) ;
      g_signal_connect(G_OBJECT(menu_item->menuitem), "activate", G_CALLBACK(launch_application), gui_new_app) ;

      gtk_widget_show_all(menu_item->menuitem) ;

      gui_app.others = g_key_file_get_string_list(conf_file, "Others",  "others",  &gui_app.nb_of_others, &error)  ;

      if (error != NULL) {

        gchar *msg = g_strdup_printf( _("Cannot register new application: configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

        display_message_dialog( _("Error !!!"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        g_free(msg) ;

        g_error_free(error) ;

        return ;

      }

      int c  ;

      gchar *app_others_cp[gui_app.nb_of_others+2];

      for (c=0 ; c < gui_app.nb_of_others ; ++c) {
        app_others_cp[c] = gui_app.others[c] ;
      }

      app_others_cp[c] = gui_new_app ;

      app_others_cp[++c] = NULL ;

      g_key_file_set_string_list(conf_file, "Others",  "others",  (const gchar **) app_others_cp, gui_app.nb_of_others+1)  ;

      g_key_file_save_to_file(conf_file, PATH_TO_APP_FILE, &error) ;


      if (error != NULL) {

        gchar *msg = g_strdup_printf( _("Cannot register new application: configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

        display_message_dialog( _("Error !!!"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        g_free(msg) ;

        g_error_free(error) ;

        return ;

      }


      gchar *gui_app_label = g_strdup_printf("  %s  ", g_path_get_basename(gui_new_app)) ;

      GtkWidget *files_checkbutton = gtk_check_button_new_with_label(gui_app_label) ;

      g_free(gui_app_label) ;

      gtk_box_pack_start(GTK_BOX(user_data), files_checkbutton, FALSE, FALSE, 0) ;

      gtk_widget_show_all(files_checkbutton) ;

      g_key_file_unref(conf_file) ;

      if (gui_app.others != NULL) {
        g_strfreev(gui_app.others) ;
      }

      gtk_widget_show_all(gui->menu->app_others_menuitem->menuitem) ;


      break ;

    }
  }

  gtk_widget_destroy(file_dialog) ;

  return ;

}

void remove_selected_items_from_applications(GtkWidget *widget, GtkWidget *files_manager_vbox) {

  /** Remove an application from the applications list . **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  /** Get the checkbuttons which contains the data. **/
  GList *check_buttons_list = gtk_container_get_children(GTK_CONTAINER(files_manager_vbox)) ;

  GList *menu_items_list    = gtk_container_get_children(GTK_CONTAINER(gui->menu->app_others_menu)) ;

  int c = 0 ;


  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_APP_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

    gchar *msg = g_strdup_printf( _("Configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

    display_message_dialog( _("Error configuration !"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_free(msg) ;

    g_error_free(error) ;

    return ;

  }


  gui_app.others = g_key_file_get_string_list(conf_file, "Others",  "others",  &gui_app.nb_of_others, &error)  ;

  gchar *gui_app_cp[gui_app.nb_of_others] ;

  int cc = 0 ;

  int rm_counter = 0 ;

  while (check_buttons_list != NULL) {

    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_buttons_list->data)) ) {
      /** The checkbutton is selected so we.. */

      g_signal_handlers_disconnect_by_func(check_buttons_list->data, launch_application, gui_app.others[c]) ;

      gtk_widget_destroy(GTK_WIDGET(menu_items_list->data)) ;

      /** Update the GUI. **/
      gtk_widget_destroy(GTK_WIDGET(check_buttons_list->data));

      ++rm_counter ;

    }
    else {

      gui_app_cp[cc] = gui_app.others[c] ;

      ++cc ;

    }

    if (check_buttons_list->next == NULL || menu_items_list->next == NULL) {
      break ;
    }
    else {
      check_buttons_list = check_buttons_list->next ;
      menu_items_list = menu_items_list->next ;
      ++c ;
    }

  }

  gui_app_cp[++cc] = NULL ;

  g_key_file_set_string_list(conf_file, "Others",  "others",  (const gchar **) gui_app_cp, gui_app.nb_of_others-rm_counter)  ;

  g_key_file_save_to_file(conf_file, PATH_TO_APP_FILE, &error) ;


  if (error != NULL) {

    gchar *msg = g_strdup_printf( _("Cannot remove application(s) from list: configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_APP_FILE), error->message) ;

    display_message_dialog( _("Error !!!"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_free(msg) ;

    g_error_free(error) ;

    return ;

  }

  if (gui_app.others != NULL) {
    g_strfreev(gui_app.others) ;
  }

  g_key_file_unref(conf_file) ;

  if ( gui_app.nb_of_others-rm_counter <= 0) {
    gtk_widget_hide(gui->menu->app_others_menuitem->menuitem) ;
  }

  return ;

}


void check_user_shell(GtkFileChooserButton *chooser, gpointer user_data) {

  /** Check if the user has select a valid shell. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (! g_file_test(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)), G_FILE_TEST_IS_EXECUTABLE) ) {

    display_message_dialog( _("The file is not an executable !"), _("The shell you have chosen isn't an executable !!!") , GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(chooser), settings.user_shell) ;

    return ;
  }

  char *user_shell_test = g_strdup_printf("%s -c ls $HOME", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)) ) ;

  if (system(user_shell_test) != 0) {

    display_message_dialog( _("Wrong shell !"), _("The file you have chosen seems not to be a valid shell."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(chooser), settings.user_shell) ;

    free(user_shell_test) ;

    return ;

  }

  free(user_shell_test) ;

  return ;
}

inline GtkWidget *generate_applications_chooser(GtkWidget *hbox, const char *icon_filepath, const char *label_text, char *app_filepath) {



    GtkWidget *icon_image = gtk_image_new_from_file(icon_filepath) ;

    GtkWidget *label = gtk_label_new(label_text) ;

    GtkWidget *file_chooser_button = gtk_file_chooser_button_new(label_text, GTK_FILE_CHOOSER_ACTION_OPEN) ;

    gtk_widget_set_size_request(file_chooser_button, (128+64), -1 ) ;

    if (g_strcmp0(app_filepath, "") != 0) {
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_button),  g_path_get_dirname(app_filepath)) ;
      gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser_button), app_filepath) ;
    }
    else {
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_button),  PATH_TO_BIN_FOLDER) ;
    }


    gtk_box_pack_start(GTK_BOX(hbox), icon_image,          FALSE, FALSE, 0) ;
    gtk_box_pack_start(GTK_BOX(hbox), label,               TRUE,  TRUE,  0) ;
    gtk_box_pack_start(GTK_BOX(hbox), file_chooser_button, FALSE, FALSE, 0) ;

    gtk_box_set_spacing(GTK_BOX(hbox), 5) ;
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5) ;

    return file_chooser_button ;

}

inline GtkWidget *generate_checkbuton(GtkWidget *hbox, const char *label, bool is_active) {

  gtk_container_set_border_width(GTK_CONTAINER(hbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(hbox), 5) ;

  GtkWidget *checkbutton = gtk_check_button_new_with_label(label) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), is_active) ;

  gtk_box_pack_start(GTK_BOX(hbox), checkbutton, TRUE, TRUE, 5) ;

  return checkbutton ;

}

inline void set_applications(char *app, GtkWidget *file_chooser) {

  if (app != NULL) {

    free(app) ;
  }
  else {
    app = g_strdup("") ;
    return ;
  }

  app = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) ;

  if (app == NULL) {
    app = g_strdup("") ;
  }

}

inline void change_applications(char *app_name, MenuItem *menu_item) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (g_strcmp0(app_name, "") != 0) {

    gchar *app_label = g_strdup_printf("  %s  ", g_path_get_basename(app_name)) ;

    gtk_label_set_text(GTK_LABEL(menu_item->label), app_label) ;

    g_free(app_label) ;

    if (! gtk_widget_get_visible(menu_item->menuitem)) {

      gtk_widget_show(menu_item->menuitem) ;

      g_signal_connect(G_OBJECT(menu_item->menuitem), "activate", G_CALLBACK(launch_application), app_name) ;

    }

  }

  return ;
}


void set_as_default(GtkWidget *widget, gpointer user_data) {

  const gchar * const *ids = gtk_source_language_manager_get_language_ids(gtk_source_language_manager_get_default()) ;


  GError *error = NULL ;

  GAppInfo *it_edit_app = g_app_info_create_from_commandline(PATH_TO_IT_EDIT, "it-edit", G_APP_INFO_CREATE_SUPPORTS_URIS, &error);

  if (error != NULL || it_edit_app == NULL) {

    char *msg = g_strdup(error->message) ;

    display_message_dialog( _("Cannot find it-edit executable."), msg, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;

    return ;
  }


  while (*ids != NULL) {

    GtkSourceLanguage *source_language = gtk_source_language_manager_get_language(gtk_source_language_manager_get_default(), *ids) ;

    gchar **mimetypes = gtk_source_language_get_mime_types(source_language) ;

    if ((g_strcmp0("HTML", gtk_source_language_get_name(source_language)) == 0) || (g_strcmp0("XML", gtk_source_language_get_name(source_language)) == 0)) {

      ++ids ;

      continue ;


    }

    if (mimetypes != NULL) {

      int c = 0 ;

      while (mimetypes[c] != NULL) {

        g_app_info_set_as_default_for_type(it_edit_app, mimetypes[c], NULL) ;

        ++c ;
      }

    }

    g_strfreev(mimetypes) ;

    ++ids ;

 }

 g_app_info_set_as_default_for_type(it_edit_app,"text/plain", NULL) ;

 display_message_dialog( _("it-edit set as default editor."), _("The right choice !!!"), GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE) ;

 return ;

}


void reset_default(GtkWidget *widget, gpointer user_data) {

  const gchar * const *ids = gtk_source_language_manager_get_language_ids(gtk_source_language_manager_get_default()) ;


  while (*ids != NULL) {

    GtkSourceLanguage *source_language = gtk_source_language_manager_get_language(gtk_source_language_manager_get_default(), *ids) ;

    gchar **mimetypes = gtk_source_language_get_mime_types(source_language) ;



    if (mimetypes != NULL) {

      int c = 0 ;

      while (mimetypes[c] != NULL) {

        g_app_info_reset_type_associations(mimetypes[c]) ;

        ++c ;
      }

    }

    g_strfreev(mimetypes) ;

    ++ids ;

 }

 g_app_info_reset_type_associations("text/plain") ;

 display_message_dialog( _("Application associations reset to default."), _("The wrong choice !!!"), GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE) ;

 return ;

}


static void is_a_new_color_choosen(GtkColorButton *widget, bool *confirm) {

  *confirm = true ;

  return ;

}

void display_configuration_dialog(GtkWidget *widget, gpointer user_data) {
  /** Generate the application configuration dialog window and register changes if some. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *configuration_dialog = gtk_dialog_new_with_buttons( _("Configure program"),
                                                                GTK_WINDOW(gui->main_window),
                                                                GTK_DIALOG_USE_HEADER_BAR | GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                                _("Apply settings"), GTK_RESPONSE_APPLY,
                                                                _("Cancel"), GTK_RESPONSE_CANCEL,
                                                                NULL);




  gtk_window_set_transient_for(GTK_WINDOW(configuration_dialog), GTK_WINDOW(gui->main_window)) ;

  gtk_window_set_resizable(GTK_WINDOW(configuration_dialog), FALSE) ;

  GtkWidget *configuration_dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(configuration_dialog));

  GtkWidget *notebook_configuration = gtk_notebook_new() ;

  gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook_configuration), TRUE);

  GtkWidget *editor_configuration_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;



  gtk_box_set_spacing(GTK_BOX(editor_configuration_vbox), 5) ;


  GtkWidget *terminal_appearance_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(terminal_appearance_vbox), 5) ;



  #define FRAME_BORDER_SIZE 2

  GtkWidget *font_colors_frame          = gtk_frame_new( _("Font settings") ) ;

  GtkWidget *displaying_settings_frame  = gtk_frame_new( _("Displaying settings") ) ;

  GtkWidget *indent_settings_frame      = gtk_frame_new( _("Indentation settings") ) ;

  GtkWidget *tabs_settings_frame        = gtk_frame_new( _("TABS settings") ) ;

  GtkWidget *backup_settings_frame      = gtk_frame_new( _("Backup file") ) ;

  GtkWidget *trailing_space_frame       = gtk_frame_new( _("Trailing space") ) ;

  gtk_container_set_border_width(GTK_CONTAINER(font_colors_frame),         FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(displaying_settings_frame), FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(indent_settings_frame),     FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(tabs_settings_frame),       FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(backup_settings_frame),     FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(trailing_space_frame),      FRAME_BORDER_SIZE) ;


  GtkWidget *font_colors_button = gtk_font_button_new_with_font(settings.editor_font) ;

  GtkWidget *font_colors_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(font_colors_hbox), 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(font_colors_hbox), 5) ;

  gtk_font_button_set_show_style(GTK_FONT_BUTTON(font_colors_button), TRUE) ;
  gtk_font_button_set_show_size(GTK_FONT_BUTTON(font_colors_button),  TRUE) ;
  gtk_font_button_set_use_font (GTK_FONT_BUTTON(font_colors_button),  TRUE) ;
  gtk_font_button_set_use_size(GTK_FONT_BUTTON(font_colors_button),   TRUE) ;


  gtk_container_set_border_width(GTK_CONTAINER(font_colors_button), 5) ;

  gtk_box_pack_start(GTK_BOX(font_colors_hbox), font_colors_button, TRUE, TRUE, 5) ;


  gtk_container_add(GTK_CONTAINER(font_colors_frame), font_colors_hbox) ;





  GtkWidget *show_lines_and_tabs_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *show_lines_checkbutton = gtk_check_button_new_with_label( _("Display lines numbers") ) ;

  GtkWidget *show_tabs_checkbutton = gtk_check_button_new_with_label( _("Display TABS characters") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(show_lines_checkbutton), settings.display_line_numbers) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(show_tabs_checkbutton),  settings.display_tabs_chars) ;

  gtk_box_pack_start(GTK_BOX(show_lines_and_tabs_vbox), show_lines_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(show_lines_and_tabs_vbox), show_tabs_checkbutton,  FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(show_lines_and_tabs_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(displaying_settings_frame), show_lines_and_tabs_vbox) ;










  GtkWidget *indent_settings_hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *auto_indent_checkbutton = gtk_check_button_new_with_label( _("Use auto-indent") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(auto_indent_checkbutton), settings.use_auto_indent) ;

  GtkWidget *indent_width_hbox       = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  GtkWidget *indent_width_label      = gtk_label_new( _("Indent width") ) ;

  GtkWidget *indent_width_spinbutton = gtk_spin_button_new_with_range (2, 16, 1) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(indent_width_spinbutton),   (gdouble) settings.indent_width ) ;
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(indent_width_spinbutton),                                 0) ;
  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(indent_width_spinbutton),                             TRUE) ;


  gtk_box_pack_start(GTK_BOX(indent_width_hbox),indent_width_label, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(indent_width_hbox),indent_width_spinbutton, FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(indent_settings_hbox), auto_indent_checkbutton, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(indent_settings_hbox), indent_width_hbox, FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(indent_settings_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(indent_settings_frame), indent_settings_hbox) ;




  GtkWidget *tabs_settings_hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *use_spaces_instead_of_tabs = gtk_check_button_new_with_label( _("Use spaces instead of TABS") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(use_spaces_instead_of_tabs), settings.use_spaces_as_tabs) ;





  GtkWidget *tabs_width_hbox       = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  GtkWidget *tabs_width_label      = gtk_label_new( _("TABS width") ) ;

  GtkWidget *tabs_width_spinbutton = gtk_spin_button_new_with_range(1, 16, 1) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(tabs_width_spinbutton), settings.tabs_width) ;
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(tabs_width_spinbutton),                  0) ;
  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(tabs_width_spinbutton),              TRUE) ;


  gtk_box_pack_start(GTK_BOX(tabs_width_hbox),tabs_width_label,      TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(tabs_width_hbox),tabs_width_spinbutton, FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(tabs_settings_hbox), use_spaces_instead_of_tabs, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(tabs_settings_hbox), tabs_width_hbox,            FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(tabs_settings_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(tabs_settings_frame), tabs_settings_hbox) ;


  GtkWidget *backup_file_vbox        = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *backup_file_checkbutton = gtk_check_button_new_with_label( _("Create a back up file on saving.") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(backup_file_checkbutton), settings.backup_file) ;

  GtkWidget *backup_suffix_hbox      = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *backup_suffix_label     = gtk_label_new( _(" Back up file suffix character: ") ) ;

  GtkWidget *backup_suffix_entry     = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(backup_suffix_entry), "~") ;

  gtk_entry_set_width_chars(GTK_ENTRY(backup_suffix_entry), 5) ;

  gtk_entry_set_alignment(GTK_ENTRY(backup_suffix_entry), 0.5) ;


  g_object_set(G_OBJECT(backup_suffix_entry), "editable", FALSE, NULL) ;

  gtk_box_pack_start(GTK_BOX(backup_suffix_hbox), backup_suffix_label,   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(backup_suffix_hbox), backup_suffix_entry,   FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(backup_file_vbox), backup_file_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(backup_file_vbox), backup_suffix_hbox,      FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(backup_file_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(backup_settings_frame), backup_file_vbox) ;


  GtkWidget *trailing_spaces_hbox        = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *trailing_spaces_checkbutton = gtk_check_button_new_with_label( _("Remove trailing space on saving file.") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(trailing_spaces_checkbutton), settings.rm_trailing_spaces) ;


  gtk_box_pack_start(GTK_BOX(trailing_spaces_hbox), trailing_spaces_checkbutton,      FALSE, FALSE, 5) ;


  gtk_container_add(GTK_CONTAINER(trailing_space_frame), trailing_spaces_hbox) ;



  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), font_colors_frame,         FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), displaying_settings_frame, FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), indent_settings_frame,     FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), tabs_settings_frame,       FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), backup_settings_frame,     FALSE, FALSE, 0 ) ;
  gtk_box_pack_start(GTK_BOX(editor_configuration_vbox), trailing_space_frame,      TRUE,  TRUE,  0 ) ;


  GtkWidget *terminal_settings_notebook         = gtk_notebook_new() ;


  GtkWidget *terminal_font_colors_frame         = gtk_frame_new( _("Font settings") ) ;

  GtkWidget *terminal_font_scale_frame          = gtk_frame_new( _("Font scale") ) ;

  GtkWidget *terminal_cursor_frame              = gtk_frame_new( _("Cursor settings") ) ;

  GtkWidget *terminal_colors_frame              = gtk_frame_new( _("Colors settings") ) ;

  GtkWidget *terminal_bold_frame                = gtk_frame_new( _("Bold settings") ) ;

  GtkWidget *terminal_pointer_autohide          = gtk_frame_new( _("Pointer autohide") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_colors_frame),       FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_scale_frame),        FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_frame),            FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_colors_frame),            FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_bold_frame),              FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_pointer_autohide),        FRAME_BORDER_SIZE) ;

  GtkWidget *terminal_font_colors_button = gtk_font_button_new_with_font(settings.term_font) ;


  g_object_set(G_OBJECT(terminal_font_colors_button), "margin", 5, NULL) ;

  gtk_font_button_set_show_style(GTK_FONT_BUTTON(terminal_font_colors_button),  TRUE) ;
  gtk_font_button_set_show_size(GTK_FONT_BUTTON(terminal_font_colors_button),   TRUE) ;
  gtk_font_button_set_use_font(GTK_FONT_BUTTON(terminal_font_colors_button),    TRUE) ;
  gtk_font_button_set_use_size(GTK_FONT_BUTTON(terminal_font_colors_button),    TRUE) ;


  gtk_container_add(GTK_CONTAINER(terminal_font_colors_frame), terminal_font_colors_button) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_colors_button), 5) ;




  GtkWidget *terminal_font_scale_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;
  GtkWidget *terminal_font_scale_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_font_scale_label = gtk_label_new( _("  Font scale  ") ) ;

  GtkWidget *terminal_font_scale_spinbutton = gtk_spin_button_new_with_range(0.25, 4.0, 0.01) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), TRUE) ;

  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), 2) ;

  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), GTK_UPDATE_IF_VALID) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), settings.font_scale) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_scale_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), terminal_font_scale_label,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), gtk_label_new(""),                TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), terminal_font_scale_spinbutton,   FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_font_scale_vbox), terminal_font_scale_hbox, FALSE, FALSE, 0) ;

  gtk_container_add(GTK_CONTAINER(terminal_font_scale_frame), terminal_font_scale_vbox) ;



  GtkWidget *terminal_cursor_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;


  GtkWidget *terminal_cursor_shape_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;


  GtkWidget *cursor_shape_block_radiobutton     = gtk_radio_button_new_with_label(NULL, _("BLOCK") );

  GtkWidget *cursor_shape_ibeam_radiobutton     = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cursor_shape_block_radiobutton), _("IBEAM") ) ;

  GtkWidget *cursor_shape_underline_radiobutton = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cursor_shape_block_radiobutton), _("UNDERLINE") ) ;

  switch (settings.cursor_shape) {

    case 0 :
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_block_radiobutton), TRUE );
      break ;

    case 1 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_ibeam_radiobutton), TRUE );
      break ;

    case 2 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_underline_radiobutton), TRUE );
      break ;
  }

  gtk_box_set_homogeneous(GTK_BOX(terminal_cursor_shape_hbox), TRUE) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_shape_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_block_radiobutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_ibeam_radiobutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_underline_radiobutton,      FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_shape_hbox, FALSE, FALSE, 0) ;







  GtkWidget *terminal_cursor_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_cursor_color_label  = gtk_label_new( _("  Cursor color  ") ) ;

  GdkRGBA cursor_color ;
  if (! gdk_rgba_parse(&cursor_color, settings.cursor_color)) {

    g_warning("Error getting cursor color !\n") ;
  }

  GtkWidget *terminal_cursor_color_button = gtk_color_button_new_with_rgba(&cursor_color) ;

  bool *cursor_color_activated = malloc(sizeof(bool)) ;

  *cursor_color_activated = false ;

  g_signal_connect(G_OBJECT(terminal_cursor_color_button), "color-set", G_CALLBACK(is_a_new_color_choosen), cursor_color_activated) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_color_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), terminal_cursor_color_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0),  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), terminal_cursor_color_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_color_hbox, FALSE, FALSE, 0) ;





  GtkWidget *terminal_cursor_blinking_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_cursor_blinking_label = gtk_label_new( _("  Cursor blink mode  ") ) ;

  GtkWidget *terminal_cursor_blinking_combo = gtk_combo_box_text_new() ;

  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 0, "BLINK SYSTEM" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 1, "BLINK ON"     ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 2, "BLINK OFF"    ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(terminal_cursor_blinking_combo), settings.cursor_blink) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_blinking_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), terminal_cursor_blinking_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0),  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), terminal_cursor_blinking_combo, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_blinking_hbox, FALSE, FALSE, 0) ;



  gtk_container_add(GTK_CONTAINER(terminal_cursor_frame), terminal_cursor_vbox) ;




  GtkWidget *terminal_bold_vbox        = gtk_box_new(GTK_ORIENTATION_VERTICAL,    5) ;
  GtkWidget *terminal_bold_color_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,  5) ;

  GtkWidget *terminal_bold_allowed_checkbutton = gtk_check_button_new_with_label( _("  Allow bold  ") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(terminal_bold_allowed_checkbutton), (settings.bold_allow) ? TRUE : FALSE ) ;

  GtkWidget *terminal_bold_color_label  = gtk_label_new( _("  Bold color  ") ) ;

  GdkRGBA bold_color ;
  if (! gdk_rgba_parse(&bold_color, settings.bold_color)) {

    g_warning("Error getting bold color !\n") ;

  }

  GtkWidget *terminal_bold_color_button = gtk_color_button_new_with_rgba(&bold_color) ;

  bool *bold_color_activated = malloc(sizeof(bool)) ;

  *bold_color_activated = false ;

  g_signal_connect(G_OBJECT(terminal_bold_color_button), "color-set", G_CALLBACK(is_a_new_color_choosen), bold_color_activated) ;

  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_allowed_checkbutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_color_label,                  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_color_button,                 FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_bold_vbox), terminal_bold_color_hbox,          FALSE, FALSE, 0) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_bold_color_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_bold_frame), terminal_bold_vbox) ;




  GtkWidget *terminal_pointer_autohide_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_pointer_autohide_chkbox = gtk_check_button_new_with_label( _("Pointer autohide") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(terminal_pointer_autohide_chkbox), settings.pointer_autohide) ;

  gtk_box_pack_start(GTK_BOX(terminal_pointer_autohide_hbox), terminal_pointer_autohide_chkbox, TRUE, TRUE, 0) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_pointer_autohide_chkbox),        5) ;

  gtk_container_add(GTK_CONTAINER(terminal_pointer_autohide), terminal_pointer_autohide_hbox) ;



  GdkRGBA bg_color ;

  if (! gdk_rgba_parse(&bg_color, settings.term_bg)) {

    g_warning("Error getting terminal background color !\n") ;
  }

  GtkWidget *terminal_bg_color_button = gtk_color_button_new_with_rgba(&bg_color) ;

  GdkRGBA fg_color ;

  if (! gdk_rgba_parse(&fg_color, settings.term_fg)) {

    g_warning("Error getting terminal foreground color !\n") ;

  }

  GtkWidget *terminal_fg_color_button = gtk_color_button_new_with_rgba(&fg_color) ;


  GtkWidget *terminal_colors_hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *terminal_bg_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;
  GtkWidget *terminal_fg_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *terminal_bg_color_label = gtk_label_new( _("  Background color  ") ) ;
  GtkWidget *terminal_fg_color_label = gtk_label_new( _("  Foreground color  ") ) ;

  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_bg_color_label,  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_bg_color_button, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_fg_color_label,  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_fg_color_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_colors_hbox), terminal_bg_color_hbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_colors_hbox), terminal_fg_color_hbox, FALSE, FALSE, 0) ;


  gtk_container_add(GTK_CONTAINER(terminal_colors_frame), terminal_colors_hbox) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_colors_hbox), 5) ;


  GtkWidget *terminal_user_shell_frame          = gtk_frame_new( _("User shell") ) ;

  GtkWidget *terminal_start_dir_frame           = gtk_frame_new( _("Start directory") ) ;

  GtkWidget *terminal_audible_bell_frame        = gtk_frame_new( _("Audible bell") ) ;

  GtkWidget *terminal_scrollback_frame          = gtk_frame_new( _("Scrollback lines") ) ;

  GtkWidget *terminal_scrolling_frame           = gtk_frame_new( _("Scrolling") ) ;

  GtkWidget *terminal_erase_binding_frame       = gtk_frame_new( _("Erasing binding") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_user_shell_frame),         FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_start_dir_frame),          FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_audible_bell_frame),       FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_scrollback_frame),         FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_scrolling_frame),          FRAME_BORDER_SIZE) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_erase_binding_frame),      FRAME_BORDER_SIZE) ;



  GtkWidget *user_shell_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *user_shell_label = gtk_label_new(     _("User shell                 ") ) ;

  GtkWidget *user_shell_file_chooser_button = gtk_file_chooser_button_new( _("Select the shell you want to use"), GTK_FILE_CHOOSER_ACTION_OPEN) ;

  g_signal_connect(G_OBJECT(user_shell_file_chooser_button), "file-set", G_CALLBACK(check_user_shell), NULL) ;

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(user_shell_file_chooser_button), settings.user_shell) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(user_shell_file_chooser_button), PATH_TO_BIN_FOLDER) ;

  gtk_box_pack_start(GTK_BOX(user_shell_hbox), user_shell_label,               FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(user_shell_hbox), user_shell_file_chooser_button, TRUE,  TRUE,  0) ;

  gtk_container_set_border_width(GTK_CONTAINER(user_shell_file_chooser_button),  5) ;

  gtk_container_set_border_width(GTK_CONTAINER(user_shell_hbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(user_shell_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_user_shell_frame), user_shell_hbox) ;





  GtkWidget *start_directory_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *start_directory_label = gtk_label_new( _("Start directory          ") ) ;

  GtkWidget *start_directory_file_chooser_button = gtk_file_chooser_button_new( _("Select the terminal starting directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER) ;

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(start_directory_file_chooser_button), settings.start_dir) ;

  gtk_box_pack_start(GTK_BOX(start_directory_hbox), start_directory_label,               FALSE, FALSE,   0) ;
  gtk_box_pack_start(GTK_BOX(start_directory_hbox), start_directory_file_chooser_button, TRUE,  TRUE,    0) ;

  gtk_container_set_border_width(GTK_CONTAINER(start_directory_file_chooser_button),  5) ;

  gtk_container_set_border_width(GTK_CONTAINER(start_directory_hbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(start_directory_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_start_dir_frame), start_directory_hbox) ;



  GtkWidget *audible_bell_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *audible_bell_chkbox = gtk_check_button_new_with_label( _("Audible bell") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(audible_bell_chkbox), settings.audible_bell) ;

  gtk_container_set_border_width(GTK_CONTAINER(audible_bell_vbox),  5) ;

  gtk_box_pack_start(GTK_BOX(audible_bell_vbox), audible_bell_chkbox,  TRUE, TRUE,   5) ;

  gtk_container_add(GTK_CONTAINER(terminal_audible_bell_frame), audible_bell_vbox) ;



  GtkWidget *scrollback_lines_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *scrollback_lines_unlimited = gtk_radio_button_new_with_label(NULL, _("Unlimited") ) ;

  GtkWidget *scrollback_lines_nb_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *scrollback_lines_other     = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(scrollback_lines_unlimited), _("Number of lines:") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scrollback_lines_unlimited), (settings.scrollback_lines == -1) ? TRUE : FALSE) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scrollback_lines_other), (settings.scrollback_lines != -1) ? TRUE : FALSE) ;




  GtkWidget *scrollback_lines_nb_spinner    = gtk_spin_button_new_with_range(0, 65535, 1) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), TRUE) ;
  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), GTK_UPDATE_IF_VALID) ;

  if (settings.scrollback_lines > -1) {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), settings.scrollback_lines) ;
  }

  gtk_container_set_border_width(GTK_CONTAINER(scrollback_lines_vbox), 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(scrollback_lines_nb_hbox), 0) ;

  gtk_box_set_spacing(GTK_BOX(scrollback_lines_nb_hbox), 5) ;


  gtk_box_pack_start(GTK_BOX(scrollback_lines_nb_hbox), scrollback_lines_other,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(scrollback_lines_nb_hbox), scrollback_lines_nb_spinner, FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(scrollback_lines_vbox), scrollback_lines_unlimited,  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(scrollback_lines_vbox), scrollback_lines_nb_hbox,    TRUE, TRUE, 0) ;



  GtkWidget *scrolling_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *scroll_on_output_checkbutton = gtk_check_button_new_with_label( _("Scroll on output") ) ;

  GtkWidget *scroll_on_keystroke_checkbutton = gtk_check_button_new_with_label( _("Scroll on keystroke") ) ;


  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scroll_on_output_checkbutton),    settings.scroll_on_output) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scroll_on_keystroke_checkbutton), settings.scroll_on_keystroke) ;


  gtk_box_pack_start(GTK_BOX(scrolling_vbox), scroll_on_output_checkbutton,    FALSE, FALSE, 5) ;
  gtk_box_pack_start(GTK_BOX(scrolling_vbox), scroll_on_keystroke_checkbutton, FALSE, FALSE, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(scrolling_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_scrolling_frame), scrolling_vbox) ;


  GtkWidget *erasing_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *erasing_backspace_binding_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *erasing_delete_binding_hbox     = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *erasing_backspace_binding_label = gtk_label_new( _("Backspace key generate: ") ) ;

  GtkWidget *erasing_delete_binding_label    = gtk_label_new( _("Delete key generate:       ") ) ;

  GtkWidget *erasing_backspace_binding_combo = gtk_combo_box_text_new() ;

  GtkWidget *erasing_delete_binding_combo    = gtk_combo_box_text_new() ;

  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 0, "Automatic" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 1, "ASCII backspace character (0x08)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 2, "ASCII delete character (0x7F)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 3, "@7 control sequence" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 4, "Terminal's erase setting" ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(erasing_backspace_binding_combo), settings.backspace_binding) ;



  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 0, "Automatic" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 1, "ASCII backspace character (0x08)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 2, "ASCII delete character (0x7F)"  );
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 3, "@7 control sequence" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 4, "Terminal's erase setting" ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(erasing_delete_binding_combo), settings.delete_binding) ;

  gtk_box_pack_start(GTK_BOX(erasing_backspace_binding_hbox), erasing_backspace_binding_label, TRUE,  TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(erasing_backspace_binding_hbox), erasing_backspace_binding_combo, FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(erasing_delete_binding_hbox), erasing_delete_binding_label, TRUE,  TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(erasing_delete_binding_hbox), erasing_delete_binding_combo, FALSE, FALSE,  0) ;

  gtk_box_set_spacing(GTK_BOX(erasing_backspace_binding_hbox), 5) ;
  gtk_box_set_spacing(GTK_BOX(erasing_delete_binding_hbox),    5) ;


  gtk_box_pack_start(GTK_BOX(erasing_vbox), erasing_backspace_binding_hbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(erasing_vbox), erasing_delete_binding_hbox,    FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(erasing_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_erase_binding_frame), erasing_vbox) ;




  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_font_colors_frame ,    FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_font_scale_frame,      FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_cursor_frame ,         FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_colors_frame ,         FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_bold_frame,            FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_pointer_autohide,      TRUE,   TRUE, 0) ;

  gtk_container_add(GTK_CONTAINER(terminal_scrollback_frame), scrollback_lines_vbox) ;


  gtk_notebook_append_page(GTK_NOTEBOOK(terminal_settings_notebook), terminal_appearance_vbox, gtk_label_new( _("Appearance") )) ;


  GtkWidget *terminal_settings_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_user_shell_frame,           FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_start_dir_frame,            FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_audible_bell_frame,         FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_scrollback_frame,           FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_scrolling_frame,            FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_erase_binding_frame,        TRUE,  TRUE,   0) ;


  gtk_notebook_append_page(GTK_NOTEBOOK(terminal_settings_notebook), terminal_settings_vbox, gtk_label_new( _("Settings") )) ;



  GtkWidget *files_manager_main_vbox          = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *files_manager_list_frame         = gtk_frame_new( _("Files manager list") ) ;

  GtkWidget *files_manager_action_frame       = gtk_frame_new( _("Actions") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(files_manager_list_frame),   FRAME_BORDER_SIZE) ;

  gtk_container_set_border_width(GTK_CONTAINER(files_manager_action_frame), FRAME_BORDER_SIZE) ;


  GtkWidget *files_manager_action_buttonbox  = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;



  gtk_button_box_set_layout(GTK_BUTTON_BOX(files_manager_action_buttonbox), GTK_BUTTONBOX_SPREAD);

  gtk_container_set_border_width(GTK_CONTAINER(files_manager_action_buttonbox), 5) ;


  GtkWidget *files_manager_delete_button    = gtk_button_new_with_label( _("Delete selected files"))  ;

  GtkWidget *files_manager_adding_button    = gtk_button_new_with_label( _("Add a file to manager") ) ;

  gtk_box_pack_start(GTK_BOX(files_manager_action_buttonbox), files_manager_delete_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(files_manager_action_buttonbox), files_manager_adding_button, FALSE, FALSE, 0) ;


  GtkWidget *link_scrolled_window           = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(link_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

  GtkWidget *files_manager_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(files_manager_vbox), 5) ;

  FILE *fp = fopen(PATH_TO_LINKS_FILE, "r");

  gint c = 0 ;

  while (fp != NULL) {

    char *label = NULL ;

    size_t n = 0  ;

    if ( getline(&label, &n, fp) == -1) {
      break ;
    }

    char *label_linefeed = strrchr(label,'\n') ;

    if ( label_linefeed != NULL  ) {
      label[label_linefeed - label] = '\0' ;
    }


    char *uri = NULL ;

    n = 0 ;

    if ( getline(&uri, &n, fp) == -1) {
      break ;
    }

    char *uri_linefeed = strrchr(uri,'\n') ;

    if ( uri_linefeed != NULL  ) {
      uri[uri_linefeed - uri] = '\0' ;
    }


    Files_Manager *file_manager_item = g_malloc(sizeof(Files_Manager)) ;
    file_manager_item->label = g_strdup(label) ;
    file_manager_item->uri   = g_strdup(uri)   ;


    files_manager_list = g_slist_insert(files_manager_list, file_manager_item, c);

    GtkWidget *files_checkbutton = gtk_check_button_new_with_label(label) ;

    g_object_set_data(G_OBJECT(files_checkbutton), "item", file_manager_item) ;

    gtk_box_pack_start(GTK_BOX(files_manager_vbox), files_checkbutton, FALSE, FALSE, 0) ;

    free(label) ;
    free(uri)   ;

    c++ ;

  }

  g_signal_connect(G_OBJECT(files_manager_delete_button), "clicked", G_CALLBACK(remove_selected_items_from_files_manager), files_manager_vbox) ;
  g_signal_connect(G_OBJECT(files_manager_adding_button), "clicked", G_CALLBACK(add_a_new_item_to_files_manager), files_manager_vbox) ;

  GtkWidget *files_manager_delete_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "list-remove.png");

  g_object_set(G_OBJECT(files_manager_delete_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(files_manager_delete_button), files_manager_delete_image);


  GtkWidget *files_manager_adding_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "list-add.png");

  g_object_set(G_OBJECT(files_manager_adding_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(files_manager_adding_button), files_manager_adding_image);


  fclose(fp) ;




  gtk_container_add(GTK_CONTAINER(link_scrolled_window), files_manager_vbox) ;

  gtk_container_add(GTK_CONTAINER(files_manager_list_frame),  link_scrolled_window ) ;

  gtk_container_add(GTK_CONTAINER(files_manager_action_frame), files_manager_action_buttonbox) ;



  gtk_box_pack_start(GTK_BOX(files_manager_main_vbox), files_manager_list_frame,       TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(files_manager_main_vbox), files_manager_action_frame,     FALSE, FALSE, 0) ;




  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), editor_configuration_vbox,  gtk_label_new( _("Editor Settings") )) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), terminal_settings_notebook, gtk_label_new( _("Terminals Settings") )) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), files_manager_main_vbox,    gtk_label_new( _("Files handler manager") )) ;



  gtk_container_add(GTK_CONTAINER(configuration_dialog_content), notebook_configuration) ;




  GtkWidget *gui_application_notebook           = gtk_notebook_new() ;


  GtkWidget *gui_application_main_vbox          = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *gui_application_programming_frame  = gtk_frame_new( _("Programming") ) ;

  GtkWidget *gui_application_utils_frame        = gtk_frame_new( _("Utils") ) ;

  GtkWidget *gui_application_others_frame       = gtk_frame_new( _("Others") ) ;



  GtkWidget *gui_application_action_frame       = gtk_frame_new( _("Actions") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(gui_application_programming_frame),  FRAME_BORDER_SIZE) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_utils_frame),        FRAME_BORDER_SIZE) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_others_frame),       FRAME_BORDER_SIZE) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_action_frame),       FRAME_BORDER_SIZE) ;



  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_APP_FILE, G_KEY_FILE_NONE, &error) ;

  gui_app.others = g_key_file_get_string_list(conf_file, "Others",  "others",  &gui_app.nb_of_others, &error)  ;

  GtkWidget *gui_application_programming_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *gui_application_programming_diff_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_programming_diff_chooser = generate_applications_chooser(gui_application_programming_diff_hbox, PATH_TO_BUTTON_ICON "text-x-ldif.png", _("Diff GUI tool"), gui_app.diff) ;

  gtk_box_pack_start(GTK_BOX(gui_application_programming_vbox), gui_application_programming_diff_hbox, FALSE, FALSE, 0) ;


  GtkWidget *gui_application_programming_debugger_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_programming_debugger_chooser = generate_applications_chooser(gui_application_programming_debugger_hbox, PATH_TO_BUTTON_ICON "debug-run.png", _("Debugger GUI tool"), gui_app.debugger) ;

  gtk_box_pack_start(GTK_BOX(gui_application_programming_vbox), gui_application_programming_debugger_hbox, FALSE, FALSE, 0) ;


  GtkWidget *gui_application_programming_python_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_programming_python_chooser = generate_applications_chooser(gui_application_programming_python_hbox, PATH_TO_BUTTON_ICON "python.png", _("Python smart interpreter"), gui_app.python) ;

  gtk_box_pack_start(GTK_BOX(gui_application_programming_vbox), gui_application_programming_python_hbox, FALSE, FALSE, 0) ;




  GtkWidget *gui_application_programming_gui_designer_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_programming_gui_designer_chooser = generate_applications_chooser(gui_application_programming_gui_designer_hbox, PATH_TO_BUTTON_ICON "kde-windows.png", _("GUI designer tool"), gui_app.gui_designer) ;

  gtk_box_pack_start(GTK_BOX(gui_application_programming_vbox), gui_application_programming_gui_designer_hbox, FALSE, FALSE, 0) ;


  GtkWidget *gui_application_programming_devhelp_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_programming_devhelp_chooser = generate_applications_chooser(gui_application_programming_devhelp_hbox, PATH_TO_BUTTON_ICON "devhelp.png", "Devhelp", gui_app.devhelp) ;

  gtk_box_pack_start(GTK_BOX(gui_application_programming_vbox), gui_application_programming_devhelp_hbox, FALSE, FALSE, 0) ;


  gtk_container_add(GTK_CONTAINER(gui_application_programming_frame), gui_application_programming_vbox) ;




  GtkWidget *gui_application_utils_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *gui_application_utils_calculator_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_calculator_chooser = generate_applications_chooser(gui_application_utils_calculator_hbox, PATH_TO_BUTTON_ICON "accessories-calculator.png", _("Calculator GUI tool"), gui_app.calculator) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_calculator_hbox, FALSE, FALSE, 0) ;



  GtkWidget *gui_application_utils_color_picker_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_color_picker_chooser = generate_applications_chooser(gui_application_utils_color_picker_hbox, PATH_TO_BUTTON_ICON "kcolorchooser.png", _("Color picker GUI tool"), gui_app.color_picker) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_color_picker_hbox, FALSE, FALSE, 0) ;



  GtkWidget *gui_application_utils_dictionary_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_dictionary_chooser = generate_applications_chooser(gui_application_utils_dictionary_hbox, PATH_TO_BUTTON_ICON "accessories-dictionary.png", _("Dictionary GUI tool"), gui_app.dictionary) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_dictionary_hbox, FALSE, FALSE, 0) ;




  GtkWidget *gui_application_utils_file_manager_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_file_manager_chooser = generate_applications_chooser(gui_application_utils_file_manager_hbox, PATH_TO_BUTTON_ICON "system-file-manager.png", _("File manager"), gui_app.file_manager) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_file_manager_hbox, FALSE, FALSE, 0) ;


  GtkWidget *gui_application_utils_notes_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_notes_chooser = generate_applications_chooser(gui_application_utils_notes_hbox, PATH_TO_BUTTON_ICON "knotes.png", _("Notes taker GUI tool"), gui_app.notes) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_notes_hbox, FALSE, FALSE, 0) ;



  GtkWidget *gui_application_utils_browser_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *gui_application_utils_browser_chooser = generate_applications_chooser(gui_application_utils_browser_hbox, PATH_TO_BUTTON_ICON "internet-web-browser.png", _("Browser"), gui_app.browser) ;

  gtk_box_pack_start(GTK_BOX(gui_application_utils_vbox), gui_application_utils_browser_hbox, FALSE, FALSE, 0) ;


  gtk_container_add(GTK_CONTAINER(gui_application_utils_frame), gui_application_utils_vbox) ;






  GtkWidget *gui_application_others_main_vbox          = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *gui_application_others_list_frame         = gtk_frame_new( _("User defined applications list") ) ;

  GtkWidget *gui_application_others_action_frame       = gtk_frame_new( _("Actions") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(gui_application_others_list_frame),    FRAME_BORDER_SIZE) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_others_action_frame),  FRAME_BORDER_SIZE) ;


  GtkWidget *gui_application_others_action_buttonbox  = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;



  gtk_button_box_set_layout(GTK_BUTTON_BOX(gui_application_others_action_buttonbox), GTK_BUTTONBOX_SPREAD);

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_others_action_buttonbox), 5) ;


  GtkWidget *gui_application_others_delete_button    = gtk_button_new_with_label( _("Delete applications") ) ;

  GtkWidget *gui_application_others_adding_button    = gtk_button_new_with_label( _("Add an application") ) ;

  gtk_box_pack_start(GTK_BOX(gui_application_others_action_buttonbox), gui_application_others_delete_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(gui_application_others_action_buttonbox), gui_application_others_adding_button, FALSE, FALSE, 0) ;


  GtkWidget *gui_application_others_scrolled_window  = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gui_application_others_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

  GtkWidget *gui_application_others_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_application_others_vbox), 5) ;




  if (gui_app.nb_of_others == 0) {

    goto list_empty ;

  }

  c = 0 ;

  while (gui_app.others[c] != NULL) {

    GtkWidget *files_checkbutton = gtk_check_button_new_with_label( g_path_get_basename(gui_app.others[c]) ) ;

    gtk_box_pack_start(GTK_BOX(gui_application_others_vbox), files_checkbutton, FALSE, FALSE, 0) ;

    ++c ;

  }

  list_empty :

  if (gui_app.others != NULL) {
    g_strfreev(gui_app.others) ;
  }

  g_signal_connect(G_OBJECT(gui_application_others_delete_button), "clicked", G_CALLBACK(remove_selected_items_from_applications), gui_application_others_vbox) ;
  g_signal_connect(G_OBJECT(gui_application_others_adding_button), "clicked", G_CALLBACK(add_a_new_item_to_applications), gui_application_others_vbox) ;


  GtkWidget *gui_application_others_delete_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "list-remove.png");

  g_object_set(G_OBJECT(gui_application_others_delete_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(gui_application_others_delete_button), gui_application_others_delete_image);


  GtkWidget *gui_application_others_adding_image  = gtk_image_new_from_file(PATH_TO_BUTTON_ICON "list-add.png");

  g_object_set(G_OBJECT(gui_application_others_adding_button), "always-show-image", TRUE, NULL ) ;

  gtk_button_set_image(GTK_BUTTON(gui_application_others_adding_button), gui_application_others_adding_image);




  gtk_container_add(GTK_CONTAINER(gui_application_others_scrolled_window), gui_application_others_vbox) ;

  gtk_container_add(GTK_CONTAINER(gui_application_others_list_frame),  gui_application_others_scrolled_window ) ;

  gtk_container_add(GTK_CONTAINER(gui_application_others_action_frame), gui_application_others_action_buttonbox) ;



  gtk_box_pack_start(GTK_BOX(gui_application_others_main_vbox), gui_application_others_list_frame,       TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(gui_application_others_main_vbox), gui_application_others_action_frame,     FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(gui_application_main_vbox), gui_application_programming_frame, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui_application_main_vbox), gui_application_utils_frame,       FALSE, FALSE, 0) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(gui_application_notebook), gui_application_main_vbox, gtk_label_new( _("Predefined applications") )) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(gui_application_notebook), gui_application_others_main_vbox, gtk_label_new( _("User defined applications")  )) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), gui_application_notebook, gtk_label_new( _("Applications")  )) ;







  GtkWidget *gui_configuration_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(gui_configuration_vbox), 5) ;


  GtkWidget *gui_sidebar_factor_frame       = gtk_frame_new( _("Sidebar terminals width") ) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_sidebar_factor_frame),       FRAME_BORDER_SIZE) ;


  GtkWidget *gui_sidebar_factor_vbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_sidebar_factor_vbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(gui_sidebar_factor_vbox), 5) ;

  GtkWidget *gui_sidebar_factor_label  = gtk_label_new( _("Main interface and Terminals-sidebar ratio:") ) ;

  gtk_label_set_justify(GTK_LABEL(gui_sidebar_factor_label), GTK_JUSTIFY_LEFT);

  GtkWidget *gui_sidebar_factor_spinbutton  = gtk_spin_button_new_with_range(0.0, 1.0, 0.001) ;


  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(gui_sidebar_factor_spinbutton), 3) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(gui_sidebar_factor_spinbutton), TRUE) ;

  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(gui_sidebar_factor_spinbutton), GTK_UPDATE_IF_VALID) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_sidebar_factor_spinbutton), settings.side_terms_factor) ;


  gtk_box_pack_start(GTK_BOX(gui_sidebar_factor_vbox), gui_sidebar_factor_label     , FALSE, FALSE,  5) ;

  gtk_box_pack_start(GTK_BOX(gui_sidebar_factor_vbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0), TRUE, TRUE, 0) ;

  gtk_box_pack_start(GTK_BOX(gui_sidebar_factor_vbox), gui_sidebar_factor_spinbutton, FALSE, FALSE, 5) ;


  gtk_container_add(GTK_CONTAINER(gui_sidebar_factor_frame), gui_sidebar_factor_vbox) ;




  GtkWidget *startup_settings_frame = gtk_frame_new( _("Settings at start") ) ;

  gtk_container_set_border_width(GTK_CONTAINER(startup_settings_frame),     FRAME_BORDER_SIZE) ;

  GtkWidget *startup_settings_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;



  GtkWidget *startup_show_terminals_sidebar_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *show_terminals_sidebar_checkbutton = generate_checkbuton(startup_show_terminals_sidebar_hbox, _("Show Terminals-sidebar at start ?"), settings.side_terms_on) ;

  GtkWidget *startup_show_big_term_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *show_big_term_checkbutton = generate_checkbuton(startup_show_big_term_hbox, _("Display Big-terminal at start ?"), settings.big_term_on) ;

  GtkWidget *startup_big_term_divided_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *show_big_term_divided_checkbutton = generate_checkbuton(startup_big_term_divided_hbox, _("Divide Big-terminal in 4 at start ?"), settings.big_term_div) ;

  GtkWidget *startup_show_buttonbar_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *show_buttonbar_checkbutton = generate_checkbuton(startup_show_buttonbar_hbox, _("Show buttonbar at start ?"), settings.buttonbar_on) ;

  GtkWidget *startup_toggle_fullscreen_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *show_fullscreen_checkbutton = generate_checkbuton(startup_toggle_fullscreen_hbox, _("Toggle to fullscreen at start ?"), settings.fullscreen) ;


  gtk_box_pack_start(GTK_BOX(startup_settings_vbox), startup_show_terminals_sidebar_hbox, TRUE, TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(startup_settings_vbox), startup_show_big_term_hbox,          TRUE, TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(startup_settings_vbox), startup_big_term_divided_hbox,       TRUE, TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(startup_settings_vbox), startup_show_buttonbar_hbox,         TRUE, TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(startup_settings_vbox), startup_toggle_fullscreen_hbox,      TRUE, TRUE, 5) ;


  gtk_container_add(GTK_CONTAINER(startup_settings_frame), startup_settings_vbox) ;


  GtkWidget *gui_set_as_default_frame       = gtk_frame_new( _("Set as default editor") ) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_set_as_default_frame),       FRAME_BORDER_SIZE) ;

  GtkWidget *gui_set_as_default_vbox  = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_set_as_default_vbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(gui_set_as_default_vbox), 5) ;

  GtkWidget *gui_set_as_default_button = gtk_button_new_with_label( _("Set it-edit as default editor") ) ;

  GtkWidget *gui_set_as_default_reset_button = gtk_button_new_with_label( _("Reset to default") ) ;

  gtk_box_pack_start(GTK_BOX(gui_set_as_default_vbox), gui_set_as_default_button,       TRUE, TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui_set_as_default_vbox), gui_set_as_default_reset_button, TRUE, TRUE, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_set_as_default_button),       5) ;
  gtk_container_set_border_width(GTK_CONTAINER(gui_set_as_default_reset_button), 5) ;

  g_signal_connect(G_OBJECT(gui_set_as_default_button),       "clicked", G_CALLBACK(set_as_default), NULL) ;
  g_signal_connect(G_OBJECT(gui_set_as_default_reset_button), "clicked", G_CALLBACK(reset_default), NULL) ;

  gtk_container_add(GTK_CONTAINER(gui_set_as_default_frame), gui_set_as_default_vbox) ;




  GtkWidget *gui_launch_cmd_frame       = gtk_frame_new( _("Launch command at start") ) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_launch_cmd_frame),       FRAME_BORDER_SIZE) ;

  GtkWidget *gui_launch_cmd_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_launch_cmd_vbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(gui_launch_cmd_vbox), 5) ;

  GtkWidget *gui_launch_cmd_label = gtk_label_new( _("Launch command in terminals at start:") ) ;

  GtkWidget *gui_launch_cmd_entry = gtk_entry_new() ;

  if (settings.command != NULL) {

    gtk_entry_set_text(GTK_ENTRY(gui_launch_cmd_entry), settings.command) ;
  }

  GtkWidget *gui_launch_cmd_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  gtk_box_pack_start(GTK_BOX(gui_launch_cmd_hbox), gui_launch_cmd_entry, TRUE, TRUE, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui_launch_cmd_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(gui_launch_cmd_vbox), gui_launch_cmd_label, FALSE, FALSE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui_launch_cmd_vbox), gui_launch_cmd_hbox,  FALSE, FALSE, 5) ;

  gtk_container_add(GTK_CONTAINER(gui_launch_cmd_frame), gui_launch_cmd_vbox) ;


  GtkWidget *separator3_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *separator3 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL) ;


  gtk_box_pack_start(GTK_BOX(separator3_vbox), separator3, FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(separator3_vbox), 5) ;








  gtk_box_pack_start(GTK_BOX(gui_configuration_vbox), gui_sidebar_factor_frame,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui_configuration_vbox), startup_settings_frame,           FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui_configuration_vbox), gui_launch_cmd_frame,             TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(gui_configuration_vbox), gui_set_as_default_frame,         TRUE,  TRUE,  0) ;



  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), gui_configuration_vbox, gtk_label_new( _("Settings") )) ;



  gtk_widget_show_all(configuration_dialog) ;

  gint result = gtk_dialog_run(GTK_DIALOG(configuration_dialog));
  switch (result) {

      case GTK_RESPONSE_APPLY :


          if (settings.editor_font != NULL) {
            free(settings.editor_font) ;
          }

          settings.editor_font = g_strdup(gtk_font_button_get_font_name(GTK_FONT_BUTTON(font_colors_button)) ) ;

          settings.display_line_numbers = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_lines_checkbutton))     ;
          settings.display_tabs_chars   = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_tabs_checkbutton))      ;
          settings.use_auto_indent      = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(auto_indent_checkbutton))    ;
          settings.indent_width         = (gint) gtk_spin_button_get_value(GTK_SPIN_BUTTON(indent_width_spinbutton))  ;
          settings.use_spaces_as_tabs   = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(use_spaces_instead_of_tabs)) ;
          settings.tabs_width           = (gint) gtk_spin_button_get_value(GTK_SPIN_BUTTON(tabs_width_spinbutton))    ;
          settings.backup_file          = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_file_checkbutton))    ;

          if (settings.term_font != NULL) {
            free(settings.term_font) ;
          }

          settings.term_font = g_strdup(gtk_font_button_get_font_name(GTK_FONT_BUTTON(terminal_font_colors_button))) ;

          if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_block_radiobutton))  ) {
            settings.cursor_shape = 0 ;
          }
          else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_ibeam_radiobutton))  ) {
            settings.cursor_shape = 1 ;
          }
          else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_underline_radiobutton))  ) {
            settings.cursor_shape = 2 ;
          }

          /** Colors settings: **/
          GdkRGBA term_bg ;
          gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_bg_color_button), &term_bg);

          if (settings.term_bg != NULL) {
            free(settings.term_bg) ;
          }

          settings.term_bg = g_strdup_printf("#%02x%02x%02x", (int) (term_bg.red * 255.0) , (int) (term_bg.green * 255.0), (int) (term_bg.blue * 255.0) ) ;

          GdkRGBA term_fg ;
          gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_fg_color_button), &term_fg);

          if (settings.term_fg != NULL) {
            free(settings.term_fg) ;
          }

          settings.term_fg = g_strdup_printf("#%02x%02x%02x", (int) (term_fg.red * 255.0) , (int) (term_fg.green * 255.0) , (int) (term_fg.blue * 255.0) ) ;


          /** Terminals settings **/
          if (settings.user_shell != NULL) {
            g_free(settings.user_shell) ;
          }

          settings.user_shell        = g_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(user_shell_file_chooser_button))) ;


          if (settings.start_dir != NULL) {
            g_free(settings.start_dir)  ;
          }

          settings.start_dir         = g_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(start_directory_file_chooser_button))) ;



          settings.scrollback_lines  = ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scrollback_lines_unlimited)) == TRUE) ? -1 : gtk_spin_button_get_value(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner))) ;

          settings.scroll_on_output     = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scroll_on_output_checkbutton)) ;
          settings.scroll_on_keystroke  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scroll_on_keystroke_checkbutton)) ;


          settings.backspace_binding    = gtk_combo_box_get_active(GTK_COMBO_BOX(erasing_backspace_binding_combo)) ;
          settings.delete_binding       = gtk_combo_box_get_active(GTK_COMBO_BOX(erasing_delete_binding_combo)) ;

          if (settings.command != NULL) {
            g_free(settings.command) ;
          }

          settings.command              = g_strdup(gtk_entry_get_text(GTK_ENTRY(gui_launch_cmd_entry))) ;
   
          settings.font_scale           = gtk_spin_button_get_value(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton))   ;
   
          settings.cursor_blink         = gtk_combo_box_get_active(GTK_COMBO_BOX(terminal_cursor_blinking_combo)) ;

          settings.bold_allow           = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(terminal_bold_allowed_checkbutton)) ;
   
   
          if (*bold_color_activated) {
   
            if (settings.bold_color != NULL) {
       
              g_free(settings.bold_color) ;
            }
     
            GdkRGBA bold_color ;
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_bold_color_button), &bold_color) ;
     
            settings.bold_color= g_strdup_printf("#%02x%02x%02x", (int) (bold_color.red * 255.0) , (int) (bold_color.green * 255.0), (int) (bold_color.blue * 255.0) ) ;
   
          }
   
 
   
          if (*cursor_color_activated) {
   
            if (settings.cursor_color != NULL) {
       
              g_free(settings.cursor_color) ;
            }
     
            GdkRGBA cursor_color ;
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_cursor_color_button), &cursor_color) ;
     
            settings.cursor_color = g_strdup_printf("#%02x%02x%02x", (int) (cursor_color.red * 255.0) , (int) (cursor_color.green * 255.0), (int) (cursor_color.blue * 255.0) ) ;
   
          }
   
     
   
          free(bold_color_activated) ;
          free(cursor_color_activated) ;
     
   
   
   
   
     

          settings.side_terms_factor = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_sidebar_factor_spinbutton)) ;

          settings.side_terms_on = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_terminals_sidebar_checkbutton)) ;

          settings.big_term_on   = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_big_term_checkbutton)) ;

          settings.buttonbar_on  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_buttonbar_checkbutton)) ;

          settings.fullscreen    = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_fullscreen_checkbutton)) ;

          settings.big_term_div  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_big_term_divided_checkbutton)) ;



          set_applications(gui_app.diff,         gui_application_programming_diff_chooser) ;
          set_applications(gui_app.debugger,     gui_application_programming_debugger_chooser) ;
          set_applications(gui_app.python,       gui_application_programming_python_chooser) ;
          set_applications(gui_app.gui_designer, gui_application_programming_gui_designer_chooser) ;
          set_applications(gui_app.devhelp,      gui_application_programming_devhelp_chooser) ;


          set_applications(gui_app.calculator,   gui_application_utils_calculator_chooser) ;
          set_applications(gui_app.color_picker, gui_application_utils_color_picker_chooser) ;
          set_applications(gui_app.dictionary,   gui_application_utils_dictionary_chooser) ;
          set_applications(gui_app.file_manager, gui_application_utils_file_manager_chooser) ;
          set_applications(gui_app.notes,        gui_application_utils_notes_chooser) ;
          set_applications(gui_app.browser,      gui_application_utils_browser_chooser) ;




          gtk_widget_destroy(configuration_dialog) ;

          /** Write settings to configuration file. **/
          write_changes_to_conf_file() ;
          write_changes_to_app_file() ;


          change_applications(gui_app.diff,         gui->menu->app_programming_diff) ;
          change_applications(gui_app.debugger,     gui->menu->app_programming_debugger) ;
          change_applications(gui_app.python,       gui->menu->app_programming_python) ;
          change_applications(gui_app.gui_designer, gui->menu->app_programming_gui_designer) ;
          change_applications(gui_app.devhelp,      gui->menu->app_programming_devhelp) ;

          change_applications(gui_app.calculator,   gui->menu->app_utils_calculator) ;
          change_applications(gui_app.color_picker, gui->menu->app_utils_color_picker) ;
          change_applications(gui_app.dictionary,   gui->menu->app_utils_dictionary) ;
          change_applications(gui_app.file_manager, gui->menu->app_utils_file_manager) ;
          change_applications(gui_app.notes,        gui->menu->app_utils_notes) ;
          change_applications(gui_app.browser,      gui->menu->app_utils_browser) ;


          /** Editor changes application. **/
          apply_editor_change() ;
  
          /** Terminals changes application. **/
          apply_terminal_change() ;

          while (gtk_events_pending()) {
             /** Waiting for configuration changes completion. **/
             gtk_main_iteration() ;
          }



          break;

      case GTK_RESPONSE_CANCEL :

         gtk_widget_destroy(configuration_dialog) ;
         break;

      default:

         gtk_widget_destroy(configuration_dialog) ;
         break;
    }


  return ;

}