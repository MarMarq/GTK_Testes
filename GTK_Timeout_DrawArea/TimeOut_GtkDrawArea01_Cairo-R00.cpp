// Para Compilar:
// gcc -Wall -lm -g TimeOut_GtkDrawArea01_Cairo-R00.cpp -o Executavel `pkg-config --cflags gtk+-2.0 --libs gtk+-2.0 

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

    GtkWidget       *darea;

    double w_larg = 1600;
    double w_alt  = 1200;
    bool toggle_stat = false;
    int width, height;
          GtkWidget       *window;
    double fase = 2;
    double amp  = 1.25;

    gboolean flag_amp = TRUE;

    gint teste;
    const char* testeCHAR = "teste";

static gboolean  on_toggled(GtkWidget *widget, gpointer data)
 {
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
        {toggle_stat = true;
        printf("ToggleButton01 --> Acionado / toggle_stat = %d\n",toggle_stat);
        }
    else
        {toggle_stat = false;
        printf("ToggleButton01 --> Liberado / toggle_stat = %d\n",toggle_stat);
        }
return FALSE;
 }

void click_ampplus(void)
{
amp=amp+0.25;
}

void click_ampminus(void)
{
amp=amp-0.25;
}


void click_faseplus(void)
{
fase=fase+0.5;
}

void click_faseminus(void)
{
fase=fase-0.5;
}


static gboolean draw_darea(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	int 	valor1;
	double 	valor2;



  static const double dashed1[] = {4.0, 21.0, 2.0};
  static int len1  = sizeof(dashed1) / sizeof(dashed1[0]);

  static const double dashed2[] = {14.0, 6.0};
  static int len2  = sizeof(dashed2) / sizeof(dashed2[0]);

  static const double dashed3[] = {2.0};

//    cairo_surface_t *surface;
    cr = gdk_cairo_create(gtk_widget_get_window(widget));

    cairo_set_source_rgba(cr, 0.45, 0.45, 0.45, 1);
    cairo_rectangle(cr,0 , 0, widget->allocation.width, widget->allocation.height);
    cairo_fill(cr);

double i = widget->allocation.width;
double j = widget->allocation.height;
double sc = fase*M_PI/i;
double y;
double h = 0;
if (amp != 0) h = h + j/amp;

//---------------------------------------------------------------------------
cairo_set_source_rgba(cr, 0, 0, 1, 1);
//cairo_set_dash(cr,dashed1, 1, 0 );
cairo_set_line_width(cr, 1.5);

cairo_move_to(cr, 0, (j/2)+(sin( (-i/2)*sc   )*(h/2))  );
for(double x=(-i/2);x<=(i/2);x=x+2)
{
	valor1 = rand()%5;
	valor2 = rand()%50;
y=x*sc;
if (valor1 < 3 ) cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2)) + valor2 );
if (valor1 == 3) cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2))  		);
if (valor1 > 3 ) cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2)) - valor2 );

}
cairo_stroke(cr);
//---------------------------------------------------------------------------
cairo_set_source_rgba(cr, 1, 1, 0, 1);
cairo_set_dash(cr,dashed1, 1, 0 );
cairo_set_line_width(cr, 1.5);

cairo_move_to(cr, 0, (j/2)+(sin( (-i/2)*sc   )*(h/2))  );
for(double x=(-i/2);x<=(i/2);x=x+10)
{
y=x*sc;
cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2))  		);
}
cairo_stroke(cr);
//---------------------------------------------------------------------------
cairo_set_source_rgba(cr, 0, 1, 1, 1);
cairo_set_dash(cr,dashed1, 1, 0 );
cairo_set_line_width(cr, 1.5);

cairo_move_to(cr, 0, (j/2)+(sin( (-i/2)*sc   )*(h/2))  );
for(double x=(-i/2);x<=(i/2);x=x+10)
{
y=x*sc;
cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2) + 25)  		);
}
cairo_stroke(cr);
//---------------------------------------------------------------------------
cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1);
cairo_set_dash(cr,dashed3, 1, 0 );
cairo_set_line_width(cr, 1.0);


