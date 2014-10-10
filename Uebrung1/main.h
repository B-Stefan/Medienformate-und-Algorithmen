// Implementierung eines Binaerbaumes zum Sortieren von Integers
// Autor: MHB, (c) 23.10.2013
#include "string.h"
#ifndef MAIN_H
#define MAIN_H /* zur Vermeidung von Mehrfachinklusion */

class TreeNode; // Deklaration, da von Tree verwendet

// Hauptklasse f�r Baum
class Tree{
private:
	int n_nodes; // Anzahl der Knoten
	TreeNode *root; // Wurzel

public:
	Tree(); // Konstruktor
	~Tree(); // Destruktor

	void Insert(std::string data); // Hinzufuegen eines Datums
	void Print(); // Ausgeben des sortierten Baumes
};

// Hilfsklasse f�r Baumknoten
class TreeNode{ // so koennte das in C++ aussehen
private: // Zugriff nur f�r Methoden der Klasse
    std::string data;
    TreeNode *left, *right;
    int* tree_n_nodes;

public:
	TreeNode(); // Konstruktoren
	TreeNode(std::string data, int * n_nodes);

	~TreeNode(); // Destruktor

	void Insert(std::string data); // Hinzufuegen eines Datums
	void Print(); // Ausgeben des sortierten Baumes
};


/* Testprogramm f�r Binaerbaum */
int main();

#endif /* MAIN_H */ 