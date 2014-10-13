#include <stdio.h>
#include <stdlib.h>
#include "string"
#include "main.h"
#include <iostream>
#include <term.h>

using namespace std;

// wenn ECHO definiert ist, werden Ausgaben zum Debuggen erzeugt


//---- Baumklasse --------------------------------------------------------
Tree::Tree(){ // Konstruktor
#ifdef ECHO
	printf("Konstruktor Tree\n");
#endif

	n_nodes = 0;
	root = NULL;
}

Tree::~Tree(){ // Destruktor
#ifdef ECHO 
	printf("Destruktor Tree\n");
#endif

	if (root != NULL) delete root;
	
#ifdef ECHO
	printf("Der letzte macht das Licht aus ;-)\n");
#endif
}

void Tree::Print(){ // Ausgabe
	if( root == NULL){
		printf("\nleerer Baum\n");
	}else{
		printf("\nAusgabe\nBaum mit %d Knoten:\n", n_nodes);

        int i;
        std::string tabstr;
        tabstr = "";
		root->Print(tabstr);
	}
	printf("\n\n");
}

void Tree::Insert( string data){ // Einfuegen eines Datums
	n_nodes++;

	if( root == NULL){
		root = new TreeNode( data, &n_nodes); // Wurzel anlegen
	}else{
		root->Insert( data); // rekursives Einfuegen
	}
}

//---- Knoten fuer Baum --------------------------------------------------
TreeNode::TreeNode(){ // Konstruktor
#ifdef ECHO
	printf("Konstruktor TreeNode\n");
#endif

	left = right = NULL;
}

TreeNode::TreeNode( string data, int* n_nodes){ // Konstruktor mit Datum
#ifdef ECHO
	cout << "Konstruktor TreeNode       " + data << endl;
#endif

	this->data = data; // this wegen des Namenskonfliktes
    this->tree_n_nodes = n_nodes;
	left = right = NULL;
}
// Implementierung eines Binaerbaumes zum Sortieren von Integers
// Autor: MHB, (c) 23.10.2013

TreeNode::~TreeNode(){ // Destruktor
	if( left  != NULL) delete left;
	if( right != NULL) delete right;


#ifdef ECHO
    cout << "Destruktor TreeNode        " + data << endl;
#endif
}

// Baumknoten �in-order� ausgeben
void TreeNode::Print(std::string tabstr){

    tabstr = tabstr+"\x20";

    if( left  != NULL) {
        left->Print(tabstr);
    } // linker Teilbaum

    cout << tabstr << data << endl;

    if( right != NULL) {
        right->Print(tabstr);
    } // rechter Teilbaum
}


// Datenelement einsortieren
void TreeNode::Insert( string data){

    if( this->data < data ){
        /* in linken Teilbaum einfuegen*/
        if( left == NULL) left = new TreeNode( data, tree_n_nodes);
		else left->Insert( data);
    }else{
        /* in rechten Teilbaum einfuegen */
        if( right == NULL) right = new TreeNode( data, tree_n_nodes);
		else right->Insert( data);
    }
}

//---- Testprogramm f�r Binaerbaum --------------------------------------
void BuildTree(){
    Tree tree; // Konstruktor wird aufgerufen
    int        i, n = 5;
    string     a[] = {"BA", "BC", "A", "BB", "E"};

    /* Elemente a[i] sortiert in 
       den Baum einfuegen */       
    for( i=0; i<n; i++){
        tree.Insert(a[i]);
    }

    /* sortierte Liste ausgeben */
    tree.Print();
}

int main(){
	BuildTree(); // bei Verlassen wird die Datenstruktur wieder abgebaut

	printf("Druecken Sie Enter\n");
	char c;
	scanf("%c", &c); // Ende
}
