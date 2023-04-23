#include <iostream>
#include <iomanip>
#include <string>
#include "clockmain.h"
using namespace std;

/*
 * Author: Michelle- Darling
 * Date: 3.14.2023
 * Purpose: Creating a 12- and 24-hour clock for Chada Tech
 */

//went ahead and read about classes in zybooks so I could use getters and setters like they asked for in the 
//addOne(insert measurement of time here) feedback tools
class Time {
private:
	int second = 0;
	int minute = 0;
	int hour = 0;
public:
	//mutators for measurement of time
	void SetSecond(int s) {
		second = s;
	}
	void SetMinute(int m) {
		minute = m;
	}
	void SetHour(int h) {
		hour = h;
	}
	//accessors for measurement of time
	int GetSecond() {
		return second;
	}
	int GetMinute() {
		return minute;
	}
	int GetHour() {
		return hour;
	}
};
//***************************************************************************************************************
string twoDigitString(unsigned int n) {
	string digitString;

	//found out from good old google that std::to_string(int) will turn variables into strings
	digitString = std::to_string(n);

	//if the number is 1 string size in length, it puts a "0" in the front of the string
	if (digitString.size() == 1) {
		digitString.insert(0, "0");
	}

	return digitString;
}
//***************************************************************************************************************
string nCharString(size_t n, char c) {
	string charaString;

	//n denotes how many characters in the string will be there
	//c denotes the character used in the string
	//as long as i is still less than n, c will be added to the charaString
	for (int i = 0; i < n; ++i) {
		charaString += c;
	}

	return charaString;
}
//***************************************************************************************************************
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
	Time updateTime; //I think this was in here from when I was troubleshooting, but I'm afraid of breaking my
	string militaryTime = "";                                                     //code again so it's staying
	string hour = "";
	string minute = "";
	string second = "";

	//convert to twoDigitString for each measurement of time
	hour = twoDigitString(h);
	minute = twoDigitString(m);
	second = twoDigitString(s);

	//put each measurement of time into a single string with colons in between
	militaryTime = hour.append(":" + minute + ":" + second);

	return militaryTime;
}
//***************************************************************************************************************
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
	Time updateTime; //same as the one from formatTime24
	string standardTime = "";
	string hour = "";
	string minute = "";
	string second = "";
	string meridian = "A M";

	//if hour is 0 in military time, that means h is 12 in standard and merdian is A M
	if (h == 0) {
		h = 12;
	}
	//else if h is greater than or equal to 12, if h is equal to 12 then h is 12, else h is equal to h - 12 and
	//meridian is P M
	else if (h >= 12) {
		h = (h == 12) ? 12 : h - 12;
		meridian = "P M";
	}

	//convert to twoDigitString for each measurement of time
	hour = twoDigitString(h);
	minute = twoDigitString(m);
	second = twoDigitString(s);

	//put each measurement of time into a single string with colons in between and a space between second and 
	//meridian
	standardTime = hour.append(":" + minute + ":" + second + " " + meridian);

	return standardTime;
}
//***************************************************************************************************************
void printMenu(unsigned int numStrings, unsigned char width) {
	//printing out the menu layout, using nCharString to post each excess of characters
	cout << nCharString(width, '*') << endl;
	cout << "* 1 - Add One Hour" << nCharString(width - 19, ' ') << "*" << endl;
	cout << endl;
	cout << "* 2 - Add One Minute" << nCharString(width - 21, ' ') << "*" << endl;
	cout << endl;
	cout << "* 3 - Add One Second" << nCharString(width - 21, ' ') << "*" << endl;
	cout << endl;
	cout << "* 4 - Exit Program" << nCharString(width - 19, ' ') << "*" << endl;
	cout << nCharString(width, '*') << endl;
}
//***************************************************************************************************************
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
	//printing out the clocks layout, using nCharString to post each excess of characters
	cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
	cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << "*   ";
	cout << "*" << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << "*" << endl;
	cout << endl;
	cout << "*" << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << "*   ";
	cout << "*" << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << "*" << endl;
	cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
}
//***************************************************************************************************************
void addOneHour(Time& updateTime) { //I learned about attaching each of these properly so that the function would
												 //recognize when it was being called from the menu or each other
	//using the accessor to get the current hour
	int h = updateTime.GetHour();

	//adding the hour by +1 if the hour is between 0 and 22 then updating the setter
	if ((h >= 0) && (h <= 22)) {
		h += 1;
		updateTime.SetHour(h);
	}
	//if the hour is 23 it wraps back around to 0 and updates the setter
	else if (h == 23) {
		h = 0;
		updateTime.SetHour(h);
	}
}
//***************************************************************************************************************
void addOneMinute(Time& updateTime) {
	//using the accessor to get the current minute
	int m = updateTime.GetMinute();

	//adding the minute by +1 if the minute is between 0 and 58 then updating the setter
	if ((m >= 0) && (m <= 58)) {
		m += 1;
		updateTime.SetMinute(m);
	}
	//if the minute is 59 it wraps back around to 0 and updates the setter, then calls addOneHour
	else if (m == 59) {
		m = 0;
		updateTime.SetMinute(m);
		addOneHour(updateTime);
	}
}
//***************************************************************************************************************
void addOneSecond(Time& updateTime) {
	//using the accessor to get the current second
	int s = updateTime.GetSecond();

	//adding the second by +1 if the second is between 0 and 58 then updating the setter
	if ((s >= 0) && (s <= 58)) {
		s += 1;
		updateTime.SetSecond(s);
	}
	//if the second is 59 it wraps back around to 0 and updates the setter, then calls addOneMinute
	else if (s == 59) {
		s = 0;
		updateTime.SetSecond(s);
		addOneMinute(updateTime);
	}
}
//***************************************************************************************************************
int main() {
	Time currentTime; //this helps connect the mutators and accessors and addOne(insert measurement of time here)
	int h;
	int m;
	int s;
	int choice;

	//recieve input for initial time
	cout << "Enter the hour in military time: " << endl;
	cin >> h;
	cout << "Enter the minutes: " << endl;
	cin >> m;
	cout << "Enter the seconds: " << endl;
	cin >> s;
	cout << endl;

	//set all measurements of time
	currentTime.SetHour(h);
	currentTime.SetMinute(m);
	currentTime.SetSecond(s);
	
	//do-while choice isn't 4 (exiting the program)
	do {
		//displays clocks, prints the menu, then asks for input for the menu option, putting the input into choice
		displayClocks(h, m, s);
		cout << endl;
		printMenu(1, 27);
		cout << endl;
		cout << "Enter the option number: " << endl;
		cin >> choice;

		//switch-case to lead to appropriate menu option
		switch (choice) {
			case 1:
				addOneHour(currentTime);
				break;
			case 2:
				addOneMinute(currentTime);
				break;
			case 3:
				addOneSecond(currentTime);
				break;
			case 4:
				cout << "Exiting program." << endl;
				break;
			default:
				cout << "Please try again." << endl;
				break;
		}
		//getting the measurements of time again to update them
		h = currentTime.GetHour();
		m = currentTime.GetMinute();
		s = currentTime.GetSecond();

	}
	while (choice != 4);
}
//***************************************************************************************************************