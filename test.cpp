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
#include <chrono>
#include <ctime>

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
    
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

              
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
    vector<string> t {};
    while (gs.length() > 0) {
        t.push_back(gs.substr(0,8));
        gs.erase((size_t)0, 8);
    }
    int i = 0;
    string v = {};
    bitset<8> d = 0;
    while (t.size() > i) {
        
        long long int epiphany = 0;
        for (int a : t[i]) {
            epiphany <<= 8;
            epiphany += a;
        }
        long long int x = epiphany;
        long long int n = x;
        d = 0;
        while (n/(2) > 0 && d.to_ulong() < 256) {
            d = d.to_ulong() + 1;
            n /= d.to_ulong() * 2;
            x /= d.to_ulong() * 2;
        }
        
        if (y < d.to_ulong()) {
            y = d.to_ulong();
            cout << y << " " << flush;
        }
        v.push_back((char)d.to_ulong());
        i++;
        if (v.size()%10000 == 0) {
            ofo << v;
            v.clear();
        }
    }
    
    ofo << v;
    v.clear();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    ////////////////ofo;
}