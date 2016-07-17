# I know we could make a better packaging system concerning gettext because it seems that
# the autotools can generate a static libintl and generating *.mo files even if the target host
# use the POSIX/XSI libiconv for translation...
# with use of following m4 macros:
#
# * AM_GNU_GETTEXT, AM_GNU_GETTEXT_VERSION, AM_GNU_GETTEXT_NEED, AM_GNU_GETTEXT_INTL_SUBDIR, AM_XGETTEXT_OPTION and AM_ICONV
#
# And by lanching gettextize --help
#
# But i don't really understand HOW-TO make it... sorry.
#
# So I have done it like this with msgfmt but it doesn't work on my system.


pot-fr-2-mo:
# This doesn't work ! I don't know why, I have try everything, sorry...
#	- $(MSGFMT) -v -f ./share/locale/fr/LC_MESSAGES/it-edit.pot -o ./share/locale/fr/LC_MESSAGES/it-edit.mo
#	if `test ! -d "$(DESTDIR)$(localedir)/fr/LC_MESSAGES"` ; then $(MKDIR_P) "$(DESTDIR)$(localedir)/fr/LC_MESSAGES" ; fi
#
# This doesn't work too ! I don't know why, I have try everything, sorry...
#	if `test ! -d "$(pkgdatadir)/share/locale/fr/LC_MESSAGES"` ; then $(MKDIR_P) "$(pkgdatadir)/share/locale/fr/LC_MESSAGES" ; fi
#	$(INSTALL) -m 0644 ./share/locale/fr/LC_MESSAGES/it-edit.mo "$(pkgdatadir)/share/locale/fr/LC_MESSAGES"
#
# So we try finally like this:
	if `test ! -d "$(DESTDIR)$(localedir)/fr/LC_MESSAGES"` ; then $(MKDIR_P) "$(DESTDIR)$(localedir)/fr/LC_MESSAGES" ; fi
	$(INSTALL) -m 0644 ./share/locale/fr/LC_MESSAGES/it-edit.mo "$(DESTDIR)$(localedir)/fr/LC_MESSAGES"

pot-de-2-mo:
# This doesn't work ! I don't know why, I have try everything, sorry...
#	- $(MSGFMT) -v -f ./share/locale/de/LC_MESSAGES/it-edit.pot -o ./share/locale/de/LC_MESSAGES/it-edit.mo ;
#	if `test ! -d "$(DESTDIR)$(localedir)/de/LC_MESSAGES"` ; then $(MKDIR_P) "$(DESTDIR)$(localedir)/de/LC_MESSAGES" ; fi
#
# This doesn't work too ! I don't know why, I have try everything, sorry...
#	if `test ! -d "$(pkgdatadir)/share/locale/de/LC_MESSAGES"` ; then $(MKDIR_P) "$(pkgdatadir)/share/locale/de/LC_MESSAGES" ; fi
#	$(INSTALL) -m 0644 ./share/locale/de/LC_MESSAGES/it-edit.mo "$(pkgdatadir)/share/locale/de/LC_MESSAGES"
	if `test ! -d "$(DESTDIR)$(localedir)/de/LC_MESSAGES"` ; then $(MKDIR_P) "$(DESTDIR)$(localedir)/de/LC_MESSAGES" ; fi
	$(INSTALL) -m 0644 ./share/locale/de/LC_MESSAGES/it-edit.mo "$(DESTDIR)$(localedir)/de/LC_MESSAGES"

install-data-hook:
#################### Start French translation try. #############################
# Optionnaly, but is not working on my system...???
	$(MAKE) pot-fr-2-mo
#################### End French translation try. ###############################
#
#################### Start German translation try. #############################
	$(MAKE) pot-de-2-mo
#################### End German translation try. ###############################
#

uninstall-hook:
	- if `test  -f "$(DESTDIR)$(localedir)/de/LC_MESSAGES/it-edit.mo"` ; then $(RM) -f "$(DESTDIR)$(localedir)/de/LC_MESSAGES/it-edit.mo" ; fi ;
	- if `test  -f "$(DESTDIR)$(localedir)/fr/LC_MESSAGES/it-edit.mo"` ; then $(RM) -f "$(DESTDIR)$(localedir)/fr/LC_MESSAGES/it-edit.mo" ; fi ;

EXTRA_DIST =  ./share/locale/de/LC_MESSAGES/it-edit.pot \
              ./share/locale/fr/LC_MESSAGES/it-edit.pot \
              ./share/locale/de/LC_MESSAGES/it-edit.mo  \
              ./share/locale/fr/LC_MESSAGES/it-edit.mo
            