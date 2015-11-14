#include "BinTree.h"

////////////////
//Constructors//
////////////////

//-----------------------------------------------
// Default Constructor
//
// Sets the root to NULL
//-----------------------------------------------
BinTree::BinTree()
{
	root = NULL;
}

//-----------------------------------------------
//Copy Constructor
//
// Checks to see if the ree is empty and calls 
// the equals helper if not
//-----------------------------------------------
BinTree::BinTree(const BinTree &a)
{
	if (a.isEmpty())
	{
		root = NULL;
		return;
	}
	else
	{
		operatorEqualsHelper(root, a.root);
		return;
	}
}

//-----------------------------------------------
// Destructor
//
// In the event of destructing, the tree calls 
// the make empty
//-----------------------------------------------
BinTree::~BinTree()
{
	this->makeEmpty();
}

/////////////////////////////
//Operator Overload Helpers//
/////////////////////////////

//-----------------------------------------------
// Output Operator Overload
//
// Prints the tree in order with a helper
//-----------------------------------------------
ostream& operator<<(ostream & o, const BinTree &a)
{
	if (a.isEmpty())
	{
		return o;
	}
	else
	{
		a.inOrderHelper(a.root, o);
		return o;
	}
}

//-----------------------------------------------
// Output Operator Helper
//
// Goes left, prints, and then goes right in
// order to print in the correct order
//-----------------------------------------------
void BinTree::inOrderHelper(Node * leaf, ostream& o) const
{
	if (leaf == NULL)
	{
		return;
	}

	inOrderHelper(leaf->left, o);
	
	o << *(leaf->data) << " ";

	inOrderHelper(leaf->right, o);
}

//-----------------------------------------------
// Operator =
//
// If the tree is empty it does nothing, otherwise
// it calls its helper function
//-----------------------------------------------
BinTree& BinTree::operator=(const BinTree &a)
{
	makeEmpty();
	if (a.isEmpty())
	{
		return *this;
	}
	else
	{
		operatorEqualsHelper(root, a.root);
		return *this;
	}
}

//-----------------------------------------------
// Operator = Helper
//
// Creates a new Node and Nodedata for each leaf
// that comes from the other tree in order to not
// have the trees have Nodes with the same address
//-----------------------------------------------
void BinTree::operatorEqualsHelper(Node *&thisLeaf, Node const *otherLeaf)
{
	thisLeaf = new Node;
	thisLeaf->data = new NodeData;
	*thisLeaf->data = *otherLeaf->data; 
	thisLeaf->left = NULL;
	thisLeaf->right = NULL;
	if (otherLeaf->left != NULL)
	{
		operatorEqualsHelper(thisLeaf->left, otherLeaf->left);
	}
	if (otherLeaf->right != NULL)
	{
		operatorEqualsHelper(thisLeaf->right, otherLeaf->right);
	}
}

//-----------------------------------------------
// Operator ==
//
// Used to compare trees
//-----------------------------------------------
bool BinTree::operator==(const BinTree &a) const
{
	return ComparisonHelper(root, a.root);
}

//-----------------------------------------------
// Operator !=
//
// Used to compare trees
//-----------------------------------------------
bool BinTree::operator!=(const BinTree &a) const
{
	return !(*this == a);
}

//-----------------------------------------------
// Operator == and != helper
//
// If both leaves are NULL, the tree is equal
// If there are contrasting children, the trees
// are not equal
// Otherwise, recursively compare more
//-----------------------------------------------
bool BinTree::ComparisonHelper(Node *thisLeaf, Node *otherLeaf) const
{
	if (thisLeaf == NULL && otherLeaf == NULL)
	{
		return true;
	}
	else if ((thisLeaf == NULL && otherLeaf != NULL) || (thisLeaf != NULL && otherLeaf == NULL))
	{
		return false;
	}
	if (*thisLeaf->data == *otherLeaf->data)
	{
		return ComparisonHelper(thisLeaf->left, otherLeaf->left) && ComparisonHelper(thisLeaf->right, otherLeaf->right);
	}
	else
	{
		return false;
	}
}

