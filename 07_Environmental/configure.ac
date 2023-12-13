#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [nobody@gmail.com])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_file, rhash_msg, rhash_print_bytes, rhash_get_digest_size, 
rhash_library_init], [], [AC_MSG_ERROR([rhash lib is required])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h rhash.h string.h unistd.h ctype.h errno.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_ARG_WITH(
    [readline],
    AS_HELP_STRING([--without-readline], [Forces use of getline]),
    [],
    AC_CHECK_LIB([readline], [readline], [], [])
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT