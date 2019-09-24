// g++ -o comptest.exe -m64 -Ofast -std=c++17 bester.cpp

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

vector<string> compress(vector<string>);
string uncompress(string v);
string pop_off(uint64_t);
string sepFix(long double epiphany);
std::vector<std::string> DIFSplitStringByNumber(const std::string & str, int len);

uint64_t end_file_len = 0;
set<char> b = {};
const bitset<64> pow64 = -1;

// To-do: Please document this. (What is "epiphany"? What is the expected
// output? Should be documented here, so that we don't need to search the whole
// file to figure it out).

// Epiphany is a multichar (upto 8) number
// that was created with >> 8 and (int)char
// so we want to bring this number back.

string sepFix(uint64_t epiphany)
{
    string v = "", w = "";
    long double t = epiphany;
    uint64_t n = (long double)(pow64.to_ullong()); /// epic);
    long double epic = t; // pow64.to_ulong()/n; //abs(round(pow64.to_ullong() * (n)));
    uint64_t lng = 0;
    
    for (int i = 25 ; i > 0 ; i--) {
        epic = t/n * pow(10,i);
        lng = epic;
        epic = lng;
        while (lng > 0) {
            v.insert(v.begin(), (unsigned char)(lng) % 256);
            lng >>= 8;
        }
        for (int c = 0 ; c < v.length() ; c++) {
            lng <<= 8;
            lng += (unsigned int)v[c];
        }
        if ((long double)lng != epic) {
            v.clear();
            continue;
        }
        int bb = 15;
        epic = lng;
        while (t - (n * (epic / pow(10,bb))) > 10 && bb-- > 0);
        if (t - (n * (epic / pow(10,bb))) <= 10 && v.length() + 3 <= 5) {
            uint8_t c = t - (n * (epic / pow(10,bb)));
            v.insert(v.begin(), (unsigned char)(c));
            if (v[0] != c)
                cout << c-(unsigned int)v[0] << flush;
            v.insert(v.begin(), (unsigned char)(bb));
            v.insert(v.begin(), (unsigned char)('%'));
            return v;
        }
        else
        {
            
            //cout << ' ' << t - (n * (lng / pow(10,bb)));
            continue;
        }
        
        uint64_t lgn = lng;
        v.clear();
        int y = 0, z = 0;
        for (int j = 25 ; j > 0 ; j--) {
            uint64_t t_ = lng;
            while (lng > 0) {
                v.insert(v.begin(), (unsigned char)(lng) % 256);
                lng >>= 8;
            }
            for (unsigned char c : v) {
                lng <<= 8;
                lng += (unsigned int)c;
            }
            if (t_ != lng) {
                lng = t_;
                v.clear();
                continue;
            }
            lng = t - (n * (lgn / pow(10,j)));
            while (lng > 0) {
                v.insert(v.begin(), (unsigned char)(lng) % 256);
                lng >>= 8;
            }
        // just taking j now ->* what is i and j?
        // I have the number of i, I just don't need it :)
            //cout << j << " " << flush;
            v.insert(v.begin(), (unsigned char)(j));
            v.push_back('S');
            // catch the best we can :)
            if (w.length() == 0 || w.length() > v.length()) {
                w = v;
            }
            if (w.length() <= 5)
                return w;
            v.clear();
        }
    }
    if (w.length() == 0) {
        long double e_ = epiphany;
        uint64_t epic_ = e_;
        
        v.push_back('?');
        
        while (epic_ > 0) {
            v.insert(v.begin(), (unsigned char)(epic_) % 256);
            epic_ >>= 8;
        }
        for (unsigned char c : v) {
            lng <<= 8;
            lng += (unsigned int)c;
        }
        if (epiphany != lng)
            cout << ".";
        return v;
    }
    return w;
    
// We are returning `v` or `w` which is the formatted
// percentage, and the number of bits taken to
// get it all in there.
}

string uncompress(string v)
{
    int j = 0, i = (int)v.back();
    int64_t x = 0;
    for (int c : v)
    {
        x <<= 8;
        x += c;
    }

    return pop_off(round(pow64.to_ullong() * (x / pow(10, i + 2))));
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t b)
{
    string y = "";
    int i = 8;

    while (i > 0 && end_file_len > 0)
    {
        bitset<8> a = b;
        b >>= 8;
        y.push_back((char)a.to_ulong());
        end_file_len--;
        i--;
    }
    string x = "";
    for (; y.length() > 0;)
    {
        x.push_back(y.back());
        y.pop_back();
    }
    return x;
}

