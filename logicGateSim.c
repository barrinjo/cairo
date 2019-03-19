#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void do_drawing(cairo_t *);

// array of clicked points
struct {
	int count;
	double coordx[100];
	double coordy[100];
} glob;


// connects the gtk event widget to the draw function in cairo
static gboolean on_draw_event(GtkWidget *widget,
			      cairo_t   *cr,
			      gpointer   user_data) {
	do_drawing(cr);

	return FALSE;
}


static float rgb(float x) {
	x = x/255;
	float value = (int)(x * 100 + .5);
	return (float)value / 100;
}

static void do_drawing(cairo_t *cr) {
	// sets source to pink
	cairo_set_source_rgb(cr, rgb(47), rgb(130), rgb(28));
	cairo_set_line_width(cr, 5);

	//for each clicked coordinate in glob.coord, draws a rectangle at that point
	for(int i = 0; i <= glob.count - 1; i++) {
		// cairo_move_to(cr, glob.coordx[i]-15, glob.coordy[i]-15);
		cairo_rectangle(cr, glob.coordx[i]-15, glob.coordy[i]-15, 30, 30);
	}

	cairo_stroke(cr);
}

static gboolean clicked(GtkWidget *widget,
			GdkEventButton *event,
			gpointer user_data) {
	//left click
	if(event->button == 1) {
		//adds coord to glob
		glob.coordx[glob.count] = event->x;
		glob.coordy[glob.count++] = event->y;
		// redraws systemn
		gtk_widget_queue_draw(widget);
	}

	if(event->button == 3) {
		// resets coordinates
		glob.count = 0;
		gtk_widget_queue_draw(widget);
	}

	return TRUE;
}

int main(int argc, char const *argv[])
{
	GtkWidget *window;
	GtkWidget *darea;

	glob.count = 0;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);

	g_signal_connect(G_OBJECT(darea), "draw",
			 G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(window, "destroy",
			 G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(window, "button-press-event",
			 G_CALLBACK(clicked), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_title(GTK_WINDOW(window), "LogicGateSim");

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}