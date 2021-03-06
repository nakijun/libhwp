/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * hwp-hwpml-parser.h
 *
 * Copyright (C) 2013-2014 Hodong Kim <hodong@cogno.org>
 *
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__HWP_H_INSIDE__) && !defined (HWP_COMPILATION)
#error "Only <hwp/hwp.h> can be included directly."
#endif

#ifndef __HWP_HWPML_PARSER_H__
#define __HWP_HWPML_PARSER_H__

#include <glib-object.h>
#include "hwp-listenable.h"
#include "hwp-hwpml-file.h"

G_BEGIN_DECLS

#define HWP_TYPE_HWPML_PARSER             (hwp_hwpml_parser_get_type ())
#define HWP_HWPML_PARSER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), HWP_TYPE_HWPML_PARSER, HwpHWPMLParser))
#define HWP_HWPML_PARSER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), HWP_TYPE_HWPML_PARSER, HwpHWPMLParserClass))
#define HWP_IS_HWPML_PARSER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HWP_TYPE_HWPML_PARSER))
#define HWP_IS_HWPML_PARSER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), HWP_TYPE_HWPML_PARSER))
#define HWP_HWPML_PARSER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), HWP_TYPE_HWPML_PARSER, HwpHWPMLParserClass))

typedef struct _HwpHWPMLParser         HwpHWPMLParser;
typedef struct _HwpHWPMLParserClass    HwpHWPMLParserClass;
typedef struct _HwpHWPMLParserPrivate  HwpHWPMLParserPrivate;

struct _HwpHWPMLParser
{
  GObject                parent_instance;
  HwpHWPMLParserPrivate *priv;

  HwpListenable         *listenable;
  gpointer               user_data;
};

/**
 * HwpHWPMLParserClass:
 * @parent_class: the parent class
 *
 * The class structure for the <structname>HwpHWPMLParser</structname> type.
 */
struct _HwpHWPMLParserClass
{
  GObjectClass parent_class;
};

struct _HwpHWPMLParserPrivate
{
  HwpSummaryInfo *info;
};

GType hwp_hwpml_parser_get_type (void);

HwpHWPMLParser *hwp_hwpml_parser_new   (HwpListenable  *listenable,
                                        gpointer        user_data);
void            hwp_hwpml_parser_parse (HwpHWPMLParser *parser,
                                        HwpHWPMLFile   *file,
                                        GError        **error);

G_END_DECLS

#endif /* __HWP_HWPML_PARSER_H__ */
