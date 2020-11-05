#include<stdio.h>
#include<stdlib.h>
#include "tree_red_black.h"


Node* make_t_nill( ){

	Node *t_nill;

	t_nill = (Node *)calloc(1,sizeof(Node) );
	if( !t_nill ){
		printf("erro ao alocar memoria\n");
		exit(1);
	}

	t_nill->color = 1;
	t_nill->right = NULL;
	t_nill->left = NULL;
	t_nill->parent = NULL;
	t_nill->key = 1000;

	return t_nill;

}

int altura_no( Node *r , Node *t_nill ){
	
	if( r == t_nill ) return -1;
	
	if( altura_no(r->left,t_nill) > altura_no(r->right,t_nill) )
		return ( altura_no(r->left,t_nill) + 1 );
	else
		return ( altura_no(r->right,t_nill) + 1 );
}

Tree* make_tree(  Node *t_nill ){

	Tree *t1;

	t1 = (Tree *)calloc(1,sizeof(Tree));
	if( !t1 ){
		printf("erro ao alocar memoria fim do programa.\n");
		exit(1);
	}

	t1->root = t_nill;
	return t1;
}

int tree_empty( Tree *t , Node *t_nill ){

	if( t->root == t_nill ) return 1; 
	return 0; 
}

int em_ordem( Node *no ,Node *t_nill ){

	if( no == t_nill ) return 0;
	else{

		em_ordem(no->left,t_nill);
		printf(" key:%d ",no->key);
		if( no->color == 1 ) printf("cor:preto  ");
		else printf("cor:vermelho ");
		em_ordem(no->right,t_nill);
	}	

}

int right_rotate( Node *no, Tree *t ){

	Node *aux;

	aux = no->left;
	no->left = aux->right;
	if( aux->right->key != 1000 ) aux->right->parent = no ; 
	aux->right = no;
	aux->parent = no->parent ;
	no->parent = aux;
	if( t->root == no ) t->root = aux;
	else{
			if( aux->parent->key > aux->key ) aux->parent->left = aux;
			else aux->parent->right = aux;
	}

	return 1; 
}

int left_rotate( Node *no , Tree *t ){

	Node *aux;
	aux = no->right; 
	no->right = aux->left;
	if( aux->left->key != 1000 ) aux->left->parent = no;
	aux->left = no; 

	aux->parent = no->parent;
	no->parent = aux;
	if( t->root == no ) t->root = aux;
	else{
			if( aux->parent->key > aux->key ) aux->parent->left = aux;
			else aux->parent->right = aux;
	}

	return 1;

}

int RB_insert_fixup( Node *no , Tree *t ){

	Node *tio;

	while( no->parent->color == 0 ){
		if( no->parent == no->parent->parent->left ){
			tio = no->parent->parent->right;
			if( tio->color == 0 ){

				no->parent->color = 1; 
				tio->color = 1; 
				no->parent->parent->color = 0; 
				no = no->parent->parent; 


			}
			else{

				if( no == no->parent->right ){
					no = no->parent;
					left_rotate( no , t );


				}
				no->parent->color = 1;	
				no->parent->parent->color = 0;	
				right_rotate( no->parent->parent , t );

			}	
		}	
		else{
			tio = no->parent->parent->left;
			if( tio->color == 0 ){

				no->parent->color = 1; 
				tio->color = 1; 
				no->parent->parent->color = 0; 
				no = no->parent->parent; 


			}
			else{
				if( no == no->parent->left ){
					no = no->parent;
					right_rotate( no , t );


				}
				no->parent->color = 1;	
				no->parent->parent->color = 0;
				left_rotate( no->parent->parent , t );

			}	

		}
	}
	t->root->color = 1;
}

