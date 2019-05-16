#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Reading {
	int day;
	int hour;
	double temperature;
};

const int not_a_month = -1;
const int not_a_reading = -7777;

struct Day {
	std::vector<double> hour{ std::vector<double>(24, not_a_reading) };
};

struct Month {
	int month{ not_a_month };
	std::vector<Day> day{ 32 };
};

struct Year {
	int year;
	std::vector<Month> months{ 12 };
};

void end_of_loop(std::istream& ist, char term, const std::string& message);

int month_to_int(std::string s);

bool is_valid(const Reading& r);

std::istream& operator>>(std::istream& is, Reading& r);

std::istream& operator>>(std::istream& is, Month& m);

std::istream& operator>>(std::istream& is, Year& y);

void print_year(std::ostream& os, Year& y);