#include <stdlib.h>
#include <string>
#include <gtk/gtk.h>
#include "rs232api2.h"
#include "rs232W_fn01.h"

    GtkWidget       *imagem1;
    GtkWidget       *imagem2;
    GtkWidget       *label3;

bool serial_stat = false;

void funcao_liga_led(GtkWidget *widget, gpointer label)
{
    char *str = new char[10];
    strcpy(str ,"PRNa\n");
if (serial_stat==true)
{
printf("LED - LIGADO\n");
gtk_image_set_from_file (GTK_IMAGE(imagem1), "led_Verm_Ligado.png" );
gtk_label_set_text(GTK_LABEL(label), "LED LIGADO");
EnviaStringRS232(str);
}else
{
gtk_label_set_text(GTK_LABEL(label3), "STATUS: Serial nao habilitada!");
printf("OPERACAO NAO PERMITIDA!\n");
}
}

void funcao_desliga_led(GtkWidget *widget, gpointer label)
{
    char *str = new char[10];
    strcpy(str ,"PRNb\n");
if (serial_stat==true)
{
printf("LED - DESLIGADO\n");
gtk_image_set_from_file (GTK_IMAGE(imagem1), "led_verm_Desligado.png" );
gtk_label_set_text(GTK_LABEL(label), "LED DESLIGADO");
EnviaStringRS232(str );
}else
{
gtk_label_set_text(GTK_LABEL(label3), "STATUS: Serial nao habilitada!");
printf("OPERACAO NAO PERMITIDA!\n");
}
}
void funcao_SAIR(GtkWidget *widget, gpointer label)
{
libera_serial();
gtk_main_quit();
}


void funcao_conectar_rs232(GtkWidget *widget,  gpointer label)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
serial_stat=true;
Inicia_Serial_Port(COM1, 8 , TWOSTOPBITS , EVENPARITY, 9600, 100);
gtk_label_set_text(GTK_LABEL(label), "RS-232-CONECTADA");
gtk_label_set_text(GTK_LABEL(label3), "STATUS: Serial habilitada!");
gtk_image_set_from_file (GTK_IMAGE(imagem2), "led_green_Ligado.png" );
    printf(" Toggle button acionado\n");
    }
    else
    {
serial_stat=false;
libera_serial();
gtk_label_set_text(GTK_LABEL(label), "RS-232-DESCONECTADA");
gtk_label_set_text(GTK_LABEL(label3), "STATUS: Serial nao habilitada!");
gtk_image_set_from_file (GTK_IMAGE(imagem2), "led_green_Desligado.png" );
    printf(" Toggle button liberado\n");
    }
}

int main (int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *button1_liga;
    GtkWidget       *button2_desliga;
    GtkWidget       *button3_sair;
    GtkWidget       *togglebutton1;
    GtkWidget       *label1;
    GtkWidget       *label2;

    gtk_init (&argc, &argv);
    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "glade_p_led_arduino4.glade", NULL); //Carrega as informações do projeto glade para o GtkBuilder

    window                  = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));       //Retorna o objeto Window, para mostrá-lo mais tarde
    button1_liga        = GTK_WIDGET(gtk_builder_get_object (builder, "button1"));   //Retorna o objeto button1, para mostrá-lo mais tarde
    button2_desliga = GTK_WIDGET(gtk_builder_get_object (builder, "button2"));   //Retorna o objeto button2, para mostrá-lo mais tarde
    button3_sair        = GTK_WIDGET(gtk_builder_get_object (builder, "button3"));   //Retorna o objeto button2, para mostrá-lo mais tarde
    togglebutton1   = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton1"));   //Retorna o objeto button2, para mostrá-lo mais tarde
    label1                      = GTK_WIDGET(gtk_builder_get_object (builder, "label1"));   //Retorna o objeto label1, para mostrá-lo mais tarde
    label2                      = GTK_WIDGET(gtk_builder_get_object (builder, "label2"));   //Retorna o objeto label1, para mostrá-lo mais tarde
    label3                      = GTK_WIDGET(gtk_builder_get_object (builder, "label3"));   //Retorna o objeto label1, para mostrá-lo mais tarde
    imagem1                 = GTK_WIDGET(gtk_builder_get_object (builder, "image1"));
    imagem2             = GTK_WIDGET(gtk_builder_get_object (builder, "image2"));

    gtk_window_set_title(GTK_WINDOW(window), "GTK - Piscando Leds no Arduino");
    gtk_builder_connect_signals (builder, NULL); //Conecta todos os eventos dentro do projeto do glade.
    g_object_unref (G_OBJECT (builder)); //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

    g_signal_connect(button1_liga,    "clicked",          G_CALLBACK(funcao_liga_led),     label1);
    g_signal_connect(button2_desliga, "clicked",          G_CALLBACK(funcao_desliga_led),  label1);
    g_signal_connect(button3_sair,    "clicked",          G_CALLBACK(funcao_SAIR),  NULL);
    g_signal_connect(togglebutton1 ,  "toggled",          G_CALLBACK(funcao_conectar_rs232),  label2);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",   G_CALLBACK(funcao_SAIR), G_OBJECT(window));
    gtk_widget_show_all(window);   //Mostra a janela com seus objetos
    gtk_main ();

    return 0;
}

