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

$(TARGET): $(BUILD)main.o $(BUILD)Image.o $(BUILD)Museum.o $(BUILD)Report.o
	$(LINK) -o main $(BUILD)main.o $(BUILD)Image.o $(BUILD)Museum.o $(BUILD)Report.o

$(BUILD)main.o: src/main.cpp include/*.h
	$(COMPILE) $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)Image.o: src/Image.cpp include/*.h
	$(COMPILE) $(SRC)Image.cpp -o $(BUILD)Image.o

$(BUILD)Museum.o: src/Museum.cpp include/*.h
	$(COMPILE) $(SRC)Museum.cpp -o $(BUILD)Museum.o

$(BUILD)Report.o: src/Report.cpp include/*.h
	$(COMPILE) $(SRC)Report.cpp -o $(BUILD)Report.o

install:
	install $(TARGET) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/lab
