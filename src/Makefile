all:
	cd cjdns; make
	cd model; make
	cd net; make
	g++ cjdns/*.o model/*.o net/*.o *.cc -lpthread -o init.out

clean:
	cd cjdns; make clean
	cd model; make clean
	cd net; make clean
	rm *.out *.o
