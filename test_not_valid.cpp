#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <istream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <chrono>
#include <ctime>
#include <bitset>
#include <string.h>
#include <tuple>
#include <cmath>

using namespace std;


string epic(uint8_t);
tuple<uint64_t, uint8_t, uint64_t> brf (uint64_t, uint8_t, uint64_t);
vector<string> compress(vector<string>);
string uncompress(uint32_t);
string pop_off(uint64_t);
uint64_t gcd (uint64_t n1, uint64_t n2);
long double n_root(long double num, int n_);

long double n_root(long double x, int d){
    long low = 0, high = 1;
    
    while (std::pow(high, d) <= x) {
        low = high;
        high *= 2;
    }
    while (low != high - 1) {
        long step = (high - low) / 2;
        long candidate = low + step;

        long double value = std::pow(candidate, d);
        if (value == x) {
            return candidate;
        }
        if (value < x) {
            low = candidate;
            continue;
        }
        high = candidate;
    }
    return low;
}

// Best nth root finder (input, base, exponent)
tuple<uint64_t, uint8_t, uint64_t> brf (uint64_t n1, uint8_t n2, uint64_t n3 = 1) {
    if (n2 > 64)
        return make_tuple(0,0,0);
        
    int x = 0;
    do {
        x = 0;
        n3++;
        while (pow(n2,n3) != n1 - x && x < pow(2,32)) {
            if (pow(n2, n3) == n1 - x) {
                cout << "?" << flush;
                break;
                //return make_tuple(n1, n2, n3);
            }
            x++;
        }
    } while (pow(n2,n3) < n1 - x);
    if (pow(n2,n3) == n1 - x)
        return make_tuple(n1, n2, n3);
    return brf(n1, ++n2, 0);
}

