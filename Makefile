
.PHONY: all
all: test_deck

test_deck: deck.cc test_deck.cc
	g++ -Wall -std=c++17 -I.. deck.cc test_deck.cc -o test_deck

.PHONY: clean
clean:
	rm -rf test_deck html latex

.PHONY: lint
lint:
	cpplint *.h *.cc

.PHONY: doc
doc:
	doxygen deck.h  # open html/classDeck.html
