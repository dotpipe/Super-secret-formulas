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
void epic(long long int epiphany, ofstream& ofo);
long long int recIdle(vector<unsigned int> answers);

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

void epic(long long int epiphany, ofstream& ofo) {
    int z = 0, d = 0;
    string v = "";
    vector<unsigned char> fg = {};
    bitset<64> cx = pow(2,64) - epiphany;
    int e = 0, f = 0;
    unsigned long long int fh = 0;
    for ( ; cx.to_ulong() > 0 ; ) {
        e = 0;
        f++;
        d = 0;
        for (int i = 2 ; i >= 0 ; i--) {
            if (cx[i] == 1) {
                d++;
                e += i;
                cx[i] = 0;
            }
            if (cx.to_ulong() == 0)
                break;
        }
        /*
        switch (e)
        {
            case 4:
                fh <<= d+1;
                fh += 4;
                break;
            case 3:
                fh <<= 2;
                fh += 3;
                break;
            case 2:
                fh <<= 2;
                fh += 2;
                break;
            case 1:
                fh <<= 2;
                fh += 1;
                break;
            default:
                fh <<= 4;
                fh += e;
            break;
        }
        */
        cx >>= 3;
        z += d+1;
        if (z > 64)
            cout << "?" << flush;
        fh <<= (d+1);
        fh += e;
        while (fh > 0 && f%8 == 0) {
            fg.push_back((unsigned char)fh);
            fh >>= 8;
        }
    }
    
    // encoding table (subtract 1 from the right, (accorded from left))
    // 
    //   1 -> 4\2\1(a) = a -> 1,   b -> 2,   c -> 3
    // a 00 will go to next byte

    for (char tn : fg)
        v.push_back((char)tn);
    ofo << v;
    v.clear();
}

int main(int c, char * argv[]) {
    
    auto start = std::chrono::system_clock::now();
    // Some computation here
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << std::ctime(&start_time) << flush;
    
    // we can leave the segments in averages per csv line
    ifstream ifo (argv[1], std::ios_base::in | std::ios_base::binary);
    ofstream ofo ("test.txt", std::ios_base::out | std::ios_base::binary);

    string hexrem = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*-_=+[{]};:'\",<.>/?|\\";
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    double file_len = gs.length();
    set<char> care = {};
    vector<string> t {};
    int y = 0, z = 0;
    int bytes = 10000;
    while ((y*bytes)+bytes < gs.length()) {
        t.push_back(gs.substr((y*bytes),bytes));
        //gs.erase(gs.begin()+(y*bytes), gs.begin()+bytes);
        if (t.size()%bytes == 0) {
            cout << ". " << flush;
        }
        y++;
    }
    if (gs.length() > 0)
        t.push_back(gs.substr(y*bytes, gs.length()-1));
    gs.clear();
    cout << ".." << flush;
    int i = 0;
    
    vector<long long int> bill = {};
    while (t.size() > i) {
        
        string tv = t[i];
        while (tv.length() > 0) {
            z = 0;
            long long int epiphany = 0, exciting = 0;
            for (int a : tv) {
                if ((epiphany << 8) + a >= pow(2,63) + a) {
                    cout << "?" << flush;
                }
                epiphany <<= 8;
                epiphany += a;
                z++;
                if (z == 7)
                    break;
            }
            if (z+1 < tv.length())
                tv = tv.substr(z+1,tv.length()-1);
            else tv.clear();
            epic(epiphany, ofo);
        }
        i++;
    }
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}