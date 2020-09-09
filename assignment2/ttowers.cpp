#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif


int check = 0;
KnightTree* rotateRight(KnightTree*& node)
{
	KnightTree* temp = node->pLeftChild;
	node->pLeftChild = temp->pRightChild;
	temp->pRightChild = node;
	node = temp;
	return node;
}
KnightTree* rotateLeft(KnightTree*& node)
{
	KnightTree* temp = node->pRightChild;
	node->pRightChild = temp->pLeftChild;
	temp->pLeftChild = node;
	node = temp;
	return node;
}
KnightTree* rightBalance(KnightTree*& node, bool& taller)
{
	KnightTree* rightTree = node->pRightChild;
	if (rightTree->balance == 1)
	{
		node->balance = 0;
		rightTree->balance = 0;
		node = rotateLeft(node);
		taller = false;
	}
	else
	{
		KnightTree* leftTree = rightTree->pLeftChild;
		if (leftTree->balance == 1)
		{
			node->balance = -1;
			rightTree->balance = 0;
		}
		else if (leftTree->balance == 0)
		{
			node->balance = 0;
			rightTree->balance = 0;
		}
		else
		{
			node->balance = 0;
			rightTree->balance = 1;
		}

		leftTree->balance = 0;
		node->pRightChild = rotateRight(rightTree);
		node = rotateLeft(node);
		taller = false;
	}

	return node;
}
KnightTree* leftBalance(KnightTree*& node, bool& taller)
{
	KnightTree* leftTree = node->pLeftChild;
	if (leftTree->balance == -1)
	{
		node->balance = 0;
		leftTree->balance = 0;
		node = rotateRight(node);
		taller = false;
	}
	else
	{
		KnightTree* rightTree = leftTree->pRightChild;
		if (rightTree->balance == -1)
		{
			node->balance = 1;
			leftTree->balance = 0;
		}
		else if (rightTree->balance == 0)
		{
			node->balance = 0;
			leftTree->balance = 0;
		}
		else
		{
			node->balance = 00;
			leftTree->balance = -1;
		}

		rightTree->balance = 0;
		node->pLeftChild = rotateLeft(leftTree);
		node = rotateRight(node);
		taller = false;
	}

	return node;
}
KnightTree* insertAVL(KnightTree*& node, int& key, int& level, bool& taller)
{
	if (node == NULL)
	{
		node = new KnightTree{key,level,0,NULL,NULL};
		taller = true;
		return node;
	}

	if (key < node->key)
	{
		
		node->pLeftChild = insertAVL(node->pLeftChild, key, level, taller);

		if (taller)
		{
			if (node->balance == -1)
			{
				node = leftBalance(node, taller);
				taller = false;
			}
			else if (node->balance == 0)
			{
				node->balance = -1;
			}
			else
			{
				node->balance = 0;
				taller = false;
			}
		}
	}
	else
	{
		if (key == node->key) {
			key++;
			//add same BSTinsert
			if (key == 777) key++;
			else if (key == 888) key++;
			else if (key == 999) key++;
		}
		if (key != 1000 && key != 998)
		{
			node->pRightChild = insertAVL(node->pRightChild, key, level, taller);
		}
		//

		if (taller)
		{
			if (node->balance == -1)
			{
				node->balance = 0;
				taller = false;
			}
			else if (node->balance == 0)
			{
				node->balance = 1;
			}
			else
			{
				node = rightBalance(node, taller);
				taller = false;
			}
		}
	}

	return node;
}
KnightTree* insertBST(KnightTree*& node, int& key, int& level)
{
	if (node == NULL)
	{
		node = new KnightTree;
		node->level = level;
		node->key = key;
		node->pLeftChild = NULL;
		node->pRightChild = NULL;
		node->balance = 0;
		return node;
	}
	if (key < node->key)
	{
		 insertBST(node->pLeftChild, key, level);
	}
	else
	{
		if (key == node->key) {
			key++;
			if (key == 777) key++;
			else if (key == 888) key++;
			else if (key == 999) key++;
		}
		if (key != 1000 && key != 998)
		{
			insertBST(node->pRightChild, key, level);
		}
		else
		{
			return NULL;
		}
	}
}
KnightTree* removeRightBalance(KnightTree*& node, bool& shorter)
{
	// TODO

	if (node->balance == -1)
	{
		node->balance = 0;
	}
	else if (node->balance == 0)
	{
		node->balance = 1;
		shorter = false;
	}
	else
	{
		KnightTree* rightTree = node->pRightChild;
		if (rightTree->balance == -1)
		{
			KnightTree* leftTree = rightTree->pLeftChild;
			if (leftTree->balance == -1)
			{
				rightTree->balance = 1;
				node->balance = 0;
			}
			else if (rightTree->balance == 0)
			{
				node->balance = -1;
				rightTree->balance = 0;
			}
			else
			{
				node->balance = -1;
				rightTree->balance = 0;
			}
			leftTree->balance = 0;
			node->pRightChild = rotateRight(rightTree);
			node = rotateLeft(node);
		}
		else
		{
			if (rightTree->balance != 0)
			{
				node->balance = 0;
				rightTree->balance = 0;
			}
			else
			{
				node->balance = 1;
				rightTree->balance = -1;
				shorter = false;
			}
			node = rotateLeft(node);

		}

	}
	return node;
}
KnightTree* removeLeftBalance(KnightTree*& node, bool& shorter)
{
	// TODO
	if (node->balance == 1)
	{
		node->balance = 0;
	}
	else if (node->balance == 0)
	{
		node->balance = -1;
		shorter = false;
	}
	else
	{
		KnightTree* leftTree = node->pLeftChild;
		if (leftTree->balance == 1)
		{
			KnightTree* rightTree = leftTree->pRightChild;
			if (rightTree->balance == 1)
			{
				leftTree->balance = -1;
				node->balance = 0;
			}
			else if (rightTree->balance == 0)
			{
				node->balance = 1;
				leftTree->balance = 0;
			}
			else
			{
				node->balance = -1;
				leftTree->balance = 0;
			}
			rightTree->balance = 0;
			node->pRightChild = rotateLeft(leftTree);
			node = rotateRight(node);
		}
		else
		{
			if (leftTree->balance != 0)
			{
				node->balance = 0;
				leftTree->balance = 0;
			}
			else
			{
				node->balance = -1;
				leftTree->balance = 1;
				shorter = false;
			}
			node = rotateRight(node);

		}

	}
	return node;
}
KnightTree* removeAVL(KnightTree*& node, int& key, bool& shorter, bool& success)
{
	// TODO
	if (node == NULL)
	{
		shorter = false;
		success = false;
		return NULL;
	}
	if (key < node->key)
	{
		node->pLeftChild = removeAVL(node->pLeftChild, key, shorter, success);
		if (shorter)
		{
			node = removeRightBalance(node, shorter);
		}
	}
	else if (key > node->key)
	{
		node->pRightChild = removeAVL(node->pRightChild, key, shorter, success);
		if (shorter)
		{
			node = removeLeftBalance(node, shorter);
		}
	}
	else
	{
		KnightTree* deleteNode = node;
		if (node->pRightChild == NULL)
		{
			node = node->pLeftChild;
			success = true;
			shorter = true;
			delete deleteNode;
			return node;
		}
		else if (node->pLeftChild == NULL)
		{
			node = node->pRightChild;
			success = true;
			shorter = true;
			delete deleteNode;
			return node;
		}
		else
		{
			KnightTree* exchPtr = node->pRightChild;
			while (exchPtr->pLeftChild != NULL)
			{
				exchPtr = exchPtr->pLeftChild;
			}
			node->key = exchPtr->key;
			node->level = exchPtr->level;
			node->pRightChild = removeAVL(node->pRightChild, exchPtr->key, shorter, success);
			if (shorter)
			{
				node = removeLeftBalance(node, shorter);
			}
		}

	}
	return node;
}
void removeBST(KnightTree*& root, int value)
{
	if (root == NULL) return;
	if (root->key < value)
		return removeBST(root->pRightChild, value);
	if (root->key > value)
		return removeBST(root->pLeftChild, value);
	if (root->key == value) {
		if (root->pLeftChild == NULL)
		{
			KnightTree* tmp = root;
			root = root->pRightChild;
			delete tmp;
			tmp = NULL;
		}
		else if (root->pRightChild == NULL)
		{
			KnightTree* tmp = root;
			root = root->pLeftChild;
			delete tmp;
			tmp = NULL;
		}
		else
		{
			KnightTree* tNode = root->pRightChild;
			while (tNode->pLeftChild != NULL)
				tNode = tNode->pLeftChild;
			root->key = tNode->key;
			removeBST(root->pRightChild, tNode->key);
		}
		return;
	}
}

