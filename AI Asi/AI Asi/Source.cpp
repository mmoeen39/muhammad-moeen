#include <iostream>
#include <string>
#include<queue>
#include<cctype>
#include<algorithm>
#include<set>
using namespace std;
class Node
{
public:
	int state;
	int action;
	Node* parent;
	int cost;

	Node();
	Node(Node&);
};
Node::Node()
{
	cost = 1;
	action = -1;
	parent = NULL;
	state = -1;
}
Node::Node(Node& n)
{
	this->state = n.state;
	this->cost = n.cost;
	this->parent = n.parent;
	this->action = n.action;
}
int m, n, t;
void input();
void display();
bool isGoal(int);
void GraphSearch();
void splitIntoStrings(string str);
Node* getChild(Node*, int);
queue<Node*>frontier;
set<Node*>exploredSet;
string* states;
string* actions;
string* plansGenerated;
int** TransistionTable;
string initialState, finalState;
int main()
{
	input();
	display();
	for (int i = 0; i < t; i++)
	{
		splitIntoStrings(plansGenerated[i]);
		GraphSearch();
		cout << endl;
	}
	system("pause");

}
void input()
{
	cout << "enter the number of states:\n";
	cin >> m;
	while (m < 1)
	{
		cout << "wrong input,enter again\n";
		cin >> m;
	}
	cout << "enter the number of actions:\n";
	cin >> n;
	while (n < 1)
	{
		cout << "wrong input,enter again\n";
		cin >> n;
	}
	cout << "enter the number of plans to be generated:\n";
	cin >> t;
	while (t < 1)
	{
		cout << "wrong input,enter again\n";
		cin >> t;
	}


	states = new string[m];
	actions = new string[n];
	plansGenerated = new string[t];

	cin.ignore();

	cout << "\nenter states\n";
	for (int i = 0; i < m; i++)
		getline(cin, states[i]);

	cout << "\nenter actions\n";
	for (int i = 0; i < n; i++)
		getline(cin, actions[i]);

	TransistionTable = new int*[m];
	for (int i = 0; i < m; i++)
		TransistionTable[i] = new int[n];

	cout << "enter values of transition\t";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> TransistionTable[i][j];
	}


	cout << "enter values for tests\n";
	for (int i = 0; i < t; i++)
		getline(cin, plansGenerated[i]);

}
void display()
{


	cout << "\nstates are :\n";
	for (int i = 0; i < m; i++)
		cout << states[i] << "\n";

	cout << "\nactions are\n";
	for (int i = 0; i < n; i++)
		cout << actions[i] << "\n";



	cout << "\ntransition table is:\n";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << TransistionTable[i][j] << "\t";
		cout << "\n";
	}


	cout << "plnas to be tested are\n";
	for (int i = 0; i < t; i++)
		cout << plansGenerated[i] << "\n";

}
bool isGoal(int a)
{
	int check = -1;
	for (int i = 0; i < m; i++)
	{
		if (transform(states[i].begin(), states[i].end(), states[i].begin(), ::toupper) == transform(finalState.begin(), finalState.end(), finalState.begin(), ::toupper))
		{
			check = i;
		}
	}
	if (a == check)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void splitIntoStrings(string str)
{
	int len = str.length();
	int x = 0;
	initialState = "";
	finalState = "";
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '	')
		{
			x = i;
			break;
		}
		else
		{
			initialState = initialState + str[i];
			i = i + 1;
		}
	}
	int k = x + 1;
	while (str[k] != '\0')
	{
		finalState = finalState + str[k];
		k = k + 1;
	}
}
void GraphSearch()
{
	Node* initial;
	initial = new Node();
	int a;
	for (int i = 0; i < m; i++)
	{
		if (transform(initialState.begin(), initialState.end(), initialState.begin(), ::toupper) == transform(states[i].begin(), states[i].end(), states[i].begin(), ::toupper))
		{
			a = i;
			break;
		}
	}
	initial->state = a;
	frontier.push(initial);
	while (!frontier.empty())
	{
		if (isGoal(frontier.front()->state))
		{
			if (frontier.front()->parent == NULL)
			{
				cout << "current state is the goal";
				exploredSet.insert(frontier.front());
				frontier.pop();
			}
			else
			{
				int count = 0;
				string* solution;
				Node* temp = new Node;
				temp = frontier.front();
				while (temp->parent != NULL)
				{
					count++;
					temp = temp->parent;
				}
				solution = new string[count];
				temp = frontier.front();
				int i = 0;
				while (temp->parent != NULL)
				{

					solution[i] = actions[temp->action];
					i++;
					temp = temp->parent;
				}
				for (int k = count; k > 0; k++)
				{
					cout << solution[k] << "->";
				}
			}
			exploredSet.insert(frontier.front());
			frontier.pop();

		}
		else
		{
			Node* temp1 = new Node();
			temp1 = frontier.front();
			exploredSet.insert(frontier.front());
			frontier.pop();
			for (int i = 0; i < n; i++)
			{
				Node* child = new Node();
				child = getChild(temp1, i);
				if (exploredSet.find(child) == exploredSet.end())
				{
					continue;
				}
				else
				{
					frontier.push(child);
				}

			}
		}
		if (frontier.empty())
		{
			cout << "No solution exists";
		}
	}
}
Node* getChild(Node* node, int a)
{
	Node* child;
	child = new Node();
	child->parent = node;
	child->action = a;
	child->state = TransistionTable[node->state][a];
	child->cost = node->cost + 1;
	return child;
}