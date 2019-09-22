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

using namespace std;

string epic(uint64_t);
uint64_t gcd (uint64_t, uint64_t);
vector<string> compress(vector<string>);
string uncompress(uint32_t);
string pop_off(uint64_t);

uint64_t gcd (uint64_t n1, uint64_t n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

string uncompress(uint32_t bytes) {
    uint8_t inc = 0, metric = 0, g_c_d = 0;
    inc = bytes%256;
    metric = (bytes >> 8)%256;
    g_c_d = (bytes >> 16)%256;
    bitset<64> n_1 = g_c_d;
    while (n_1.to_ulong() + g_c_d < metric)
        n_1 = n_1.to_ulong() + g_c_d;

    while (--inc - 1 >= 0)
        g_c_d++;

    return pop_off(n_1.to_ulong());
}

string pop_off(uint64_t b) {
    string y = "";
    while (b > 0) {
        unsigned char x = b%256;
        y.push_back(x);
        b >>= 8;
    }
    return y;
}

string epic(uint64_t epiphany) {

    string v = "";
    // Deriving variable
    uint64_t fh = 0;
    uint8_t x = 0;

    int b = gcd(15,epiphany);
    while (b == 1 && x < 16) {
        epiphany--;

        b = gcd(15,epiphany);
        x++;
    }
    if (1 != b) {
        int y = 64;
        while (!(pow(2,64 - y) < epiphany)) y--;
        unsigned char f = 0;
        if (256 > x && 256 > y) {
            f = ((64-y) << 4) + x;
            v.push_back(y);
            v.push_back(x);
            v.push_back(b);
            return v;
        }
        else
        {
            cout << ":" << flush;
            v.push_back('?');
            v.push_back(y);
            v.push_back(x);
            v.push_back(b);
            return v;
        }
    }
    else {
        // Derive
        fh = pow(2,63) * 1.9;
        //fh = fh - epiphany;
        bitset<64> fg = epiphany, fj = 0;
        for (int i = 0 ; 0 < fg.to_ulong() ; i++) {
            bitset<3> c = 0;
            if (fg[0] == 1 && fg[1] == 1) {
                fj = fj.to_ulong() + 3;
                fj <<= 3;
            }
            if (fg[0] == 0 && fg[1] == 1) {
                fj = fj.to_ulong() + 2;
                fj <<= 2;
            }
            if (fg[0] == 1 && fg[1] == 0) {
                fj = fj.to_ulong() + 1;
                fj <<= 1;
            }
            if (fg[0] == 0 && fg[1] == 0) {
                fj = fj.to_ulong() << 1;
            }
            fg >>= 2;
        }
        fh = fj.to_ullong();
    }

    while (fh > 0) {
        unsigned char f = fh%256;
        v.push_back(f);
        fh >>= 8;
    }
    v.push_back(']');
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
    // continuous zipping; opt @cmdline
    vector<string> s = {};
    while (t.size() > i) {
        // tv is the current segment
        string tv = t[i];
        // `j` tells us what generation of
        // inversion we're on. We turn them
        // all into a large 64 bit numbre (3 8bytes/64bits)
        // epitome is the second generation of
        // the 3 generations that go into the 64 bits
        // Readers Note: we're using inversion
        //          x = epitome
        // for instance, macompplished is the 3rd

        uint64_t epiphany = 0;
        while (tv.length() > 0) {
            z = 0;

            // epiphany is the first generation
            // it takes the value of exciting
            uint64_t exciting = 0;

            // Let's go thur each character in a 8 byte
            // sequence and put them end to end. We'll
            // use this to compress with.
            for (unsigned int a : tv) {
                // Obvious, I think
                exciting <<= 8;
                exciting += a;
                z++;
                // Kick out every 8 bytes
                if (z == 8)
                    break;
            }

            // Shed the last 8 bytes
            if (z < tv.length())
                tv = tv.substr(z,tv.length()-1);
            else
                tv.clear();
            /// Invert the 3 generations
            inv_total = exciting; // pow(2,63)

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

    char * zip_count = argv[4];
    long int zips = 0;
    if (c < 4) {
        cout << "* You may add a 2nd argument to zip multiple times";
        cout << "\n* " << argv[0] << " -(c|d) <file_to_zip> <integer>";
        cout << "\n* Default: 3\n";
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
        int bytes = 10000;
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
        // File is loaded completely
        cout << ".." << flush;
        while (zips > 0) {
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
                if (i > 0 && i%3 == 0) {
                    n.insert(tiptum);
                    tiptum.clear();
                }
                tiptum.push_back(r);
                i++;
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
        string g = "";
        uint32_t JJM_spaces = ((int)('J') << 16) + ((int)('J') << 8) + (int)('M');
        bitset<24> buckets = 0;
        for (string j : t) {
            for (int h : j) {
                buckets <<= 8;
                buckets = buckets.to_ulong() + h;
                y++;
                if (buckets.to_ulong() == JJM_spaces) {
                    for (int i = 0 ; i < 8 ; i++)
                        g += ' ';
                    buckets = 0;
                    continue;
                }
                if (buckets.to_ulong() > 0 && y%3 == 0) {
                    g += uncompress(buckets.to_ulong());
                    buckets = 0;
                }
            }
            g += uncompress(buckets.to_ulong());
            ofo << g;
            g.clear();
        }
    }
    //output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}