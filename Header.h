#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdarg>
#include <cassert>
#include <vector>
using namespace std;

class CSet {
private:
	unsigned int Power;
	int* Plural; //= new int[Power];
public:
	CSet();
	~CSet();
	CSet(const CSet& p2);
	CSet(CSet&& p2) noexcept;
	CSet(unsigned int pow);
	unsigned int GetPower();
    unsigned int PowerOfPlural();
	void SetPower(unsigned int pow);
	void GetPlural();
	int GetElPlural(int index);
	void SetPlural(int count,...);
	void print();
	void AddToPlural(int toadd);
	void DeleteByPass(int whatdelete);
	bool IsExist(int search);
	int PluralMax();
	int PluralMin();
	CSet operator+(CSet& n2);
	CSet operator-(CSet& p2);
	CSet operator/(CSet& p2);
	CSet& operator=(CSet&& p2) noexcept;
	friend ostream& operator<<(ostream& out, const CSet& n2);
	friend istream& operator>>(istream& in, CSet& n2);

};
#endif;
