# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
LDFLAGS = 

# Archivos fuente
SRCS = main.cpp particle.cpp electron.cpp hit.cpp

# Archivos objeto (sustituir .cpp por .o)
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
TARGET = particle_sim.exe

# Regla principal
all: $(TARGET)

# Linkear todos los objetos para crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados (versión Windows)
clean:
	del /Q $(OBJS) $(TARGET) 2>nul || echo "Archivos no encontrados"

# Limpiar todo y recompilar
rebuild: clean all

# Regla para mostrar ayuda
help:
	@echo Comandos disponibles:
	@echo   make        - Compilar el proyecto
	@echo   make clean  - Eliminar archivos objeto y ejecutable
	@echo   make run    - Compilar y ejecutar
	@echo   make help   - Mostrar esta ayuda

# Compilar y ejecutar
run: all
	$(TARGET)

# Compilar con debugging adicional
debug: CXXFLAGS += -DDEBUG -O0
debug: all

# Versión simplificada sin dependencias automáticas
.PHONY: all clean rebuild help run debug