#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
//#include <ctime>
#include <gtk/gtk.h>


using namespace std;

    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *view_Rx;
    GtkWidget       *button1_clr;
    GtkWidget       *button_toggle_cnt;

    GtkTextBuffer   *buffer_rx;
    bool            toggle_on = false;
    bool            expose_on = false;

//**************************************************
static gboolean fn_CLR_Buffer(GtkWidget *widget , GtkTextBuffer *buffer)
{
    GtkTextIter start;
    GtkTextIter   end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_delete(buffer, &start,&end);
return TRUE;
}
//**************************************************
//**************************************************
static gboolean fn_CNT_rs232(GtkWidget *widget,  gpointer data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
        toggle_on = true;
    }
    else
    {
        toggle_on = false;
    }

return TRUE;
}
//**************************************************
//**************************************************
//**************************************************
static gboolean fn_UPD_buffer(  gpointer data)
{
    string linha;
    gchar *dados_buffer;

    GtkTextIter start;
    GtkTextIter   end;

    if (toggle_on == true)
    {
    gtk_text_buffer_get_start_iter(buffer_rx, &start);
    gtk_text_buffer_get_end_iter(buffer_rx, &end);
            linha.append("AGUARDANDO RESPOSTA DO ROBO:.....NENHUMA RESPOSTA!\n\n");
    gtk_text_buffer_insert(buffer_rx, &end, linha.c_str(), linha.size()-1 );
    }
 linha.clear();

return TRUE;
}
//**************************************************
//**************************************************
//**************************************************
//**************************************************

int main (int argc, char *argv[])
{
gtk_init (&argc, &argv);

    builder = gtk_builder_new();
    const gchar *title = "GTK_GLADE_TextView01.glade";
    gtk_builder_add_from_file (builder, title, NULL);

    window                      = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));
    gtk_window_set_title(GTK_WINDOW(window),title);

    view_Rx                     = GTK_WIDGET(gtk_builder_get_object (builder, "textview1"));
    button_toggle_cnt           = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton1"));
    button1_clr                 = GTK_WIDGET(gtk_builder_get_object (builder, "button1"));

    buffer_rx = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view_Rx));

    gtk_builder_connect_signals (builder, NULL);    //Conecta todos os eventos dentro do projeto do glade.
    g_object_unref (G_OBJECT (builder));            //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

    g_signal_connect(G_OBJECT(button1_clr)              , "clicked"         ,G_CALLBACK(fn_CLR_Buffer),           buffer_rx     );
    g_signal_connect(G_OBJECT(button_toggle_cnt)        , "toggled"         ,G_CALLBACK(fn_CNT_rs232) ,           NULL          );

g_timeout_add (200, fn_UPD_buffer , NULL );

g_signal_connect_swapped(G_OBJECT(window)       , "destroy"         ,G_CALLBACK(gtk_main_quit),          window);
gtk_widget_show_all(window);   //Mostra a janela com seus objetos
gtk_main ();

    return 0;
}


