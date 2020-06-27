#include <iostream> 
#include <list> 
#include <vector>
#include <iomanip>
using namespace std;

class Matrix
{
public:
	int** liczby;
	int N;
	Matrix(int N);

	void input();
	void print();

private:

};

Matrix::Matrix(int N)
{
	this->N = N;

	liczby = new int* [N];
	for (size_t i = 0; i < N; i++)
	{
		liczby[i] = new int[N];
		for (size_t j = 0; j < N; j++) { liczby[i][j] = 0; }
	}
	this->input();
}

void Matrix::input()
{

	for (size_t i = 0; i < N; i++)
	{
		cout << "Podaj " << N << " kolumn " << i + 1 << " wiersza: ";
		for (size_t j = 0; j < N; j++)
		{
			cin >> this->liczby[i][j];
		}
	}
}

void Matrix::print()
{
	cout << "   ";
	for (int i = 0; i < N; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (int i = 0; i < N; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < N; j++)
			cout << setw(3) << liczby[i][j];
		cout << endl;
	}
}


class Graph
{
	int V;
	list<int>* adj;

public:
	Graph(int V) 
	{ 
		this->V = V; 
		adj = new list<int>[V]; 
	}

	void addEdge(int v, int w);
	bool isConnected();
	int isEulerian();
	void test();
	void DFS(int v, bool visited[]);

	void matrix_to_list(int** tab);
	void matrix_to_list(Matrix m);	

};

void Graph::addEdge(int w1, int w2)
{
	adj[w1].push_back(w2);
	adj[w2].push_back(w1);
}

void Graph::DFS(int v, bool visited[])
{
	visited[v] = true;
	list<int>::iterator i;

	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i, visited);
}

bool Graph::isConnected()
{
	bool* visited = new bool[V];
	int i;

	for (i = 0; i < V; i++) { visited[i] = false; }

	for (i = 0; i < V; i++)
		if (adj[i].size() != 0)
			break;


	if (i == V) { return true; }

	DFS(i, visited);

	for (i = 0; i < V; i++)
		if (visited[i] == false && adj[i].size() > 0)
			return false;
	return true;
}

int Graph::isEulerian()
{
	if (isConnected() == false) { return 0; }

	int odd = 0;
	for (int i = 0; i < V; i++)
		if (adj[i].size() & 1)
			odd++;

	if (odd > 2) { return 0; }


	return (odd) ? 1 : 2;
}
void Graph::test()
{
	switch (isEulerian())
	{
	case 0:
		cout << "Graf nie jest Eulerowy" << endl;
		break;
	case 1:
		cout << "Graf posiada sciezke Eulera" << endl;
		break;
	case 2:
		cout << "Graf posiada cykl Eulera" << endl;
		break;
	default:
		break;
	}
}

void Graph::matrix_to_list(int **tab)
{
	for (size_t i = 1; i < this->V; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (tab[i][j]) this->addEdge(i, j);
		}
	}
}

void Graph::matrix_to_list(Matrix m)
{
	for (size_t i = 1; i < this->V; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (m.liczby[i][j]) this->addEdge(i, j);
		}
	}
}



// Driver program to test above function 
int main()
{
	int N=0;
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> N;

	Matrix macierz(N);
	macierz.print();

	Graph graf(N);
	graf.matrix_to_list(macierz);
	graf.test();	


	system("pause");
	return 0;
}

