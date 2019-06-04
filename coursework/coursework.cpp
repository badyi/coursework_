#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>

void print_all_r();

using namespace std;

int max_len = 13;

class my_string {

	private:

		char* _ch;
		int _length;

	public:

		my_string() {

			_ch = nullptr;
			_length = 0;

		}

		~my_string() {
			char* current = _ch;
			delete current;
		}

		my_string(char* c) {

			
			_length = strlen(c);

			if (_length > max_len)
				max_len = _length;

			_ch = new char[_length + 1];
			strcpy_s(_ch, _length + 1, c);

		}

		my_string(const char* c) {

			_length = strlen(c);

			if (_length > max_len)
				max_len = _length;

			_ch = new char[_length + 1];
			strcpy_s(_ch, _length + 1, c);

		}

		int Length() {
			return _length;
		}

		void change_ch(char* str) { 

			_length = strlen(str);
			delete[] _ch;
			_ch = new char[_length + 1];
			strcpy_s(_ch, _length + 1, str);

			if (_length > max_len)
				max_len = _length;

		}

		const char* get_ch() {
			return _ch;
		}

		bool operator ==(const my_string& right) {

			if (this->_length == right._length) {

				for (int i = 0; i < this->_length; i++) {
					if (_ch[i] != right._ch[i]) {
						return false;
					}
				}

			}

			else
				return false;
			return true;

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

			if (_length > max_len)
				max_len = _length;
		}

		friend ostream& operator << (ostream &os, const my_string& current) { 

			os << current._ch;
			return os;

		}

		friend ostream& operator << (ostream &os, my_string* current) { // cout

			os << current->_ch;
			return os;

		}

		friend istream& operator >> (istream &in, my_string& current) {
			current._ch = new char();
			in >> current._ch;
			current._length = strlen(current._ch);
			return in;
		}

		friend istream& operator >> (istream &in, my_string* current) {

			current->_ch = new char[256];
			in >> current->_ch;
			current->_length = strlen(current->_ch);

			return in;
		}

};

class request {

	private:

		my_string* departure;
		my_string* destination;
		my_string* flight_number;
		my_string* surname;
		my_string* name;
		my_string* patronymic;
		my_string* departure_date;
		my_string* departure_time;

	public:
	
		request() {

			departure = nullptr;
			destination = nullptr;
			flight_number = nullptr;
			surname = nullptr;
			name = nullptr;
			patronymic = nullptr;
			departure_date = nullptr;
			departure_time = nullptr;

		}

		request(my_string* dep, my_string* des, my_string* fn, my_string* s, my_string* n, my_string* p, my_string* dd, my_string* dt) {

			departure = dep;
			destination = des;
			flight_number= fn;
			surname = s;
			name = n;
			patronymic = p;
			departure_date = dd;
			departure_time = dt;

		}

		~request() {

			delete departure;
			delete destination;
			delete flight_number;
			delete surname;
			delete name;
			delete patronymic;
			delete departure_time;
			delete departure_date;

		}

		my_string* get_date() {

			return departure_date;

		}

		my_string* get_flight_n() {

			return flight_number;

		}

		friend ostream& operator << (ostream &os, request* current) {

			os << ' ' << left << setw(max_len + 1) << current->departure << ' ';
			os << setw(max_len + 1) << current->destination << ' ';
			os << setw(max_len + 1) << current->flight_number << ' ' << setw(max_len + 1) << current->surname << ' ';
			os << setw(max_len + 1) << current->name << ' ' << setw(max_len + 1) << current->patronymic << ' ';
			os << setw(max_len) << current->departure_date << setw(max_len - 6) << right << current->departure_time;
			return os;

		}
};

class Stack {
private:
	class node {
		friend Stack;
		int key;
		node* next;
	};

	node* head;

public:
	Stack() {
		head = nullptr;
	}

	void push(int key) {
		node* t = new node();
		if (head)
			t->next = head;
		head = t;
		head->key = key;
	}

	int pop() {
		if (head) {
			node* buf = head;
			int t = head->key;
			head = head->next;
			delete(buf);
			return t;
		}
		else {
			cout << "ERROR";
			return -1;
		}
	}

	void print(node* current) {
		cout << current->key << endl;
		if (current->next) {
			print(current->next);
		}

	}

	void print() {
		if (head)
			print(head);
		else
			cout << "ERROR. Stack is empty";
	}

	void copy(const Stack& other) {
		if (other.head != nullptr) {
			if (other.head->next)
				copy((const Stack&)other.head->next);
			push(other.head->key);
		}
	}

	Stack(const Stack& other) {
		node* head;
		copy(other);
	}

	bool empty() {
		return head == nullptr;
	}

	~Stack() {
		node* buf = head;
		if (head != nullptr)
			while (buf->next) {
				buf = head->next;
				delete[] buf;
			}
		delete[] head;
	}
};

