#!/bin/bash
l=$(echo "$1" | awk '{print tolower($0)}')
srcdir=$1/src/
mkdir -p $1/build/ $srcdir
echo "#include <stdio.h>"$'\n'"#include <unistd.h>"$'\n'$'\n'"int main(int argc, char **argv) {"$'\n'$'\n'"}" > $srcdir/$l.c
echo $'\n'"$l: $1/\$(SRCDIR)/$l.c"$'\n'$'\t'"\$(CC) \$(CFLAGS) \$^ -o $1/\$(BLDDIR)/$l" >> Makefile
subl $srcdir/$l.c


