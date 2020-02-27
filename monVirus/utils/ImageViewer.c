#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

static void button_triggered(GtkWidget *widget, gpointer data)
{
    //g_print("Nouveau message\n");
}

static void activate (GtkApplication* app,gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_box;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  /*button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window),button_box);

  button = gtk_button_new_with_label("Bonjour");
  g_signal_connect(button,"clicked", G_CALLBACK(button_triggered),window);
  gtk_container_add(GTK_CONTAINER(button_box),button);*/

  GdkPixbuf * pixbuf = gdk_pixbuf_new_from_file("../one-piece-1274390_1920.jpg",NULL);
  GdkPixbuf * pixbuf_resized = gdk_pixbuf_scale_simple(pixbuf,400,400,GDK_INTERP_BILINEAR);
  
  GtkWidget *image;
  image = gtk_image_new_from_pixbuf(pixbuf_resized);
  //gtk_container_add (GTK_CONTAINER (window), image);

  GtkWidget* grid = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget* previous = gtk_button_new_with_label("Précédant");
  GtkWidget* next = gtk_button_new_with_label("Suivant");

  gtk_grid_attach(GTK_GRID(grid),previous,0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid),next,1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid),image,0,0,10,10);
  
  //gtk_widget_show (image);
  //gtk_widget_show (window);`

  gtk_widget_show_all (window);
}

int main (int argc,char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}