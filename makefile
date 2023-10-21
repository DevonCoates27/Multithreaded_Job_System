compile: 
	clang++ -g -std=c++14 ./Code/*.cpp -o output

testWorks:
	clang++ -g -std=c++14 ./Code/TestWorks/*.cpp -o testWorksExecutable

testCompileError:
	clang++ -g -std=c++14 ./Code/TestCompileError/*.cpp -o testCompileErrorExecutable

testLinkError:
	clang++ -g -std=c++14 ./Code/TestLinkError/*.cpp -o testLinkErrorExecutable

