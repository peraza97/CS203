COMPILE = g++
CFLAGS = -std=c++11

branchism: app.o predictor.o bht.o main.o 
	$(COMPILE) $(CFLAGS) app.o predictor.o bht.o main.o  -o branchism

app.o: app.cpp
	$(COMPILE) $(CFLAGS) -c app.cpp

predictor.o: predictor.cpp
	$(COMPILE) $(CFLAGS) -c predictor.cpp

bht.o: bht.cpp
	$(COMPILE) $(CFLAGS) -c bht.cpp

main.o: main.cpp
	$(COMPILE) $(CFLAGS) -c main.cpp

clean: 
	rm *.o branchism

