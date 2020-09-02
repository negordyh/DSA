#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif


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
KnightTree* insert(KnightTree*& node, int& key, int& level, bool& taller)
{
	if (node == NULL)
	{
		node = new KnightTree;
		node->level = level;
		node->key = key;
		taller = true;
		node->pLeftChild = NULL;
		node->pRightChild = NULL;
		node->balance = 0;
		return node;
	}

	if (key < node->key)
	{
		
		node->pLeftChild = insert(node->pLeftChild, key, level, taller);

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
		if (key == node->key) key++;
		node->pRightChild = insert(node->pRightChild, key, level, taller);

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
KnightTree* BSTinsert(KnightTree*& node, int& key, int& level)
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
		 BSTinsert(node->pLeftChild, key, level);
	}
	else
	{
		if (key == node->key) key++;
		if (key != 1000 && key != 998)
		{
			BSTinsert(node->pRightChild, key, level);
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
KnightTree* removeNode(KnightTree*& node, int& key, bool& shorter, bool& success)
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
		node->pLeftChild = removeNode(node->pLeftChild, key, shorter, success);
		if (shorter)
		{
			node = removeRightBalance(node, shorter);
		}
	}
	else if (key > node->key)
	{
		node->pRightChild = removeNode(node->pRightChild, key, shorter, success);
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
			KnightTree* newRoot = node->pLeftChild;
			success = true;
			shorter = true;
			delete deleteNode;
			return newRoot;
		}
		else if (node->pLeftChild == NULL)
		{
			KnightTree* newRoot = node->pRightChild;
			success = true;
			shorter = true;
			delete deleteNode;
			return newRoot;
		}
		else
		{
			KnightTree* exchPtr = node->pRightChild;
			while (exchPtr->pLeftChild != NULL)
			{
				exchPtr = exchPtr->pLeftChild;
			}
			node->key = exchPtr->key;
			node->level = exchPtr->level;;
			node->pRightChild = removeNode(node->pRightChild, exchPtr->key, shorter, success);
			if (shorter)
			{
				node = removeRightBalance(node, shorter);
			}
		}

	}
	return node;
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
KnightTree* insert777(KnightTree* node, KnightTree* Aragorn777)
{
	if (node == NULL) return Aragorn777;
	BSTinsert(Aragorn777, node->key, node->level);
	

	//NLR
	
	insert777(node->pLeftChild, Aragorn777);
	insert777(node->pRightChild, Aragorn777);
	return Aragorn777;
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
KnightTree* gapQuaiVat(eventList* pEvent, KnightTree*& node, int& key, int &level) {
	int key_QV = abs(pEvent->nEventCode / 10);
	int level_QV = abs(pEvent->nEventCode % 10);

	KnightTree* temp = node;
	int p = node->key;
	int k = abs(node->key - key);

	while (temp != NULL)
	{
		if (key_QV == temp->key) { p = temp->key; break; }
		else if (key > temp->key)
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

	if (key != 777) {
		if (key_QV == 777) {
			if (getLeaf(node) == key_QV) 
			{
				bool shorter = true;
				bool success = true;
				if (getDepth(node) >= level_QV)
				{
					node = removeNode(node, temp->key, shorter, success);
				}
			}
			else return NULL;
		}

		else {
			if (temp->level >= level_QV) return NULL;
			else {
				bool shorter = true;
				bool success = true;
				node = removeNode(node, temp->key, shorter, success);
			}
		}
	}

	else {
		if (temp->level == level_QV) return NULL;
		else {
			bool shorter = true;
			bool success = true;
			node = removeNode(node, temp->key, shorter, success);
		}
	}

	// BUG CMNR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (key_QV == 888)
	{
		if (temp->level >= level_QV) return NULL;
		else
		{
			KnightTree* temp = node;
			int p = node->key;
			int k = abs(node->key - key);

			while (temp != NULL)
			{
				if (key_QV == temp->key) { p = temp->key; break; }
				else if (key > temp->key)
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
				do
				{
					bool shorter = true;
					bool success = true;
					node = removeNode(node, temp->key, shorter, success);
				}  while (temp->level >= level_QV);
		}
	}

	return node;
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
		else if (pEvent->nEventCode / 10000 == 1) {
			hiepSi(pEvent, key, level);
			bool taller = true;

			//Aragon
			if (key == 777) {
				KnightTree* knight777 = new KnightTree;
				knight777->key = key;
				knight777->level = level;
				knight777->pLeftChild = knight777->pRightChild = NULL;
				knight777->balance = 0;
				
				pTree = insert777(pTree, knight777);
			}

			//Gimli
			else if (key == 0) {
				int node_count = countNumNodes(pTree);
				int node_height = getHeight(pTree);

				if (node_count == pow(2, node_height) - 1);
				else BSTinsert(pTree, key, level);
			}

			//Gandalf

			//Legolas


			else
			BSTinsert(pTree, key, level);
		}

		//case: 2XYZ (hiepsi giaicuu quacau)
		else if (pEvent->nEventCode / 1000 == 2) {
			key = pEvent->nEventCode % 1000;
			plusLevel(pTree, key);
		}

		//case: 3XYZ (gap Gla)
		else if (pEvent->nEventCode / 1000 == 3) {
			level = 9;
		}

		//case: 5 (Saruman chaytron)
		else if (pEvent->nEventCode == 5)
		{
			
		}

		if (pTree == NULL) return NULL;
		pEvent = pEvent->pNext;
	}
	
	return pTree;
}



