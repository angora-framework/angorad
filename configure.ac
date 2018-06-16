AC_INIT([angorad], [1.0], [zachdeibert@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_PROG_CC
AC_CHECK_PROG([CPYC], [cpyc], [cpyc], [:])
AM_CONDITIONAL([FOUND_CPYC], [test "x$CPYC" != x:])
AM_COND_IF([FOUND_CPYC],,[AC_MSG_ERROR([required program 'cpyc' not found.])])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
