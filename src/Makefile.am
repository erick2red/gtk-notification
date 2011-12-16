## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(datadir)/gtk_notification_demo/ui
ui_DATA = gtk_notification_demo.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GTK_NOTIFICATION_DEMO_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gtk_notification_demo

gtk_notification_demo_SOURCES = \
	main.c						\
	gtk-notification.c			\
	gtk-notification.h

gtk_notification_demo_LDFLAGS = \
	-Wl,--export-dynamic

gtk_notification_demo_LDADD = $(GTK_NOTIFICATION_DEMO_LIBS)


EXTRA_DIST = $(ui_DATA)
	
# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/gtk_notification_demo
