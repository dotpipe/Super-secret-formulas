#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <istream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <bitset>
#include <set>

using namespace std;

unsigned int gcd (unsigned int, unsigned int);

unsigned int gcd (unsigned int n1, unsigned int n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}
long long int recIdle(vector<unsigned int> answers) {
    int range_size = 256;
	long long total = 0;
    long long int powr = 1;
	for (int i = 0 ; i < answers.size() ; i++) {
		powr = 1;
		for (int u = 0 ; u < i ; u++) {
			powr *= range_size;
		}
	    total = total + (powr * answers[i]);
    }
	long long int bitbyte = total;
	return total;
}
int main(int c, char * argv[]) {

    // we can leave the segments in averages per csv line
    ifstream ifo (argv[1], std::ios_base::in | std::ios_base::binary);
    ofstream ofo ("test.txt", std::ios_base::out | std::ios_base::binary);

    string hexrem = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*-_=+[{]};:'\",<.>/?|\\";
    long x = 0, y = 0;
    string str = "";
    vector<int> ordered {};
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    double file_len = gs.length();
    set<char> care = {};
    while (gs.length() > 0) {
        vector<long long int> t {};
        vector<unsigned int> v = {};
        if (gs.length() >= 6) {
            string c = gs.substr(0,6);
            for (int a : c) {
                v.push_back(a);
            }
        }
        else {
            for (int a : gs) {
                v.push_back(a);
            }
        }
        gs = gs.substr(6,gs.length()-1);
        t.push_back(recIdle(v));
        for (long int x : t) {
            long int n = x;
            bitset<4> b = 0;
            while (n/(8) > 0 && b.to_ulong() < 15) {
                b = b.to_ulong() + 1;
                n /= 8;
            }
            long a = n;
            
            bitset<4> c = 0;
            while (a/(2) > 0 && c.to_ulong() < 7) {
                c = c.to_ulong() + 1;
                a /= 2;
            }
            
            unsigned long e = a;
            x = (b.to_ulong()) << 4;
            c <<= 1 + (bool)(e);
            x += (c.to_ulong());
            char bear = x;
            care.insert(bear);
            ofo << bear;
        }
        
    }
    cout << care.size();
}