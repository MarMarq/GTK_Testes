#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
//#include <ctime>
#include <gtk/gtk.h>
#include "rs232api2.h"
#include "rs232W_fn01.h"
#include "file_manip01.h"

using namespace std;

    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *view_Tx;
    GtkWidget       *view_Rx;
    GtkWidget       *button_toggle_cnt;
    GtkWidget       *button_toggle_loop;
    GtkWidget       *button1_grv;
    GtkWidget       *button3_sair;
    GtkWidget       *button4_snd;
    GtkWidget       *button5_clr;
    GtkWidget       *button7_ins;
    GtkWidget       *button8_SAV;
    GtkWidget       *button2_RCF;
    GtkWidget       *button9_RPP;

    GtkWidget *hbox1_TX;
    GtkWidget *hbox5_RX;
    GtkWidget *hbox6_CFG;

    GtkTextBuffer   *buffer_tx;
    GtkTextBuffer   *buffer_rx;

    GtkComboBox     *cmb_porta;
    GtkComboBox     *cmb_taxa;
    GtkComboBox     *cmb_bytesize;
    GtkComboBox     *cmb_stopbits;
    GtkComboBox     *cmb_paridade;
    GtkComboBox     *cmb_timeout;

    GtkWidget       *imagem1;
    GtkWidget       *imagem2;
    GtkWidget       *imagem3;
    GtkWidget       *label4_stat;

        int PORTA;
        int DataBits;
        BYTE STOPBITS;
        BYTE PARIDADE;
        int TAXA;
        int timeout;
        BOOL ERRO;

    useconds_t tempo = 999000;
  unsigned int count=0;
string linha;
string rs_buffer;

BOOL serial_stat    = FALSE;
BOOL serial_nerro   = FALSE;
BOOL progam_start   = TRUE;
BOOL timer01        = FALSE;
time_t t0;
time_t t1;
double elapsed;

