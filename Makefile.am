## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

gtk_notification_demodocdir = ${prefix}/doc/gtk_notification_demo
gtk_notification_demodoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(gtk_notification_demodoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gtk_notification_demodocdir)