int getLeaf(KnightTree* node)
{
	static int k= 0;
	if (node != NULL) k++;
	else return k;
	getLeaf(node->pLeftChild);
	getLeaf(node->pRightChild);
	return k;
}
int getHeight(KnightTree* node) {
	if (node == NULL)
		return 0;
	int lh = getHeight(node->pLeftChild);
	int rh = getHeight(node->pRightChild);
	return (lh > rh ? lh : rh) + 1;
}
int getDepth(KnightTree* node) {
	if (node == NULL)
		return 0;
	if (node->pLeftChild == NULL && node->pRightChild == NULL)
		return 1;
	if (!node->pLeftChild)
		return getDepth(node->pRightChild) + 1;
	if (!node->pRightChild)
		return getDepth(node->pLeftChild) + 1;
	return (getDepth(node->pLeftChild) > getDepth(node->pRightChild) ? getDepth(node->pLeftChild) : getDepth(node->pRightChild)) + 1;
}
int countNumNodes(KnightTree* node) {
	if (node == NULL)
		return (0);
	return (1 + countNumNodes(node->pLeftChild) + countNumNodes(node->pRightChild));
}
bool checkComplete(KnightTree* node, int index, int numberNodes) {
	if (node == NULL)
		return true;

	if (index >= numberNodes)
		return false;

	return (checkComplete(node->pLeftChild, 2 * index + 1, numberNodes) &&
			checkComplete(node->pRightChild, 2 * index + 2, numberNodes));
}


