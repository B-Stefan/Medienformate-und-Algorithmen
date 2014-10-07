// Implementierung eines Binaerbaumes zum Sortieren von Integers
// Autor: MHB, (c) 23.10.2013

#ifndef MAIN_H
  #define MAIN_H /* zur Vermeidung von Mehrfachinklusion */

class TreeNode; // Deklaration, da von Tree verwendet

// Hauptklasse für Baum
class Tree{
private:
	int n_nodes; // Anzahl der Knoten
	TreeNode *root; // Wurzel

public:
	Tree(); // Konstruktor
	~Tree(); // Destruktor

	void Insert( int data); // Hinzufuegen eines Datums
	void Print(); // Ausgeben des sortierten Baumes
};

// Hilfsklasse für Baumknoten
class TreeNode{ // so koennte das in C++ aussehen
private: // Zugriff nur für Methoden der Klasse
    int data;       
    TreeNode *left, *right;

public:
	TreeNode(); // Konstruktoren
	TreeNode( int data);

	~TreeNode(); // Destruktor

	void Insert( int data); // Hinzufuegen eines Datums
	void Print(); // Ausgeben des sortierten Baumes
};


/* Testprogramm für Binaerbaum */
int main();

#endif /* MAIN_H */ 