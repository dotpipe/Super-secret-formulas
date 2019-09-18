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

tuple<uint64_t, uint64_t, long double> brf(uint64_t, long double);
vector<string> compress(vector<string>);
string uncompress(uint32_t);
string pop_off(uint64_t);
string sepFix(unsigned long long int epiphany);

string sepFix(unsigned long long int epiphany)
{
    tuple<uint8_t, uint64_t, long double> gce = make_tuple(0, 0, 0);
    string v = "";
    //while (epiphany > 0)
    {
        gce = brf(epiphany, 2);
        v.push_back((char)get<0>(gce));
        double x = get<2>(gce)*10;
        uint16_t y = round(x);
        y >>= 8;
        v.push_back((char)y%256);
        cout << " " << get<2>(gce);
        uint64_t f = (uint64_t)get<1>(gce);
        if ((f) > 0) {
            v.push_back('[');
            while (f > 0) {
                v.push_back((char)f%256);
                f >>= 8;
            }
            v.push_back(']');
        }
        return v;
    }
}
// Best nth root finder (input, base, exponent)
tuple<uint64_t, uint64_t, long double> brf(uint64_t n1, long double n2 = 3)
{
    long double n3 = 0, nmrk = 0;
    while (n2 <= 64)
    {
        long double mk = 0, tptm = 0, mnk = 0, x = 0, dad = 0;
        for (n3 = 0; tptm != n1 || mnk > 6250 ; nmrk++) {
            n3 += 0.015625;
            mk += 0.0073125;
            dad += 0.00390625;
            mnk = pow(n1, 1.0/(mk+n3+dad));
            tptm = pow((mnk), (mk+n3+dad));
        }
        if (tptm - n1 == 0)
        {
            uint64_t y = (tptm);
            return make_tuple(nmrk, 0, (mnk));
        }
        
    }
    return make_tuple(0, 0, 0);
}

// TODO: REDO
string uncompress(string zip)
{
    uint64_t inc = 0, exponent = 0, base = 0;
    long double n_1 = 0, n3 = 0, md = 0, sa = 0;
    int f = zip[0];
    while (f > 0) {
        n3 += 0.015625;
        md += 0.0073125;
        sa += 0.00390625;
        f--;
    }
    n_1 = 0;
    base = zip[2];
    base <<= (zip[1] << 8);
    base /= 10;
    base += 0.05;
    if (zip.length() > 3 && zip[2] == '[' && zip[zip.length()-1] == ']') {
        for (int i = 4 ; i < zip.length()-1 ; i++) {
            inc <<= 8;
            inc += zip[i];
        }
    }
    n_1 = pow(base, (n3+md+sa)) + inc;
    return pop_off(n_1);
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t b)
{
    string y = "";
    int i = 0;
    while (i++ < 8)
    {
        int a = (b % 256);
        unsigned char x = a;
        y.push_back(x);
        b >>= 8;
    }
    return y;
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
                exciting += a + 1;
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

            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (m.length() > 8000)
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
    double file_len = gs.length();

    if (0 == strcmp(argv[1], "-c"))
    {
        // All of file in segments
        vector<string> t{};
        int y = 0;
        //Segment size
        int bytes = 16000;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
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
        gs.clear();
        // File is loaded
        cout << ".." << flush;
        while (zips > 0)
        {
            // Use epic() to compress
            t = compress(t);
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
            for (int r : c)
            {
                i++;
                //if (i > 0)
                { 
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
    else if (0 == strcmp(argv[1], "-d"))
    {
        int bytes = file_len;
        vector<string> t = {};
        int y = 0;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
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
            for (int h = 0 ; h < j.length() ; h++)
            {
                buckets <<= 8;
                buckets = buckets.to_ulong() + j[h];
                y++;
                JJM_spaces.push_back((char)j[h]);
                if ("JJM" == JJM_spaces)
                {
                    for (int i = 0; i < 8; i++)
                        ofo << ' ';
                    buckets = 0;
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 3 && j[h+1] != '[')
                {
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 3)
                {
                    for ( ; h < j.length() ; )
                    {
                        JJM_spaces.push_back(j[h]);
                        h++;
                        if (j[h] == ']')
                            break;
                    }   
                }
            }
        }
    }
    //output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}