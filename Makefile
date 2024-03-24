# Répertoires
BUILD_DIR := build
DOCS_DIR := docs
INCLUDE_DIR := include
SRC_DIR := src
TESTS_DIR := tests

# Fichiers source
SRCS := $(wildcard $(SRC_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/ai/*.c) \
        $(wildcard $(SRC_DIR)/controller/*.c) \
        $(wildcard $(SRC_DIR)/model/*.c) \
        $(wildcard $(SRC_DIR)/network/*.c) \
        $(wildcard $(SRC_DIR)/view/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Fichiers source des tests
TEST_SRCS := $(wildcard $(TESTS_DIR)/*.c) \
             $(wildcard $(TESTS_DIR)/ai/*.c) \
             $(wildcard $(TESTS_DIR)/controller/*.c) \
             $(wildcard $(TESTS_DIR)/model/*.c) \
             $(wildcard $(TESTS_DIR)/view/*.c) \
			 $(wildcard $(SRC_DIR)/ai/*.c) \
        	 $(wildcard $(SRC_DIR)/controller/*.c) \
        	 $(wildcard $(SRC_DIR)/model/*.c) \
        	 $(wildcard $(SRC_DIR)/network/*.c) \
        	 $(wildcard $(SRC_DIR)/view/*.c)
TEST_OBJS := $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRCS))

# Nom de l'application principale
APP := hex

# Nom de l'application de tests
TEST_APP := test_hex

# Commande pour générer la documentation avec Doxygen
DOXYGEN := doxygen

# Options du compilateur
CC := gcc
CFLAGS := -Wall -I$(INCLUDE_DIR)

# Création des dossiers build s'ils n'existent pas déjà
$(BUILD_DIR) :
	@mkdir -p $@

# Génération de la configuration Doxyfile si elle n'existe pas
$(DOCS_DIR)/DoxyFile:
	@mkdir -p $(DOCS_DIR)
	echo "INPUT = $(SRC_DIR)" > $@
	echo "OUTPUT_DIRECTORY = $(DOCS_DIR)" >> $@

# Règle de construction des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction des fichiers objets des tests
$(BUILD_DIR)/test_%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction de l'application principale
$(APP): $(OBJS)
	$(CC) $^ -o $@

# Règle de construction de l'application de tests
test: $(TEST_APP) clean

$(TEST_APP): $(TEST_OBJS)
	$(CC) $^ -o $@

# Règle de construction de la documentation
docs: $(DOCS_DIR)/DoxyFile
	$(DOXYGEN) $<
	@ln -s html/index.html $(DOCS_DIR)/Documentation.html 2>/dev/null || \
	(mklink $(DOCS_DIR)\html\index.html $(DOCS_DIR)\Documentation.html && \
	attrib +h $(DOCS_DIR)\Documentation.html)

# Règle pour nettoyer les fichiers générés sauf l'exécutable
clean:
	rm -rf $(BUILD_DIR) $(TEST_APP)

# Règle pour nettoyer les fichiers générés
cleanall: clean
	rm -rf $(APP)

# Définition de la cible par défaut
.DEFAULT_GOAL := all

# Définition de la cible 'clean' comme cible phony
.PHONY: clean cleanall docs test

# Règle pour générer l'exécutable seul
all: $(APP) clean

# Règle pour générer l'exécutable et garder les .o
keep: $(APP)

# Règle pour reconstruire entièrement l'exécutable
rebuild: cleanall all