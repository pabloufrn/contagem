cd libs
tar -xf zlib-*.tar.gz
cd zlib-*.tar.gz
cd zlib-*/
./configure
make
cd ..
tar -xf gzstream.tgz
cp zlib-*/zlib.h gzstream
cp zlib-*/zconf.h gzstream
cd gzstream
make
cd ../../
cp libs/zlib-*/libz.a lib
cp libs/gzstream/libgzstream.a lib
rm -rf libs/zlib-*/
rm -rf libs/gzstream/
