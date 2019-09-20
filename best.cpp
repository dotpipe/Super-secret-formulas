// g++ -o comptest.exe -m64 -Ofast -std=c++17 best.cpp

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

string brf(uint64_t, long double);
vector<string> compress(vector<string>);
string uncompress(uint32_t);
string pop_off(uint64_t);
string sepFix(unsigned long long int epiphany);
string stressTest(uint64_t, uint8_t nmrk, string zip, long double mnk);

uint64_t end_file_len = 0;
set<unsigned long long int> b = {};

string sepFix(unsigned long long int epiphany)
{
    string v = brf(epiphany, 0);
    return v;
}

// Best nth root finder (input, base, exponent)
string brf(uint64_t n1, long double n2 = 3)
{
    long double n3 = 0, nmrk = 0, n4 = 0, n5 = 0, n6 = 0;
    long double mk = 0, tptm = 0, mnk = 0, dad = 0;
    // Using nmrk to show how many times we looped,
    // we can eliminate the train of decimals, with
    // a small integer. This, because its just like x*nmrk.
    for (n3 = 0; tptm != n1 || mnk > 256 ; nmrk++) {
    // having all 5 decimals lets the computer run more
    // balanced between math and logic.
        n4 += 0.19625;
        n2 += 0.15625;
        n3 += 0.015625;
        mk += 0.0073125;
        dad += 0.00390625;
        n5 += 0.001953125;
    // mnk is needed t be the nth root
        mnk = pow(n1, 1.0/(n4+n2+mk+n3+dad+n5));
    // this verifies we have the root. 
        tptm = pow(mnk, (n4+n2+mk+n3+dad+n5));
    }
    string zip = "";
    uint64_t z = (tptm);
    
    bitset<64> y = mnk*100000000; //  mnk (nth root)
    // Split up the gce[2] variable because its a 2 decimal double
    uint64_t x = y.to_ullong();
    if (n1 == 0)
        return "JJM";   
    //cout << x << " " << endl << flush;
    // record into zip string
    while (y.to_ullong() > 0) {
        zip.push_back((char)(y.to_ullong()%256));
        y >>= 8;
    }
    cout << zip.size() << "&" << endl;
    // this checks out to make sure we have
    // all the data coming back
    zip = stressTest(n1, nmrk, zip, mnk);
    return zip;

}

// You will be basing the decompression upon
// this function, stressTest(). It checks that
// we're getting the right data and and having
// enough bread crumbs to the answer.

string stressTest(uint64_t t, uint8_t nmrk, string zip, long double mnk)
{
    double n_2 = 0, exponent = 0;
    long double n3 = 0, mk = 0, dad = 0, n4 = 0, n5 = 0, n2 = 0, n1 = 0;
    uint64_t n_1 = 0, hi = 0;
    long double base = 0, inc = 0, tptm = 0;
    int f = 0;
// This is nmrk (f)
// nmrk is most often a 21 or 22
// so below we use percents for the
// difference (yay!)
    while (22 > f) {
    // having all 5 decimals lets the computer run more
    // balanced between math and logic.
        n4 += 0.19625;
        n2 += 0.15625;
        n3 += 0.015625;
        mk += 0.0073125;
        dad += 0.00390625;
        n5 += 0.001953125;
        f++;
    }
// This will be the final whole number
    for (int i = 0 ; i < zip.length() ; i++) {
        n_1 <<= 8;
        n_1 += zip[zip.length()-1-i];
        base = n_1;
    }
    n_2 = base;
    hi = round(n_2);
    n_2 = (long double)hi;
    mnk;
// this is going back to equivalence with mnk
// (the root base)
    tptm = n_2 / 100000000;
    //cout << tptm << " " << mnk << endl << flush;
// Here we're just getting the percent
// difference between the whole number
// t, and the number we got through
// saving the information. (scary)
    unsigned long long int t2 = 0;
    //t2 = t2 - t;
    long double percent_of = ((long double)tptm/mnk);
    long double final_perc = (percent_of+tptm);
    uint64_t copy_perc = final_perc * 10000;
    cout << final_perc << " " << endl;
    while (copy_perc > 0) {
        zip += (copy_perc%256);
        copy_perc >>= 8;
    }
    t2 = pow((tptm),(n4+n2+mk+dad+n5));
    copy_perc = final_perc;
    final_perc = (double)(t2 / (final_perc/10000));
    if (final_perc < 1)
        cout << (double)(percent_of) << "#";
    uint64_t t3 = (final_perc);
    if (t3 == t || t-t3 == 0 || t == 0 || t-t3-1 == 0 || t-t3+1 == 0)
    {}    //cout << "@" << flush;
    else {
        cout << t3 << " " << t << endl << flush;
    }
    //else if (t != 0) {
     //   cout << setprecision(25) << t-(uint64_t)(t2*final_perc) << " " << t << endl << flush;
     //   copy_perc = final_perc;
        //cout << (double)t-(double)(t2*final_perc)+t2 << endl;
// Save a little space by offsetting what
// we're getting at a time. 5 bytes each
// unless that with a '$' at the end.
 
    if (t == 0)
        zip = "%!"; 
    else if (t - t3 - 1 == 0) {
        zip += '$';
    }
    else if (t - t3 + 1 == 0) {
        zip += '@';
    }
    else if (zip.length() == 6) {
        zip += '#';
    }
    //cout << zip.length();
    return zip;

}


string uncompress(string zip)
{
    long double n_2 = 2, exponent = 0, hi = 0;
    long double n3 = 0, mk = 0, dad = 0, n4 = 0, n2 = 0;
    uint64_t n_1 = 0;
    uint64_t base = 0, inc = 0;
    int f = 0;
// This is nmrk (f)
    while ((int)zip[0] > f++) {
        n4 += 0.19625;
        n2 += 0.15625;
        n3 += 0.015625;
        mk += 0.0073125;
        dad += 0.00390625;
    }
// This will be the final whole number
    base = zip[1];
    base <<= 8;
    base += zip[2];
    base <<= 8;
    base += zip[3];
    n_2 = base;
    hi = n_2 / 100;
// This is the difference from what was input
// And what our nth root produced (generally 0)

    if (zip.length() > 4 && zip[4] == '[' && zip[zip.length()-1] == ']') {
        for (int i = 5 ; i < zip.length()-1 ; i++) {
            inc <<= 8;
            inc += zip[i];
        }
    }
    
    n_1 = pow(hi, (n4+n2+mk+n3+dad));

    return pop_off(n_1);
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
    for ( ; y.length() > 0 ; ) {
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
                m += "JJM";
            else
                m += sepFix(inv_total);
                
            inv_total = 0;
            
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
        ofo << "[" << std::hex << gs.length() << "]";
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
        int i = 0;
        string out_size_h = "";
        do {
            i++;
            out_size_h.push_back(gs[i]);
        } while (gs[i+1] != ']');
        cout << out_size_h << " " << flush;
        end_file_len = strtol(out_size_h.c_str(),NULL,16);
        gs.erase(gs.begin(),gs.begin()+i+2);
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
            for (int h = 0 ; h < j.length() ; h++)
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
                else if (JJM_spaces.length() == 4 && j[h+1] != '[')
                {
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
                else if (JJM_spaces.length() == 4)
                {
                    for ( ; h < j.length() ; )
                    {
                        JJM_spaces.push_back(j[h]);
                        h++;
                        if (j[h-1] == ']')
                            break;
                    }
                    ofo << uncompress(JJM_spaces);
                    JJM_spaces.clear();
                }
            }
        }
    }
    cout << " " << b.size() << "b";
    //output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}