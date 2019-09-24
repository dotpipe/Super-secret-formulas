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
#include <iterator>
#include <regex>

using namespace std;

vector<string> compress(vector<string>);
string uncompress(string v);
string pop_off(uint64_t);
string compRoutine(long double epiphany);
std::vector<std::string> DIFSplitStringByNumber(const std::string &str, int len);

uint64_t end_file_len = 0;
set<char> b = {};
const bitset<64> pow64 = -1;
double file_len = 0;

// fast template to split up zips into their
// segments
template <class Container>
void split4(const std::string &str, Container &cont,
            const std::string &delims = " ")
{
    std::size_t current, previous = 0;
    current = str.find_first_of(delims);
    while (current != std::string::npos)
    {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}

// Epiphany is a multichar (upto 8 byte) number
// that was created with a
// for (int char : ) 
//      += (int)char;
//      >>= 8;

// loop. so we want to bring this number back.

string compRoutine(uint64_t epiphany)
{
    string v = "", w = "";
    long double t = epiphany;
    uint64_t n = (long double)(pow64.to_ullong()); /// epic);
    long double epic = t;                          // pow64.to_ulong()/n; //abs(round(pow64.to_ullong() * (n)));
    uint64_t lng = 0;

    for (int i = 25; i > 0; i--)
    {
        // get percent of proximity to 2^64
        epic = t / n * pow(10, i);
        // have epic in int and double for
        // bitwise and division
        lng = epic;
        epic = lng;
        // log percent
        while (lng > 0)
        {
            v.insert(v.begin(), (unsigned char)(lng) % 256);
            lng >>= 8;
        }
        // double check log
        for (int c = 0; c < v.length(); c++)
        {
            lng <<= 8;
            lng += (unsigned int)v[c];
        }
        // if its wrong, start over
        // continue statement moves ua along
        if ((long double)lng != epic)
        {
            v.clear();
            continue;
        }
        // bb = deepest decimal
        int bb = 15;
        epic = lng;
        // how close can we get to 0 difference
        // between actual and logged proximity
        // percentage
        while (t - (n * (epic / pow(10, bb))) > 10 && bb-- > 0)
            ;
        // record to file, eliminate doubts we have
        // incorrect data
        if (t - (n * (epic / pow(10, bb))) <= 10 && v.length() < 5)
        {
            uint8_t c = t - (n * (epic / pow(10, bb)));
            v.insert(v.begin(), (unsigned char)(c));
            if (v[0] != c)
                cout << c - (unsigned int)v[0] << flush;
            v.insert(v.begin(), (unsigned char)(bb));
            if (v[0] != bb)
                cout << c - (unsigned int)v[0] << flush;
            v.insert(v.begin(), (unsigned char)('%'));
            return v;
        }
        if (v.length() < w.length() || w.length() == 0)
            w = v;
        v.clear();
        // continue if we passed by the `i`th decimal
        // and couldn't find a suitable number
        // SO! We try to get something closer.
    }

    // If we did not find anything, we can just record it here
    // This is the bulkiest part of the compression, and is
    // used as a last resort.
    long double e_ = epiphany;
    uint64_t epic_ = e_;

    v.push_back('?');
    v.push_back('?');

    while (epic_ > 0)
    {
        v.insert(v.begin(), (unsigned char)(epic_) % 256);
        epic_ >>= 8;
    }
    for (unsigned char c : v)
    {
        lng <<= 8;
        lng += (unsigned int)c;
    }
    // output if error in log
    if (epiphany != lng)
        cout << ".";

    return v;

    // We are returning `v` or `w` which is the formatted
    // percentage, and the number of bits taken to
    // get it all in there.
}

string uncompress(string v)
{

    int dec = v[0];
    int offset = v[1];

    int64_t x = 0;

    for (int c = 3; c < v.length(); c++)
    {
        x <<= 8;
        x += (unsigned int)v[c];
    }

    return pop_off(round(pow64.to_ullong() * (x / pow(10, dec))) + offset);
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
                exciting <<= 8;
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
                m += "JJM%";
            else
                m += compRoutine(inv_total);

            inv_total = 0;

            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (m.length() > 48000)
            {
                s.push_back(m);
                file_len += m.length();
                m.clear();
            }
        }
        i++;
    }
    if (inv_total != 0)
    {
        m += compRoutine(inv_total);
        s.push_back(m);
        file_len += m.length();
        m.clear();
    }

    return s;
}