////////////////////
//Member Functions//
////////////////////

//-----------------------------------------------
// Children Checker
//
// Checks to see if the Node's children are NULL
// and returns whether or not they are
//-----------------------------------------------
bool BinTree::childrenExist(Node *leaf) const
{
	if (leaf->left == NULL && leaf->right == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//-----------------------------------------------
// Is Empty?
//
// No root? Then the tree has to be empty
//-----------------------------------------------
bool BinTree::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------
// Make Empty
//
// Checks to make sure the tree isn't empty and
// then calls the helper function
//-----------------------------------------------
void BinTree::makeEmpty()
{
	if (isEmpty())
	{
		return;
	}
	makeEmpty(root, root->data);
	root = NULL;
}

//-----------------------------------------------
// Make Empty Helper
//
// Goes through the tree recursively, making sure
// that the leaf isn't NULL, then deletes its data
//-----------------------------------------------
void BinTree::makeEmpty(Node *leaf, NodeData *&a)
{
	if (leaf != NULL)
	{
		makeEmpty(leaf->left, leaf->left->data);
		makeEmpty(leaf->right, leaf->right->data);
		delete a;
		a = NULL;
		delete leaf;
		leaf = NULL;
	}
}

//-----------------------------------------------
// Insert
//
// Inserts a Node into the tree by calling the
// helper function
//-----------------------------------------------
bool BinTree::insert(NodeData *insert)
{
	if (root != NULL)
	{
		return this->insert(insert, root);
	}
	else
	{
		root = new Node;
		root->data = insert;
		root->left = NULL;
		root->right = NULL;
	}
}

//-----------------------------------------------
// Insert Helper
//
// Checks to see if the Node exists every recursive
// call and then makes sure the Node is placed in
// the right place to insert, doing so with recursion
//-----------------------------------------------
bool BinTree::insert(NodeData *insert, Node *leaf)
{
	if (*insert == *leaf->data)
	{
		return false;
	}
	if (*insert < *leaf->data)
	{
		if (leaf->left != NULL)
		{
			this->insert(insert, leaf->left);
		}
		else
		{
			leaf->left = new Node;
			leaf->left->data = insert;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
			return true;
		}
	}
	else if (*insert > *leaf->data)
	{
		if (leaf->right != NULL)
		{
			this->insert(insert, leaf->right);
		}
		else
		{
			leaf->right = new Node;
			leaf->right->data = insert;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
			return true;
		}
	}
}

//-----------------------------------------------
// Retrieve
//
// Finds a Node with the specified NodeData and 
// uses the helper method to set the Nodedata pointer
// to that address
//-----------------------------------------------
bool BinTree::retrieve(const NodeData &a, NodeData *&l) const
{
	return retrieve(a, l, root);
}

//-----------------------------------------------
// Retrieve Helper
//
// Helper function that recursively searches the 
// tree with Node Data comparisons then sets the
// Node with the proper data to the second parameter
//-----------------------------------------------
bool BinTree::retrieve(const NodeData &a, NodeData *&b, Node *leaf) const
{
	if (leaf != NULL)
	{
		if (a == *leaf->data)
		{
			b = leaf->data;
			return true;
		}
		if (a < *leaf->data)
		{
			retrieve(a, b, leaf->left);
		}
		else
		{
			retrieve(a, b, leaf->right);
		}
	}
	else
	{
		b = NULL;
		return false;
	}
}

//-----------------------------------------------
// Display Sideways
//
// Method given to students for program
//-----------------------------------------------
void BinTree::displaySideways() const {
	cout << endl;
	sideways(root, 0);
}

//-----------------------------------------------
// Display Sideways Helper
//
// Helper method given to students for program
//-----------------------------------------------
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//-----------------------------------------------
// Get Height
//
// Had many issues with getting this one just right,
// so this is inefficient but whatever its late 
// Anyways, this function uses the retrieve function
// in order to check to see if the Node exists in
// the tree. Without it, this will cause a crash
// Then I set what I don't need to NULL and then
// Use my two helper methods to find the answer
//-----------------------------------------------
int BinTree::getHeight(const NodeData &a) const
{
	Node *leaf;
	NodeData *find;
	
	if (!retrieve(a, find))
	{
		find = NULL;
		return 0;
	}
	find = NULL;

	if(!retrieveNode(a, root, leaf))
	{
		return 0;
	}
	else
	{
		int c = 1;
		getHeightHelper(leaf, c, 1);
		leaf = NULL;
		return c;
	}
}

//-----------------------------------------------
// Get Height Retrieve Node Helper
//
// This function is almost the same as the retrieve
// method but instead looks recursively for the Node
// that corresponds to the given NodeData in the tree
//-----------------------------------------------
bool BinTree::retrieveNode(const NodeData &a, Node *leaf, Node *&ret) const
{
	if (leaf != NULL)
	{
		if (a == *leaf->data)
		{
			ret = leaf;
			return true;
		}
		if (leaf->left != NULL)
		{
			retrieveNode(a, leaf->left, ret);
		}
		if (leaf->right != NULL)
		{
			retrieveNode(a, leaf->right, ret);
		}
	}
	/*
	else
	{
		ret = NULL;
		return false;
	}*/
}

//-----------------------------------------------
// Get Height Helper
//
// The icing on the cake... Uses a reference to
// an int to keep track of that int and using the
// found Node from the previous function, recusrively
// runs down the possible paths of the tree and if
// the number of times gotten down is greater than
// the int reference, then it sets the int reference
// to that int
//-----------------------------------------------
void BinTree::getHeightHelper(Node *leaf, int &c, int n) const
{
	cout << *leaf->data << endl;
	if (!childrenExist(leaf))
	{
		if (n > c)
		{
			c = n;
		}
		return;
	}
	if (leaf->left != NULL)
	{
		getHeightHelper(leaf->left, c, n + 1);
	}
	if (leaf->right != NULL)
	{
		getHeightHelper(leaf->right, c, n + 1);
	}
}

//-----------------------------------------------
// BSTree To Array
//
// Checks to see if the tree is empty, then uses
// a helper function for the rest
//-----------------------------------------------
void BinTree::bstreeToArray(NodeData* a[])
{
	if (isEmpty())
	{
		return;
	}
	else
	{
		int c = -1;
		bstreeToArray(a, root, c);
		makeEmpty();
	}
}

//-----------------------------------------------
// BSTree to Array Helper
//
// Goes in order through the tree much like the
// InOrderHelper and uses an int reference to create
// new NodeData in the right index for a sorted array
//-----------------------------------------------
void BinTree::bstreeToArray(NodeData *a[], Node *leaf, int &c)
{
	if (leaf == NULL)
	{
		return;
	}

	bstreeToArray(a, leaf->left, c);
	c += 1;
	a[c] = new NodeData;
	*a[c] = *leaf->data;
	bstreeToArray(a, leaf->right, c);
}

//-----------------------------------------------
// Array to BSTree
//
// Finds the length of the array in terms of NodeData,
// makes the tree empty, then calls the helper function
// After the helper function is called, the array gets
// turned to NULL completely
//-----------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[]) 
{
	int i = 0, high = 0;
	while (arr[i] != NULL) 
	{
		high++;
		i++;
	}
	makeEmpty();
	arrayToBSTree(arr, root, 0, high - 1);
	i = 0;
	while (arr[i] != NULL)
	{
		arr[i] = NULL;
		i++;
	}
}

//-----------------------------------------------
// Array to BSTree Helper
//
// Helper function works similarly to a merge sort
// in order to make a balanced tree... The new leaves
// use the same address as the array NodeDatas to
// make the tree
//-----------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[], Node* &leaf, int low, int high) 
{
	if (low <= high) 
	{
		int mid = (high + low) / 2;
		leaf = new Node;
		leaf->data = array[mid];
		leaf->left = NULL;
		leaf->right = NULL;
		arrayToBSTree(array, leaf->left, low, mid - 1);
		arrayToBSTree(array, leaf->right, mid + 1, high);
	}
}