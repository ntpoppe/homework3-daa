#include <iostream>

// An instance of node represents an element in the adjacency list for a vertex.
struct Node {
	// Constructor for Node using an initializer list. Takes in a vertex (v) and node pointer (n), defaulting to nullptr.
	Node(int v, Node* n = nullptr) {
		vertex = v;
		next = n;
	}

	int vertex;
	Node* next;
};

// A graph class implemented with an array of header nodes.
class Graph {
private:
	int numVerticies; // Number of vertices in the graph.
	Node** adjLists; // Array of pointers. Each point is the head of a linked list.
public:
	// Constructor for graph. Allocates the array and sets each header pointer to nullptr.
	Graph(int n) {
		numVerticies = n;
		adjLists = new Node * [numVerticies];

		for (int i = 0; i < numVerticies; i++) {
			adjLists[i] = nullptr;
		}
	}

	// Destructor for graph. Frees all allocated memory.
	~Graph() {
		for (int i = 0; i < numVerticies; i++) {
			Node* curr = adjLists[i];
			while (curr != nullptr) {
				Node* temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
		delete[] adjLists;
	}

	// Adds an edge between vertices u and v. Since this is undirected, we can add entries to both adjacency lists.
	void addEdge(int u, int v) {
		// Insert v into u's adjacency list
		adjLists[u] = new Node(v, adjLists[u]);

		// Insert u and v's adjacency list
		adjLists[v] = new Node(u, adjLists[v]);
	}

	void deleteEdge(int u, int v) {
		// Remove v from u's list.
		Node* curr = adjLists[u];
		Node* prev = nullptr;
		while (curr != nullptr) {
			if (curr->vertex == v) {
				if (prev == nullptr)
					adjLists[u] = curr->next;
				else
					prev->next = curr->next;

				delete curr;
				break;
			}

			prev = curr;
			curr = curr->next;
		}

		// Remove u from v's list.
		curr = adjLists[v];
		prev = nullptr;
		while (curr != nullptr) {
			if (curr->vertex == u) {
				if (prev == nullptr)
					adjLists[v] = curr->next;
				else
					prev->next = curr->next;

				delete curr;
				break;
			}

			prev = curr;
			curr = curr->next;
		}
	}

	// Utility to help visualize the graph's structure, printing out each vertex's adjacency list.
	void printGraph() {
		for (int i = 0; i < numVerticies; i++) {
			std::cout << "Vertex " << i << ": ";
			Node* curr = adjLists[i];
			while (curr != nullptr) {
				std::cout << curr->vertex << " -> ";
				curr = curr->next;
			}

			std::cout << "NULL" << std::endl;
		}
	}
};

int main() {
	// Create a graph with 7 vertices.
	int vertices = 7;
	Graph g(vertices);

	// Add some edges.
	// 0-1, 1-4, 2-3, 1-3, 3-4, 5-2, 1-6, 6-2, 6-3.
	g.addEdge(0, 1);
	g.addEdge(1, 4);
	g.addEdge(2, 3);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(5, 2);
	g.addEdge(1, 6);
	g.addEdge(6, 2);
	g.addEdge(6, 3);

	std::cout << "Graph after adding edges:" << std::endl;
	g.printGraph();

	// Deletes the edge 1-4 
	std::cout << "\nDeleting edge 1-4:" << std::endl;
	g.deleteEdge(1, 4);

	std::cout << "\nGraph after deleting edge 1-4:" << std::endl;
	g.printGraph();

	return 0;
}

