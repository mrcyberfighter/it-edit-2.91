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

#include "editor_callbacks.h"


inline void update_page_number(GtkWidget *notebook) {

  /** Update the page number data from the tab_button. **/

  int nb_page = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook)) ;

  int c ;

  for (c=0 ; c < nb_page ; c++) {

    GtkWidget *notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), c) ;

    GtkWidget *tab_hbox = gtk_notebook_get_tab_label(GTK_NOTEBOOK(notebook), notebook_page) ;


    GList *tab_child = gtk_container_get_children(GTK_CONTAINER(tab_hbox)) ;

    GList *node = g_list_nth(tab_child, 3) ;


    GtkWidget *tab_button = (GtkWidget *) node->data ;


    gint *page_number = g_object_get_data(G_OBJECT(tab_button), "page_number") ;

    *page_number = c ;

    g_object_set_data(G_OBJECT(tab_button), "page_number", page_number) ;

  }

  return ;

}

void close_page(GtkButton *button, void *user_data) {
    /** Close a file by removing it from the notebook and recompute the page_number for bigger value thant the page to close. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  /** Getting the page number: **/
  gint *page_number = (gint *) g_object_get_data(G_OBJECT(button), "page_number") ;

  /**  Getting the notebook page, textview and buffer **/
  GtkWidget *notebook_page      = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), *page_number) ;
  GtkWidget *current_textview   = gtk_bin_get_child(GTK_BIN(notebook_page)) ;

  free(g_object_get_data(G_OBJECT(gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_textview))), "filepath")) ;



  File_Editor *file_editor = (File_Editor *) g_object_get_data(G_OBJECT(current_textview), "file_editor") ;

  #ifdef RELOADING_FUNC
  /** Remove the timeout associated with the current editor. **/
  file_editor->timeout_return = FALSE ;
  check_file_has_change(file_editor) ;
  #endif

  if ( g_object_get_data(G_OBJECT(file_editor->textview),   "highlight_textview_selection") ) {
    free(g_object_get_data(G_OBJECT(file_editor->textview), "highlight_textview_selection")) ;
  }

  free(file_editor) ;

  gtk_notebook_remove_page(GTK_NOTEBOOK(gui->editor_notebook), *page_number );


  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

  if (number_of_pages == 0) {

    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->current_row_col), _("Line: 0 ; Column: 0 ;") ) ;
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->total_rows_cols), _("Total lines: 0 ; Total chars: 0 ;") ) ;
    gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), "") ;


    if (open_file_dirname != NULL) {
      free(open_file_dirname) ;
    }

    open_file_dirname = g_strdup(g_get_home_dir()) ;

    free(page_number) ;

    return  ;

  }

  int c ;

  char *dirpath[number_of_pages] ;
  int   dirpath_counter[number_of_pages] ;


  for (c=0 ; c < number_of_pages ; c++) {
    /** Update the page number stored as data **/

    GtkWidget *notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;

    GtkWidget *textview      = gtk_bin_get_child(GTK_BIN(notebook_page)) ;

    dirpath[c] = g_strdup_printf("%s", g_path_get_dirname(g_object_get_data(G_OBJECT(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview))), "filepath")) ) ;

    dirpath_counter[c] = 1 ;



  }

  update_page_number(gui->editor_notebook) ;

  /** Compute the best value to set as file selector start folder. **/
  for (c=0 ; c < number_of_pages ; c++) {
    int cc ;
    for (cc=number_of_pages-1 ; cc > c ; cc--) {
      if (strcmp(dirpath[c], dirpath[cc]) == 0) {
        dirpath_counter[c]++ ;
      }
    }
  }

  int max   = 0 ;
  int index = 0 ;

  for (c=0 ; c < number_of_pages ; c++) {
     if (dirpath_counter[c] >= max) {
       max=dirpath_counter[c] ;
       index = c ;
     }
  }

  /** Storing best last opened file folder. **/

  if (open_file_dirname != NULL) {
    free(open_file_dirname) ;
  }

  open_file_dirname = g_strdup_printf("%s", dirpath[index]) ;

  for (c=0 ; c < number_of_pages ; c++) {
    free(dirpath[c]) ;
  }


  free(page_number) ;

  return  ;

}

