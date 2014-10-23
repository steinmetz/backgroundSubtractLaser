all:
	g++ -I include -std=c++0x *.cpp -o out `pkg-config opencv --cflags --libs`

clean:
	rm out

