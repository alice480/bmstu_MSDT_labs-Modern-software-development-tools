TARGET = bin/lab
COMPILE = g++ -std=c++17 -c -Iinclude -O0 --coverage
LINK = g++ --coverage
SRC = src/
BUILD = build/

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
	rm -rf $(BUILD)*
	rm -rf $(TARGET)
	rm -rf *.gcno

$(TARGET): $(BUILD)l1_UserInterface.o $(BUILD)l2_ApplicationLayer.o $(BUILD)l3_DomainLayer.o $(BUILD)l4_InfrastructureLayer.o
	$(LINK) -o main $(BUILD)l1_UserInterface.o $(BUILD)l2_ApplicationLayer.o $(BUILD)l3_DomainLayer.o $(BUILD)l4_InfrastructureLayer.o

$(BUILD)l1_UserInterface.o: src/l1_UserInterface.cpp include/l2_ApplicationLayer.h include/l3_DomainLayer.h include/l4_InfrastructureLayer.h
	$(COMPILE) $(SRC)l1_UserInterface.cpp -o $(BUILD)l1_UserInterface.o

$(BUILD)l2_ApplicationLayer.o: src/l2_ApplicationLayer.cpp include/l2_ApplicationLayer.h include/l3_DomainLayer.h include/l4_InfrastructureLayer.h
	$(COMPILE) $(SRC)l2_ApplicationLayer.cpp -o $(BUILD)l2_ApplicationLayer.o

$(BUILD)l3_DomainLayer.o: src/l3_DomainLayer.cpp include/l3_DomainLayer.h include/l4_InfrastructureLayer.h
	$(COMPILE) $(SRC)l3_DomainLayer.cpp -o $(BUILD)l3_DomainLayer.o

$(BUILD)l4_InfrastructureLayer.o: src/l4_InfrastructureLayer.cpp include/l4_InfrastructureLayer.h
	$(COMPILE) $(SRC)l4_InfrastructureLayer.cpp -o $(BUILD)l4_InfrastructureLayer.o

install:
	install $(TARGET) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/lab