void change_current_page(GtkNotebook *notebook, GtkWidget *page, guint page_num, gpointer user_data) {
  /** Change notebook page callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Getting current notebook page editor. **/
  current_editor.current_notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), page_num) ;
  current_editor.current_textview      = gtk_bin_get_child(GTK_BIN(current_editor.current_notebook_page)) ;
  current_editor.current_buffer        = gtk_text_view_get_buffer(GTK_TEXT_VIEW(current_editor.current_textview)) ;

  reset_search() ;

  /** Getting the search contexts **/
  searching.source_search_steps_context     = (GtkSourceSearchContext  *) g_object_get_data(G_OBJECT(current_editor.current_textview), "source_search_steps_context") ;
  searching.source_search_highlight_context = (GtkSourceSearchContext  *) g_object_get_data(G_OBJECT(current_editor.current_textview), "source_search_highlight_context") ;

  gtk_source_search_context_set_highlight(searching.source_search_steps_context, FALSE) ;

  gpointer filepath = g_object_get_data(G_OBJECT(current_editor.current_buffer), "filepath") ;

  gtk_label_set_text(GTK_LABEL(gui->bottom_bar->filename_label), g_path_get_basename(filepath)) ;

  set_syntax_highlight_radio( (const char *) g_object_get_data(G_OBJECT(current_editor.current_textview), "lang_id") ) ;

  if (filepath != NULL) {

    if (open_file_dirname != NULL) {
      g_free(open_file_dirname) ;
    }

    open_file_dirname = g_strdup(g_path_get_dirname(filepath)) ;
  }

  // TODO: Check if it's right !
  gtk_widget_grab_focus(current_editor.current_textview) ;

  return ;

}

void page_reorder(GtkNotebook *notebook, GtkWidget   *child, guint page_num, gpointer user_data) {

  /** Page-reordering callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  update_page_number(GTK_WIDGET(notebook)) ;

  return ;

}


void update_completion(GtkTextBuffer *textbuffer, gpointer user_data) {
  /** Completion updating callback. **/

  /** @NOTE: actual i can implement only one completion object per notebook page.
             In other words, i cannot merge the datas from the differents open files to feed only one general completion object.
             What would be better if you work with multiples files on a same project.
  ******************************************************************************************************************************/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** I have read the update is automatic:

  GtkSourceCompletion *source_completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(user_data)) ;

  GtkSourceCompletionWords *source_completion_words = gtk_source_completion_words_new("completion", NULL) ;

  gtk_source_completion_words_register(source_completion_words, GTK_TEXT_BUFFER(textbuffer)) ;

  gtk_source_completion_add_provider(source_completion, GTK_SOURCE_COMPLETION_PROVIDER(source_completion_words), NULL) ;

  g_object_set(G_OBJECT(source_completion_words), "scan-batch-size", gtk_text_buffer_get_line_count(textbuffer), NULL) ;

  */


  return ;

}


void update_rows_cols_info(GtkWidget *widget, GdkEvent  *event, gpointer user_data) {

  /** Update the file editor bottom bar by updating
    * -) The cursor position line and column
    * -) The total number of lines and characters.
    * This function is called at the end from every event: very often.
    ******************************************************************/



  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkTextIter main_iter ;

  GtkTextBuffer *textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));

  /** Getting cursor position. **/
  GtkTextMark *mark         = gtk_text_buffer_get_insert(textbuffer) ;

  gtk_text_buffer_get_iter_at_mark(textbuffer, &main_iter, mark);

  GtkTextIter *rows_iter    =  gtk_text_iter_copy(&main_iter) ;
  GtkTextIter *cols_iter    =  gtk_text_iter_copy(&main_iter) ;

  /** Setting up the current cursor position line and column numbers label text **/
  char *current_row_col_text ;
  current_row_col_text = g_strdup_printf( _("Line: %d ; Column: %d ;"), gtk_text_iter_get_line(rows_iter), gtk_text_iter_get_line_offset(cols_iter) ) ;
  gtk_label_set_text(GTK_LABEL(gui->bottom_bar->current_row_col), current_row_col_text) ;


  /** Setting up the current total number of lines and characters label text . **/
  char *total_rows_cols_text ;
  total_rows_cols_text = g_strdup_printf( _("Total lines: %d ; Total chars: %d ;"), gtk_text_buffer_get_line_count(textbuffer)-1, gtk_text_buffer_get_char_count(textbuffer) ) ;
  gtk_label_set_text(GTK_LABEL(gui->bottom_bar->total_rows_cols), total_rows_cols_text) ;


  free(current_row_col_text)   ;
  free(total_rows_cols_text)   ;

  gtk_text_iter_free(rows_iter) ;
  gtk_text_iter_free(cols_iter) ;

  GtkTextIter start_iter ;
  GtkTextIter end_iter ;



  gtk_text_buffer_get_start_iter(textbuffer, &start_iter);

  gtk_text_buffer_get_end_iter(textbuffer, &end_iter);

  /** This is a very slow operation so we take care about how often we execute this function (but unfortunatly needed @here). **/
  gtk_source_buffer_ensure_highlight(GTK_SOURCE_BUFFER(textbuffer), &start_iter, &end_iter) ;

  /** MSG:

      Maybe a bad idea by a loop ending ?

 
  while (gtk_events_pending()) {

   gtk_main_iteration();

  }

  */

  return  ;
}


