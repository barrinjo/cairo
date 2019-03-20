#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void do_drawing(cairo_t *);

// array of clicked points
struct {
	int count;
	double coordx[256];
	double coordy[256];
} glob;
gboolean boxInMotion = FALSE;
int movingBox;

// connects the gtk event widget to the draw function in cairo
static gboolean on_draw_event(GtkWidget *widget,
			      cairo_t   *cr,
			      gpointer   user_data) {
	do_drawing(cr);

	return FALSE;
}

static int check_boxes (float x, float y) {
	// iterates through the boxes and checks the mouse coordinates to see
	// if the mouse is in the boxes
	int i;
	for(i = 0; i < glob.count; i++) {
		if(x < glob.coordx[i]+20 && x > glob.coordx[i] - 20) {
			if(y < glob.coordy[i]+20 && y > glob.coordy[i] - 20) {
				return i+1;
			}
		}
	}
	return 0;
}

static float rgb(float x) {
	x = x/255;
	float value = (int)(x * 100 + .5);
	return (float)value / 100;
}

static void do_drawing(cairo_t *cr) {
	// sets source to pink
	cairo_set_source_rgb(cr, rgb(47), rgb(130), rgb(28));
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
	cairo_set_line_width(cr, 5);

	//for each clicked coordinate in glob.coord, draws a rectangle at that point
	for(int i = 0; i <= glob.count - 1; i++) {
		// cairo_move_to(cr, glob.coordx[i]-15, glob.coordy[i]-15);
		cairo_rectangle(cr, glob.coordx[i]-15, glob.coordy[i]-15, 30, 30);
	}

	cairo_stroke(cr);
}

static void moveBox(int i, int x, int y) {
	glob.coordx[i] = x;
	glob.coordy[i] = y;
}

static gboolean clicked(GtkWidget *widget,
			GdkEventButton *event,
			GdkEventMotion *motion,
			gpointer user_data) {

	int boxLoc = check_boxes(event->x, event->y);

	if(event->button == 2 && boxInMotion == TRUE) {
		moveBox(movingBox, event->x, event->y);
		boxInMotion = FALSE;
	}

	// left click outside of box
	if(event->button == 2 && boxLoc && boxInMotion == FALSE) {
		movingBox = boxLoc - 1;		
		boxInMotion = TRUE;
	}

	//left click outside box
	if(event->button == 1 && !check_boxes(event->x, event->y)) {
		//adds coord to glob
		glob.coordx[glob.count] = event->x;
		glob.coordy[glob.count++] = event->y;
		// printf("ugh\n");
	}

	if(event->button == 3) {
		// resets coordinates
		glob.count = 0;
		gtk_widget_queue_draw(widget);
	}

	// if(boxInMotion)
	// 	moveBox(boxLoc, event->x, event->y);

	gtk_widget_queue_draw(widget);
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