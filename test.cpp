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

using namespace std;

string epic(uint64_t, uint8_t);
tuple<uint64_t, uint8_t, uint8_t> brf (uint64_t, uint8_t, uint8_t);
vector<string> compress(vector<string>);
string uncompress(string);
string pop_off(uint64_t);
uint64_t gcd (uint64_t n1, uint64_t n2);

// greatest common denominator
// Just seeing if we're dealing with
// prime number or not, we will decrement
// each time we find it is, and repeat.
uint64_t gcd (uint64_t n1, uint64_t n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

// TODO: REDO
string uncompress(string zip) {
    uint8_t inc = zip[2], exponent = zip[1], base = zip[0];
    bitset<64> n_1 = 0;

    n_1 = pow(base, exponent) + inc;
    return pop_off(n_1.to_ulong());
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t b) {
    string y = "";
    int i = 8;
    while (i-- > 0) {
        uint8_t c = (b-1)%256;
        if (abs(c)%256 == 0) {
            y.push_back((char)255);
        }
        else if (abs(c)%256 == 1) {
            y.push_back((char)0);
        }
        else {
            unsigned char x = abs(c)%256;
            y.push_back(x);
        }
        b >>= 8;
    }
    return y;
}

// make assertions and content
string epic(uint64_t epiphany, uint8_t x) {

    string v = "";

    tuple<long double, uint8_t, uint8_t> gce = make_tuple(0,0,0);

    for (int i = 2; i < 8 ; i++) {
        for (int j = 2 ; j < 16 ; j++) {
            if (epiphany == pow(i,j)) {
                v.push_back((char)get<1>(gce));
                v.push_back((char)get<2>(gce));
                v.push_back(x);
                return v;
            }
        }
    }
    return v;
}

vector<string> compress(vector<string> t) {

    int i = 0, z = 0;

    // We're looping through each segment
    // Moving with t[i] (i++ at the bottom)
    int j = 0;
    uint64_t inv_total = 0;
    string m = "";
    // This is to make the loop for
    // continuous zipping; opt @cmdline argv[3]
    vector<string> s = {};
    while (t.size() > i) {
        // tv is the current segment
        string tv = t[i];

        // exciting is the 64 bit 8 byte
        // value of the sequences as they
        // are read in to the compressor
        uint64_t exciting = 0;
        while (tv.length() >= 8) {
            z = 0;

            // Let's go thru each char, sequencing 8 bytes
            // end to end. We'll
            // use this to compress with.
            for (unsigned int a : tv) {
                // Obvious, I think
                bitset<8> h = a;
                exciting <<= 8;
                exciting += (a-1)%256;
                z++;
                // 8 byte limit
                if (z == 8)
                    break;
            }

            // Shed the last ? bytes substr(?,->)
            if (z < tv.length())
                tv = tv.substr(z,tv.length()-1);

            inv_total = exciting;

            int y = 0, z = 0;
            if (inv_total == 0)
                m += "JJM";
            else {
                int x = 0;
                string n = "";
                do {
                    n.clear();
                    if (y%16 == 0) {
                        z++;
                        --inv_total;
                    }
                    if (inv_total == pow(z, y)) {
                        n.push_back(x);
                        n.push_back(y);
                        n.push_back(z);
                    }
                    x++;
                    y++;
                } while (n.length() != 3);
                m += n;
            }

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

    string n = "";
    s.push_back(m);
    m.clear();
    return s;
}

int main(int c, char * argv[]) {

    long int zips = 0;
    if (c < 5) {
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
    double file_len = gs.length();

    if (0 == strcmp(argv[1], "-c")) {
        // All of file in segments
        vector<string> t {};
        int y = 0;
        //Segment size
        int bytes = 48000;
    // Segments are made to make reading the file in
    // much easier, and faster. We're only concentrating
    // on the little of the file at once.
        // Take to making segments
        while (bytes <= gs.length()) {
            t.push_back(gs.substr(0,bytes));
            gs = gs.substr(bytes, gs.length()-1);
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(0,gs.length()-1));
        gs.clear();
        // File is loaded
        cout << ".." << flush;
        long double w = 0;
        while (zips > 0) {
            // Use epic() to compress
            t = compress(t);
            zips--;
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
                if (i > 0) {
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
        int bytes = 48000;
        vector<string> t = {};
        int y = 0;
    // Segments are made to make reading the file in
    // much easier, and faster. We're only concentrating
    // on the little of the file at once.
        // Take to making segments
        while (bytes <= gs.length()) {
            t.push_back(gs.substr(0,bytes));
            if (t.size()%bytes == 0) {
                cout << ". " << flush;
            }
            gs = gs.substr(bytes, gs.length()-1);
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(0,gs.length()-1));
        gs.clear();
        string g = "", JJM_spaces = "";
        for (string j : t) {
            for (int h : j) {
                JJM_spaces.push_back((char)h);
                if ("JJM" == JJM_spaces) {
                    for (int i = 0 ; i < 8 ; i++)
                        ofo << (char)(0);
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 3) {
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
            }
            ofo << JJM_spaces;
            JJM_spaces.clear();
        }
    }
    //output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}
