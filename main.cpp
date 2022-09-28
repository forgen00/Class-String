#include <iostream>
#include <cstring>

class String {
private:
	char* str;
	int size;
	int capacity;

	void resize(int new_capacity) {
		char* new_str = new char[new_capacity];
		for (int i = 0; i < size; ++i) {
			new_str[i] = str[i];
		}
		delete[] str;
		str = new_str;
		capacity = new_capacity;
	}

public:
	String(): size(1), capacity(1), str(new char[capacity]) {}
	String(const char* string);
	String(const String& s);
	~String();

	String& operator=(const String& other);
	
	friend bool operator==(const String& left, const String& right);
	friend bool operator<(const String& left, const String& right);
	friend bool operator!=(const String& left, const String& right);
	friend bool operator<=(const String& left, const String& right);
	friend bool operator>=(const String& left, const String& right);
	friend bool operator>(const String& left, const String& right);

	friend String operator+(const String& left, const String& right);
	friend String operator+(const String& left, char c);
	String& operator+=(const String& right);
	String &operator+=(char c);

	void print();
	String tolower()const;
	//String toupper()const; 
	//void reverse(int start, int end);   //pos - с какой позиции, end - по какую (включительно)

	//Ищет первое вхождение строки other в строку, к которой применяется метод.
	//Если вхождения нет - то возвращаем -1
	/*
	 Пример:
	 String s = "abcbabccc";
	 String other = "bab";
	 std::cout << s.find(); //Выведет 3
	 */
	//int find(const String& other);
};

//size - фактическое количество элементов, capacity - вместимость массива

String::String(const char* s): size(strlen(s)), capacity(size * 2), str(new char[strlen(s) * 2]) {
	for (int i = 0; i < size; ++i) {
		str[i] = s[i];
	}
}
String::String(const String& s): size(s.size), capacity(s.capacity), str(new char[s.size * 2]) {
	for (int i = 0; i < s.size; ++i) {
		str[i] = s.str[i];
	}
}

String::~String() {
	delete[] str;
}

String& String::operator=(const String& other) {
	if (str == other.str) {
		return *this;
	}
	String new_string;
	new_string.size = other.size;
	new_string.capacity = other.capacity;
	for (int i = 0; i < size; ++i) {
		new_string.str[i] = other.str[i];
	}
	return new_string;
}

bool operator==(const String& left, const String& right) {
	for (int i = 0; i < std::min(left.size, right.size); ++i) {
		if (left.str[i] != right.str[i]) {
			return false;
		}
	}
	if (left.size != right.size) {
		return false;
	}
	return true;
}

bool operator<(const String& left, const String& right) {
	for (int i = 0; i < std::min(left.size, right.size); ++i) {
		if (left.str[i] < right.str[i]) {
			return true;
		}
	}
	if (left.size < right.size) {
		return true;
	}
	return false;
}

bool operator!=(const String& left, const String& right) {
	return !(left == right);
}

bool operator<=(const String& left, const String& right) {
	return !(left < right);
}

bool operator>=(const String& left, const String& right) {
	return !(left < right) || left == right ? true : false;
}

bool operator>(const String& left, const String& right) {
	return !(left < right);
}

String operator+(const String & left, const String & right) {
	int new_size = left.size + right.size;
	int new_capacity = new_size * 2;
	char* new_str = new char[new_capacity];
	for (int i = 0; i < left.size; ++i) {
		new_str[i] = left.str[i];
	}
	int k = 0;
	for (int i = left.size; i < new_size; ++i) {
		new_str[i] = right.str[k];
		++k;
	}
	String new_string(new_str);
	new_string.size = new_size;
	new_string.capacity = new_capacity;
	return new_string;
}

String operator+(const String& left, char c) {
	String result(left);
	if (left.size < left.capacity) {
		result.str[++result.size] = c;
	}
	else {
		result.resize(result.capacity * 2);
		result.str[++result.size] = c;
	}	
	return result;
}

String& String::operator+=(const String& right) {
	if (size + right.size > capacity) {
		resize(capacity * 2);
	}
	return *this = *this + right;
}

String& String::operator+=(char c) {
	if (size < capacity) {
		resize(capacity * 2);
	}
	return *this = *this + c;
}

void String::print() {
	for (int i = 0; i < size; ++i) {
		std::cout << str[i];
	}
}

//Метод должен вернуть новую строку, в которой все буквы верхнего регистра стали буквами нижнего регистра
String String::tolower()const {
	String result;
	for (int i = 0; i < size; ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			result.str[i] += str[i] + 32;
		}
		else {
			result.str[i] += str[i];
		}
	}
	return result;
}

/*
//Метод должен вернуть новую строку, в которой все буквы верхнего регистра стали буквами верхнего регистра
String String::toupper()const {

}

//Разворот строки
void reverse(int start, int end) {

}   //pos - с какой позиции, end - по какую (включительно)

//Ищет первое вхождение строки other в строку, к которой применяется метод.
//Если вхождения нет - то возвращаем -1
/*
 Пример:
 String s = "abcbabccc";
 String other = "bab";
 std::cout << s.find(); //Выведет 3
 
int find(const String& other) {

}
*/

int main() {
	String s("aBcDe");
	s.tolower();
	s.print();
	return 0;
}