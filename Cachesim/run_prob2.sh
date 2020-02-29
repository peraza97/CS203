echo "512KB Cache, 16B block, direct"
./build/cachesim -f $1 -c 512KB -b 16B -w 1
echo "512KB Cache, 16B block, 2 Way"
./build/cachesim -f $1 -c 512KB -b 16B -w 2
echo "512KB Cache, 16B block, 4 Way"
./build/cachesim -f $1 -c 512KB -b 16B -w 4
echo "512KB Cache, 16B block,  fully associative"
./build/cachesim -f $1 -c 512KB -b 16B -w 0