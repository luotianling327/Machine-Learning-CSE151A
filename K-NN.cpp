// CSE151A Homework#1 (Plus Problems)
// Name: Tianling Luo
// PID: A16186344
// Ans:
// a) Test error is 0.168142.
// b) Test error is 0.0707965.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class nba {
public:
string name;
string position;
int h;
int w;
double h_st;
double w_st;
};
int main() {
// training points
vector<nba> train;
ifstream fin("train.csv");
string line1;
int sumh = 0;
int sumw = 0;
while (getline(fin, line1)) {
nba nba1;
istringstream sin(line1);
vector<string> fields;
string field;
while (getline(sin, field, ',')) {
fields.push_back(field);
}
nba1.name = fields[0];
nba1.position = fields[1];
stringstream geek1(fields[2]);
geek1 >> nba1.h;
sumh += nba1.h;
stringstream geek2(fields[3]);
geek2 >> nba1.w;
sumw += nba1.w;
train.push_back(nba1);
}
fin.close();
int n1 = train.size();
double aveh = sumh * 1.0 / n1;
double avew = sumw * 1.0 / n1;
double sth, stw;
sumh = sumw = 0;
for (int i = 0; i < n1; i++) {
sumh += (train[i].h - aveh) * (train[i].h - aveh);
sumw += (train[i].w - avew) * (train[i].w - avew);
}
double sdh = sqrt(sumh / n1);
double sdw = sqrt(sumw / n1);
for (int i = 0; i < n1; i++) {
train[i].h_st = (train[i].h - aveh * 1.0) / sdh;
train[i].w_st = (train[i].w - avew * 1.0) / sdw;
}
// testing points
vector<nba> test;
ifstream fin2("test.csv");
string line2;
int count1 = 0;
int count2 = 0;
while (getline(fin2, line2)) {
nba nba1;
istringstream sin(line2);
vector<string> fields;
string field;
while (getline(sin, field, ',')) {
fields.push_back(field);
}
nba1.name = fields[0];
nba1.position = fields[1];
stringstream geek1(fields[2]);
geek1 >> nba1.h;
nba1.h_st = (nba1.h - aveh * 1.0) / sdh;
stringstream geek2(fields[3]);
geek2 >> nba1.w;
nba1.w_st = (nba1.w - avew * 1.0) / sdw;
test.push_back(nba1);
double distance1 = 100;
double distance2 = 100;
string position1;
string position2;
for (int i = 0; i < n1; i++) {
int d1=sqrt((train[i].h - nba1.h) * (train[i].h - nba1.h) +
(train[i].w - nba1.w) * (train[i].w - nba1.w));
if (d1 < distance1) {
distance1 = d1;
position1 = train[i].position;
}
int d2 = sqrt((train[i].h_st - nba1.h_st) * (train[i].h_st -
nba1.h_st) +
(train[i].w_st - nba1.w_st) * (train[i].w_st - nba1.w_st));
if (d2 < distance2) {
distance2 = d2;
position2 = train[i].position;
}
}
if (position1 == nba1.position) {
count1++;
}
if (position2 == nba1.position) {
count2++;
}
}
fin2.close();
int n2 = test.size();
double error1 = 1 - (count1*1.00 / n2);
double error2 = 1 - (count2*1.00 / n2);
cout << "Test error without standardizing the data is " << error1 << endl;
cout << "Test error with standardizing the data is " << error2 << endl;
}
