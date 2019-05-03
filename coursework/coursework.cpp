﻿
#include "pch.h"
#include <iostream>

using namespace std;

class my_string { // my own vector <char> ~ string

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

			_length = strlen(c);
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

		void change_ch(char* str) { // change key field

			_length = strlen(str);
			delete[] _ch;
			_ch = new char[_length + 1];
			strcpy_s(_ch, _length + 1, str);

		}

		friend ostream& operator << (ostream &os, const my_string& current) { // cout

			os << current._ch;
			return os;

		}

		friend ostream& operator << (ostream &os, my_string* current) { // cout

			os << current->_ch;
			return os;

		}

};


class request {

	private:

		my_string* departue;
		my_string* destination;
		my_string* flight_number;
		my_string* surname;
		my_string* name;
		my_string* patronymic;
		my_string* departure_date;
		my_string* departue_time;

	public:
	
		request() {

			departue = nullptr;
			destination = nullptr;
			flight_number = nullptr;
			surname = nullptr;
			name = nullptr;
			patronymic = nullptr;
			departure_date = nullptr;
			departue_time = nullptr;

		}

		request(my_string* dep, my_string* des, my_string* fn, my_string* s, my_string* n, my_string* p, my_string* dd, my_string* dt) {

			departue = dep;
			destination = des;
			flight_number= fn;
			surname = s;
			name = n;
			patronymic = p;
			departure_date = dd;
			departue_time = dt;

		}

		void add(my_string* dep, my_string* des, my_string* fn, my_string* s, my_string* n, my_string* p, my_string* dd, my_string* dt) {

			departue = dep;
			destination = des;
			flight_number = fn;
			surname = s;
			name = n;
			patronymic = p;
			departure_date = dd;
			departue_time = dt;

		}

		friend ostream& operator << (ostream &os, const request& current) {

			os << current.departue << "  " << current.destination << "  " << current.flight_number << "  " << current.surname << "  " << current.name << "  " << current.patronymic << "  " << current.departure_date << "  " << current.departue_time << endl;
			return os;

		}

		friend ostream& operator << (ostream &os, request* current) {

			os <<  current->departue << "  " << current->destination << "  " << current->flight_number << "  " << current->surname << "  " << current->name << "  " << current->patronymic << "  " << current->departure_date << "  " << current->departue_time << endl;
			return os;

		}

		void print() {

			cout << departue << "  " << destination<< "  " << flight_number << "  " << surname << "  " << name << "  " << patronymic << "  " << departure_date << "  " << departue_time << endl;
		
		}
	
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
	void add(request* r) {

		node* buf = new node();
		buf->R = r;

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
	
	int size() {
		node* current = head;
		int counter = 0;
		while (current != nullptr) {
			counter++;
			current = current->next;
		}
		return counter;
	}
	
	request* operator [](int i) {
		request* t = find_by_index(i)->R;
		return t;
	}

	node* find_by_index(int i) {

		node* buf = head;

		if (i >= 0) {
			int j = 0;
			while (j++ < i) {
				buf = buf->next;
			}
			return buf;
		}

		cout << "ERROR";
		return nullptr;
	}

	void delete_by_index(int i) {
		node* buf = find_by_index(i);
		if (buf != nullptr) {
			if (buf == head) {
				head = buf->next;
				head->previous = nullptr;
				delete buf;
			}
			else if (buf == last) {
				last = buf->previous;
				last->next = nullptr;
				delete buf;
			}
			else {
				buf->previous->next = buf->next;
				buf->next->previous = buf->previous;
				delete buf;
			}
		}
	}
	//node* findByKey(int key);
	//void deleteByKey(int key);
	//void insertByINDX(int i, int key);
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

//}
//

List requests;

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

	char* str = new char[256];
	cin >> str;
	return str;

}

void enter_full_name(my_string* s, my_string* n, my_string* p) {
	char* str = new char[256];
	for (int i = 0; i< 3; i++) {
		cin >> str;
		if (i == 0)
			s->change_ch(str);
		if (i == 1)
			n->change_ch(str);
		if (i == 2)
			p->change_ch(str);
	}
}

void adding() {

	my_string* departue;
	my_string* destination;
	my_string* flight_number;
	my_string* surname = new my_string();
	my_string* name = new my_string();
	my_string* patronymic = new my_string();
	my_string* departure_date;
	my_string* departue_time;

	cout << "Departue: ";
	departue = new my_string(Enter());
	cout << "Destination: ";
	destination = new my_string(Enter());
	cout << "flight number: ";
	flight_number = new my_string(Enter());
	cout << "full name: ";
	enter_full_name(surname, name, patronymic);
	cout << "departure date: ";
	departure_date = new my_string(Enter());
	cout << "departue time: ";
	departue_time = new my_string(Enter());

	
	request* test = new request(departue , destination, flight_number, surname, name , patronymic, departure_date, departue_time);
	requests.add(test);
}

void print_all_r() {
	
	if (requests.size() > 0)
		for (int i = 0; i < requests.size(); i++) {
			request* current = requests[i];
			//current->print();
			cout << current;
		}
	else
		cout << endl << "error";
}

void remove() {

	int i;
	cout << "index: ";
	cin >> i;

	if (i > -1 && i < requests.size()) {
		requests.delete_by_index(i);
		cout << endl << "successful";
	}
	else
		cout << endl << "error";
}

void menu() {

	cout << "menu\n0. exit\n1. add\n2.delete by index\n3. find by index\n4.save\n5.load" << endl;
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
			remove();
			break;
		case(3):
			print_all_r();
			break;
		default:
			break;
		}
	}
}

int main() {
	menu();
	return 0;
}