#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif
void del(ringsignList*& EcHead, ringsignList*& EC, int a, int k);
int compareLevel(knight& theKnight, eventList* pEvent, ringsignList*& EC, ringsignList*& EcHead, int i)
{
	int maxHP = theKnight.HP;
	int b = i % 10;
	int levelO = i > 6 ? (b > 5 ? b : 5) : b;

	if (theKnight.level < levelO)
	{
		
		double baseDamage;
		switch (pEvent->nEventCode / 10)
		{
		case 1: baseDamage = 1;	break;
		case 2: baseDamage = 1.8; break;
		case 3: baseDamage = 4.5; break;
		case 4: baseDamage = 8.2; // Gollum
			if (maxHP != 777) del(EcHead,EC, 1, pEvent->nEventCode % 10);
			break;
		case 5: baseDamage = 7.5; // Lurtz
			if (maxHP != 777) del(EcHead, EC,0, pEvent->nEventCode % 10);
			break;
		case 6: baseDamage = 9;	  break;
		case 9: baseDamage = 0.1; // Saruman
			if (maxHP != 777) del(EcHead, EC,2, pEvent->nEventCode % 10);
			break;
		default:
			break;
		}
		int damage = baseDamage * levelO * 10;
		
		theKnight.HP = theKnight.HP - damage;

		return -1;
	}
	else if (theKnight.level == levelO) return 0;
	else {
		if (pEvent->nEventCode / 10 != 9)
		{
			ringsignList* a = new ringsignList;
			a->nRingsign = pEvent->nEventCode % 10;
			a->pNext = NULL;
			EC->pNext = a;
			EC = EC->pNext;
		}
		return 1;
	}

}
void del(ringsignList*& EcHead, ringsignList*& EC, int a, int k)
{
	//xoa 3 phan tu dau
	if (a == 0)
	{
		int count = 0;
		ringsignList* temp = EcHead;
		while (temp != NULL && count < 3)
		{
			temp = temp->pNext;
			count++;
		}
		EcHead = temp;
	}
	//xoa phan tu trung cuoi cung
	if (a == 1)
	{
		int count = 0;
		int index = -1;
		ringsignList* temp = EcHead;
		while (temp != NULL)
		{
			if (temp->nRingsign == k)
			{
				index = count;
			}
			count++;
			temp = temp->pNext;
		}
		temp = EcHead;
		if (index == -1) return;
		if (index == 0) EcHead = EcHead->pNext;
		else
		{
			while (index != 1)
			{
				temp = temp->pNext;
				index--;
			}
			temp->pNext = temp->pNext->pNext;

		}
		if (temp->pNext == NULL) EC = temp;
	}
	//xoa tat ca phan tu trung
	if (a == 2)
	{
		while ( EcHead!=NULL && EcHead->nRingsign == k)
		{
			EcHead = EcHead->pNext;
		}
		if (EcHead == NULL) return;
		ringsignList* temp = EcHead;
		while (temp->pNext != NULL)
		{
			if (temp->pNext->nRingsign == k)
			{
				temp->pNext = temp->pNext->pNext;
			}
			temp = temp->pNext;
		}
		EC = temp;
		
	}
	//xoa phan tu 0
	if (a == 3)
	{
		ringsignList* temp = EcHead;
		while (temp->nRingsign == 0)
		{
			temp = temp->pNext;
		}
		EcHead = temp;
		
	}
	//xoa phan tu cuoi cung
	if (a == 4)
	{
		if (EcHead == NULL) return;
		if (EcHead->pNext == NULL) {
			EcHead = NULL;  return;
		}
		ringsignList* last = EcHead;
		while (last->pNext->pNext != NULL)
			last = last->pNext;

		EC = last;
		last->pNext = NULL;
	}
}
void reverse(ringsignList*& head)
{
	ringsignList* pre = NULL;
	ringsignList* cur = head;
	ringsignList* next;
	while (cur != NULL)
	{
		next = cur->pNext;
		cur->pNext = pre;
		pre = cur;
		cur = next;
	}
	head = pre;
}
ringsignList* plusOne(ringsignList* head)
{
	if (head == NULL) return 0;
	ringsignList* last = NULL;
	ringsignList* cur = head;
	while (cur->pNext != NULL) {

		if (cur->nRingsign != 9) {
			last = cur;
		}
		cur = cur->pNext;
	}

	if (cur->nRingsign != 9) {
		cur->nRingsign++;
		return head;
	}

	if (last == NULL) {
		last = new ringsignList();
		last->nRingsign = 0;
		last->pNext = head;
		head = last;
	}

	last->nRingsign++;
	last = last->pNext;

	while (last != NULL) {
		last->nRingsign = 0;
		last = last->pNext;
	}

	return head;
}

ringsignList* combat(knight& theKnight, eventList* pEvent)
{
	int maxHP = theKnight.HP;

	ringsignList* pList = new ringsignList;
	pList->nRingsign = theKnight.nInitRingsign;
	pList->pNext = NULL;
	ringsignList* temp = pList;

	//fighting for honor and love here
	ringsignList* a = new ringsignList;
	eventList* p = pEvent;

	int i = 1;
	
	while (pEvent != NULL && theKnight.HP>0 && pList!=NULL)
	{
		//end match
		if (pEvent->nEventCode == 0 ||  theKnight.HP < 1)
		{
			if (p == pEvent)
			{

			}
			break;
		}
		
		//match Uruk-hai
		if (pEvent->nEventCode / 10 == 1 && maxHP != 999)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Ma nhan (Ringrwaiths)
		if (pEvent->nEventCode / 10 == 2 && maxHP != 999)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Strider
		if (pEvent->nEventCode / 10 == 3 && maxHP != 888)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Gollum:
		if (pEvent->nEventCode / 10 == 4)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Lurtz
		if (pEvent->nEventCode / 10 == 5)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Gimli
		if (pEvent->nEventCode / 10 == 6 && maxHP != 888 && maxHP != 999)
		{
			compareLevel(theKnight, pEvent, temp, pList, i);
		}

		//match Saruman
		if (pEvent->nEventCode / 10 == 9)
		{
			if (compareLevel(theKnight, pEvent, temp, pList, i) == 1)
			{
				temp = pList;
				reverse(pList);
			}

		}


		//match Arwen 
		if (pEvent->nEventCode == 7)
		{
			ringsignList* head = pList;
			plusOne(pList);
			if (head != NULL) {
				head->nRingsign;
				del(pList,temp, 3, 0);
			}
			
		}

		//match Galadriel 
		if (pEvent->nEventCode == 8)
		{
			if (theKnight.HP != maxHP)
			{
				theKnight.HP = maxHP;
				if (maxHP != 888 && maxHP != 777) del(pList,temp, 4, 8);
			}
		}
		i++;
		pEvent = pEvent->pNext;
	}
	if (theKnight.HP <= 0) pList = NULL;
	return pList;

}

int checkPalindrome(ringsignList* pRingsign)
{
	int s = 0;
	if (pRingsign == NULL) return 0;
	while (pRingsign != NULL)
	{
		s = s * 10 + pRingsign->nRingsign;
		pRingsign = pRingsign->pNext;
	}
	int reverse = 0;
	for (int i = s; i != 0; i /= 10)
	{
		int r = i % 10; 
		reverse = reverse * 10 + r;
	}
	if (s == reverse) return 1;
	
	return 0;
	
}







