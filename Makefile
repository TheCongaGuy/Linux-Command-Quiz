compileMain: main.cpp test.cpp eventManager.cpp data.cpp LinkedList.hpp Node.hpp Profile.hpp
	@echo "Constructing Program..."
	@g++ main.cpp test.cpp eventManager.cpp data.cpp -o main
	@./main