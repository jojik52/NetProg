# Имя исполняемого файла
TARGET = udp_client

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++11

# Исходные файлы
SRCS = main.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