vector<string> compress(vector<string> t)
{

    int i = 0, z = 0;

    // We're looping through each segment
    // Moving with t[i] (i++ at the bottom)
    int j = 0;
    uint64_t inv_total;
    string m = "";
    // This is to make the loop for
    // continuous zipping; opt @cmdline argv[3]
    vector<string> s = {};
    while (t.size() > i)
    {
        // tv is the current segment
        string tv = t[i];

        uint64_t epiphany = 0;
        while (tv.length() > 0)
        {
            z = 0;

            // exciting is the 64 bit 8 byte
            // value of the sequences as they
            // are read in to the compressor
            uint64_t exciting = 0;

            // Let's go thru each char, sequencing 8 bytes
            // end to end. We'll
            // use this to compress with.
            for (unsigned int a : tv)
            {
                // Obvious, I think
                exciting <<= 4;
                exciting += a;
                z++;
                // 8 byte limit
                if (z == 8)
                    break;
            }

            // Shed the last ? bytes substr(?,->)
            if (z < tv.length())
                tv = tv.substr(z, tv.length() - 1);
            else
                tv.clear();

            inv_total = exciting;

            int y = 0;
            if (inv_total == 0)
                m += "JJM";
            else
                m += sepFix(inv_total);

            inv_total = 0;

            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (m.length() > 48000)
            {
                s.push_back(m);
                m.clear();
            }
        }
        i++;
    }
    m += sepFix(inv_total);
    s.push_back(m);
    m.clear();

    return s;
}

std::vector<std::string> DIFSplitStringByNumber(const std::string & str, int len)
{
    std::vector<std::string> entries;
    for(std::string::const_iterator it(str.begin()); it != str.end();)
    {
        int nbChar = std::min(len,(int)std::distance(it,str.end()));
        entries.push_back(std::string(it,it+nbChar));
        it=it+nbChar;
    };
    return entries;
}

int main(int argc, char* argv[])
{

    long int zips = 0;
    if (argc < 5)
    {
        cout << "* You may add a 3rd argument to zip multiple times";
        cout << "\n* " << argv[0] << " -(c|d) <file_to_zip> <output> <integer>";
        cout << "\n* Defaulting to: 3\n";
        zips = 3;
    }
    else
    {
        zips = strtol(argv[4], NULL, 10);
    }

    auto start = std::chrono::system_clock::now();
    // Start Timer
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << std::ctime(&start_time) << flush;

    // Input/Output
    ifstream ifo(argv[2], std::ios_base::in | std::ios_base::binary);
    ofstream ofo(argv[3], std::ios_base::out | std::ios_base::binary);

    // Create Buffer
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");

    // File length
    double file_len = gs.length();

    if (0 == strcmp(argv[1], "-c"))
    {
        ofo << "[" << std::hex << gs.length() << "]";
        // All of file in segments
        vector<string> t{};
        int y = 0;
        // Segment size
        int bytes = 48000;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
        t = DIFSplitStringByNumber(gs,bytes);
        /*
        while ((y * bytes) + bytes < gs.length())
        {
            t.push_back(gs.substr((y * bytes) + bytes, bytes));
            if (t.size() % bytes == 0)
            {
                cout << ". " << flush;
            }
            y++;
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(y * bytes, gs.length() - 1));
        */
        gs.clear();
        // File is loaded
        cout << ".." << flush;
        while (zips > 0)
        {
            // Use epic() to compress
            t = compress(t);
            t.push_back("XIV#");
            zips--;
            long double w = 0;
            for (string i : t)
                w += i.length();
            cout << round((w / file_len) * 100) << "% " << flush;
        }

        // Entropy of Compress output
        set<string> n = {};
        int i = 0;
        for (string c : t)
        {

            string tiptum = "";
            for (unsigned char r : c)
            {
                b.insert(r);
                ofo << r;
            }

            i = 0;
            
        }
        cout << n.size() << " ";
    }
    else if (0 == strcmp(argv[1], "-d"))
    {
        int bytes = file_len;
        vector<string> t = {};
        int y = 0;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
        int i = 0;
        string out_size_h = "";
        do
        {
            i++;
            out_size_h.push_back(gs[i]);
        } while (gs[i + 1] != ']');
        cout << out_size_h << " " << flush;
        end_file_len = strtol(out_size_h.c_str(), NULL, 16);
        gs.erase(gs.begin(), gs.begin() + i + 2);
        cout << end_file_len << flush;
        while ((y * bytes) + bytes < gs.length())
        {
            t.push_back(gs.substr((y * bytes) + bytes, bytes));
            if (t.size() % bytes == 0)
            {
                cout << ". " << flush;
            }
            t.push_back(gs);
            gs.clear();
            y++;
        }
        // Get last of the file
        if (gs.length() > 0)
            t.push_back(gs.substr(y * bytes, gs.length() - 1));
        gs.clear();
        y = 0;
        string g = "", JJM_spaces = "";
        bitset<24> buckets = 0;
        for (string j : t)
        {
            for (int h = 0; h < j.length(); h++)
            {
                y++;
                JJM_spaces.push_back((char)j[h]);
                if ("JJM" == JJM_spaces)
                {
                    for (int i = 0; i < 8; i++)
                        ofo << ' ';
                    buckets = 0;
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 4 && j[h + 1] != '[')
                {
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 4)
                {
                    for (; h < j.length();)
                    {
                        JJM_spaces.push_back(j[h]);
                        h++;
                        if (j[h - 1] == ']')
                            break;
                    }
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
            }
        }
    }
    cout << " " << b.size() << "b";
    // output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
