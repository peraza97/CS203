## Installation

To compile the project, run the following command in the top level directory
```sh
make
```

## Usage
run the following command in the top level directory
```sh
$ ./build/branchism -f <file> -m <history> -n <n-bit predictor> -a <address bits>
```
Optional parameters:
* -f : input file 
* -m : how many bits of global history will be used
* -n : type of predictor (1 or 2)
* -a : how many bits of the address will be used (default is 8)

### Example
```
$ ./build/branchism -f ./text/gcc-8M.txt -m 6 -n 1
```
