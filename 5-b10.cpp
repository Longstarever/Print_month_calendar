#include <iostream>
#include <iomanip>
using namespace std;

int zeller(int y, int m, int d) {
	int year, shiji, xingqi, week;
	if (m > 2) {
		year = y % 100;
		shiji = y / 100;
		xingqi = year + (int)(year / 4) + (int)(shiji / 4) - 2 * shiji + (int)(13 * (m + 1) / 5) + d - 1;
		while (xingqi < 0) {
			xingqi = xingqi + 7;
		}
		week = xingqi % 7;
	}
	if (m < 3) {
		y = y - 1;
		m = m + 12;
		year = y % 100;
		shiji = y / 100;
		xingqi = year + (int)(year / 4) + (int)(shiji / 4) - 2 * shiji + (int)(13 * (m + 1) / 5) + d - 1;
		while (xingqi <= 0) {
			xingqi = xingqi + 7;
		}
		week = xingqi % 7;
	}
	return week;
}

int calendar(int nian, int yue, int xingqi) {
	int i = 1, j = 0, tianshu, c;
	c = ((nian % 4 == 0) && (nian % 100)) || (nian % 400 == 0);//闰年
	c ? tianshu = 29 : tianshu = 28;
	switch (yue) {//其他月
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			tianshu = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			tianshu = 30;
			break;
	}
	return tianshu;
}

void print(int rili[][42],int xingqi[],int tianshu[],int n) {
	int a = 0, b = 0, c = 0, mid = 0;
	int i = 0,hang=1,j=0;
	int index[13] = { 0 };
	int yue = 1,mon=1;
	while (1) {
		for (a = 0; ; a++) {
			if (a == n) {
				cout << endl;
				break;
			}
			cout << right << setw(13) << yue << "月" << setw(17) << "";
			mon = yue;
			yue++;
		}
		for (b = 0;; b++) {
			if (b == n) {
				cout << endl;
				break;
			}
			cout << left << setw(4) << "Sun" << setw(4) << "Mon" << setw(4) << "Tue" << setw(4) << "Wed"
				<< setw(4) << "Thu" << setw(4) << "Fri" << setw(4) << "Sat" << "    ";
		}
		if (mon % n == 0) {
			c = 0;
			while (1) {
				mon = yue - n;
				for (; c<n;) {
					for (hang = 0; hang < 6; hang++) {
						if (hang > 4) {//判断是否需要继续执行输出
							for (i = yue - n; i < yue; i++) {
								c = c + index[i];
							}
							if (c >= n) {
								break;
							}
							else {
								c = 0;
							}
						}
						if (c >= n) {
							break;
						}
						for (i = 0; i < 7; i++) {
							if (rili[mon][hang * 7 + i] > rili[mon][hang * 7 + i+1]) {
								index[mon] = 1;//代表此月所有天数输出完毕
							}
							if (rili[mon][hang * 7 + i] == 0) {
								cout << setw(4) << " ";//0代表输出4个空格
							}
							else {
								cout << left << setw(4)<<rili[mon][hang * 7 + i];//正常输出日期
							}
							for (j = yue - n; j < yue; j++) {
								c = c + index[j];
							}
							if (c >= n) {
								cout << endl;
								break;
							}
							else {
								c = 0;
							}
							if (i == 6) {
								if (mon == yue - 1) {
									cout << endl;
									mon = yue - n;
									break;
								}
								else {
									cout << setw(4) << "";
									i = -1;
									mon++;
									continue;
								}
							}
						}
					}
					if (c >= n) {
						break;
					}
				}
				if (c >= n) {
					break;
				}
			}
		}
		cout << endl;
		if (yue > 12) {
			break;
		}
	}
}

int main() {
	int n;
	int rili[13][42] = { 0 };
	int nian, yue, ri = 1, xingqi[13] = {0}, tianshu[13] = {0}, i = 1, j = 0;
	bool a = 0, b = 0, c = 0, d = 0, e = 0;
	while (1) {
		cout << "请输入年份[1900-2100]" << endl;
		cin >> nian ;   //读入x的方式必须是 cin>>int型变量，不允许其他方式
		if (cin.good() == 0) {
			cin.clear();
			cin.ignore(2451504, '\n');
			continue;
		}
		if (nian < 1900 || nian>2100) {
			cin.clear();
			continue;
		}
		if (nian >= 1900 && nian <= 2100) {
			a = 1;
			break;
		}
	}
	while (1) {
		cout << "请输入每行打印的月份数[1/2/3/4/6/12]" << endl;
		cin >> n;
		if (cin.good() == 0) {
			cin.clear();
			cin.ignore(2451504, '\n');
			continue;
		}
		switch (n) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 6:
			case 12:
				b = 1;
				break;
		}
		if (b == 0) {
			cin.ignore(2451504, '\n');
			continue;
		}
		if (b == 1) {
			break;
		}
	}
	c = ((nian % 4 == 0) && (nian % 100)) || (nian % 400 == 0);//闰年
	for (yue = 1; yue < 13; yue++) {
		xingqi[yue] = zeller(nian, yue, ri);
		tianshu[yue] = calendar(nian, yue, xingqi[yue]);
		j = j + tianshu[yue];
	}
	for (yue = 1; yue < 13; yue++) {
		int t = xingqi[yue];
		for (i = 0; i < tianshu[yue]; i++) {
			rili[yue][t + i] = i + 1;
		}
	}
	cout << nian << "年的日历:" << endl << endl;
	print(rili, xingqi, tianshu, n);
	cout << endl;
	return 0;
}
