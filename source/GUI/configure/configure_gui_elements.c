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
#include "./configure_gui_elements.h"

void setting_sourceview_settings(GtkSourceView *view) {
  /** Configure the GtkSourceView according to configuration. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gtk_source_view_set_auto_indent(view, settings.use_auto_indent) ;
  gtk_source_view_set_indent_on_tab(view, TRUE);
  gtk_source_view_set_indent_width(view, settings.indent_width) ;

  gtk_source_view_set_insert_spaces_instead_of_tabs(view, settings.use_spaces_as_tabs);
  /** FIXME: ??? gtk_source_view_set_smart_home_end(view, GTK_SOURCE_SMART_HOME_END_BEFORE) ;   ??? **/


  gtk_source_view_set_show_line_numbers(view, settings.display_line_numbers) ;

  gtk_source_view_set_tab_width(view, settings.tabs_width) ;

  if (settings.display_tabs_chars) {
    gtk_source_view_set_draw_spaces(view, GTK_SOURCE_DRAW_SPACES_TAB) ;
  }

  GtkCssProvider *provider = gtk_css_provider_new ();



  gchar *text_css = g_strconcat("GtkTextView {\n"
                                 "font : ",
                                 settings.editor_font,
                                 "}\n",
                                 NULL) ;

  gtk_css_provider_load_from_data(provider, text_css, -1, NULL) ;

  g_free(text_css) ;

  GdkDisplay *display = gdk_display_get_default() ;

  GdkScreen *screen = gdk_display_get_default_screen(display) ;

  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER) ;



  g_object_unref(provider) ;

  return ;
}




void configure_terminal(GtkWidget *vteterminal, bool initialize) {
  /** Configure the VteTerminal according to the configuration. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  vte_terminal_set_default_colors(VTE_TERMINAL(vteterminal)) ;

  /** Font settings: **/
  PangoFontDescription *font_desc = pango_font_description_from_string(settings.term_font) ;

  g_object_set(G_OBJECT(vteterminal), "font-desc", font_desc, NULL) ;

  vte_terminal_set_font_scale(VTE_TERMINAL(vteterminal),  settings.font_scale) ;


  /** Cursor settings: **/
  vte_terminal_set_cursor_shape(VTE_TERMINAL(vteterminal), (settings.cursor_shape == 0) ? VTE_CURSOR_SHAPE_BLOCK : (settings.cursor_shape == 1) ? VTE_CURSOR_SHAPE_IBEAM : VTE_CURSOR_SHAPE_UNDERLINE) ;

  vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(vteterminal), (settings.cursor_blink == 0) ? VTE_CURSOR_BLINK_SYSTEM : (settings.cursor_blink == 1) ? VTE_CURSOR_BLINK_ON : VTE_CURSOR_BLINK_OFF) ;

  vte_terminal_set_audible_bell(VTE_TERMINAL(vteterminal), settings.audible_bell) ;

  vte_terminal_set_mouse_autohide(VTE_TERMINAL(vteterminal), settings.pointer_autohide) ;

  /** Bold setting: **/

  vte_terminal_set_allow_bold(VTE_TERMINAL(vteterminal), settings.bold_allow) ;

  GdkRGBA bold_color ;
  gdk_rgba_parse(&bold_color, settings.bold_color) ;
  vte_terminal_set_color_bold(VTE_TERMINAL(vteterminal), &bold_color) ;



  /** Erasing keys binding. **/
  g_object_set(G_OBJECT(vteterminal), "backspace-binding", (settings.backspace_binding == 0) ? VTE_ERASE_AUTO :
                                                           (settings.backspace_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                           (settings.backspace_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                           (settings.backspace_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                               VTE_ERASE_TTY,
                                                           NULL) ;

  g_object_set(G_OBJECT(vteterminal), "delete-binding", (settings.delete_binding == 0) ? VTE_ERASE_AUTO :
                                                        (settings.delete_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                        (settings.delete_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                        (settings.delete_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                         VTE_ERASE_TTY,
                                                         NULL) ;



  /** Colors settings: **/
  GdkRGBA bg_terminal ;
  gdk_rgba_parse(&bg_terminal, settings.term_bg) ;
  GdkRGBA fg_terminal ;
  gdk_rgba_parse(&fg_terminal, settings.term_fg) ;

  vte_terminal_set_color_foreground(VTE_TERMINAL(vteterminal), &fg_terminal) ;

  vte_terminal_set_color_background(VTE_TERMINAL(vteterminal), &bg_terminal) ;


  /** Usual default settings: **/
  vte_terminal_set_scrollback_lines(VTE_TERMINAL(vteterminal),    settings.scrollback_lines) ;

  vte_terminal_set_scroll_on_output(VTE_TERMINAL(vteterminal),    settings.scroll_on_output) ;

  vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(vteterminal), settings.scroll_on_keystroke) ;

  if (initialize) {

    vte_terminal_set_encoding(VTE_TERMINAL(vteterminal), vte_terminal_get_encoding(VTE_TERMINAL(vteterminal)), NULL)  ;  // default

    /** Mouse left button double click word separators: The following characters are not register as word separators. **/
    vte_terminal_set_word_char_exceptions(VTE_TERMINAL(vteterminal), vte_terminal_get_word_char_exceptions(VTE_TERMINAL(vteterminal)) ) ;
 
    vte_terminal_set_rewrap_on_resize(VTE_TERMINAL(vteterminal), TRUE) ;
 
    vte_terminal_set_size(VTE_TERMINAL(vteterminal), 80, 24) ;

  }

  return ;
}

void apply_editor_change(void) {
  /** Apply changes to every noetbbok page. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gint number_of_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->editor_notebook)) ;

  int c ;
  for (c = 0 ; c < number_of_pages ; c++) {

    GtkWidget *notebook_child              = gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->editor_notebook), c) ;
    GtkWidget *current_textview            = gtk_bin_get_child(GTK_BIN(notebook_child)) ;

    setting_sourceview_settings(GTK_SOURCE_VIEW(current_textview)) ;
  }

  return ;

}

void apply_terminal_change(void) {

  gint page_nb = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) ;

  int c ;

  for (c=0 ; c < page_nb ; c++) {

    Terminals *terminals = g_object_get_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->terminal_notebook),c)), "terminals") ;

    configure_terminal(terminals->terminal_1->terminal, false) ;
    configure_terminal(terminals->terminal_2->terminal, false) ;
  }


  configure_terminal(gui->big_terminal->terminal, false) ;

  configure_terminal(gui->big_four_terminals->terminal_1->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_2->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_3->terminal, false) ;
  configure_terminal(gui->big_four_terminals->terminal_4->terminal, false) ;

  return ;
}