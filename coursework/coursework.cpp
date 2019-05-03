
#include "pch.h"
#include <iostream>

using namespace std;

class my_string {

private:
	char* _ch;
	int _length;

public:

	my_string() {
		_ch = nullptr;
		_length = 0;
	}

	my_string(char* c) {
		_length = strlen(c);
		_ch = new char[_length + 1];
		strcpy_s(_ch, _length + 1, c);	// you can use just strspy();
	}

	my_string(const char* c) {
		_length = strlen(c);;
		_ch = new char[_length + 1];
		strcpy_s(_ch, _length + 1, c);
	}

	my_string& operator = (const my_string& right) {

		if (this == &right) {
			return *this;
		}

		if (_length != right._length || _length == 0) {
			delete[] _ch;
			_length = right._length;
			_ch = new char[_length + 1];
		}
		strcpy_s(_ch, _length, right._ch);
	}

	char operator [] (int i) {
		return _ch[i];
	}

	void print() {
		cout << _ch;
	}


	friend ostream& operator << (ostream &os, const my_string& current) {
		os << current._ch;
		return os;
	}
	friend ostream& operator << (ostream &os, my_string* current) {
		os << current->_ch;
		return os;
	}
};


class request {

	my_string* departue;
	my_string* destination;
	my_string* flight_number;
	my_string* surname;
	my_string* name;
	my_string* patronymic;

};

class List {
	struct node {

		request* R;

		node* next;
		node* previous;

		node() {

			request* R = new request();
			next = nullptr;
			previous = nullptr;

		}
	};

	node* head;
	node* last;

public:
	List() {

		head = nullptr;
		last = nullptr;

	}
	void add() {

		node* buf = new node();
		if (head == nullptr)
			head = buf;
		if (last != nullptr) {
			last->next = buf;
			last->next->previous = last;
		}
		last = buf;
	}

	bool empty() {
		return head == nullptr;
	}
	//node* findByKey(int key);
	//node* findByINDX(int i);
	//void deleteByKey(int key);
	//void deleteByINDX(int i);
	//void insertByINDX(int i, int key);
	//void printAll();
};

//
//List::node* List::findByKey(int key) {
//
//	node* buf = head;
//
//	while (buf != nullptr) {
//		if (buf->key == key)
//			return buf;
//		buf = buf->next;
//	}
//
//	return nullptr;
//}
//
//List::node* List::findByINDX(int i) {
//
//	node* buf = head;
//
//	if (i >= 0) {
//		int j = 0;
//		while (j++ < i) {
//			buf = buf->next;
//		}
//		return buf;
//	}
//
//	cout << "ERROR";
//	return nullptr;
//}
//
//void List::deleteByKey(int key) {
//	node* buf = findByKey(key);
//	if (buf != nullptr) {
//		if (buf == head) {
//			head = buf->next;
//			head->previous = nullptr;
//			delete buf;
//		}
//		else if (buf == last) {
//			last = buf->previous;
//			last->next = nullptr;
//			delete buf;
//		}
//		else {
//			buf->previous->next = buf->next;
//			buf->next->previous = buf->previous;
//			delete buf;
//		}
//	}
//}
//
//void List::deleteByINDX(int i) {
//	node* buf = findByINDX(i);
//	if (buf != nullptr) {
//		if (buf == head) {
//			head = buf->next;
//			head->previous = nullptr;
//			delete buf;
//		}
//		else if (buf == last) {
//			last = buf->previous;
//			last->next = nullptr;
//			delete buf;
//		}
//		else {
//			buf->previous->next = buf->next;
//			buf->next->previous = buf->previous;
//			delete buf;
//		}
//	}
//}
//
//void List::printAll() {
//	node* buf = head;
//	if (!empty()) {
//		while (buf != nullptr) {
//			cout << '{' << buf->key << "} ";
//			buf = buf->next;
//		}
//	}
//}
//
//void List::insertByINDX(int i, int key) {
//
//	if (!empty()) {
//
//		node* buf = new node();
//		buf->key = key;
//
//		if (buf != nullptr) {
//			if (i == 0) {
//				buf->next = head;
//				head->previous = buf;
//				head = buf;
//			}
//			else {
//				node* buf2 = findByINDX(i);
//				buf->next = buf2;
//				buf2->previous->next = buf;
//				buf->previous = buf2->previous;
//				buf2->previous = buf;
//			}
//		}
//	}
//}

char* Enter() {

	char* str = new char(256);
	cin >> str;
	return str;
	/*
	char sep[] = " ";
	cin.getline(str, 256);
	cin.ignore();
	char* token = strtok(str, sep);
	while (token) {

		token = strtok(NULL, sep);
	}*/
}

void adding() {

	my_string* departue;
	my_string* destination;
	my_string* flight_number;
	my_string* surname;
	my_string* name;
	my_string* patronymic;
	my_string* date;
	my_string* hours;

	int n = 6;

	cout << "Departue: ";
	departue = new my_string(Enter());
	cout << "Destination: ";
	destination = new my_string(Enter());
	cout << departue << "  " << destination;
	cout << "flight number: ";
	flight_number = new my_string(Enter());

}

void menu() {

	cout << "menu\n0. exit\n1. add\n2.delete by index\n3. find by \n4.save\n5.load" << endl;
	int ent = -1;
	while (ent != 0) {
		cout << "Enter:";
		cin >> ent;
		switch (ent)
		{
		case(1):
			adding();
			break;
		case(2):
			break;
		default:
			break;
		}
		ent = 0;
	}
}

void kekdel() {

}

int main() {
	menu();
	return 0;
}
