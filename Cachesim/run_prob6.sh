echo "file gcc-10K.memtrace"
echo "64KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 64KB -b 32B -w 2 | grep "Miss rate"
echo "128KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 128KB -b 32B -w 2 | grep "Miss rate"
echo "256KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 256KB -b 32B -w 2 | grep "Miss rate"
echo "512KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 512KB -b 32B -w 2 | grep "Miss rate"
echo "1MB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 1MB -b 32B -w 2 | grep "Miss rate"
echo "2MB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-10K.memtrace" -c 2MB -b 32B -w 2 | grep "Miss rate"

echo "\nfile gcc-1M.memtrace"
echo "64KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 64KB -b 32B -w 2 | grep "Miss rate"
echo "128KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 128KB -b 32B -w 2 | grep "Miss rate"
echo "256KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 256KB -b 32B -w 2 | grep "Miss rate"
echo "512KB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 512KB -b 32B -w 2 | grep "Miss rate"
echo "1MB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 1MB -b 32B -w 2 | grep "Miss rate"
echo "2MB Cache, 32B block, 2 Way"
./build/cachesim -f "files/gcc-1M.memtrace" -c 2MB -b 32B -w 2 | grep "Miss rate"