void textbuffer_changed_modified(GtkTextBuffer *textbuffer, GtkWidget *tab_label) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Display an asterix next to the notebook page tab label if the editor content has change and has not be saved.
    * To mark that the editor content is not saved.
    ***************************************************************************************************************/
  if (gtk_text_buffer_get_modified(textbuffer)) {
      /** The editor content has change: **/

      /** Getting current notebook page filename. **/
      gpointer filepath = g_object_get_data(G_OBJECT(textbuffer), "filepath") ;

      /** Getting the current notebook page tab text. **/
      const char *tab_label_text = gtk_label_get_text(GTK_LABEL(tab_label)) ;

      if (tab_label_text[0] == '*') {
          /** The tab is already mark as changed with an asterix. **/
          remove_searching_tag() ;
          return ;
      }
      else {

          /** We must set the tab text without asterix. **/

          if (g_strcmp0(tab_label_text,"New") == 0 ) {
              /** The default New named file. **/

              gtk_label_set_text(GTK_LABEL(tab_label),"*New") ;

              remove_searching_tag() ;
              return ;
          }
          else {
              /** File opened in the program. **/

              char *tab_label_text ;
              tab_label_text = g_strdup_printf("*%s", g_path_get_basename(filepath)) ;
              gtk_label_set_text(GTK_LABEL(tab_label), tab_label_text) ;
              free(tab_label_text) ;

              remove_searching_tag() ;
              return ;
          }

      }

  }
  else {
    /** The file is marked with the not-modfied flag, even last save or at save time without changes. **/

    /** We must erase the asterix marker from the filename tab component **/

    /** Getting current notebook page filename. **/
    gpointer filepath = g_object_get_data(G_OBJECT(textbuffer), "filepath") ;

    /** Getting the current notebook page tab text. **/
    const char *tab_label_text = gtk_label_get_text(GTK_LABEL(tab_label)) ;

    if (tab_label_text[0] == '*') {
        /** The tab is mark as changed with an asterix. **/

        if (g_strcmp0(tab_label_text,"*New") == 0 ) {
              /** The default New named file. **/

              gtk_label_set_text(GTK_LABEL(tab_label),"New") ;

              remove_searching_tag() ;
              return ;

         }
        else {
          /** File opened in the program. **/

          char *tab_label_text ;
          tab_label_text  = g_strdup(g_path_get_basename(filepath)) ;
          gtk_label_set_text(GTK_LABEL(tab_label),tab_label_text) ;
          free(tab_label_text) ;

          remove_searching_tag() ;
          return ;
       }

    }

  }




  while (gtk_events_pending()) {

   gtk_main_iteration();

  }

  return  ;

}

gboolean textview_button_release_event(GtkWidget *textview, GdkEvent  *event, gpointer   user_data) {
  /** Function to set the selected text matches highlight off. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkTextBuffer *textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)) ;

  gboolean get_selection = FALSE ;

  g_object_get(G_OBJECT(textbuffer), "has-selection", &get_selection, NULL) ;

  if (get_selection) {
    highlight_selection(GTK_TEXT_VIEW(textview)) ;
  }
  else {
    destroy_highlight_selection() ;
  }

  return FALSE ; /** Continue event propagation to other handlers **/

}

gboolean textview_button_press_event(GtkWidget *textview, GdkEvent  *event, gpointer   user_data) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(textview), FALSE) ; /** Case by go to line function line highlighting. **/

  /** Function to set the selected text matches highlight off. **/

  GtkTextBuffer *textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)) ;

  gboolean get_selection = FALSE ;

  g_object_get(G_OBJECT(textbuffer), "has-selection", &get_selection, NULL) ;

  if (! get_selection) {

    destroy_highlight_selection() ;

    remove_searching_tag() ;

  }

  return FALSE ; /** Continue event propagation to other handlers **/
}

void switch_spaces_tabs(GtkWidget *widget, gboolean *switcher) {

  /** Switch use of tabs callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(widget)) ;

  int c ;

  for (c=0 ; c < number_of_pages ; c++) {

    GtkWidget *notebook_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(widget), c) ;

    GtkWidget *sourceview    = gtk_bin_get_child(GTK_BIN(notebook_page)) ;

    gtk_source_view_set_insert_spaces_instead_of_tabs(GTK_SOURCE_VIEW(sourceview), *switcher) ;

  }

  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(widget)) <= 0) {

    return ;
  }

  GtkWidget *sourceview = gtk_bin_get_child(GTK_BIN(gtk_notebook_get_nth_page(GTK_NOTEBOOK(widget), gtk_notebook_get_current_page(GTK_NOTEBOOK(widget))))) ;

  gtk_widget_grab_focus(sourceview) ;

  return ;
}