// Quick function to split up file by length
std::vector<std::string> DIFSplitStringByNumber(const std::string &str, int len)
{
    std::vector<std::string> entries;
    for (std::string::const_iterator it(str.begin()); it != str.end();)
    {
        int nbChar = std::min(len, (int)std::distance(it, str.end()));
        entries.push_back(std::string(it, it + nbChar));
        it = it + nbChar;
    };
    return entries;
}

int main(int argc, char *argv[])
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
    const double file_len = gs.length();

    if (0 == strcmp(argv[1], "-c"))
    {
        // All of file in segments
        vector<string> t{};
        int y = 0;
        // Segment size
        int bytes = 48000;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
        t = DIFSplitStringByNumber(gs, bytes);
        gs.clear();
        // File is loaded
        cout << ".." << flush;
        long double file_size = file_len;
        while (zips > 0)
        {
            // Use compress() to compress
            stringstream f;
            // record file_len in hex
            f << "[" << std::hex << file_size << "]";
            // Insert zip mark and file size
            t = compress(t);
            t.insert(t.begin(), f.str());
            t.insert(t.begin(), "RXIVE");
            // draw segment line
            t.push_back("XIV#");
            // approach 0 zip calls left to do
            zips--;
            file_size = 0;
            // total percent of original file size
            for (string i : t)
                file_size += i.length();
            cout << round((file_size / file_len) * 100) << "% " << flush;
        }

        // Entropy of Compress output
        set<string> n = {};
        int i = 0;
        for (string c : t)
        {
            // How many unique characters
            // are in the output

            // cousin's name, here for reference :)
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
        while (gs.substr(0, 5) == "RXIVE")
        {
            gs.erase(gs.begin(), gs.begin() + 5);
            int bytes = file_len;
            vector<string> t = {};
            int y = 0;
            // Segments are made to make reading the file in
            // much easier, and faster. We're only concentrating
            // on the little of the file at once.
            // Take to making segments
            int i = 0;
            string out_size_h = "";

            // Read in original filesize
            do
            {
                i++;
                out_size_h.push_back(gs[i]);
            } while (gs[i + 1] != ']');

            // Decode file size
            end_file_len = strtol(out_size_h.c_str(), NULL, 16);
            gs.erase(gs.begin(), gs.begin() + i + 2);
            cout << end_file_len << flush;
            gs.clear();

            // Split file into original segments
            split4<vector<string>>(gs, t, "XIV#");
            vector<string> d = {};
            // split into further segments to easily
            // give over to uncompress() and pop_off()
            for (string a : t)
            {
                split4<vector<string>>(a, d, "%");
            }
            string g = "", JJM_spaces = "";

            // Deconstruct file to decompress
            for (string j : d)
            {
            
                if (string::npos != j.find("??"))
                {
                    vector<string> hjsplit = {};
                    string delim = "??";
                    split4<vector<string>>(j,hjsplit,delim);
                    j.clear();
                    regex  const expression("[^??]+");
                    std::string const text(j);
                    
                    std::ptrdiff_t const match_count(std::distance(
                        std::sregex_iterator(text.begin(), text.end(), expression),
                        std::sregex_iterator()));
                    gs += uncompress(hjsplit[0]);
                    for (int i = 1 ; i < hjsplit.size() ; i++)
                        gs += pop_off(strtoull(hjsplit[i].c_str(),NULL,256));
                }
                else
                    gs += uncompress(j);
            }
        }
        ofo << gs;
    }
    cout << " " << b.size() << "b";
    // output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
