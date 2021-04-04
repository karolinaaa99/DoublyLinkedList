#include <iostream>

using namespace std;

class Elem //komorka listy
{
private:
	int v; //key, data
	Elem* next_elem;
	Elem* prev_elem;

public:
	Elem();				//tworzy pusty element
	Elem(int x);			//tworzy element przechowujący x
	int value();			//zwraca wartość 
	void setValue(int v);		//ustawia wartość v
	Elem* next();			//zwraca następny element
	Elem* prev();			//zwraca poprzednielement
	void setNext(Elem* p);		//ustawia p jako następny element
	void setPrev(Elem* p);		//ustawia p jako poprzedni element
};

Elem::Elem()
{
	next_elem = NULL;
	prev_elem = NULL;
	v = 0; //zeby byla jakas wartosc
}

Elem::Elem(int x)
{
	next_elem = NULL;
	prev_elem = NULL;
	v = x;
}

int Elem::value()
{
	return v;
}

void Elem::setValue(int v)
{
	this->v = v; //stary v staje sie nowym v, element, do ktorego sie teraz konkretnie odwoluje
}

Elem* Elem::next()
{
	return next_elem;
}

Elem* Elem::prev()
{
	return prev_elem;
}

void Elem::setNext(Elem* p)
{
	next_elem = p;
}

void Elem::setPrev(Elem* p)
{
	prev_elem = p;
}

class SortedDLList //lista
{
private:
	Elem* head;			//wskaźnik na pierwszy element list
	Elem* tail;			//wskaźnik na ostatni element list
	int list_size;			//długość listy, czyli inaczej liczba elementow listy

public:
	SortedDLList();				//tworzy pustą listę
	bool empty();				//zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
	int size();				//zwraca wielkość listy (liczbę elementów w liście)
	Elem* first();  			//zwraca pozycję pierwszego elementu
	Elem* last();   			//zwraca pozycję ostatniego elementu
	Elem* next(Elem* p);			//zwraca pozycję elementu następnego za p
	Elem* prev(Elem* p);			//zwraca pozycję elementu poprzedniego przed p
	int retrieve(Elem* p); 			//zwraca element z pozycji p
	Elem* locate(int x);  			//zwrac pozycję pierwszego wystąpienia elementu x, -1 jeśli x nie występuje
	void insert(int x); 			//wstawia x z zachowniem porządku
	void del(int x);      			//usuwa pierwsze wystąpienie element x		
	void delALLx(int x);             //usuwa wszystkie wystapienia elementu x
	void clear();				//usuwa całą listę
	friend ostream& operator<<(ostream& out, SortedDLList& l); //wypisuje elementu listy	
};

SortedDLList::SortedDLList()
{
	head = tail = NULL;
	list_size = 0;
}

bool SortedDLList::empty()
{
	if (list_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SortedDLList::size()
{
	return list_size;
}

Elem* SortedDLList::first()
{
	return head;
}

Elem* SortedDLList::last()
{
	return tail;
}

Elem* SortedDLList::next(Elem* p)
{
	if (empty())
	{
		return NULL;
	}
	if (head == tail)
	{
		return NULL;
	}
	if (p == tail)
	{
		return NULL;
	}
	return p->next();
}

Elem* SortedDLList::prev(Elem* p)
{
	if (empty())
	{
		return NULL;
	}
	if (head == tail)
	{
		return NULL;
	}
	if (p == head)
	{
		return NULL;
	}
	return p->prev();
}

int SortedDLList::retrieve(Elem* p)
{
	if (empty())
	{
		return NULL;
	}
	else
	{
		return p->value();
	}
}

Elem* SortedDLList::locate(int x)
{
	if (empty())
	{
		return NULL;
	}
	Elem* p = head;
	while (p->value() != x)
	{
		if (p == tail)
			return NULL;
		p = p->next();
	}
	return p;
}

void SortedDLList::insert(int x)
{
	if (empty())
	{
		head = new Elem(x); //wywolujemy drugi konstruktor, tworzymy nowy pierwszy element
		tail = head;
		head->setNext(NULL);
		head->setPrev(NULL);
		list_size++;
	}
	else
	{
		if (head->value() >= x) //tworze nowy element przed dotychczasowa head
		{
			Elem* p = new Elem;
			p->setValue(x);
			p->setPrev(NULL);
			head->setPrev(p);
			p->setNext(head);
			head = p;
			list_size++;
		}
		else
		{
			if (head == tail) //nowy element jest wiekszy od head, czyli tworze nowy tail, bo lista jest jednoelementowa
			{
				tail = new Elem(x);
				head->setNext(tail);
				tail->setPrev(head);
				tail->setNext(NULL);
				list_size++;
				return;
			}
			Elem* p = head;
			while (p != tail)
			{
				if (p->next()->value() >= x) //wstawiam nowy element pomiedzy head i tail
				{
					Elem* newElem = new Elem(x);
					p->next()->setPrev(newElem);
					newElem->setNext(p->next());
					p->setNext(newElem);
					newElem->setPrev(p);
					list_size++;
					return;

				}
				p = p->next();
			}
			//wstawiam nowy element za tail
			Elem* new_elem = new Elem(x);
			new_elem->setPrev(tail);
			tail->setNext(new_elem);
			new_elem->setNext(NULL);
			tail = new_elem;
			list_size++;
		}
	}
}

void SortedDLList::del(int x)
{
	Elem* p = locate(x);
	if (p == NULL) //elementu nie ma w liscie lub lista jest pusta
	{
		return;
	}
	else if (p == head) //poszukiwany element jest head
	{
		head = head->next();
		delete p;
		list_size--;
	}
	else if (p != tail) //poszukiwany element jest pomiedzy head a tail
	{
		p->prev()->setNext(p->next());
		p->next()->setPrev(p->prev());
		delete p;
		list_size--;
	}
	else //poszukiwany element jest tail
	{
		tail = tail->prev();
		delete p;
		list_size--;
	}
}

void SortedDLList::delALLx(int x)
{
	if (empty())
	{
		return;
	}
	else
	{
		Elem* p = locate(x);
		while (p != NULL)
		{
			p = locate(x);
			if (p == NULL)
				break;
			if (p->prev() != NULL)
			{
				p->prev()->setNext(p->next());
				p->next()->setPrev(p->prev());
				delete p;
				list_size--;
			}
			else
			{
				head->next()->setPrev(NULL);
				head = head->next();
				delete p;
				list_size--;
			}
		}
	}
}

void SortedDLList::clear()
{
	if (empty())
	{
		return;
	}
	else
	{
		while (head!=NULL)
		{
			Elem* p = head;
			head->next()->setPrev(NULL);
			head = head->next();
			delete p;
			list_size = 0;
		}
	}
}

ostream& operator<<(ostream& out, SortedDLList& l)
{
	if (l.empty())
	{
		return out;
	}
	Elem* temp = l.head;
	

	while(temp != NULL)
	{
		out << temp->value() << " ";
		temp = temp->next();
	}
	return out;
}

int main()
{
	SortedDLList lista;
	lista.insert(2);
	lista.insert(5);
	lista.insert(5);
	lista.insert(8);
	lista.insert(1);
	lista.insert(1);
	lista.insert(9);
	cout << lista << endl;

	
	lista.delALLx(1);
	cout << lista;

	return 0;
}