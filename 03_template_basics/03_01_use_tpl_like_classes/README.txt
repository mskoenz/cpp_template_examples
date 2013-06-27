if you want to build the, open a termial and do the following:

cmake .
make

and the program should be built. To clean all the generated files just run

./clean

the neater version is:

mkdir build
cd build
cmake ../
make

and to remove

cd ../
rm -rf ./build
