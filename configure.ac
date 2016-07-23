#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([it-edit], [2.91], [mrcyberfighter@gmail.com], , [http://www.open-source-projects.net/IT-Edit/IT-Edit_presentation.html])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_COPYRIGHT([GPLv3])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CPP_WERROR
AC_PROG_CC_STDC
AC_PROG_CC_C99

AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_LN_S

AC_PATH_PROG([CHMOD], [chmod],                          [no])
AC_PATH_PROG([CHOWN], [chown],                          [no])
AC_PATH_PROG([CP],    [cp],                             [no])
AC_PATH_PROG([RM],    [rm],                             [no])
AC_PATH_PROG([MV],    [mv],                             [no])
AC_PATH_PROG([WC],    [wc],                             [no])
AC_PATH_PROG([MV],    [mv],                             [no])
AC_PATH_PROG([TOUCH], [touch],                         [no])
AC_PATH_PROG([SED],   [sed],                            [no])
AC_PATH_PROG([XDG_DESKTOP_MENU], [xdg-desktop-menu],    [no])

if test "$CHMOD" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$CHOWN" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$CP" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$RM" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$MV" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$WC" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$TOUCH" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)
 
fi

if test "$SED" = no ; then

  AC_MSG_ERROR(Install the sed program !      , 1)
 
fi 

if test "$XDG_DESKTOP_MENU" = no ; then
 
  AC_MSG_ERROR(Install the xdg-utils package !, 1)

fi 
      

# Ho my translations works nowhere but it worked on my development environment ???
#AC_PATH_PROG([MSGFMT], [msgfmt],                        AC_MSG_WARN(Install the gettext package !      ))
#AC_SUBST(PRG_USER, $USER)

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-3.0], , AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ******************* GTK 3 library required for it-edit *****************
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([GTKSOURCEVIEW], [gtksourceview-3.0], , AC_MSG_ERROR(   gtksourceview-3.0 library not detected !!!

   ************* gtksourceview-3.0 library required for it-edit ***********
   Install the gtksourceview-3.0 library from your package manager or
   from source.

   You must have the package: libgtksourceview-3.0-common installed too.

   This package provide common files for the GTK+ syntax highlighting
   widget GtkSourceView: this is a text widget that extends the standard
   GTK+ 3.x text widget GtkTextView.

   It improves GtkTextView by implementing syntax highlighting and
   other features typical of a source editor.

   WARNING: Take care to install the development files from gtksourceview !
            Often call: libgtksourceview-3.0-dev or
                        libgtksourceview-3.0-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


AC_CHECK_LIB([vte-2.91],
             [vte_terminal_new],
             ,
             AC_MSG_ERROR(   vte-2.91 library not detected !!!

   ****************** vte-2.91 library required for it-edit ****************
   Install the libvte-2.91 library from your package manager or from source.

   WARNING: Take care to install the development files from vte-2.91 !!!
            Often call: libvte-2.91-dev or libvte-2.91-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


AC_CHECK_LIB([m],
             [roundf],
             ,
             AC_MSG_ERROR(Math library required from it-edit, 1))

# Checks for header files.
AC_CHECK_HEADERS([stdio.h string.h limits.h fcntl.h inttypes.h libintl.h locale.h stdint.h unistd.h stdlib.h string.h stdbool.h math.h sys/time.h sys/stat.h sys/types.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday realpath gettext setlocale strchr strrchr])



AC_CONFIG_FILES([Makefile
                 source/Makefile
                 translations/Makefile
                 data/Makefile
                 texi/Makefile
                 man/Makefile
                 desktop/Makefile
                 doc/Makefile
                 ])





AC_OUTPUT

AC_MSG_NOTICE(System check OK !!!)

echo "
  ************************ ${PACKAGE_STRING} **********************

  Package: ${PACKAGE_NAME}
  Version: ${PACKAGE_VERSION}

  ${PACKAGE_NAME} an integrated terminals programming text editor
  with severals others functionnalities.

  Package dependencies: gtk-3, gtksourceview.3.0, vte-2.91, math.

  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}

  Prefix: ${prefix}

  Author: Brüggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}."