all:
	cd cjdns; make
	cd model; make
	#g++ cjdns/*.o model/*.o *.cc -o init.out

clean:
	cd cjdns; make clean
	cd model; make clean
	rm *.out *.o
