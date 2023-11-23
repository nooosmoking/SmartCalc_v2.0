

SOURCE := $(shell find ./ -iname "*.c" -o -iname "*.h")
TEST_SOURCE := model/model.cc model/model.h model/token.h tests/test.cc
	
all: install 
	../build/calc

install:
	mkdir -p ../build
	cmake -S . -B ../build || true
	cmake open ../build/ || true
	cmake --build ../build --target all || true

uninstall:
	rm -rf ../build

test:
	g++ -g -std=c++17 ${TEST_SOURCE} -o $@ -lgtest -lpthread 
	./$@
	
dvi:
	open readme.html

dist:
	git archive --format=tar.gz -o CPP3_SmartCalc_v2.0.tar.gz develop

format: $(SOURCE)
	cp ../materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	-rm -rf *tar.gz
	-rm -rf ../build
	-rm test