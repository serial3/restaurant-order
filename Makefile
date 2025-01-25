CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LDFLAGS = -lgmock_main -lgmock -lgtest -lgtest_main -pthread

# Diretórios de include
INCLUDES = -Iconfigreader -Iorder -Isales

# Fontes e objetos
TESTS = order/test_order
APP = main
TEST_SRCS = order/test_order.cpp
SRC_SRCS = $(wildcard configreader/*.cpp order/*.cpp sales/*.cpp)
OBJS = $(filter-out $(TEST_SRCS:.cpp=.o), $(SRC_SRCS:.cpp=.o))

# Alvo padrão
all: $(TESTS) $(APP)

# Compilação dos testes
$(TESTS): $(TEST_SRCS) $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(INCLUDES)

# Compilação da aplicação principal
$(APP): $(OBJS) main.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDES)

# Regra geral para compilar arquivos .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(TESTS) $(APP) $(OBJS) main.o

# Executar testes
run-tests: $(TESTS)
	./$(TESTS)

# Executar aplicação principal
run: $(APP)
	./$(APP)