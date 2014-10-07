#include <stdio.h>
#include <stdlib.h>

#include "main.h"

// wenn ECHO definiert ist, werden Ausgaben zum Debuggen erzeugt
#define ECHO

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
		root->Print();
	}
	printf("\n\n");
}

void Tree::Insert( int data){ // Einfuegen eines Datums
	n_nodes++;

	if( root == NULL){
		root = new TreeNode( data); // Wurzel anlegen
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

TreeNode::TreeNode( int data){ // Konstruktor mit Datum
#ifdef ECHO
	printf("Konstruktor TreeNode( %d)\n", data);
#endif

	this->data = data; // this wegen des Namenskonfliktes
	left = right = NULL;
}
// Implementierung eines Binaerbaumes zum Sortieren von Integers
// Autor: MHB, (c) 23.10.2013

TreeNode::~TreeNode(){ // Destruktor
	if( left  != NULL) delete left;
	if( right != NULL) delete right;

#ifdef ECHO
	printf("Destruktor TreeNode( %d)\n", data);
#endif
}

// Baumknoten “in-order“ ausgeben
void TreeNode::Print(){
    if( left  != NULL) left->Print(); // linker Teilbaum
    printf(" %5d", data);
    if( right != NULL) right->Print(); // rechter Teilbaum
}

// Datenelement einsortieren
void TreeNode::Insert( int data){

    if( this->data > data ){
        /* in linken Teilbaum einfuegen*/
        if( left == NULL) left = new TreeNode( data);
		else left->Insert( data);
    }else{
        /* in rechten Teilbaum einfuegen */
        if( right == NULL) right = new TreeNode( data);
		else right->Insert( data);
    }
}

//---- Testprogramm für Binaerbaum --------------------------------------
void BuildTree(){
    Tree tree; // Konstruktor wird aufgerufen
    int     i, n = 8;
    int     a[] = {7,8,3,5,17,2,10,11};

    /* Elemente a[i] sortiert in 
       den Baum einfuegen */       
    for( i=0; i<n; i++){
        tree.Insert( a[i]);
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
