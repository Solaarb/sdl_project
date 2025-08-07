TARGET = jeu.exe

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

# Compilateur et options
CC = gcc
CFLAGS = -Wall -g -I$(INC_DIR) $(shell sdl2-config --cflags)

# Liens SDL
LDFLAGS = $(shell sdl2-config --libs)

# Recherche automatique des fichiers sources
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des .o dans obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le dossier obj s'il n'existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Nettoyage
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)