int hiepSi(eventList* pEvent, int& key, int& level) {
	level = pEvent->nEventCode % 10;
	key = pEvent->nEventCode / 10 % 1000; 
	
	return 0;
}
void insert777(KnightTree* node, KnightTree*& Aragorn777)
{
	if (node == NULL) return;
	//NLR
	insertBST(Aragorn777, node->key, node->level);
	insert777(node->pLeftChild, Aragorn777);
	insert777(node->pRightChild, Aragorn777);
}
void insert999(KnightTree* node, KnightTree*& Gandalf999) {
	if (node == NULL) return;
	bool taller = true;
	//RNL
	insert999(node->pRightChild, Gandalf999);
	insertAVL(Gandalf999, node->key, node->level, taller);
	insert999(node->pLeftChild, Gandalf999);
}

KnightTree *Legolas(KnightTree* node)
{
	KnightTree static* arr;
	static int i = 0;
	if (node == NULL) return NULL;
	else
	{
		Legolas(node->pLeftChild);
		if (arr == NULL)
		{
			arr = new KnightTree;
			arr->key = node->key;
			arr->level = node->level;
			arr->pLeftChild = arr->pRightChild = NULL;
			
		}
		else
		{
			static KnightTree* temp = arr;

			temp->pRightChild = new KnightTree;
			temp = temp->pRightChild;
			temp->key = node->key;
			temp->level = node->level;
			temp->pLeftChild = temp->pRightChild = NULL;
			
		}
		Legolas(node->pRightChild);
	}
	return arr;
}
KnightTree* insert888(KnightTree* node, KnightTree* Legolas888) {
	KnightTree* arr = Legolas(node);
	KnightTree* temp = arr;
	if (Legolas888->key < arr->key)
	{
		Legolas888->pRightChild = arr;
		arr = Legolas888;
		return arr;
	}
	while (temp->pRightChild != NULL)
	{
		if (Legolas888->key < temp->pRightChild->key)
		{
			Legolas888->pRightChild = temp->pRightChild;
			temp->pRightChild = Legolas888;
			return arr;
		}
		temp = temp->pRightChild;
	}
	temp->pRightChild = Legolas888;

	return arr;
}
KnightTree* leftTree(KnightTree* arr, int k)
{
	KnightTree* temp = arr;
	KnightTree* node = NULL;
	float i = 0;
	k--;
	
	while (i != (int)k / 2)
	{
		bool taller = true;
		insertAVL(node, temp->key, temp->level, taller);
		temp = temp->pRightChild;
		i++;
	}
	return node;
}
KnightTree* rightTree(KnightTree* arr, int k)
{
	KnightTree* temp = arr;
	KnightTree* node = NULL;
	int i = 0;
	k--;
	while (i != k / 2+1)
	{
		temp = temp->pRightChild;
		i++;
	}
	
	while (i != k+1)
	{
		bool taller = true;
		insertAVL(node, temp->key, temp->level, taller);
		i++;
		temp = temp->pRightChild;
	}
	return node;
}
KnightTree* getMidNode(KnightTree* arr, int k)
{
	k--;
	int static i = k / 2;
	static KnightTree* temp = arr;
	while (i != 0)
	{
		temp = temp->pRightChild;
		i--;
	}
	static KnightTree* node = new KnightTree;
	node->key = temp->key;
	node->level = temp->level;
	
	node->balance = 0;
	node->pLeftChild = leftTree(arr, ++k);
	node->pRightChild = rightTree(arr, k);
	
	return node;
}


