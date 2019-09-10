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
long long int recIdle(string answers) {
    int range_size = 256;
	long long total = 0;
    long long int powr = 1;
	for (int i = 0 ; i < answers.length() ; i++) {
		powr = 1;
		for (int u = 0 ; u < i ; u++) {
			powr *= range_size;
		}
	    total = total + (powr * answers[i]);
	    if (total + (pow(range_size,i+1) * answers[i+1]) > pow(2,64)) {
	        cout << "never" << flush;
	        exit(0);
        }
    }
	long long int bitbyte = total;
	return total;
}
int main(int c, char * argv[]) {
    
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << std::ctime(&start_time) << flush;
    
    // we can leave the segments in averages per csv line
    ifstream ifo (argv[1], std::ios_base::in | std::ios_base::binary);
    ofstream ofo ("test.txt", std::ios_base::out | std::ios_base::binary);

    string hexrem = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*-_=+[{]};:'\",<.>/?|\\";
    long x = 0;
    string str = "";
    vector<int> ordered {};
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    double file_len = gs.length();
    set<char> care = {};
    vector<string> t {};
    while (gs.length() >= 10000) {
        t.push_back(gs.substr(0,10000));
        gs.erase(gs.begin(), gs.begin()+10000);
        if (t.size()%1000 == 0) {
            cout << ". " << flush;
        }
    }
    if (gs.length() > 0)
        t.push_back(gs);
    gs.clear();
    cout << ".." << flush;
    int i = 0;
    string v = {};
    string v2 = {};
    bitset<8> d = 0;
    while (t.size() > i) {
        int y = 0;
        long long int epiphany = 0;
        while (t[i].length() > 0) {
            y = 0;
            for (int a : t[i]) {
                //epiphany <<= 8;
                //epiphany += a;
                v.push_back(a);
                if (++y == 8)
                    break;
            }
            
            t[i] = t[i].substr(8,t[i].length()-1);
            long long int x = recIdle(v); // epiphany;
            long long int n = x;
            d = 0;
            while (n/(2) > 0 && d.to_ulong() < 256) {
                d = d.to_ulong() + 1;
                n /= d.to_ulong() * 2;
                x /= d.to_ulong() * 2;
            }
            
            v2.push_back((char)d.to_ulong());
            v.clear();
            if (v2.size()%10000 == 0) {
                ofo << v2;
                v2.clear();
                cout << ". " << flush;
            }
        }
        i++;
    }
    
    ofo << v;
    v.clear();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}