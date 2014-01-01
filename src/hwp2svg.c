/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * hwp2svg.c
 * 
 * Copyright (C) 2013-2014 Hodong Kim <hodong@cogno.org>
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <glib-object.h>
#include <cairo-svg.h>
#include "hwp.h"

int main (int argc, char **argv)
{
  GError  *error = NULL;
  HwpPage *page;
  gdouble  width = 0.0, height = 0.0;

  if (argc < 2) {
    puts ("Usage: hwp2svg file.hwp");
    return 0;
  }

#if (!GLIB_CHECK_VERSION(2, 35, 0))
  g_type_init();
#endif

  HwpFile     *file     = hwp_file_new_for_path (argv[1], &error);
  HwpDocument *document = hwp_file_get_document (file,    &error);

  guint n_pages = hwp_document_get_n_pages (document);
  if (n_pages < 1) {
    puts ("There is no page");
    return -1;
  }

  cairo_surface_t *surface;
  cairo_t *cr;
  gchar *filename;
  for (guint i = 0; i < n_pages; i++) {
    hwp_page_get_size (page, &width, &height);
    filename = g_strdup_printf("page%d.svg", i);
    surface = cairo_svg_surface_create (filename, width, height);
    cr = cairo_create (surface);

    page = hwp_document_get_page (document, i);
    hwp_page_render (page, cr);
    cairo_show_page (cr);

    g_free (filename);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
  }

  g_object_unref (document);
  g_object_unref (file);
  return 0;
}