void plusLevel(KnightTree*& node, int key)
{
	KnightTree* temp = node;
	int p = node->key;
	int k = abs(node->key - key);

	while (temp != NULL)
	{
		if (key == temp->key) { p = temp->key; break; }
		else if (key > temp->key)
		{
			if ((abs(temp->key - key)) < k) p = temp->key;
			temp = temp->pRightChild;
			
		}
		else if (key < temp->key)
		{
			if ((abs(temp->key - key)) < k) p = temp->key;
			temp = temp->pLeftChild;
			
		}
	}

	temp = node;
	while (p != temp->key)
	{
		if (p > temp->key) temp = temp->pRightChild;
		else temp = temp->pLeftChild;
	}
	if (temp->level == 9) return;
	temp->level++;

}
KnightTree* gapQuaiVat(eventList* pEvent, KnightTree*& node, int& key, int& level) {
	if (node == NULL) return NULL;
	int key_QV = abs(pEvent->nEventCode / 10);
	int level_QV = abs(pEvent->nEventCode % 10);

	KnightTree* temp = node;
	int p = node->key;
	int k = abs(node->key - key);

	while (temp != NULL)
	{
		if (key_QV == temp->key) { p = temp->key; break; }
		else if (key_QV > temp->key)
		{
			if ((abs(temp->key - key_QV)) < k) p = temp->key;
			temp = temp->pRightChild;

		}
		else if (key_QV < temp->key)
		{
			if ((abs(temp->key - key_QV)) < k) p = temp->key;
			temp = temp->pLeftChild;

		}

	}
	temp = node;
	while (p != temp->key)
	{
		
		if (p > temp->key) temp = temp->pRightChild;
		else temp = temp->pLeftChild;
	}

		if (check == 7 && node->level == level_QV) return node;
		if (temp->level < level_QV) {
			if (node->key == 777 || node->key == 888 || node->key == 999) check = 0;
			if (check == 9) {
				bool shorter = true;
				bool success = true;
				removeAVL(node, p, shorter, success);
			}
			else {
				removeBST(node, p);
			}
			if (node == NULL) return NULL;
			if (node->key == 777)  check = 7;
			if (key_QV == 888) gapQuaiVat(pEvent, node, p, level);
		}

		if (key_QV == 777)
		{
			if (getLeaf(node) == key_QV)
			{
				if (getDepth(node) >= level_QV)
				{
					removeBST(node, p);
				}
			}
		}
		
	return node;
}

KnightTree* gapGla(eventList* pEvent, KnightTree*& node, int& key, int& level) {
	int key_Gla = pEvent->nEventCode % 1000;

	KnightTree* temp = node;
	int p = node->key;
	int k = abs(node->key - key);

	while (temp != NULL)
	{
		if (key_Gla == temp->key) { p = temp->key; break; }
		else if (key_Gla > temp->key)
		{
			if ((abs(temp->key - key_Gla)) < k) p = temp->key;
			temp = temp->pRightChild;

		}
		else if (key_Gla < temp->key)
		{
			if ((abs(temp->key - key_Gla)) < k) p = temp->key;
			temp = temp->pLeftChild;

		}

	}
	temp = node;
	while (p != temp->key)
	{
		if (p > temp->key) temp = temp->pRightChild;
		else temp = temp->pLeftChild;
	}

	if (temp->level != 9) temp->level = 9;
	return node;
}

