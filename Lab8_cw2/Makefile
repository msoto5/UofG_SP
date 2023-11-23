dependencyDiscoverer: dependencyDiscoverer.cpp
	clang++ -Wall -Werror -std=c++17 -o dependencyDiscoverer dependencyDiscoverer.cpp -lpthread

clean:
	rm -f *.o dependencyDiscoverer *~

tests: dependencyDiscoverer
	clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror -o dependencyDiscoverer dependencyDiscoverer.cpp -lpthread
	clang -fsanitize=address -Wall -Werror -g dependencyDiscoverer.c -o dependencyDiscoverer
	clang -fsanitize=undefined -Wall -Werror dependencyDiscoverer.c -o dependencyDiscoverer
	clang -fsanitize=memory -Wall -Werror dependencyDiscoverer.c -o dependencyDiscoverer