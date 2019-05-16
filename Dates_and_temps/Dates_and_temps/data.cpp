#include "pch.h"
#include "data.h"

std::vector<std::string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};

std::vector<std::string> month_print_tbl = {
	"January", "February", "March", "April",
	"May", "June", "July", "August", "September",
	"October", "November", "December"
};

void end_of_loop(std::istream& ist, char term, const std::string& message) {
	if (ist.fail()) {
		ist.clear();
		char ch;
		if (ist >> ch && ch == term) return; //всё хорошо
		std::cout << message << std::endl;
	}
}

int month_to_int(std::string s) {
	for (int i = 0; i < 12; i++) if (month_input_tbl[i] == s) return i;
	return -1;
}

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

bool is_valid(const Reading& r) {
	//Грубая проверка
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temperature < implausible_min ||
		implausible_max < r.temperature)
		return false;
	return true;
}

std::istream& operator>>(std::istream& is, Reading& r) {
	//Считываем показания температуры из потока is в r
	//Формат: (3 4 9.7)
	//Проверяем формат, но не корректность данных
	char ch1;
	if (is >> ch1 && ch1 != '(') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') std::cout << "Bad input.\n";
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

std::istream& operator>>(std::istream& is, Month& m) {
	//Считываем объект класса Month из потока is в объект m
	//Формат: { month feb ... }
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string month_maker;
	std::string mm;
	is >> month_maker >> mm;
	if (!is || month_maker != "month")
		std::cout << "Wrong start of Month.\n";
	m.month = month_to_int(mm);

	Reading r;
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}
	if (invalids)
		std::cout << "Wrong data in Month: " << invalids << std::endl;
	if (duplicates)
		std::cout << "Duplicated data in Month: " << duplicates << std::endl;
	end_of_loop(is, '}', "Wrong end of Month");
	return is;
}

std::istream& operator>>(std::istream& is, Year& y) {
	//Считываем объект класса Year из потока is в объект y
	//Формат: { year 1972 ... }
	char ch;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}

	std::string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		std::cout << "Wrong beginning of Year.\n";
	y.year = yy;
	while (true) {
		Month m;
		if (!(is >> m)) break;
		y.months[m.month] = m;
	}

	end_of_loop(is, '}', "Wrong end of Year");
	return is;
}

std::string int_to_month(int m) {
	return month_print_tbl[m];
}

void print_year(std::ostream& os, Year& y) {
	int activeMonths = 0;

	for (int i = 0; i < y.months.size(); i++) if (y.months[i].month != -1) activeMonths++;
	os << "{ year " << y.year << " ";
	if (activeMonths >= 1) {
		for (int i = 0; i < 12; i++) {
			auto *currMonth = &y.months[i];
			if (currMonth->month != -1)
			os << '\n' << '\t' << "{ month " << int_to_month(currMonth->month) << " }";
		}
		os << '\n' << "}" << std::endl;
	}
	else os << "}" << std::endl;
}