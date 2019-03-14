#include <cairo.h>

int main(void)
{
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 520, 60);
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face(cr, "Sans",
			       CAIRO_FONT_SLANT_NORMAL,
			       CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);

	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "Westballz is my addy daddy");
	cairo_rectangle(cr, 0, 0, 50, 50);

	cairo_surface_write_to_png(surface, "image.png");

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}