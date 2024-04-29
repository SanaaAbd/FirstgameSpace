#!/bin/sh

set -e

make -f Makefile

rm -rf dest
mkdir -p dest

mv pixab dest/
cp /usr/lib/libraylib.so dest/

cp -rf res/ dest/res

mv dest pixab-lin

tar czvf pixab-lin.tar.gz pixab-lin/

rm -rf pixab-lin