cairo_move_to(cr,0,(j/2));
cairo_line_to(cr,i,(j/2));
cairo_move_to(cr,(i/2),0);
cairo_line_to(cr,(i/2),j);
cairo_stroke(cr);

    cairo_destroy(cr);
     return TRUE;
 }


static gboolean invalidate_drawing(gpointer data)
  {
    GdkWindow *win;

    g_print("Timer Signal | amp = %2.3f\n",amp);
if (toggle_stat==true)
{
	if ((flag_amp==TRUE)&&(amp <= 3))
		amp=amp+0.25;
	else
		flag_amp=FALSE;
	if ((flag_amp==FALSE)&&(amp >= 1.25))
		amp=amp-0.25;
	else
		flag_amp=TRUE;
}
    win = gtk_widget_get_window(GTK_WIDGET(data));
    if (win) {
        GtkAllocation allocation;

        gtk_widget_get_allocation(GTK_WIDGET(data), &allocation);
        gdk_window_invalidate_rect(win, &allocation, FALSE);
    }

return TRUE;

  }




int main (int argc, char *argv[])
{
//    const char event[8]="clicked";
    const char *event="clicked";
    GtkBuilder      *builder;

    GtkWidget       *togglebutton1;
    GtkWidget       *button1; // Amp+
    GtkWidget       *button2; // Amp-
    GtkWidget       *button4; // Fase+
    GtkWidget       *button5; // Fase-

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "glade03b.glade", NULL);                        //Carrega as informações do projeto glade para o GtkBuilder
    window          = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));          //Retorna o objeto Window, para mostrá-lo mais tarde
    darea           = GTK_WIDGET(gtk_builder_get_object (builder, "DrawingArea"));      //Retorna o objeto DrawingArea, para mostrá-lo mais tarde
    togglebutton1   = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton1"));    //Retorna o objeto togglebutton1, para mostrá-lo mais tarde
    button1         = GTK_WIDGET(gtk_builder_get_object (builder, "button1"));          //Retorna o objeto button1, para mostrá-lo mais tarde
    button2         = GTK_WIDGET(gtk_builder_get_object (builder, "button2"));          //Retorna o objeto button2, para mostrá-lo mais tarde
    button4         = GTK_WIDGET(gtk_builder_get_object (builder, "button4"));          //Retorna o objeto button4, para mostrá-lo mais tarde
    button5         = GTK_WIDGET(gtk_builder_get_object (builder, "button5"));          //Retorna o objeto button5, para mostrá-lo mais tarde


    gtk_window_set_title(GTK_WINDOW(window), "GTK DrawArea 02");


    gtk_builder_connect_signals (builder, NULL); //Conecta todos os eventos dentro do projeto do glade.
    g_object_unref (G_OBJECT (builder)); //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

    g_signal_connect(G_OBJECT(togglebutton1)  , "toggled"        , G_CALLBACK(on_toggled)     ,   NULL);
//    g_signal_connect_swapped(G_OBJECT(window) , "expose-event"   , G_CALLBACK(draw_darea)     ,G_OBJECT(darea));
    g_signal_connect(G_OBJECT(darea), "expose-event", G_CALLBACK(draw_darea), NULL);


    g_signal_connect(G_OBJECT(button1)          ,event   ,G_CALLBACK(click_ampplus)           ,NULL);
    g_signal_connect(G_OBJECT(button2)          ,event   ,G_CALLBACK(click_ampminus)          ,NULL);
    g_signal_connect(G_OBJECT(button4)          ,event   ,G_CALLBACK(click_faseplus)          ,NULL);
    g_signal_connect(G_OBJECT(button5)          ,event   ,G_CALLBACK(click_faseminus)         ,NULL);


    g_signal_connect_swapped(G_OBJECT(window) , "destroy"        ,
                    G_CALLBACK(gtk_main_quit)  , G_OBJECT(window));

    g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE,250,invalidate_drawing,darea,NULL);  // Variação atualizada da linha acima :-)

    gtk_widget_show_all(window);   //Mostra a janela com seus objetos
    gtk_main ();



    return 0;
}

