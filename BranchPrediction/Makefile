COMPILE = g++
CFLAGS = -std=c++11

branchism: app.o oneBit.o twoBit.o main.o 
	$(COMPILE) $(CFLAGS) app.o oneBit.o twoBit.o main.o  -o branchism

app.o: app.cpp
	$(COMPILE) $(CFLAGS) -c app.cpp

oneBit.o: oneBit.cpp
	$(COMPILE) $(CFLAGS) -c oneBit.cpp

twoBit.o: twoBit.cpp
	$(COMPILE) $(CFLAGS) -c twoBit.cpp

main.o: main.cpp
	$(COMPILE) $(CFLAGS) -c main.cpp

clean: 
	rm *.o branchism

