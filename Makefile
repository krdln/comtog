default: comtog

install: comtog
	cp -i comtog /usr/local/bin/

uninstall:
	rm /usr/local/bin/comtog

clean:
	rm -f comtog

%: %.cpp
	g++ -std=c++0x -O3 -Wall -Wextra $< -o $@