int insert_node(Tree *t , int info , Node *t_nill ){

	Node *aux,*ant; 
	Node *new_node;	

	aux = t->root;
	ant = t->root;

	while( aux != t_nill ){
		if( aux->key < info ){
			ant = aux;
			aux = aux->right;

		}
		else{
			ant = aux;
			aux = aux->left;
		}

	}
	new_node = ( Node *)calloc(1,sizeof( Node ));
	if( !new_node ){
		printf("erro na memoria.");
		exit(1);
	}
	new_node->key = info;
	new_node->color = 0;
	new_node->right = t_nill;
	new_node->left = t_nill;
	if( ant == t_nill ){

		t->root = new_node;
		new_node->parent = t_nill;
	}
	else{
			new_node->parent = ant;
			if( info > ant->key )
				ant->right = new_node;
			else
				ant->left = new_node;
	}
	RB_insert_fixup( new_node , t);
	return 1;

}

Node* search_minimo( Node *no , Node *t_nill ){

	Node *ant;
	while( no != t_nill ){
		ant=no;
		no=no->left;
	}
	return ant;
}

Node* search_maximo( Node *no , Node *t_nill){
	Node *ant;
	while( no != t_nill ){
		ant=no;
		no=no->right;
	}
	return ant;
}

int delete_node( Tree *t , int info , Node *t_nill ){

	Node *aux,*guarda;
	Node *maximo;
	Node *x;
	int cor_removida;
	aux = t->root;
	while(  aux->key != info ){
		if( aux->key > info ){

			aux = aux->left;
		}
		else{

			aux = aux->right;
		}
	}
	while( 1 ){
		cor_removida = aux->color;
		if( aux->right == t_nill ){
			x = aux->left;
			if( aux->parent != t_nill ){
				if( aux->left != t_nill ) aux->left->parent = aux->parent;
				if( aux->parent->key >= aux->key ){
					aux->parent->left=aux->left;
				}
				else aux->parent->right=aux->left;
			}
			else{
				t->root = aux->left;
				if( aux->left != t_nill ) aux->left->parent = aux->parent;
			}	
			break;
		}
		else if( aux->left == t_nill ){
			x = aux->right;
			if( aux->parent != t_nill ){
				aux->right->parent = aux->parent;
				if( aux->parent->key > aux->key ){
					aux->parent->left=aux->right;

				}
				else aux->parent->right=aux->right;
			}
			else{
			 	t->root = aux->right;
			 	if( aux->right != t_nill ) aux->right->parent = aux->parent;
			} 	
			break;
		}
		else{
			maximo = search_maximo( aux->left ,t_nill );
			aux->key = maximo->key;
			aux = maximo;
		}
	}
	guarda = aux->parent;
	free(aux);
	if( cor_removida == 1 ){
		if( x == t_nill ){
			x->parent = guarda; 
		}
		RB_delete_fix_up(t,x);	
	}
	return 1;
}
int RB_delete_fix_up(Tree *t,Node *x ){
	Node *irmao;
	while( x != t->root && x->color == 1 ){
		if( x == x->parent->left ){
			irmao = x->parent->right;
			if( irmao->color == 0 ){
				irmao->color = 1; 
				x->parent->color = 0 ; 
				left_rotate(x->parent,t); 
				irmao = x->parent->right;
			}
			if( irmao->left->color == 1  && irmao->right->color == 1 ){

				irmao->color = 0; 
				x = x->parent;

			}
			else{
				if( irmao->right->color == 1 ){
					irmao->left->color = 1; 
					irmao->color = 0;	
					right_rotate(irmao,t);
					irmao = x->parent->right;
				}
				irmao->color = x->parent->color;
				x->parent->color = 1;
				irmao->right->color = 1;
				left_rotate(x->parent,t);
				x = t->root;
			}
		}	
		else{
			irmao = x->parent->left;
			if( irmao->color == 0 ){
				irmao->color = 1;
				x->parent->color = 0 ;
				right_rotate(x->parent,t); 
				irmao = x->parent->left;

			}
			if( irmao->left->color == 1  && irmao->right->color == 1 ){

				irmao->color = 0; 
				x = x->parent;

			}
			else{
				if( irmao->left->color == 1 ){

					irmao->right->color = 1; 
					irmao->color = 0;	
					left_rotate(irmao,t);
					irmao = x->parent->left;

				}
				
				irmao->color = x->parent->color;
				x->parent->color = 1;
				irmao->left->color = 1;
				right_rotate(x->parent,t);
				x = t->root;
			}
		}
	}	

	x->color = 1; 

	return 1;
}