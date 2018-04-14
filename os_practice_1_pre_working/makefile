#Part to include a kind of global Variables
CXX = g++
CXXFLAGS = -Wall -g
#Omce variables were declared we built a prerrequisite dependence -kind of difficult-
main: main.o Point.o Rectangle.o
	$(CXX) $(CXXFLAGS) -o soft main.o Point.o Rectangle.o #The way to compile the prerrequisite is difine in this part

clean:
	rm main.o Point.o Rectangle.o
