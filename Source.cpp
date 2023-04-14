#include "Header.h"

CSet::CSet() {
	Power = 0;
	Plural = NULL;
}

CSet::~CSet() {
	delete[] Plural;
	Power = NULL;
}

CSet::CSet(unsigned int pow) {
	Plural = NULL;
	Power = pow;
}

void CSet::SetPower(unsigned int pow) {
	Power = pow;
}

unsigned int CSet::GetPower() {
	return Power;
}

int CSet::GetElPlural(int index) {
	int* Array = new int[Power];
	for (int i = 0; i < Power; ++i)
		 Array[i] = Plural[i];
	return Array[index];
}

void CSet::GetPlural() {
	cout << "Your plural is: ";
	for (int i = 0; i < Power; i++)
		cout << Plural[i]<<"  ";
}

void CSet::SetPlural(int count,...) {
    double sum = 0;
    va_list list;
    va_start(list, count);
	Plural = new int[count];

    for (int arg = 0; arg < count; ++arg)
        Plural[arg] = va_arg(list, int);
	Power = count;
    va_end(list);
}

void CSet::print() {
	cout << "Power of plural " << Power << endl << "Plural:{";
	for (int i = 0; i < Power; i++){
		cout << Plural[i] << ",";
	}
	cout <<"}"<< endl;
}

bool CSet::IsExist(int search) {
	bool found = false;
	for (int i = 0; i < Power; i++) {
		if (Plural[i] == search) {
			found = true;
			break;
		}
	}
	return found;
}

unsigned int CSet::PowerOfPlural() {
	return CSet::GetPower();
}

int CSet::PluralMax() {
	if (Plural != NULL) {
		int max = Plural[0];
		for (int i = 0; i < Power; i++) {
			if (max < Plural[i]) {
				max = Plural[i];
			}
		}
		return max;
	}
}

int CSet::PluralMin() {
	if (Plural != NULL) {
		int min = Plural[0];
		for (int i = 0; i < Power; i++) {
			if (min > Plural[i]) {
				min = Plural[i];
			}
		}
		return min;
	}
}

void CSet::AddToPlural(int toadd) {
	int* tmp = new int[Power];
	for (int i = 0; i < Power; i++) {
		tmp[i] = Plural[i];
	}
	Power++;
	Plural = new int[Power];
	Plural[Power - 1] = toadd;
	for (int i = 0; i < Power - 1; i++) {
		Plural[i] = tmp[i];
	}
	delete[] tmp;
	this->SetPower(Power);
}

void CSet::DeleteByPass(int whatdelete) {
	int index = 0;
	for (int i = 0; i < Power; i++) {
		if (Plural[i] == whatdelete) {
			index = i;
			break;
		}
	}
	index += 1;
	if (index == 1) {
		for (int i = 0; i < Power; i++) {
			Plural[i] = Plural[i + 1];
		}
		this->SetPower(--Power);
	}
	else if (index != 1 && index > 1) {
		--index;
		for (int i = index; i <= Power; i++)
		{
			Plural[i] = Plural[i + 1];
		}
		this->SetPower(--Power);
	}
}

CSet CSet::operator+(CSet& p2) {  // here union of plurals
	unsigned int TotalPower = this->GetPower() + p2.GetPower();
	int ind = 0;
	int* tmp = new int[TotalPower];
	for (int i = 0; i < this->GetPower(); i++) {
		tmp[i] = Plural[i];
		ind = i;
	}
	ind++;
	for (int i =0 ; ind < TotalPower&& i<p2.GetPower(); ind++,i++) {
		tmp[ind] = p2.Plural[i];
	}
	cout << endl;
	for (int i = 0; i < TotalPower; i++)
		cout << tmp[i] << endl;

	cout << endl << endl << endl;
	sort(tmp, tmp + TotalPower);
	auto last = unique(tmp, tmp + TotalPower); 
	auto n = distance(tmp, last); 
	p2.Power = n;
	p2.Plural = new int[n];
	for (int i = 0; i < n; i++) {
        p2.Plural[i] = tmp[i];
	}
	delete[] tmp;
	return p2;
}

CSet CSet::operator-(CSet& p2) {
	int count = 0;
	vector<int> intersect;
	sort(this->Plural, this->Plural+this->GetPower());
	sort(p2.Plural, p2.Plural + p2.GetPower());
	int i = 0;
	int j = 0;
	while (i < this->GetPower() && j < p2.GetPower()) {
		if (this->Plural[i] == p2.Plural[j]) {
			intersect.push_back(this->Plural[i]);
			i++;
			j++;
		}
		else if (this->Plural[i] < p2.Plural[j]) {
			i++;
		}
		else {
			j++;
		}
	}

	p2.Power = intersect.size();
	p2.Plural = new int[p2.GetPower()];
	for (int i = 0; i < p2.GetPower(); i++) {
		p2.Plural[i] = intersect[i];
	}

	return p2;
}

CSet CSet::operator/(CSet& p2) {
	int count = 0;
	vector<int> intersect;
	sort(this->Plural, this->Plural + this->GetPower());
	sort(p2.Plural, p2.Plural + p2.GetPower());
	int i = 0;
	int j = 0;
	while (i < this->GetPower() && j < p2.GetPower()) {
		if (this->Plural[i] == p2.Plural[j]) {
			intersect.push_back(this->Plural[i]);
			i++;
			j++;
		}
		else if (this->Plural[i] < p2.Plural[j]) {
			i++;
		}
		else {
			j++;
		}
	}
	int k = 0; 
	for (int i = 0; i < p2.GetPower(); i++) {
		bool found = false;
		for (int j = 0; j < intersect.size(); j++) {
			if (p2.Plural[i] == intersect[j]) {
				found = true;
				break;
			}
		}
		if (!found) {
			p2.Plural[k++] = p2.Plural[i];
		}
	}
	p2.Power = k;
	return p2;
}

ostream& operator<<(ostream& out, const CSet& n2) {
	out << "Plural power:  " << n2.Power << endl;
	out << "Plural: " << endl;
	for (int i = 0; i < n2.Power; i++) {
		out << n2.Plural[i]<<" ";
	}
	return out;
}

istream& operator>>(istream& in, CSet& n2) {
	in >> n2.Power;
	int i = 0;
	while (i < n2.Power) {
		in >> n2.Plural[i];
		++i;
	}
	return in;
}

CSet::CSet(const CSet& p2):  Power(p2.Power){ //copy constructor
 Plural = new int[Power];
 memcpy(Plural, p2.Plural, Power * sizeof(unsigned int));
}

CSet::CSet(CSet&& p2) noexcept : Plural(nullptr), Power(0) { // move constructor
	swap(Plural, p2.Plural);
	swap(Power, p2.Power);
}

CSet& CSet::operator=(CSet&& p2) noexcept {
	if (this != &p2) {
		delete[] Plural;
		Plural = nullptr;
		Power = 0;
		swap(Plural, p2.Plural);
		swap(Power, p2.Power);
	}
	return *this;
}


