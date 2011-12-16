/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Erick Pérez Castellanos 2011 <erick.red@gmail.com>
 * 
 gtk-notification-demo is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-notification-demo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */

#include <config.h>
#include <gtk/gtk.h>

#include <glib/gi18n.h>

#include "gtk-notification.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/gtk_notification_demo/ui/gtk_notification_demo.ui" */
#define UI_FILE "src/gtk_notification_demo.ui"
#define TOP_WINDOW "window"

static void actioned_signal_handler(GtkWidget * not, gpointer user_data) {
	g_print("Clicked action button\n");
	g_print("Wwill do something now, destroy the widget for instance\n");
	gtk_widget_destroy(not);
}

static void show_notification_cb(GtkWidget * button, gpointer user_data) {
	GtkWidget * notification = gtk_notification_new("Operation will want to undo", "Undo");
	gtk_widget_set_size_request(notification, 400, -1);
	gtk_widget_show(notification);
	g_signal_connect(notification, "actioned", G_CALLBACK(actioned_signal_handler), NULL);

	g_print("Created notification widget\n");

	GtkBuilder * builder = GTK_BUILDER(user_data);
	GtkWidget * overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
	gtk_overlay_add_overlay(GTK_OVERLAY(overlay), notification);
}

static GtkWidget* create_window(void) {
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
		g_critical("Couldn't load builder file: %s", error->message);
		g_error_free(error);
	}

	g_signal_connect(gtk_builder_get_object(builder, TOP_WINDOW), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(gtk_builder_get_object(builder, "execute_button"), "clicked", G_CALLBACK(show_notification_cb), builder);

	gtk_widget_grab_focus(GTK_WIDGET(gtk_builder_get_object(builder, "execute_button")));

	/* Get the window object from the ui file */
	window = GTK_WIDGET(gtk_builder_get_object(builder, TOP_WINDOW));
	if (!window) {
		g_critical("Widget \"%s\" is missing in file %s.", TOP_WINDOW, UI_FILE);
	}

	GtkWidget * overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
	GdkRGBA transparent = { 0, 0, 0, 0 };
	gtk_widget_override_background_color(overlay, 0, &transparent);

	return window;
}

int main(int argc, char *argv[]) {
	GtkWidget *window;

#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif

	gtk_init(&argc, &argv);

	window = create_window();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
