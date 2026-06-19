calc.exe : main.o contact.o file.o populate.o validate.o
	gcc -o address.exe main.o contact.o file.o populate.o validate.o

main.o : main.c
	gcc -c main.c

contact.o : contact.c
	gcc -c contact.c

file.o : file.c
	gcc -c file.c

populate.o : populate.c
	gcc -c populate.c

validation.o : validate.c
	gcc -c validate.c

clean :
	rm *.exe *.o