#include <iostream>
#include <clocale>
#include <iomanip>
#include <cstring>
#include <string>
#include <Windows.h>
using namespace std;
///////////////////////////////////////////////////////////
const int MAX = 12;
char month[12][10] = { "января"	,"февраля",	"марта",	"апреля"	, "мая", 	"июня",	"июля",	"августа", "сентября",	"октября",	"ноября",	"декабря" };
void printHead();
int day_in_month(int num);
void getstring(char* mas);
void getnum(int& num);
///////////////////////////////////////////////////////////
class CONTACT
{
private:
	char* surname = new char[MAX];
	char* name = new char[MAX];
	long long number = 0; 
	int* date = new int[3];
public:
	// конструктор по умолчанию
	CONTACT()
	{ 
		this->get();
	}
	// конструктор с пятью аргументами
	CONTACT(char* surname, char* name, long long num, int * date) : surname(surname), name(name), number(num), date(date)
	{ }
	void display() const // вывод на экран
	{
		string print_name = surname;
		print_name += " ";
		print_name += name;
		cout << endl << left << setw(24) << print_name
			<< "|\t" << number
			<< "\t|\t" << date[0] << " " <<  month[date[1] - 1] << " " << date[2];
	}
	void get() // ввод данных пользователем
	{
		cout << "\n\nВведите данные нового контакта: " << endl;
		cout << "Фамилия: ";
		getstring(surname);
		cout << "Имя: ";
		getstring(name);
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер телефона: ";
		cin>>number;
		while (cin.fail() || number < pow(10,10) || number > pow(10, 11))
		{
			cin.clear(); // Очистить поток ввода
			cin.ignore(cin.rdbuf()->in_avail()); // Очистить буфер
			cout << "Неверный формат. Введите номер телефона: ";
			cin >> number;
		}
		cout << "Дата рождения ";
		input_date();

	}
	void input_date()
	{
		cout << "\nДень: ";
		getnum(date[0]);
		cout << "Месяц: ";
		getnum(date[1]);
		cout << "Год: ";
		getnum(date[2]);
		while (date[1] > 12 || date[0] > day_in_month(date[1]) || date[2] > 2022 || date[2] < 1900)
		{
			cout << "Неверный формат даты. Введите повторно";
			input_date();
		}
	}
	char* getname() { return name; }
	char* getsurname() { return surname; }

	bool issurname(char * find_sur)
	{
		if (!strcmp(this->surname, find_sur)) return true;
		else return false;
	}
	bool isperson(char* find_sur, char* find_name )
	{
		if (!strcmp(this->surname, find_sur) && !strcmp(this->name, find_name)) return true;
		else return false;
	}
}; // конец класса CONTACT


///////////////////////////////////////////////////////////
struct note  // один элемент списка
{
	CONTACT * person;   // некоторые данные
	note* next; // указатель на следующую структуру
};