//**************************************************
static gboolean show_error01(void)
{
  GtkWidget *dialog;
  const char *message01 = "Erro ao iniciar a porta serial ";
  const char *message02 = "\nA porta ";
  const char *message03 = " se encontra instalada?";
  char str[4];

  if (PORTA==COM1) strcpy(str,"COM1");
  if (PORTA==COM2) strcpy(str,"COM2");
  if (PORTA==COM3) strcpy(str,"COM3");
  if (PORTA==COM4) strcpy(str,"COM4");

  char *message = new char[strlen(message01) + strlen(message02) + strlen(message03) + (2*strlen(str)) - 5 ];
  strcpy(message,message01);
  strcat(message,str);
  strcat(message,message02);
  strcat(message,str);
  strcat(message,message03);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            message );
  gtk_window_set_title(GTK_WINDOW(dialog), "Erro");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  return true;
}
//**************************************************
static gboolean show_error02(void)
{
  GtkWidget *dialog;

    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Porta serial DESABILITADA!!" );
  gtk_window_set_title(GTK_WINDOW(dialog), "Erro");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  return true;
}
//**************************************************
static gboolean show_error03(void)
{
  GtkWidget *dialog;

    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Tecla DESABILITADA!!" );
  gtk_window_set_title(GTK_WINDOW(dialog), "Erro");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  return true;
}
//**************************************************
static gboolean fn_REC_buffer(GtkWidget *widget, GtkTextBuffer *buffer)
{
        MANIPULA_ARQUIVO ponteiro;
        bool rf;
        gchar *dados_buffer;
        GtkTextIter start;
        GtkTextIter   end;
        const char *NomeArq = "dados.txt";

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    dados_buffer = gtk_text_buffer_get_text(buffer , &start , &end , TRUE);

    char *dados = new char [strlen(dados_buffer) ];
    strcpy( dados , dados_buffer );
    rf = ponteiro.EscreveArqASCII( NomeArq , dados );
  return rf;
}
//**************************************************
static gboolean fn_INS_Buffer(GtkWidget *widget , GtkTextBuffer *buffer)
{
        MANIPULA_ARQUIVO Ponteiro;
        string linha;
        GtkTextIter start;
        GtkTextIter   end;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    linha=Ponteiro.LeArqASCII("dados.txt");
    gtk_text_buffer_insert(buffer, &end, linha.c_str(), linha.size()-1 );

return TRUE;
}
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
static gboolean fn_SND_buffer(GtkWidget *widget, GtkTextBuffer *buffer)
{
        gchar *dados_buffer;
        GtkTextIter start;
        GtkTextIter   end;

    if (serial_stat == TRUE)
    {
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    dados_buffer = gtk_text_buffer_get_text(buffer , &start , &end , TRUE);

    char *dados = new char [strlen(dados_buffer) ];
    strcpy( dados , dados_buffer );
    EnviaStringRS232(dados);
    }else
    {
        show_error02();
    }
  return (BOOL)serial_stat;
}
//**************************************************
static gboolean fn_LOOP_SND(GtkWidget *widget, GtkTextBuffer *buffer)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
    show_error03();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
    }
  return true;
}
//**************************************************
void fn_CFG_rs232(void)
{
        int porta = gtk_combo_box_get_active (cmb_porta);
        int taxa  = gtk_combo_box_get_active (cmb_taxa);
        int bytes = gtk_combo_box_get_active (cmb_bytesize);
        int stopb = gtk_combo_box_get_active (cmb_stopbits);
        int parid = gtk_combo_box_get_active (cmb_paridade);
        int timeo = gtk_combo_box_get_active (cmb_timeout);

        int mult = 100;

        if (porta==0)  PORTA=COM1;
        if (porta==1)  PORTA=COM2;
        if (porta==2)  PORTA=COM3;
        if (porta==3)  PORTA=COM4;

        if (taxa==0)  TAXA=1200;
        if (taxa==1)  TAXA=2400;
        if (taxa==2)  TAXA=4800;
        if (taxa==3)  TAXA=9600;
        if (taxa==4)  TAXA=14400;
        if (taxa==5)  TAXA=19200;
        if (taxa==6)  TAXA=38400;
        if (taxa==7)  TAXA=56000;
        if (taxa==9)  TAXA=115200;

        if (bytes==0)  DataBits=8;
        if (bytes==1)  DataBits=7;
        if (bytes==2)  DataBits=6;
        if (bytes==3)  DataBits=5;
        if (bytes==4)  DataBits=4;

        if ( stopb==0)  STOPBITS=ONESTOPBIT;
        if ( stopb==1)  STOPBITS=ONE5STOPBITS;
        if ( stopb==2)  STOPBITS=TWOSTOPBITS;

        if ( parid==0)   PARIDADE=EVENPARITY;
        if ( parid==1)   PARIDADE=ODDPARITY;
        if ( parid==2)   PARIDADE=MARKPARITY;
        if ( parid==3)   PARIDADE=NOPARITY;

        if (timeo==0)  timeout=1*mult;
        if (timeo==1)  timeout=2*mult;
        if (timeo==2)  timeout=3*mult;
        if (timeo==3)  timeout=4*mult;
        if (timeo==4)  timeout=5*mult;
}
//**************************************************
void fn_CNT_rs232(GtkWidget *widget,  gpointer label)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
        printf(" Toggle button acionado\n");
        fn_CFG_rs232();

        if (Inicia_Serial_Port(PORTA, DataBits , STOPBITS , PARIDADE, TAXA, timeout ))
        {
        gtk_label_set_text(GTK_LABEL(label), "STATUS: Serial habilitada!");
        gtk_image_set_from_file (GTK_IMAGE(imagem3), "rsc/img/led_green_Ligado.png");
        serial_stat = TRUE;
        }else
        {
        serial_stat = FALSE;
        show_error01();
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
        }
    }
    else
    {
    libera_serial();
    serial_stat = FALSE;
    gtk_label_set_text(GTK_LABEL(label), "STATUS: Serial nao habilitada!");
    gtk_image_set_from_file (GTK_IMAGE(imagem3), "rsc/img/led_green_Desligado.png" );
    printf(" Toggle button liberado\n");
    }
}
//**************************************************
static gboolean fn_RCV_rs232(gpointer data)
{
//        gchar *dados_buffer;
        string linha;
        GtkTextIter start;
        GtkTextIter   end;

  char c;
  string rs_buffer;

    if(serial_stat)
    {
      if ( !recebe_caracter_serial(&c) )
        {
        rs_buffer+=c;
        linha.append(rs_buffer);
        gtk_text_buffer_get_start_iter(buffer_rx, &start);
        gtk_text_buffer_get_end_iter(buffer_rx, &end);
//        dados_buffer = gtk_text_buffer_get_text(buffer_rx , &start , &end , TRUE);
        gtk_text_buffer_insert(buffer_rx, &end, linha.c_str(), linha.size()-1 );
        }
        linha.clear();
    }
return TRUE;
}
//**************************************************
//**************************************************
//**************************************************
int main (int argc, char *argv[])
{
gtk_init (&argc, &argv);

    builder = gtk_builder_new();
    const gchar *title = "rsc/interface/GTK_GLADE_SERIAL_MSN03.glade";
    gtk_builder_add_from_file (builder, title, NULL);

    window                      = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));
    gtk_window_set_title(GTK_WINDOW(window),title);

    view_Tx                     = GTK_WIDGET(gtk_builder_get_object (builder, "textview1"));
    view_Rx                     = GTK_WIDGET(gtk_builder_get_object (builder, "textview2"));
    button_toggle_cnt           = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton1"));
    button_toggle_loop          = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton2"));
    button1_grv                 = GTK_WIDGET(gtk_builder_get_object (builder, "button1"));
    button2_RCF                 = GTK_WIDGET(gtk_builder_get_object (builder, "button2"));
    button3_sair                = GTK_WIDGET(gtk_builder_get_object (builder, "button3"));
    button4_snd                 = GTK_WIDGET(gtk_builder_get_object (builder, "button4"));
    button5_clr                 = GTK_WIDGET(gtk_builder_get_object (builder, "button5"));
    button7_ins                 = GTK_WIDGET(gtk_builder_get_object (builder, "button7"));
    button8_SAV                 = GTK_WIDGET(gtk_builder_get_object (builder, "button8"));
    button9_RPP                 = GTK_WIDGET(gtk_builder_get_object (builder, "button9"));
    label4_stat                 = GTK_WIDGET(gtk_builder_get_object (builder, "label4"));
    hbox1_TX                    = GTK_WIDGET(gtk_builder_get_object (builder, "hbox1"));
    hbox5_RX                    = GTK_WIDGET(gtk_builder_get_object (builder, "hbox5"));
    hbox6_CFG                   = GTK_WIDGET(gtk_builder_get_object (builder, "hbox6"));

    cmb_porta                   = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox1"));
    cmb_taxa                    = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox2"));
    cmb_bytesize                = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox3"));
    cmb_stopbits                = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox4"));
    cmb_paridade                = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox5"));
    cmb_timeout                 = GTK_COMBO_BOX(gtk_builder_get_object (builder, "combobox6"));

    imagem1 = gtk_image_new_from_file("rsc/img/led_verm_Desligado.png"   );
    imagem2 = gtk_image_new_from_file("rsc/img/led_yellow_Desligado.png" );
    imagem3 = gtk_image_new_from_file("rsc/img/led_green_Desligado.png" );

        gtk_container_add(GTK_CONTAINER(hbox1_TX),imagem1);
        gtk_container_add(GTK_CONTAINER(hbox5_RX),imagem2);
        gtk_container_add(GTK_CONTAINER(hbox6_CFG),imagem3);

    buffer_tx = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view_Tx));
    buffer_rx = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view_Rx));

    gtk_combo_box_set_active(   cmb_porta       ,   0   );
    gtk_combo_box_set_active(   cmb_taxa        ,   3   );
    gtk_combo_box_set_active(   cmb_bytesize    ,   0   );
    gtk_combo_box_set_active(   cmb_stopbits    ,   0   );
    gtk_combo_box_set_active(   cmb_paridade    ,   3   );
    gtk_combo_box_set_active(   cmb_timeout     ,   4   );

    gtk_builder_connect_signals (builder, NULL);    //Conecta todos os eventos dentro do projeto do glade.
    g_object_unref (G_OBJECT (builder));            //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

