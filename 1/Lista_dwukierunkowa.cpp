#include <iostream>

//Definicja listy dwukierunkowej
typedef long T;

typedef struct NODE {
	T value;
	struct NODE* next;
	struct NODE* prev;
} Node;

typedef struct {
	Node* first;
	Node* last;
} List;

//Usuwanie elementu z listy dwukierunkowej
void remove2(List& L, Node* e)
{
	if (e->prev)
		e->prev->next = e->next;
	else
		L.first = e->next;
	if (e->next)
		e->next->prev = e->prev;
	else
		L.last = e->prev;
	delete e;
}

//Wyszukiwanie w liście dwukierunkowej
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


//Funkcje do stworzenia:
//-----------------------------------------------//


void push_front(List* L, T w)
{
	Node* p = new Node;
	p->value = w;
	p->next = L->first;
	p->prev = NULL;
	L->first = p;
	if (p->next)
		p->next->prev = p;
	else L->last = p;
}

void push_back(List* L, T w)
{
	Node* p = new Node;
	p->value = w;
	p->next = NULL;
	p->prev = L->last;
	L->last = p;
	if (p->prev)
		p->prev->next = p;
	else L->first = p;
}

void pop_2(List* L, T w)
{
	Node* address = search(L, w);
	remove2(*L, address);
}

void pop_front2(List* L)
{
	remove2(*L, L->first);
}

void pop_back2(List* L)
{
	remove2(*L, L->last);
}

int insert(List* L, T value) {
	//Zmienne pomocnicze
	Node* new_;
	Node* curr;
	Node* prev;

	new_ = new Node; /* Utwórz element Node*/

	if (new_ == NULL)
	{ /* weryfikacja przydzielonej pamieci*/
		printf("Nie udalo sie przydzielic pamieci");
		return 1;
	}

	else
	{ /* Ustal dane elementarne w Node*/
		new_->value = value;
		new_->next = NULL;
		new_->prev = NULL;
	}

	//Jeśli lista jest pusta
	if (L->first == NULL)
	{
		L->first = new_;
		L->last = new_;
		new_->next = NULL;
		new_->prev = NULL;
	}
	else
	{
		curr = L->first;
		prev = NULL;

		while ((curr != NULL) && (value > curr->value))
		{
			prev = curr;
			curr = curr->next;

		}
		//Jeśli podamy mniejszą liczbę niż poprzednie
		if (curr != NULL)
		{
			prev->next = new_;
			new_->prev = prev;
			new_->next = curr;
			curr->prev = new_;
		}
		//Jesli podamy większą liczbę niż poprzednie
		else
		{
			prev->next = new_;
			new_->prev = prev;
			L->last = new_;
		}

	}
	return 0;
}

int delete_(List *L, T value)
{
	Node *prev;
	Node *curr;

	if (L->first == NULL)
	{
		return 1; /* Lista pusta */
	}
	else
	{	//Jeśli trzeba usunąć pierwszy element
		if (value == L->first->value)
		{
			curr = L->first;
			L->first = L->first->next;
			L->first->prev = NULL;
			delete curr;
		}
		else
		{ /* znajdz w liscie element do usuniecia*/
			prev = L->first;
			curr = L->first->next;
			while (curr != NULL && curr->value != value)
			{
				prev = curr;
				curr = curr->next;
			}
			if (curr == NULL)
			{
				return 1;
				/* element nie zostalznaleziony */
			}
			else
			{

				/* Usun znaleziony element */
				prev->next = curr->next;
				if (curr->next == NULL)
					L->last = prev;
				if (curr->next != NULL)
					curr->next->prev = prev;
				delete curr;
			}
		}
	}
	return 0;
}



int main()
{

	List* Lista = new List;
	Lista->first = Lista->last = NULL;

	push_front(Lista, 1);
	push_front(Lista, 2);
	push_front(Lista, 3);
	push_back(Lista, 4);
	push_back(Lista, 5);
	push_back(Lista, 6);
	pop_2(Lista, 2);
	pop_front2(Lista);
	pop_back2(Lista);

	List* Lista2 = new List;
	Lista2->first = Lista2->last = NULL;

	insert(Lista2, 1);
	insert(Lista2, 10);
	insert(Lista2, 2);
	insert(Lista2, 20);
	delete_(Lista2, 2);



	system("pause");
}
