randmain: randmain.c randcpuid.c
	gcc -c randmain.c -o randmain.o 
	gcc -c randcpuid.c -o randcpuid.o
	gcc -ldl -Wl,-rpath=. -o randmain randmain.o randcpuid.o

randlibhw.so: randlibhw.c
	gcc -march=native -mtune=native -mrdrnd -c -fpic randlibhw.c
	gcc -march=native -mtune=native -mrdrnd -shared -o randlibhw.so randlibhw.o

randlibsw.so: randlibsw.c
	gcc -march=native -mtune=native -mrdrnd -c -fpic randlibsw.c
	gcc -march=native -mtune=native -mrdrnd -shared -o randlibsw.so randlibsw.o



