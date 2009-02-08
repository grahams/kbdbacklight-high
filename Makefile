
kbdbacklight-high: kbdbacklight-high.o 
	c++ kbdbacklight-high.o -o kbdbacklight-high -framework IOKit -framework CoreFoundation

kbdbacklight-high.o: kbdbacklight-high.c
	c++ -c kbdbacklight-high.c -o kbdbacklight-high.o

clean:
	rm kbdbacklight-high.o kbdbacklight-high