bool checkNodeEqual(KnightTree* node, int k)
{
	if (node == NULL) return 0;
	if (node->level == k) return 1;
	checkNodeEqual(node->pLeftChild, k);
	checkNodeEqual(node->pRightChild, k);
	return 0;
}
KnightTree* assignZero(KnightTree* node)
{
	if (node == NULL) return NULL;
	node->level = 0;
	assignZero(node->pLeftChild);
	assignZero(node->pRightChild);
}
KnightTree* SarumanExit(KnightTree* pTree, int k)
{
	bool c = 1;
	while (k != 0)
	{
		int i = k % 10;
		k /= 10;
		 c = checkNodeEqual(pTree, i);
		 if (c == 0) return pTree;
	}
	assignZero(pTree);
	return pTree;
}
int checkKey(int key, KnightTree* node, KnightTree* Tree) 
{
	if (node == NULL) return key;
	if (key == node->key) {
		key++;
		if (key == 888 || key == 777 || key == 999) key++;
		return checkKey(key, Tree, Tree);
	}
	if (key < node->key)return checkKey(key, node->pLeftChild, Tree);
	if (key > node->key)return checkKey(key, node->pRightChild, Tree);

}
KnightTree* siege(eventList* pEvent, ringsignList* pSarumanList)
{
	KnightTree* pTree = NULL;
	//let's save the lady
	while (pEvent != NULL)
	{
		int key, level = 0;
		//case: -XYZL (gap quaiVat)
		if (pEvent->nEventCode < 0) {
			gapQuaiVat(pEvent, pTree, key, level);
		}
		
		
		//case: 1XYZL (hiepSi)
		if (pEvent->nEventCode / 10000 == 1)
		{
			hiepSi(pEvent, key, level);
			key = checkKey(key, pTree, pTree);
			bool taller = true;
			if (key == 777) check = 7;
			if (key==888) check = 8;
			if (key == 999) check = 9;
			if (key == 777 || key == 888 || key == 999)
			{

				//Aragon
				if (key == 777) {
					KnightTree* knight777 = new KnightTree{ key,level,0,NULL,NULL };
					insert777(pTree, knight777);
					pTree = knight777;
				}

				//Gandalf
				if (key == 999) {
					KnightTree* knight999 = new KnightTree{ key,level,0,NULL,NULL };
					insert999(pTree, knight999);
					pTree = knight999;
				}
				//Legolas
				if (key == 888) {
					int count = countNumNodes(pTree);
					KnightTree* knight888 = new KnightTree{ key,level,0,NULL,NULL };
					KnightTree* p = insert888(pTree, knight888); count++;
					pTree = getMidNode(p, count);
				}
				
			}

			//GIMLI
			else if (key == 0) 
			{
				int node_count = countNumNodes(pTree);
				int node_height = getHeight(pTree);

				if (node_count != pow(2, node_height) - 1)
				{
					insertAVL(pTree, key, level, taller);
					if (pTree->key == 777)
					{
						check = 7;
					}
				}

			}

			else
			{
				if (check!=9)
					insertBST(pTree, key, level);
				else 
				{
					bool taller = true;
					insertAVL(pTree, key, level, taller);
					if (pTree->key == 777)
					{
						check = 7;
					}
				}
			}
		}

		//case: 2XYZ (hiepsi giaicuu quacau)
		else if (pEvent->nEventCode / 1000 == 2) {
			key = pEvent->nEventCode % 1000;
			plusLevel(pTree, key);
		}
		//case: 3XYZ (gap Gla)
		else if (pEvent->nEventCode / 1000 == 3) {
			gapGla(pEvent, pTree, key, level);
		}
		//case: 5 (Saruman chaytron)
		else if (pEvent->nEventCode == 5)
		{
			SarumanExit(pTree, level);
		}

		if (pTree == NULL) return NULL;
		pEvent = pEvent->pNext;
	}
	return pTree;
}



