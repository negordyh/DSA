#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

const int MAX_CHARACTER_PER_LINE = 250;

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(const char* file_name, knight& theKnight, eventList*& pEvent)
{
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_PER_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	//----------- read knight information -----------
	fgets(str, MAX_CHARACTER_PER_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);

	//read HP 
	while (start < len && str[start] == ' ')
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start++] - '0';
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	//read level
	while (start < len && str[start] == ' ')
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start++] - '0';
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	//read nInitRingsign 
	while (start < len && str[start] == ' ')
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start++] - '0';
	}
	theKnight.nInitRingsign = num;

	//------------------ read event list ----------------
	eventList* tail = NULL;
	while (1)
	{
		str = new char[MAX_CHARACTER_PER_LINE];
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_PER_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
		while (start < len)
		{
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			int num = 0;

			while (start < len && str[start] <= '9' && str[start] >= '0')
			{
				num = num * 10 + str[start++] - '0';
			}

			eventList* current_event = new eventList;
			current_event->nEventCode = num;
			current_event->pNext = NULL;

			if (pEvent == NULL)
				pEvent = current_event;

			if (tail != NULL)
				tail->pNext = current_event;
			tail = current_event;
		}
	}
	fclose(f);

	/*
	//test for reading
	while (pEvent != NULL)
	{
		cout << pEvent->nEventCode << endl;
		pEvent = pEvent->pNext;
	}
	*/

	return 1;
}

void display(knight theKnight, ringsignList* pList)
{
	cout.flush();
	//cout << theKnight.HP;
	if (checkPalindrome(pList))
		cout << "God saves the Fellowship";
	else
	{
		while (pList)
		{
			cout << pList->nRingsign;
			pList = pList->pNext;
		}
	}
	cout << endl << theKnight.HP << endl;
}


int main()
{

	knight theKnight;
	eventList* pEvent = NULL;
	ringsignList* pList = NULL;
	
	readFile("input.txt", theKnight, pEvent);
	pList = combat(theKnight, pEvent);
	display(theKnight, pList);

	// delete garbage
	eventList* p;
	while (pEvent != NULL) {
		p = pEvent;
		pEvent = pEvent->pNext;
		delete p;
	}
	ringsignList* q;
	while (pList != NULL) {
		q = pList;
		pList = pList->pNext;
		delete q;
	}
	return 0;
}
