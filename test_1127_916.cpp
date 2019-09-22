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

string epic(uint8_t);
tuple<uint8_t, long double, long double> brf (unsigned long long int, long double, long double);
vector<string> compress(vector<string>);
string uncompress(uint32_t);
string pop_off(uint64_t);
uint64_t gcd (uint64_t n1, uint64_t n2);

// Best nth root finder (input, base, exponent)
tuple<uint8_t, long double, long double> brf (unsigned long long int n1, long double n2 = 3, long double n3 = 1) {
    long double nr = (1/n2);
    unsigned long long int rn = pow(n1,nr);
    while (n2 > 0 && rn > pow(n2,n3) < n1) {
        n2--;
        n3 = 0;
        while (pow(n2,n3) < n1) ++n3;
        if (n1 - pow(n2,n3) == 0) {
            unsigned long long int x = pow(n2,n3-1) - n1;
            cout << pow(n2,n3) << endl;
            cout << n1 << endl << flush;
            return make_tuple(x, n2, n3);
        }
    }
    return make_tuple(0,0,0);
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
    uint8_t inc = zip[2], exponent = zip[1], base = zip[0];
    bitset<24> n_1 = 0;
    n_1 = pow(base, exponent) + inc;
    return pop_off(n_1.to_ulong());
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t b) {
    string y = "";
    int i = 0;
    while (i++ < 8) {
        int a = (b%256) - 1;
        unsigned char x = a;
        y.push_back(x);
        b >>= 8;
    }
    return y;
}

// make assertions and content
string epic(uint64_t epiphany) {

    string v = "";
    // Deriving variable
    uint8_t f = 0;
    uint8_t x = 0;

    tuple<uint8_t, long double, long double> gce = make_tuple(0,0,0);
    uint64_t b = gcd(31, epiphany);

    while(b == 1) {
        b = gcd(31, --epiphany);
        x++;
    }
    while (x < pow(2,32)) {
        for (int i = 63 ; i > 0 ; i--) {
            gce = brf(epiphany,i,1);
            if (get<1>(gce) != 0) {
                v.push_back((char)get<1>(gce));
                v.push_back((char)get<2>(gce));
                if (get<0>(gce) == 0)
                    v.push_back(' ');
                else
                    v.push_back((char)get<0>(gce));

                return v;
            }
        }
    }

    cout << "Error: Invalid stream" << flush;
    exit(0);

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
                exciting += a + 1;
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
    double file_len = gs.length();

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
            long double w = 0;
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
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}