class List {

	class node {

		friend List;
		request* R;
		node* next;
		node* previous;

	};

	node* head;
	node* last;


	node* find_by_index(int i) {

		node* buf = head;

		if (i >= 0) {
			int j = 0;
			while (j++ < i) {
				buf = buf->next;
			}
			return buf;
		}

		cout << "Ошибка";
		return nullptr;
	}

public:
	List() {

		head = nullptr;
		last = nullptr;

	}

	~List() {
		delete head;
		delete last;
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

		if (current != nullptr) {
			int counter = 0;
			while (current != nullptr) {
				counter++;
				current = current->next;
			}
			return counter;
		}
		else
			return 0;
	}

	void delete_by_index(int i) {

		node* buf = find_by_index(i);

		if (buf != nullptr) {

			if (buf == head) {
				head = buf->next;
				if (head != nullptr)
					head->previous = nullptr;
				if (buf == head && size() == 1)
					last = nullptr;
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

	void insert_by_index(int i, request* key) {

		if (!empty()) {

			node* buf = new node();
			buf->R = key;

			if (buf != nullptr) {
				if (i == 0) {
					buf->next = head;
					head->previous = buf;
					head = buf;
				}
				else {
					node* buf2 = find_by_index(i);
					buf->next = buf2;
					buf2->previous->next = buf;
					buf->previous = buf2->previous;
					buf2->previous = buf;
				}

			}
		}
	}

	void swap(int i, int j) {

		node* n1 = find_by_index(i);
		node* n2 = find_by_index(j);
		if (i < j && j == size() - 1) {
			insert_by_index(i, n2->R);
			delete_by_index(j + 1);

		    add(n1->R);
			delete_by_index(i + 1);
		}
		else if (i < j) {
			insert_by_index(i, n2->R);
			delete_by_index(j + 1);

			insert_by_index(j, n1->R);
			delete_by_index(i + 1);
		}
		else if (i > j && i == size() - 1) {
			insert_by_index(j, n1->R);
			delete_by_index(i + 1);

			add(n2->R);
			delete_by_index(j + 1);
		}
		else if ( i > j) {
			insert_by_index(j, n1->R);
			delete_by_index(i + 1);

			insert_by_index(i, n2->R);
			delete_by_index(j + 1);
		}
	}

	request* operator [](int i) {

		request* t = find_by_index(i)->R;
		return t;

	}

};

List requests;

char* Enter() {

	char* str = new char[256];
	cin >> str;
	return str;

}

void print_column_names() {

	cout << endl << '|' << left << setw(max_len + 1) << "Отправление: " << '|' << setw(max_len + 1) << "Прибытие: " << '|' << setw(max_len + 1) << "Номер рейса:" << '|';
	cout << setw(max_len + 1) << "Имя:" << '|' << setw(max_len + 1) << "Фамилия:" << '|' << setw(max_len + 1) << "Отчество:" << '|';
	cout << setw(max_len) << "Дата:" << '|' << setw(max_len - 6) << "Время:" << '|' << setw(5) << "i:" << '|' << endl;

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

	my_string* departure;
	my_string* destination;
	my_string* flight_number;
	my_string* surname = new my_string();
	my_string* name = new my_string();
	my_string* patronymic = new my_string();
	my_string* departure_date;
	my_string* departure_time;

	cout << endl;
	
	cout << "Отправление из: ";
	departure = new my_string(Enter());
	cout << "Прибытие в: ";
	destination = new my_string(Enter());
	cout << "Номер рейса: ";
	flight_number = new my_string(Enter());
	cout << "Ф.И.О: ";
	enter_full_name(surname, name, patronymic);
	cout << "Дата вылета: ";
	departure_date = new my_string(Enter());
	cout << "Время вылета: ";
	departure_time = new my_string(Enter());

	
	request* test = new request(departure , destination, flight_number, surname, name , patronymic, departure_date, departure_time);
	requests.add(test);
	
}

void print_all_r() {
	
	if (requests.size() > 0) {

		for (int i = 0; i < max_len * 8 + 8 + 7; i++)
			cout << '_';

		print_column_names();

		for (int i = 0; i < requests.size(); i++) {

			request* current = requests[i];
			cout << current;
			cout <<"  "<< left<< setw(5) << i << '|' << endl;

		}

		for (int i = 0; i < max_len * 8 + 8 + 7; i++)
			cout << '-';
		cout << endl;

	}

	else
		cout << "Ошибка. Список пуст.";
}

void remove() {

	if (0 != requests.size()) {

		int t;
		cout << "1. Удалить по индексу     \n";
		cout << "2. Удалить по дате        \n";
		cout << "3. Удалить по номеру рейса\n";
		cout << "4. Удалить все заявки     \n:";

		cin >> t;

		if (t == 1) {

			int i;
			cout << "Индекс: ";
			cin >> i;

			if (i > -1 && i < requests.size()) {
				requests.delete_by_index(i);
				cout << "Успешно";
			}
			else
				cout << "Ошибка. Выхд за рамки списка.";
		}

		else if (t == 2) {

			my_string* date;

			cout << "Дата: ";
			bool f = false;
			date = new my_string(Enter());

			for (int j = 0; j < requests.size(); j++) {

				if (*requests[j]->get_date() == *date) {
					requests.delete_by_index(j);
					f = true;
					j = 0;
				}

			}
			if (f)
				cout << "Успешно";
			else
				cout << "Не найдено";
		}

		else if (t == 3) {

			my_string* fn;

			cout << "Номер рейса: ";

			fn = new my_string(Enter());
			
			bool f = false;
			for (int j = 0; j < requests.size(); j++) {

				if (*requests[j]->get_flight_n() == *fn) {
					requests.delete_by_index(j);
					j = 0;
					f = true;
				}
			}
			if (f)
				cout << "Успешно";
			else
				cout << "Не найдено";
		}

		else if (t == 4) {
			int n = requests.size();
			for (int j = 0; j < n; j++) {
				requests.delete_by_index(0);
			}
		}
	}

	else 
		cout << "Ошибка. Список пуст.";

}

void find() {

	if (!requests.empty()) {
		int i;
		cout << endl << "Индекс: ";
		cin >> i;

		print_column_names();

		cout << requests[i] << "  " << left << setw(5) << i << '|' << endl;
	}
	else
		cout << "Ошибка. Список пуст.";
}

void load_data() {

	ifstream file("database.txt");

	my_string* departue;
	my_string* destination;
	my_string* flight_number;
	my_string* surname;
	my_string* name;
	my_string* patronymic;
	my_string* departure_date;
	my_string* departure_time;

	char* buf = new char[256];

	if (file.is_open()) {

		while (true) {

			file >> buf;
			my_string* departure = new my_string(buf);	
			file >> buf;
			my_string* destination = new my_string(buf);
			file >> buf;
			my_string* flight_number = new my_string(buf);
			file >> buf;
			my_string* surname = new my_string(buf);
			file >> buf;
			my_string* name = new my_string(buf);
			file >> buf;
			my_string* patronymic = new my_string(buf);
			file >> buf;
			my_string* departure_date = new my_string(buf);
			file >> buf;
			my_string* departure_time = new my_string(buf);

			request* test = new request(departure, destination, flight_number, surname, name, patronymic, departure_date, departure_time);
			requests.add(test);

			if (file.eof())
				break;

		}

		cout << "Успешно";

	}
	else {

		cout << "Ошибка. Проверьте файл database.txt";

	}

}

void find_by_d_fl() {

	int i;
	bool flag = true;

	cout << endl;
	cout << "|1. По номеру рейса       |\n";
	cout << "|2. По дате               |\n";
	cout << "|3. По дате и номеру рейса|\n";
	cout << ':';
	cin >> i;
	cout << endl;

	if (requests.size() > 0) {
		if (i == 1) {

			my_string* fn;
			cout << "Номер рейса: ";
			fn = new my_string(Enter());

			for (int j = 0; j < requests.size(); j++) {

				if (*requests[j]->get_flight_n() == *fn) {
					if (flag) {
						print_column_names();
						flag = false;
					}
					cout << requests[j] << setw(5) << j << '|' << endl;
				}

			}

			if (flag) {
				cout << "Заявок с данными параметрами не найдены.";
			}
		}

		else if (i == 2) {

			my_string* date;
			cout << "Дата: ";
			date = new my_string(Enter());

			for (int j = 0; j < requests.size(); j++) {

				if (*requests[j]->get_date() == *date) {
					if (flag) {
						print_column_names();
						flag = false;
					}
					cout << requests[j] << setw(5) << j << '|' << endl;
				}

			}

			if (flag) {
				cout << "Заявок с данными параметрами не найдены.";
			}
		}

		else if (i == 3) {

			my_string* fn;
			cout << "Номер рейса: ";
			fn = new my_string(Enter());

			my_string* date;
			cout << "Дата: ";
			date = new my_string(Enter());


			for (int j = 0; j < requests.size(); j++) {

				if ((*requests[j]->get_date() == *date) && (*requests[j]->get_flight_n() == *fn)) {

					if (flag) {
						print_column_names();
						flag = false;
					}

					cout << requests[j] << setw(5) << j << '|' << endl;
				}
			}

			if (flag) {
				cout << "Заявок с данными параметрами не найдено.";
			}
		}
	}

	else
		cout << "Ошибка. Список пуст.";
}

void p_menu() {

	cout << "-------------------------Menu------------------------------|\n";
	cout << "| 0. Выход                                                 |\n";
	cout << "| 1. Вывести меню                                          |\n";
	cout << "| 2. Добавить заявку                                       |\n";
	cout << "| 3. Вывести на экран весь список заявок                   |\n";
	cout << "| 4. Найти по индекску заявку                              |\n";
	cout << "| 5. Удалить заявку/заявки                                 |\n";
	cout << "| 6. Вывод заявок по заданному номеру рейса и дате вылета  |\n";
	cout << "| 7. Сохранить данные                                      |\n";
	cout << "| 8. Загрузить                                             |\n";
	cout << "| 9. Сортировка по дате                                    |\n";
	cout << "|__________________________________________________________|\n";

}

void save(){

	if (requests.size() != 0) {
		cout << "Удалить предыдущие данные?\n";
		cout << "1.Да\n";
		cout << "2.Нет\n:";
		int t;
		cin >> t;

		if (t == 1) {

			ofstream file("database.txt", ios::trunc);

			for (int i = 0; i < requests.size(); i++) {

				file << requests[i];
				if (i != requests.size() - 1)
					file << endl;

			}

			cout << "Успешно";
		}

		else if (t == 2) {

			ofstream file("database.txt", ios::app);

			file << endl;

			for (int i = 0; i < requests.size(); i++) {

				file << requests[i];
				if (i != requests.size() - 1)
					file << endl;

			}

			cout << "Успешно";
		}
	}

	else 
		cout << "Ошибка. Список пуст.";

}

int compare(my_string* d1 , my_string* d2) { 
	
	int y1, y2, m1, m2 , day1, day2;

	(d1->get_ch()[0] & 0xCF) != 0 ? day1 = (d1->get_ch()[0] & 0xCF) * 10 + (d1->get_ch()[1] & 0xCF) : day1 = (d1->get_ch()[1] & 0xCF);

	(d2->get_ch()[0] & 0xCF) != 0 ? day2 = (d2->get_ch()[0] & 0xCF) * 10 + (d2->get_ch()[1] & 0xCF) : day2 = (d2->get_ch()[1] & 0xCF);


	(d1->get_ch()[3] & 0xCF) != 0 ? m1 = (d1->get_ch()[3] & 0xCF) * 10 + (d1->get_ch()[4] & 0xCF) : m1 = (d1->get_ch()[4] & 0xCF);

	(d2->get_ch()[3] & 0xCF) != 0 ? m2 = (d2->get_ch()[3] & 0xCF) * 10 + (d2->get_ch()[4] & 0xCF) : m2 = (d2->get_ch()[4] & 0xCF);


	(d1->get_ch()[6] & 0xCF) != 0 ? y1 = (d1->get_ch()[6] & 0xCF) * 10 + (d1->get_ch()[7] & 0xCF) : y1 = (d1->get_ch()[7] & 0xCF);

	(d2->get_ch()[6] & 0xCF) != 0 ? y2 = (d2->get_ch()[6] & 0xCF) * 10 + (d2->get_ch()[7] & 0xCF) : y2 = (d2->get_ch()[7] & 0xCF);

	if (y1 > y2)
		return 1;
	else if (y1 < y2)
		return -1;

	else {

		if (m1 > m2)
			return 1;
		else if (m1 < m2)
			return -1;

		else {

			if (day1 > day2)
				return 1;
			else if (day1 < day2)
				return -1;

			else
				return 0;
		}
	}

	return 0;

}

Stack s;

void sort_by_date() {

	if (!requests.empty()) {
		int n = requests.size();
		s.push(0);
		s.push(n - 1);
		while (!s.empty()) {

			int l = s.pop();
			int f = s.pop();
			while (f < l) {
				int f1 = f;
				int l1 = l;

				my_string* mid = requests[(f1 + l1) / 2]->get_date();

				while (f1 < l1) {
					while (compare(requests[f1]->get_date(), mid) == -1) {
						f1++;
					}
					while (compare(requests[l1]->get_date(), mid) == 1)
						l1--;
					if (f1 <= l1) {

						requests.swap(f1, l1);
						f1++;
						l1--;

					}
				}

				if (f1 < l) {
					s.push(f1);
					s.push(l);
				}
				l = l1;
			}
		}
		cout << "Успешно";
	}

	else
		cout << "Ошибка список пуст";
}

void menu() {

	p_menu();

	int ent = -1;

	while (ent != 0) {

		cout << endl << "Ввод: ";
		cin >> ent;
		switch (ent)
		{
		case(1):
			p_menu();
			break;
		case(2):
			adding();
			break;
		case(3):
			print_all_r();
			break;
		case(4):
			find();
			break;
		case(5):
			remove();
			break;
		case(6):
			find_by_d_fl();
			break;
		case(7):
			save();
			break;
		case(8):
			load_data();
			break;
		case(9):
			sort_by_date();
			break;
		default:
			break;
		}

	}
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu();
	return 0;
}