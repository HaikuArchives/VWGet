/* src/config.h.  Generated automatically by configure.  */
/* Configuration header file.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef CONFIG_H
#define CONFIG_H

/* Define if you have the <alloca.h> header file.  */
#define HAVE_ALLOCA_H 1

/* AIX requires this to be the first thing in the file.  */
#ifdef __GNUC__
# define alloca __builtin_alloca
#else
# if HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifdef _AIX
 #pragma alloca
#  else
#   ifndef alloca /* predefined by HP cc +Olibcalls */
char *alloca ();
#   endif
#  endif
# endif
#endif

/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef pid_t */

/* Define if you have the ANSI C header files.  */
/* #undef STDC_HEADERS */

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define if your architecture is big endian (with the most
   significant byte first).  */
#define WORDS_BIGENDIAN 1

/* Define this if you want the NLS support.  */
/* #undef HAVE_NLS */

/* Define if you want the FTP support for Opie compiled in.  */
#define USE_OPIE 1

/* Define if you want the HTTP Digest Authorization compiled in.  */
#define USE_DIGEST 1

/* Define if you want the debug output support compiled in.  */
#define DEBUG 1

/* Define if you have sys/time.h header.  */
#define HAVE_SYS_TIME_H 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME 1

/* Define if you have struct utimbuf.  */
#define HAVE_STRUCT_UTIMBUF

/* Define if you have the uname function.  */
#define HAVE_UNAME 1

/* Define if you have the gethostname function.  */
#define HAVE_GETHOSTNAME 1

/* Define if you have the select function.  */
#define HAVE_SELECT 1

/* Define if you have the gettimeofday function.  */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the sys/utsname.h header.  */
#define HAVE_SYS_UTSNAME_H 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the vsnprintf function.  */
/* #undef HAVE_VSNPRINTF */

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strncasecmp function.  */
#define HAVE_STRNCASECMP 1

/* Define if you have the strptime function.  */
/* #undef HAVE_STRPTIME */

/* Define if you have the mktime function.  */
#define HAVE_MKTIME 1

/* Define if you have the symlink function.  */
#define HAVE_SYMLINK 1

/* Define if you have the access function.  */
#define HAVE_ACCESS 1

/* Define if you have the isatty function.  */
#define HAVE_ISATTY 1

/* Define if you have the signal function.  */
#define HAVE_SIGNAL 1

/* Define if you have the gettext function.  */
/* #undef HAVE_GETTEXT */

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <utime.h> header file.  */
#define HAVE_UTIME_H 1

/* Define if you have the <sys/utime.h> header file.  */
/* #undef HAVE_SYS_UTIME_H */

/* Define if you have the <sys/select.h> header file.  */
/* #undef HAVE_SYS_SELECT_H */

/* Define if you have the <pwd.h> header file.  */
#define HAVE_PWD_H 1

/* Define if you have the <signal.h> header file.  */
#define HAVE_SIGNAL_H 1

/* Define if you have the <libintl.h> header file.  */
/* #undef HAVE_LIBINTL_H */

/* Define if you have the <locale.h> header file.  */
#define HAVE_LOCALE_H 1

/* Define to be the name of the operating system.  */
#define OS_TYPE ""

/* Define if you wish to compile with socks support.  */
/* #undef HAVE_SOCKS */

/* Define to 1 if ANSI function prototypes are usable.  */
#define PROTOTYPES 1

#endif /* CONFIG_H */
