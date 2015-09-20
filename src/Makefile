all:
	cd cjdns; make
	cd model; make
	cd net; make
	cd cntl; make
	g++ cjdns/*.o model/*.o net/*.o cntl/*.o *.cc -lpthread -o init.out

clean:
	cd cjdns; make clean
	cd model; make clean
	cd net; make clean
	cd cntl; make clean
	rm *.out 
