g++ -c main.cpp -o .\main.o
g++ -c .\Classes\duhr.cpp -o .\Classes\duhr.o
g++ .\main.o .\Classes\duhr.o -o .\main.exe
del .\main.o
del .\Classes\duhr.o
.\main