//    g_signal_connect(G_OBJECT(button2_cfg)          , "pressed"         ,G_CALLBACK(fn_CFG_rs232),           NULL);
//    g_signal_connect(G_OBJECT(button_toggle_loop)   , "toggled"         ,G_CALLBACK(fn_LOOP_SND),            buffer_tx);

    g_signal_connect(G_OBJECT(button1_grv)              , "clicked"         ,G_CALLBACK(fn_REC_buffer),           buffer_tx     );
    g_signal_connect(G_OBJECT(button4_snd)              , "clicked"         ,G_CALLBACK(fn_SND_buffer),           buffer_tx     );
    g_signal_connect(G_OBJECT(button5_clr)              , "clicked"         ,G_CALLBACK(fn_CLR_Buffer),           buffer_tx     );
    g_signal_connect(G_OBJECT(button7_ins)              , "clicked"         ,G_CALLBACK(fn_INS_Buffer),           buffer_tx     );
    g_signal_connect(G_OBJECT(button_toggle_cnt)        , "toggled"         ,G_CALLBACK(fn_CNT_rs232) ,           label4_stat   );
    g_signal_connect(G_OBJECT(button_toggle_loop)       , "toggled"         ,G_CALLBACK(fn_LOOP_SND) ,            NULL          );
//    g_signal_connect_swapped(G_OBJECT(window)           , "expose-event"    ,G_CALLBACK(fn_RCV_rs232) ,           buffer_rx     );

g_timeout_add (1, fn_RCV_rs232 , NULL );

g_signal_connect_swapped(G_OBJECT(window)       , "destroy"         ,G_CALLBACK(gtk_main_quit),          window);
gtk_widget_show_all(window);   //Mostra a janela com seus objetos
gtk_main ();

    return 0;
}


