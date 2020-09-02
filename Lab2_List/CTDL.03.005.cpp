#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
using namespace std;

class Node {
public:
	double coeff;
	int exp;
	Node *link;

	Node(double coeff, int exp) {
		this->coeff = coeff;
		this->exp = exp;
		this->link = NULL;
	}
};

class Polynomial {
	Node *head;

protected:
	int insertNode(Node* pPre, double coeff,  int exp);
	void deleteNode(Node* pPre, Node* pLoc);

public:
	Polynomial();
	Polynomial(const Polynomial&);
	~Polynomial();
	void clear();
	const Polynomial& operator=(const Polynomial&);
    void check();

	// TODO methods
	void insertTerm(double coeff, int exp);
};

int main(int argc, char *argv[])
{
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);

    Polynomial* po = new Polynomial();

    double coeff;
    int exp;
    while (ifs.good()) {
        ifs >> coeff >> exp;
        po->insertTerm(coeff, exp);
    }

    po->check();

    delete po;
    ifs.close();

    return 0;
}

void Polynomial::insertTerm(double coeff, int exp) {
    // TODO
if (coeff == 0) return;
	if (this->head == NULL) {
		Node* pNew = new Node(coeff, exp);
		this->head = pNew;
	}
	else if(exp>this->head->exp){
		Node* pNew = new Node(coeff, exp);
		pNew->link = this->head;
		this->head = pNew;
	}
	else if (exp == this->head->exp) {
		this->head->coeff += coeff;
		if (this->head->coeff == 0) deleteNode(NULL, this->head);
	}
	else {
		Node* _pre = this->head;
		Node* _loch = this->head->link;
		while (_pre->link != NULL&&_pre->link->exp > exp) {
			_pre = _pre->link;
			_loch = _loch->link;
		}
		if (_loch != NULL && exp == _loch->exp) {
			_loch->coeff += coeff;
			if (_loch->coeff == 0) deleteNode(_pre, _loch);
		}
		else insertNode(_pre, coeff, exp);
	}
	return;
}

Polynomial::Polynomial() {
	this->head = NULL;
}

Polynomial::Polynomial(const Polynomial& a) {
	Node* p = a.head;
	head = NULL;
	while (p != NULL) {
		insertTerm(p->coeff, p->exp);
		p = p->link;
	}
}

const Polynomial& Polynomial::operator=(const Polynomial& a) {
	if (this != &a) {
		clear();
		Node* p = a.head;
		while (p != NULL) {
			insertTerm(p->coeff, p->exp);
			p = p->link;
		}
		return (*this);
	}
}

int Polynomial::insertNode(Node*pPre, double coeff, int exp) {
	Node *pNew = new Node(coeff, exp);
	if (pNew == NULL)
		return 0;
	if (pPre == NULL) {
		pNew->link = this->head;
		this->head = pNew;
	}
	else {
		pNew->link = pPre->link;
		pPre->link = pNew;
	}
	return 1;
}

void Polynomial::deleteNode(Node *pPre, Node *pLoc) {
	if (pPre == NULL) {
		this->head = pLoc->link;
	}
	else {
		pPre->link = pLoc->link;
	}

	delete pLoc;
}

void Polynomial::clear() {
	Node *temp;
	while (this->head != NULL) {
		temp = this->head;
		this->head = this->head->link;
		delete temp;
	}
}

Polynomial::~Polynomial() {
	this->clear();
}

void Polynomial::check() {
    Node *temp = this->head;
    while (temp != NULL) {
        cout << temp->coeff << " " << temp->exp << endl;
        temp = temp->link;
    }
}