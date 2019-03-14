#include <cairo.h>
#include <cairo-pdf.h>

int main(void)
{
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_pdf_surface_create("pdffile.pdf", 600, 700);
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face(cr, "Times New Roman",
			       CAIRO_FONT_SLANT_NORMAL,
			       CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);

	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "Alex19 doesn't break records");

	cairo_show_page(cr);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);

	return 0;
}