// greatest common denominator
// Just seeing if we're dealing with
// prime number or not, we will decrement
// each time we find it is, and repeat.
uint64_t gcd (uint64_t n1, uint64_t n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

// TODO: REDO
string uncompress(string zip) {
	uint8_t inc = zip[2], exponent = zip[0], base = zip[1];
	bitset<64> n_1 = 0;
	n_1 = pow(base, exponent) + inc;
	return pop_off(n_1.to_ulong());
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t b) {
	string y = "";
	int i = 0;
	while (i++ < 8) {
	    int a = (b%256);
	    if (a > 0)
	        a--;
	    else a = 255;
		y.push_back(a);
		b >>= 8;
	}
	return y;
}

// make assertions and content
string epic(uint64_t epiphany, int x = 0) {

    string v = "";
    // Deriving variable
    uint8_t f = 0;
    bitset<64> bits = 0, dec = 0;
    double gt = 0;
    while (256 < (long double)epiphany) {
        f++;
        dec <<= 1;
        if (0 <= (epiphany/64 - round(epiphany/64))) {
            dec = dec.to_ullong() + 1;
            epiphany /= 64;
        }
        dec <<= 1;
        if (0 <= (epiphany/32 - round(epiphany/32))) {
            dec = dec.to_ullong() + 1;
            epiphany /= 32;
        }
        dec <<= 1;
        if (0 <= (epiphany/16 - round(epiphany/16))) {
            dec = dec.to_ullong() + 1;
            epiphany /= 16;
        }
        dec <<= 1;
        if (0 <= (epiphany/8 - round(epiphany/8))) {
            dec = dec.to_ullong() + 1;
            epiphany /= 8;
        }
    }
    cout << (int)f << "*" << dec.to_ullong() << " " << flush;
    // f is how many times we divided by 64.
    // Each time we divide by sixty-four, we
    // deleted the first bit if dec has a 1
    // otherwise it was a even number. This
    // was the best I can come up with.
    
    v.push_back(f);
    v.push_back(dec.to_ulong() >> 8);
    dec >>= 8;
    v.push_back(dec.to_ulong());
    
    return v;
    
}

vector<string> compress(vector<string> t) {

    int i = 0, z = 0;
    
    // We're looping through each segment
    // Moving with t[i] (i++ at the bottom)
    int j = 0;
    uint64_t inv_total;
    string m = "";
    // This is to make the loop for
    // continuous zipping; opt @cmdline argv[3]
    vector<string> s = {};
    while (t.size() > i) {
        // tv is the current segment
        string tv = t[i];
        
        uint64_t epiphany = 0;
        while (tv.length() > 0) {
            z = 0;
            
            // exciting is the 64 bit 8 byte 
            // value of the sequences as they
            // are read in to the compressor
            uint64_t exciting = 0;
            
            // Let's go thru each char, sequencing 8 bytes
            // end to end. We'll
            // use this to compress with.
            for (unsigned int a : tv) {
                // Obvious, I think
                exciting <<= 8;
                exciting += (a);
                z++;
                // 8 byte limit
                if (z == 8)
                    break;
            }
            
            // Shed the last ? bytes substr(?,->)
            if (z < tv.length())
                tv = tv.substr(z,tv.length()-1);
            else
                tv.clear();
            
            inv_total = exciting;
            
            int y = 0;
            if (inv_total == 0)
                m += "JJM";
            else
                m += epic(inv_total);
                
            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (m.length() > 8000) {
                s.push_back(m);
                m.clear();
            }
        }
        i++;
    }
    {
        m += epic(inv_total);
        s.push_back(m);
        m.clear();
    }
    return s;
}

int main(int c, char * argv[]) {
    
    
    long int zips = 0;
    if (c < 4) {
        cout << "* You may add a 3rd argument to zip multiple times";
        cout << "\n* " << argv[0] << " -(c|d) <file_to_zip> <output> <integer>";
        cout << "\n* Defaulting to: 3\n";
        zips = 3;
    }
    else
    {
        zips = strtol(argv[4],NULL,10);
    }
    
    auto start = std::chrono::system_clock::now();
    // Start Timer
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << std::ctime(&start_time) << flush;
    
    // Input/Output
    ifstream ifo (argv[2], std::ios_base::in | std::ios_base::binary);
    ofstream ofo (argv[3], std::ios_base::out | std::ios_base::binary);
    
    // Create Buffer
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    
    // File length
    long double file_len = gs.length();
    
    if (0 == strcmp(argv[1], "-c")) {
        // All of file in segments
        vector<string> t {};
        int y = 0;
        //Segment size
        int bytes = 16000;
    // Segments are made to make reading the file in
    // much easier, and faster. We're only concentrating
    // on the little of the file at once.
        // Take to making segments
        while ((y*bytes)+bytes < gs.length()) {
            t.push_back(gs.substr((y*bytes)+bytes,bytes));
            if (t.size()%bytes == 0) {
                cout << ". " << flush;
            }
            y++;
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(y*bytes, gs.length()-1));
        gs.clear();
        // File is loaded
        cout << ".." << flush;
        while (zips > 0) {
            // Use epic() to compress
            t = compress(t);
            zips--;
            uint64_t w = 0;
            for (string i : t)
                w += i.length();
            cout << round((w/file_len) * 100) << "% " << flush;
        }
        
        // Entropy of Compress output
        set<string> n = {};
        int i = 0;
        for (string c : t) {
            string tiptum = "";
            for (int r : c) {
                i++;
                if (i > 0) { // && i%3 == 0) {
                    n.insert(tiptum);
                    tiptum.clear();
                }
                tiptum.push_back(r);
            }
            i = 0;
            ofo << c;
        }
        cout << n.size() << " ";
    }
    else if (0 == strcmp(argv[1], "-d")) {
        int bytes = 30000;
        vector<string> t = {};
        int y = 0;
    // Segments are made to make reading the file in
    // much easier, and faster. We're only concentrating
    // on the little of the file at once.
        // Take to making segments
        while ((y*bytes)+bytes < gs.length()) {
            t.push_back(gs.substr((y*bytes)+bytes,bytes));
            if (t.size()%bytes == 0) {
                cout << ". " << flush;
            }
            y++;
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(y*bytes, gs.length()-1));
        gs.clear();
        y = 0;
        string g = "", JJM_spaces = "";
        bitset<24> buckets = 0;
        for (string j : t) {
            for (int h : j) {
                buckets <<= 8;
                buckets = buckets.to_ulong() + h;
                y++;
                JJM_spaces.push_back((char)h);
                if ("JJM" == JJM_spaces) {
                    for (int i = 0 ; i < 8 ; i++)
                        ofo << ' ';
                    buckets = 0;
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 3) {
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                    
                }
            }
        }
    }
    //output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<long double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}