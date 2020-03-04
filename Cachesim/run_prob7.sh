echo "8KB Cache, 32B block, 4 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 8KB -b 32B -w 4 | grep "Miss rate"
echo "Infinite size Cache(512MB), 32B block, 4 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 2GB -b 32B -w 4 | grep "Miss rate"
echo "8KB Cache, 32B block, Fully associative"
./build/cachesim -f "files/gcc-1M.memtrace" -c 8KB -b 32B -w 0 | grep "Miss rate"