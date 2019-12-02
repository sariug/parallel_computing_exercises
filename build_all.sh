#!/bin/bash

# 30_20_2019
cd 30_10_2019
mkdir build
cd build
cmake ..
make
cd ../..

# 06_11_2019
cd 06_11_2019
mkdir build
cd build
cmake ..
make
cd ../..

# 13_11_2019
cd 13_11_2019
mkdir build
cd build
cmake ..
make
cd ../..



# 20_11_2019
cd 20_11_2019
mkdir build
cd build
cmake ..
make
cd ../..

# 27_11_2019
cd 27_11_2019
mkdir build
cd build
cmake ..
make && make test
cd ../..

# How does this work ? Finding all the folders, but also trying the main folders. So not just the subfolders. 
# for d in $(find */   -maxdepth 0  -not -path '*/\.*'); do
#   if [ -d "$d" ]; then
#    echo "$d"
#	cd $PWD/$d
#  	mkdir build
#  	cd build
#  	cmake ..
#	make
#	cd ../..
#  fi
#	done

