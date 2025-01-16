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
int sortingIndex = 3;
using namespace std;
using namespace std::chrono;

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

/////////////////// RB-Tree ///////////////////
class RB_tree
{
private:
    Node *root;

public:
    publisher *best_seller[3];
    stack<string> tree_deep_stack;

    Node *get_root();

    Node *RB_insert(Node *root, Node *ptr);
    void insertValue(vector<string>);
    void RB_left_rotate(Node *);
    void RB_right_rotate(Node *);
    void RB_insert_fixup(Node *);
    void preorder();
    void find_best_seller();

    RB_tree();
    ~RB_tree();
};

void Node::set_color(int color)
{
    this->color = color;
}

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


RB_tree generate_RBT_tree_from_csv(string file_name)
{
    RB_tree temp_RBtree;

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

        temp_RBtree.insertValue(tokens);

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
            temp_RBtree.find_best_seller();
            print_best_sellers(year - 1, temp_RBtree.best_seller);
        }
    }
    temp_RBtree.find_best_seller();
    print_best_sellers(year, temp_RBtree.best_seller);
    return temp_RBtree;
}
bool searchInRBT(Node *root, const string &name) {
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
RB_tree sortAndSearch(const string &inputFile, const string &outputFile, int columnToSort, bool ascending, int searchCount)
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

   
    RB_tree RB = generate_RBT_tree_from_csv(outputFile);

    
    vector<string> random_names;
    srand(0);
    for (int i = 0; i < searchCount; i++)
    {
        random_names.push_back(rows[rand() % rows.size()][0]); 
    }

    
    auto start = high_resolution_clock::now();
    for (const auto &name : random_names)
    {
        searchInRBT(RB.get_root(), name);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    
    double averageTime = static_cast<double>(duration.count()) / searchCount;
    cout << "Average time taken for a search in RBT is " << averageTime << " nanoseconds." << endl;

    
    inFile.close();
    outFile.close();

    return RB;
}


////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char *argv[])
{

     RB_tree RBtree = generate_RBT_tree_from_csv(argv[1]);
     RBtree.preorder();
    //  Fill this function.
    //bool ascending = true; // Explicitly setting the default value
    //int searchCount = 50;
    //RB_tree RBtree = sortAndSearch(argv[1], "outputfile", 0, ascending, searchCount);sortAndSearch takes an output file paremetr to output to sorted version of the file to make sure that it is sorted
    return EXIT_SUCCESS;
}

/////////////////// Node ///////////////////

Node::Node(publisher key)
{
    this->key = key;
    this->color = 1; // "RED";
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

/////////////////// RB-Tree ///////////////////
Node *RB_tree::get_root()
{

    // Fill this function.

    return this->root;
}

Node *RB_tree::RB_insert(Node *root, Node *ptr)
{

    if (root == nullptr)
    {
        root = ptr;
        return root;
    }
    if (ptr->key.name < root->key.name)
    {
        root->left = RB_insert(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->key.name > root->key.name)
    {
        root->right = RB_insert(root->right, ptr);
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

void RB_tree::insertValue(vector<string> n)
{

    publisher temp;
    temp.name = n[sortingIndex];
    temp.na_sales = stof(n[4]);
    temp.eu_sales = stof(n[5]);
    temp.others_sales = stof(n[6]);
    int year = stoi(n[2]);

    Node *newNode = new Node(temp);
    this->root = RB_insert(this->root, newNode);
    RB_insert_fixup(newNode);
}
void RB_tree::RB_left_rotate(Node *ptr)
{

    Node *temp = ptr->right; 
    ptr->right = temp->left; 

    if (temp->left != nullptr)
    {
        temp->left->parent = ptr; 
    }

    temp->parent = ptr->parent; 

    if (ptr->parent == nullptr)
    {
        root = temp; 
    }
    else if (ptr == ptr->parent->left)
    {
        ptr->parent->left = temp; 
    }
    else
    {
        ptr->parent->right = temp; 
    }

    temp->left = ptr;   
    ptr->parent = temp; 
}

void RB_tree::RB_right_rotate(Node *ptr)
{

    Node *temp = ptr->left;  
    ptr->left = temp->right; 

    if (temp->right != nullptr)
    {
        temp->right->parent = ptr; 
    }

    temp->parent = ptr->parent; 

    if (ptr->parent == nullptr)
    {
        root = temp; 
    }
    else if (ptr == ptr->parent->right)
    {
        ptr->parent->right = temp; 
    }
    else
    {
        ptr->parent->left = temp; 
    }

    temp->right = ptr;  
    ptr->parent = temp; 
}

void RB_tree::RB_insert_fixup(Node *ptr)
{
    while (ptr != this->root && ptr->parent != nullptr && ptr->parent->color == 1)
    {
        if (ptr->parent == ptr->parent->parent->left)
        {
            Node *uncle = ptr->parent->parent->right;
            if (uncle != nullptr && uncle->color == 1)
            {
                ptr->parent->set_color(0);         // Parent becomes BLACK
                uncle->set_color(0);               // Uncle becomes BLACK
                ptr->parent->parent->set_color(1); // Grandparent becomes RED
                ptr = ptr->parent->parent;         // Move to grandparent
            }
            else
            {
                if (ptr == ptr->parent->right)
                {
                    ptr = ptr->parent;
                    this->RB_left_rotate(ptr);
                }
                ptr->parent->set_color(0);
                ptr->parent->parent->set_color(1);
                this->RB_right_rotate(ptr->parent->parent);
            }
        }
        else
        {
            Node *uncle = ptr->parent->parent->left;
            if (uncle != nullptr && uncle->color == 1)
            {
                ptr->parent->set_color(0);
                uncle->set_color(0);
                ptr->parent->parent->set_color(1);
                ptr = ptr->parent->parent;
            }
            else
            {
                if (ptr == ptr->parent->left)
                {
                    ptr = ptr->parent;
                    this->RB_right_rotate(ptr);
                }
                ptr->parent->set_color(0);
                ptr->parent->parent->set_color(1);
                this->RB_left_rotate(ptr->parent->parent);
            }
        }
    }
    this->root->set_color(0); // Root is always BLACK
}

void RB_tree::preorder()
{
    stack<pair<int, Node*> > Stack;
    Stack.push(make_pair(0, this->root));
    while (!Stack.empty())
    {
        pair<int, Node*> index = Stack.top();
        Stack.pop();
        for (int i = 0; i < index.first; i++)
        {
            cout<< "-";
        }
        cout << "(" << (index.second->color == 1 ? "RED" : "BLACK") << ")" << index.second->key.name << "\n";
        if (index.second->right != nullptr)
        {
            Stack.push(make_pair(index.first+1,index.second->right));
        }
        if (index.second->left != nullptr)
        {
            Stack.push(make_pair(index.first+1,index.second->left));
        }
    }
}



void RB_tree::find_best_seller()
{

    stack<Node *> preorder;
    if (root != nullptr)
    {
        preorder.push(root);
    }
    if (root == nullptr)
    {
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

RB_tree::RB_tree()
{
    this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

RB_tree::~RB_tree()
{
}