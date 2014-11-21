/* example-start text text.c */

/* text.c */

#include <stdio.h>
#include <gtk/gtk.h>

/*
void text_toggle_editable (GtkWidget *checkbutton,
                           GtkWidget *text)
{
  gtk_text_set_editable(GTK_TEXT(text),
                        GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void text_toggle_word_wrap (GtkWidget *checkbutton,
                            GtkWidget *text)
{
  gtk_text_set_word_wrap(GTK_TEXT(text),
                         GTK_TOGGLE_BUTTON(checkbutton)->active);
}
*/

#define DESCRIBE_KEY_COMBO(KEYCOMBO, DESCRIPTION) \
  gtk_text_insert(GTK_TEXT(text), NULL, &color, NULL, KEYCOMBO, -1); \
  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, " - " DESCRIPTION "\n", -1);

void close_application( GtkWidget *widget,
                        gpointer   data )
{
       gtk_main_quit();
}

int main( int argc,
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *box1;
  GtkWidget *box2;
  GtkWidget *hbox;
  GtkWidget *button;
  GtkWidget *check;
  GtkWidget *separator;
  GtkWidget *table;
  GtkWidget *vscrollbar;
  GtkWidget *text;
  GdkColormap *cmap;
  GdkColor color;
  GdkFont *fixed_font;

  FILE *infile;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_POPUP);
  gtk_widget_set_usize (window, 1900, 1080);
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);
  gtk_signal_connect (GTK_OBJECT (window), "destroy",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_window_set_title (GTK_WINDOW (window), "Mike Help");
  gtk_container_set_border_width (GTK_CONTAINER (window), 0);


  box1 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box1);
  gtk_widget_show (box1);


  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
  gtk_widget_show (box2);


  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacing (GTK_TABLE (table), 0, 2);
  gtk_table_set_col_spacing (GTK_TABLE (table), 0, 2);
  gtk_box_pack_start (GTK_BOX (box2), table, TRUE, TRUE, 0);
  gtk_widget_show (table);

  /* Create the GtkText widget */
  text = gtk_text_new (NULL, NULL);
  gtk_text_set_editable (GTK_TEXT (text), TRUE);
  gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (text);

  /* Add a vertical scrollbar to the GtkText widget */
  vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
                    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (vscrollbar);

  /* Get the system color map and allocate the color red */
  cmap = gdk_colormap_get_system();
  color.red = 0xffff;
  color.green = 0;
  color.blue = 0;
  if (!gdk_color_alloc(cmap, &color)) {
    g_error("couldn't allocate color");
  }

  /* Load a fixed font */
  fixed_font = gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");

  /* Realizing a widget creates a window for it,
 *    * ready for us to insert some text */
  gtk_widget_realize (text);

  /* Freeze the text widget, ready for multiple updates */
  gtk_text_freeze (GTK_TEXT (text));

  /* Insert some colored text */
  //gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
  //                 "Supports ", -1);
  //gtk_text_insert (GTK_TEXT (text), NULL, &color, NULL,
  //                 "colored ", -1);

  gtk_text_insert(GTK_TEXT(text), NULL, &color, NULL, "Mike's How-To Use His Computer Guide!\n\n", -1);

  DESCRIBE_KEY_COMBO("Ctrl-F1", "Show this help. You found it!");

  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "\n*** So you are using a tiling window manager. There are multple workspaces, which fill a screen and have a layout. You can cycle through layouts with Alt-Space, and cycle through the windows with Alt-j and Alt-k. The rest is detailed here.\n\n", -1);

  DESCRIBE_KEY_COMBO("Alt-[0-9]", "Hit alt + some number n, to move to the nth workspace. Each workspace has different windows");
  DESCRIBE_KEY_COMBO("Alt-Shift-[0-9]", "Move the current window to the nth workspace");
  DESCRIBE_KEY_COMBO("Alt-Click+drag", "Remove the window from the layout so that it hovers, and move it around");
  DESCRIBE_KEY_COMBO("Alt-Left Click+drag", "Remove the window from the layout so that it hovers, and resize it");
  DESCRIBE_KEY_COMBO("Alt-t", "Re-add a floating window to the layout");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-C", "Close the currently highlighted window");
  DESCRIBE_KEY_COMBO("Alt-Space", "Toggle current workspace layout");
  DESCRIBE_KEY_COMBO("Alt-j", "Move to the next window in the workspace");
  DESCRIBE_KEY_COMBO("Alt-k", "Move to the previous window in the workspace");
  DESCRIBE_KEY_COMBO("Alt-Shift-j", "Move the current window forward in the layout");
  DESCRIBE_KEY_COMBO("Alt-Shift-k", "Move the current window backward in the layout");

  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "\n*** It doesn't ship with standard laptop display meters for things like sound and battery, so I made my own\n\n", -1);

  DESCRIBE_KEY_COMBO("Windows-Space", "Show the current battery level");
  DESCRIBE_KEY_COMBO("Windows-Volume Up", "Increase volume");
  DESCRIBE_KEY_COMBO("Windows-Volume Down", "Decrease volume");
  DESCRIBE_KEY_COMBO("Windows-Volume Mute", "Mute volume");
  DESCRIBE_KEY_COMBO("Windows-Brightness Up", "Increase brightness");
  DESCRIBE_KEY_COMBO("Windows-Brightness Down", "Decrease brightness");
  DESCRIBE_KEY_COMBO("Function-Brightness Off", "Disable laptop screen. This is hardware based, not software based, so I didn't code this myself and I can't change the key combos for it");

  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "\n*** Starting programs\n\n", -1);

  DESCRIBE_KEY_COMBO("Alt-P", "Run a command (usually to open a program). Autocompletes the command, hit enter to run it");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  DESCRIBE_KEY_COMBO("firefox", "...");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  DESCRIBE_KEY_COMBO("speed-dreams-2", "...");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  DESCRIBE_KEY_COMBO("xpdf", "PDF viewer");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  DESCRIBE_KEY_COMBO("openoffice.org", "Open source microsoft office clone");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  DESCRIBE_KEY_COMBO("VirtualBox", "Virtual machines. You can launch my windows vm from here");
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");
  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "what else do you want?\n", -1);
  DESCRIBE_KEY_COMBO("Ctrl-Shift-Enter", "Open a terminal (because terminals are awesome)");

  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "\n*** And then monitor settings can be changed by opening a terminal and running the following commands\n\n", -1);

  DESCRIBE_KEY_COMBO("tv", "Configure TV over hdmi");
  DESCRIBE_KEY_COMBO("newmonitor on", "Turn on monitor over hdmi with monitor settings");
  DESCRIBE_KEY_COMBO("newmonitor on 1080x1020", "Turn on monitor over hdmi with custom resolution");
  DESCRIBE_KEY_COMBO("screenblank off", "Disable screensaver");
  DESCRIBE_KEY_COMBO("screenblank on", "Enable screensaver");

  gtk_text_insert(GTK_TEXT(text), NULL, &text->style->black, NULL, "\n*** Random advice\n\n", -1);

  DESCRIBE_KEY_COMBO("Connect to wifi", "Open a terminal and run 'nmcli dev wifi list' to see available networks, then run 'nmcli dev wifi connect YourNetwork password YourPassword'");
  DESCRIBE_KEY_COMBO("vim", "Use vim.");

  /* Thaw the text widget, allowing the updates to become visible */
  gtk_text_thaw (GTK_TEXT (text));

  hbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (box2), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  /*
  check = gtk_check_button_new_with_label("Editable");
  gtk_box_pack_start (GTK_BOX (hbox), check, FALSE, FALSE, 0);
  gtk_signal_connect (GTK_OBJECT(check), "toggled",
                      GTK_SIGNAL_FUNC(text_toggle_editable), text);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
  gtk_widget_show (check);
  check = gtk_check_button_new_with_label("Wrap Words");
  gtk_box_pack_start (GTK_BOX (hbox), check, FALSE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT(check), "toggled",
                      GTK_SIGNAL_FUNC(text_toggle_word_wrap), text);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), FALSE);
  gtk_widget_show (check);
  */

  separator = gtk_hseparator_new ();
  gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 0);
  gtk_widget_show (separator);

  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
  gtk_widget_show (box2);

  button = gtk_button_new_with_label ("close");
  gtk_signal_connect (GTK_OBJECT (button), "clicked",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button);
  gtk_widget_show (button);

  gtk_widget_show (window);

  gtk_main ();

  return(0);
}
