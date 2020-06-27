#include <iostream>


//Definicja listy jednokierunkowej
typedef long T;
typedef struct NODE {
	T value;
	struct NODE* next;
} Node;

typedef struct {
	Node* first;
	Node* last;
} List;


//Szukanie elementu 'x' w liœcie
Node* search(List const* L, T x)
{
	Node* p = L->first;
	while (p != NULL) {
		if (p->value == x) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

//Dodanie elementu do listy jednokierunkowej
void push_front(List* L, T w)
{
	Node* p = new Node;
	p->value = w;
	p->next = NULL;
	if (L->first == NULL) { // lista pusta
		L->first = L->last = p;
	}
	else {
		p->next = L->first;
		L->first = p;
	}
}

//Usuniêcie pierwszego elementu z listy jednokierunkowej
void pop_front(List* L)
{
	// jeden element lub lista pusta
	if (L->first == L->last) {
		free(L->first);
		L->first = L->last = NULL;
	}
	else {
		Node* p = L->first;
		L->first = p->next;
		free(p);
	}
}

//Usuniêcie elementu z listy kierunkowej na podstawie adresu
void remove(List* L, Node* e)
{
	Node* p;
	if (L->first == e)
	{
		pop_front(L);
	}
	else
	{
		p = L->first;
		while (p->next != e)
			p = p->next;

		p->next = e->next;
		delete e;
	}
}

//Usuniêcie wybranego elementu z listy jednokierunkowej
void pop_1(List* L, T w)
{
	Node* address = search(L, w);
	remove(L, address);
}



int main()
{

	List* Lista = new List;
	Lista->first = Lista->last = NULL;

	push_front(Lista, 1);
	push_front(Lista, 2);
	push_front(Lista, 3);
	push_front(Lista, 4);
	pop_front(Lista);
	pop_1(Lista, 2);

	system("pause");
}
