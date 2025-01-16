#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;
int sortingIndex = 3;

/////////////////// Player ///////////////////
class publisher
{
public:
	string name;
	float na_sales;
	float eu_sales;
	float others_sales;
};

/////////////////// Node ///////////////////
class Node
{
public:
	publisher key;
	int color; // "Red"=1 or "Black"=0
	Node *parent, *left, *right;

	Node(publisher);
	~Node();
	int get_color();
	void set_color(int);
};

/////////////////// BST-Tree ///////////////////
class BST_tree
{
private:
	Node *root;

public:
	publisher *best_seller[3];
	stack<string> tree_deep_stack;

	Node *get_root();

	Node *BST_insert(Node *root, Node *ptr);
	void insertValue(vector<string>);
	void find_best_seller();

	BST_tree();
	~BST_tree();
};

void print_best_sellers(int year, publisher *temp_publisher[3])
{
	cout.precision(5);
	cout << "End of the " + to_string(year) + " Year" << endl;
	cout << "Best seller in North America: " + temp_publisher[0]->name + " - " << temp_publisher[0]->na_sales << " million" << endl;
	cout << "Best seller in Europe: " + temp_publisher[1]->name + " - " << temp_publisher[1]->eu_sales << " million" << endl;
	cout << "Best seller rest of the World: " + temp_publisher[2]->name + " - " << temp_publisher[2]->others_sales << " million" << endl;
}
vector<string> tokenizeCSVLine(const string &line) {
    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = line.find(',', start)) != string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(line.substr(start));

    return tokens;
}
bool searchInBST(Node *root, const string &name) {
    while (root != nullptr) {
        if (root->key.name == name) {
            return true;
        }
        if (name < root->key.name) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return false;
}
BST_tree generate_BST_tree_from_csv(string file_name)
{
	BST_tree temp_BSTtree;

	ifstream csvFile(file_name);
	string line;

	// Skip the header line
	getline(csvFile, line);

	vector<int> decade; 
		int year;
	
	while (getline(csvFile, line))
	{
		vector<string> tokens = tokenizeCSVLine(line); 

		if (tokens.size() != 7)
			continue; 

		
		temp_BSTtree.insertValue(tokens);

		// Decade calculation
		 year = stoi(tokens[2]); 
		if (year <= 1990)
		{
			decade.push_back(0);
		}
		else if (year <= 2000)
		{
			decade.push_back(1);
		}
		else if (year <= 2010)
		{
			decade.push_back(2);
		}
		else if (year <= 2020)
		{
			decade.push_back(3);
		}

		// Check if the decade has changed
		if (decade.size() >= 2 && decade[decade.size() - 1] - decade[decade.size() - 2] == 1)
		{
			temp_BSTtree.find_best_seller();
			print_best_sellers(year - 1, temp_BSTtree.best_seller);
		}
	}
	temp_BSTtree.find_best_seller();
	print_best_sellers(year , temp_BSTtree.best_seller);
	return temp_BSTtree;
}

BST_tree sortAndSearch(const string &inputFile, const string &outputFile, int columnToSort, bool ascending, int searchCount)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);
    vector<vector<string>> rows;
    string line;

    
    getline(inFile, line);
    string header = line;

    
    while (getline(inFile, line))
    {
        rows.push_back(tokenizeCSVLine(line));
    }

   
    sort(rows.begin(), rows.end(), [columnToSort, ascending](const vector<string> &a, const vector<string> &b)
         {
        if (ascending) {
            return a[columnToSort] < b[columnToSort];
        } else {
            return a[columnToSort] > b[columnToSort];
        } });

   
    outFile << header << endl;
    for (const auto &row : rows)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            outFile << row[i];
            if (i < row.size() - 1)
            {
                outFile << ",";
            }
        }
        outFile << endl;
    }

    
    BST_tree BST = generate_BST_tree_from_csv(outputFile);

    
    vector<string> random_names;
    srand(0);
    for (int i = 0; i < searchCount; i++)
    {
        random_names.push_back(rows[rand() % rows.size()][0]); // Assuming the first element is the name
    }

    
    auto start = high_resolution_clock::now();
    for (const auto &name : random_names)
    {
        searchInBST(BST.get_root(), name);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    // Compute average search time
    double averageTime = static_cast<double>(duration.count()) / searchCount;
    cout << "Average time taken for a search in BST is " << averageTime << " nanoseconds." << endl;

   
    inFile.close();
    outFile.close();

    return BST;
}






////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char *argv[])
{

	BST_tree BSTtree = generate_BST_tree_from_csv("C:/Users/ASUS/OneDrive/Masaüstü/aaa/HW3_BLG335E/VideoGames.csv");

	// Fill this function.
	//bool ascending = true;  
    //int searchCount = 50;
    //BST_tree BSTtree = sortAndSearch("C:/Users/ASUS/OneDrive/Masaüstü/aaa/HW3_BLG335E/VideoGames.csv", "C:/Users/ASUS/OneDrive/Masaüstü/aaa/HW3_BLG335E/sortedVideoGames.csv", 0, ascending, searchCount);

	return EXIT_SUCCESS;
}

/////////////////// Node ///////////////////

Node::Node(publisher key)
{
	this->key = key;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

Node *BST_tree::get_root()
{

	// Fill this function.

	return this->root;
}

Node *BST_tree::BST_insert(Node *root, Node *ptr)
{
	if (root == NULL)
	{
		root = ptr;
		return root;
	}
	if (ptr->key.name < root->key.name)
	{
		root->left = BST_insert(root->left, ptr);
		root->left->parent = root;
	}
	else if (ptr->key.name > root->key.name)
	{
		root->right = BST_insert(root->right, ptr);
		root->right->parent = root;
	}
	else
	{ // if equal

		root->key.na_sales += ptr->key.na_sales;
		root->key.eu_sales += ptr->key.eu_sales;
		root->key.others_sales += ptr->key.others_sales;
	}
	return root;
}

void BST_tree::insertValue(vector<string> n)
{

	publisher temp;
	temp.name = n[sortingIndex];
	temp.na_sales = stof(n[4]);
	temp.eu_sales = stof(n[5]);
	temp.others_sales = stof(n[6]);
	int year = stoi(n[2]);

	Node *newNode = new Node(temp);
	this->root = BST_insert(this->root, newNode);
}

void BST_tree::find_best_seller()
{

	stack<Node *> preorder;
	if (root != nullptr)
	{
		preorder.push(root);
	}
	if (root == nullptr) {
        best_seller[0] = nullptr;
        best_seller[1] = nullptr;
        best_seller[2] = nullptr;
        return;
    }
	best_seller[0] = &root->key;
	best_seller[1] = &root->key;
	best_seller[2] = &root->key;

	while (!preorder.empty())
	{
		Node *node = preorder.top();
		preorder.pop();
		if (node == nullptr)
			continue;

		if (node)
		{
			if (node->key.na_sales > best_seller[0]->na_sales)
			{
				best_seller[0] = &node->key;
			}
			if (node->key.eu_sales > best_seller[1]->eu_sales)
			{
				best_seller[1] = &node->key;
			}
			if (node->key.others_sales > best_seller[2]->others_sales)
			{
				best_seller[2] = &node->key;
			}
			preorder.push(node->right);
			preorder.push(node->left);
		}
	}
}

BST_tree::BST_tree()
{
	this->root = NULL;
	this->best_seller[0] = NULL;
	this->best_seller[1] = NULL;
	this->best_seller[2] = NULL;
}

BST_tree::~BST_tree()
{
}