///////////////////////////////////////////////////////////
class NOTE // список
{
private:
	note* end;
	note* first;
public:
	NOTE()            // конструктор без параметров
	{
		first = NULL;
		end = NULL;
	}     // первого элемента пока нет
	void addfirstitem(CONTACT* contact) // добавление элемента в начало
	{
		note* newlink = new note;      // выделяем память
		newlink->person = contact;             // запоминаем данные
		newlink->next = first;         // запоминаем значение first
		first = newlink;               // first теперь указывает на новый элемент
	}
	///////////////////////////////////////////////////////////
	void addenditem(CONTACT* contact) // добавление элемента в конец
	{
		note* newlink = new note;      // выделяем память
		newlink->person = contact;             // запоминаем данные
		if (first == NULL)
		{
			first = newlink;
			newlink->next = NULL;
		}
		else
		{
			newlink->next = NULL;         // передвигаем end
			end->next = newlink;
		}
		end = newlink;               // end теперь указывает на новый элемент
	}
	///////////////////////////////////////////////////////////
	void findSurname(char* contact)
	{
		note* current = first;
		bool flag = false;
		while (current)
		{
			if (current->person->issurname(contact))
			{
				current->person->display();
				flag = true;
			}
			current = current->next;
		}
		if (!flag) cout << "\nКонтакты с такой фамилией не найдены" << endl;
	}
	///////////////////////////////////////////////////////////
	note* findContact(CONTACT* contact)
	{
		note* current = first;
		while (current)
		{
			if (current->person->isperson(contact->getsurname(), contact->getname())) return current;
			current = current->next;
		}
		return NULL;
	}
	///////////////////////////////////////////////////////////
	note* findContact(char* find_sur, char* find_name)
	{
		note* current = first;
		bool flag = false;
		while (current)
		{
			if (current->person->isperson(find_sur, find_name))
			{
				flag = true;
				return current;
			}
			current = current->next;
		}
		if (!flag) cout << "\nКонтакт не найден" << endl;
		return NULL;
	}
	///////////////////////////////////////////////////////////
	void delContact(char* find_sur, char* find_name)
	{
		note* cutCont = findContact(find_sur, find_name);
		if (cutCont == first) first = first->next;
		else
		{
			note* current = first;
			while (current->next != cutCont)
				current = current->next;
			// удаление элемента
			current->next = cutCont->next;
			if (cutCont == end) end = current;
		}
		delete cutCont;
	}
	///////////////////////////////////////////////////////////
	void display()
	{
		printHead();
		note* current = first;           // начинаем с первого элемента
		while (current)                 // пока есть данные
		{
			current->person->display();   // печатаем данные
			current = current->next;       // двигаемся к следующему элементу
		}
	}
	///////////////////////////////////////////////////////////
	void Free()
	{
		if (first == NULL) return;
		note* current = first;
		note* temp;
		while (current)
		{
			temp = current;
			current = current->next;
			delete temp;
		}
		first = NULL;
	}
	note* getfirst() { return first; }
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	int answer = -1;
	NOTE book;
	while (answer != 0)
	{
		cout << endl <<
			"1 - Добавить в конец" << endl <<
			"2 - Вывод списка" << endl <<
			"3 - Добавить в начало" << endl <<
			"4 - Поиск контакта по фамилии" << endl <<
			"5 - Удаление" << endl <<
			"6 - Редактировать" << endl <<
			"7 - Сохранить в файл" << endl <<
			"0 - Выход\nВыберите действие: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> answer;
		while (cin.fail() || answer < 0 || answer > 8)
		{
			cin.clear(); // Очистить поток ввода
			cin.ignore(cin.rdbuf()->in_avail()); // Очистить буфер
			cout << "Ошибка ввода, выберите действие: "; 
			cin >> answer;
		}
		switch (answer)
		{
		case 1:
		{
			CONTACT* contact = new CONTACT;
			if (book.findContact(contact)) cout << "Контакт с таким именем уже существует" << endl;
			else book.addenditem(contact);
			break;
		}
		case 2:
		{
			if (book.getfirst()) book.display();
			else cout << "Нет данных!" << endl;
			break;
		}
		case 3:
		{
			CONTACT* contact = new CONTACT;
			if (book.findContact(contact)) cout << "Контакт с таким именем уже существует" << endl;
			else book.addfirstitem(contact);
			break;
		}
		case 4:
		{
			if (!book.getfirst()) { cout << "Нет данных!" << endl; break; }
			char* surname = new char[MAX];
			cout << "\nВведите фамилию для поиска: ";
			getstring(surname);
			book.findSurname(surname);
			cout << "\n\n";
			break;
		}
		case 5:
		{
			if (!book.getfirst()) { cout << "\nДанные отсутствуют!" << endl; break; }
			char* surname = new char[MAX];
			char* name = new char[MAX];
			cout << "Введите данные контакта, которого хотите удалить: " << endl;
			cout << "Фамилия: ";
			getstring(surname);
			cout << "Имя: ";
			getstring(name);
			book.delContact(surname, name);
			break;
		}
		}
	}
	return 0;
}
void printHead()
{
	cout  <<"\n\n\t Имя" << right <<
		setw(13) <<"|" <<
		setw(19) << "Номер телефона" <<
		setw(5) << "|" << 
		setw(21) << "Дата рождения" << endl;
	cout << "-------------------------------------------------------------------------";
}
int day_in_month(int num) { return (28 + (num + (num / 8)) % 2 + 2 % num + 2 * (1 / num)); }
void getstring(char* mas)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(mas, MAX);
	while (cin.fail())
	{
		cin.clear(); // Очистить поток ввода
		cin.ignore(cin.rdbuf()->in_avail()); // Очистить буфер
		cout << "Ошибка ввода. Введите строку: ";
		cin.getline(mas, MAX);
	}
}
void getnum(int& num)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> num;
	while (cin.fail())
	{
		cin.clear(); // Очистить поток ввода
		cin.ignore(cin.rdbuf()->in_avail()); // Очистить буфер
		cout << "Некорректный ввод. Введите целочисленное значение: ";
		cin >> num;
	}
}