#!/bin/sh

set -e

make -f Makefile.windows

rm -rf dest
mkdir -p dest

mv pixab.exe dest/
cp raylib.dll dest/

cp -rf res/ dest/res

mv dest pixab-win

zip -r pixab-win.zip pixab-win/

rm -rf pixab-win
