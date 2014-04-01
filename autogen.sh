#!/bin/sh
# Run this to generate all the initial makefiles, etc.

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

olddir=`pwd`
cd "$srcdir"

AUTORECONF=`which autoreconf`
if test -z $AUTORECONF; then
  echo "*** No autoreconf found, please install it ***"
  exit 1
fi

if (grep "^IT_PROG_INTLTOOL" $srcdir/configure.ac >/dev/null); then
  INTLTOOLIZE=`which intltoolize`
  if test -z $INTLTOOLIZE; then
    echo "*** No intltoolize found, please install it ***"
    exit 1
  fi
fi

# README and INSTALL are required by automake, but may be deleted by clean
# up rules. to get automake to work, simply touch these here, they will be
# regenerated from their corresponding *.in files by ./configure anyway.
touch README INSTALL

autoreconf --force --install --verbose || exit $?

intltoolize --copy --force --automake

cd "$olddir"
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"
