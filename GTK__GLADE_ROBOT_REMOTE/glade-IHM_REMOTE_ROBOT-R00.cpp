#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <string>

#include "rs232api2.h"
#include "rs232_cfg01.h"

/*
definições:
'6' --> +x
'4' --> -x
'8' --> +y
'2' --> -y
'Z' --> +z
'z' --> -z

'9' --> +x+y (1 quad.)
'7' --> -x+y (2 quad.)
'1' --> -x-y (3 quad.)
'3' --> +x-y (4 quad.)
*/

void click_x_pos(void)
{
string buffer="PRN6\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_x_neg(void)
{
string buffer="PRN4\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_y_pos(void)
{
string buffer="PRN8\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_y_neg(void)
{
string buffer="PRN2\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_z_pos(void)
{
string buffer="PRNZ\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_z_neg(void)
{
string buffer="PRN-Z\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}
void click_x_pos_y_pos(void)
{
string buffer="PRN9\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}

void click_x_neg_y_pos(void)
{
string buffer="PRN7\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}

void click_x_neg_y_neg(void)
{
string buffer="PRN1\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}

void click_x_pos_y_neg(void)
{
string buffer="PRN3\r";
EnviaStringRS232(buffer);
     buffer="PRN_COM1_ON_\r";
    EnviaStringRS232(buffer);
}


void Toggle_Botao01(GtkWidget *widget)
{
        string buffer="PRN_COM1_ON_\r";
 if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {printf("\nToggle ACIONADO");
    LeRS232Conf("RS232.conf");
    EnviaStringRS232(buffer);
    }else
    {printf("\nToggle DESACIONADO");
    libera_serial();
     buffer="PRN_COM1_OFF_\r";
    EnviaStringRS232(buffer);
     buffer="PRN_COM1_OFF_\r";
    EnviaStringRS232(buffer);
    }
}

void Sair_Programa(void)
{
   gtk_main_quit();
    libera_serial();
}
int main (int argc, char *argv[])
{
    char *event="pressed";
    GtkBuilder      *builder;
    GtkWidget       *window;

    GtkWidget       *buttonX_POS;
    GtkWidget       *buttonX_NEG;
    GtkWidget       *buttonY_POS;
    GtkWidget       *buttonY_NEG;
    GtkWidget       *buttonZ_POS;
    GtkWidget       *buttonZ_NEG;

    GtkWidget       *buttonX_POS_Y_POS; // 1º QUADRANTE
    GtkWidget       *buttonX_NEG_Y_POS; // 2º QUADRANTE
    GtkWidget       *buttonX_NEG_Y_NEG; // 3º QUADRANTE
    GtkWidget       *buttonX_POS_Y_NEG; // 4º QUADRANTE

    GtkWidget       *togglebutton1;
    GtkWidget       *button_sair;
    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();

    gtk_builder_add_from_file (builder, "glade06_Robot_Remote.glade", NULL); //Carrega as informações do projeto glade para o GtkBuilder
    window = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));       //Retorna o objeto Window, para mostrá-lo mais tarde
    gtk_window_set_title(GTK_WINDOW(window), "REMOTO-RS232");

 //   gtk_builder_connect_signals (builder, NULL); //Conecta todos os eventos dentro do projeto do glade.
    buttonX_POS   = GTK_WIDGET(gtk_builder_get_object(builder,"button6"));
    buttonX_NEG   = GTK_WIDGET(gtk_builder_get_object(builder,"button4"));
    buttonY_POS   = GTK_WIDGET(gtk_builder_get_object(builder,"button2"));
    buttonY_NEG   = GTK_WIDGET(gtk_builder_get_object(builder,"button8"));
    buttonZ_POS   = GTK_WIDGET(gtk_builder_get_object(builder,"button5"));
    buttonZ_NEG   = GTK_WIDGET(gtk_builder_get_object(builder,"button10"));

    buttonX_POS_Y_POS   = GTK_WIDGET(gtk_builder_get_object(builder,"button3"));
    buttonX_NEG_Y_POS   = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
    buttonX_NEG_Y_NEG   = GTK_WIDGET(gtk_builder_get_object(builder,"button7"));
    buttonX_POS_Y_NEG   = GTK_WIDGET(gtk_builder_get_object(builder,"button9"));

    togglebutton1 = GTK_WIDGET(gtk_builder_get_object(builder,"togglebuttonC"));
    button_sair   = GTK_WIDGET(gtk_builder_get_object(builder,"button13"));

    g_signal_connect(G_OBJECT(togglebutton1)        ,"toggled"     ,G_CALLBACK(Toggle_Botao01)  ,G_OBJECT(window));
    g_signal_connect(G_OBJECT(button_sair)          ,"clicked"     ,G_CALLBACK(Sair_Programa)   ,NULL);

    g_signal_connect(G_OBJECT(buttonX_POS)          ,event   ,G_CALLBACK(click_x_pos)           ,NULL);
    g_signal_connect(G_OBJECT(buttonX_NEG)          ,event   ,G_CALLBACK(click_x_neg)           ,NULL);
    g_signal_connect(G_OBJECT(buttonY_POS)          ,event   ,G_CALLBACK(click_y_pos)           ,NULL);
    g_signal_connect(G_OBJECT(buttonY_NEG)          ,event   ,G_CALLBACK(click_y_neg)           ,NULL);
    g_signal_connect(G_OBJECT(buttonZ_POS)          ,event   ,G_CALLBACK(click_z_pos)           ,NULL);
    g_signal_connect(G_OBJECT(buttonZ_NEG)          ,event   ,G_CALLBACK(click_z_neg)           ,NULL);

    g_signal_connect(G_OBJECT(buttonX_POS_Y_POS)    ,event   ,G_CALLBACK(click_x_pos_y_pos)     ,NULL);
    g_signal_connect(G_OBJECT(buttonX_NEG_Y_POS)    ,event   ,G_CALLBACK(click_x_neg_y_pos)     ,NULL);
    g_signal_connect(G_OBJECT(buttonX_NEG_Y_NEG)    ,event   ,G_CALLBACK(click_x_neg_y_neg)     ,NULL);
    g_signal_connect(G_OBJECT(buttonX_POS_Y_NEG)    ,event   ,G_CALLBACK(click_x_pos_y_neg)     ,NULL);

    g_object_unref (G_OBJECT (builder)); //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.
    gtk_widget_show_all(window);   //Mostra a janela com seus objetos
    gtk_main ();

    return 0;
}

