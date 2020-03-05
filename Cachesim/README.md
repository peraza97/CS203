## Installation

To compile the project, run the following command in the top level directory
```sh
make
```

## Usage
run the following command in the top level directory
```sh
$ ./build/cachesim -f <file> -c <cache size> -b <block size> -w <ways>
```
Optional parameters:
* -f : input file 
* -c : cachse size (can use B,KB,MB,GB)
* -b : block size (can use B,KB,MB,GB)
* -w : number of ways

### Example
```
$ ./build/cachesim -f "files/gcc-10K.memtrace" -c 512KB -b 32B -w 1
```
