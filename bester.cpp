// g++ -o comptesvect_tbl_of_file.exe -m64 -Ofast -std=c++17 bester.cpp

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
#include <stdlib.h>

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
    string str_of_ints = "", w = "";
    long double total_of_ints = epiphany;
    uint64_t n = (long double)(pow64.to_ullong());
    long double epic = total_of_ints;
    uint64_t lng = 0;

    for (int i = 25; i > 0; i--)
    {
        // get percent of proximity to 2^64
        epic = total_of_ints / n * pow(10, i);
        // have epic in int and double for
        // bitwise and division
        lng = epic;
        epic = lng;
        // log percent
        while (lng > 0)
        {
            str_of_ints.insert(str_of_ints.begin(), (unsigned char)(lng) % 256);
            lng >>= 8;
        }
        // double check log
        for (int c = 0; c < str_of_ints.length(); c++)
        {
            lng <<= 8;
            lng += (unsigned int)str_of_ints[c];
        }
        // if its wrong, start over
        // continue statement moves ua along
        if ((long double)lng != epic)
        {
            str_of_ints.clear();
            continue;
        }
        // bb = deepest decimal
        int bb = 15;
        epic = lng;
        // how close can we get to 0 difference
        // between actual and logged proximity
        // percentage
        while (total_of_ints - (n * (epic / pow(10, bb))) > 10 && bb-- > 0)
            ;
        // record to file, eliminate doubts we have
        // incorrect data
        if (total_of_ints - (n * (epic / pow(10, bb))) <= 10 && str_of_ints.length() < 5)
        {
            uint8_t tmp_total = total_of_ints - (n * (epic / pow(10, bb)));
            str_of_ints.insert(str_of_ints.begin(), (unsigned char)(tmp_total));
            if (str_of_ints[0] != tmp_total)
                cout << tmp_total - (unsigned int)str_of_ints[0] << flush;
            str_of_ints.insert(str_of_ints.begin(), (unsigned char)(bb));
            if (str_of_ints[0] != bb)
                cout << tmp_total - (unsigned int)str_of_ints[0] << flush;
            str_of_ints.insert(str_of_ints.begin(), (unsigned char)('%'));
            return str_of_ints;
        }
        
        if (str_of_ints.length() < w.length() || w.length() == 0)
            w = str_of_ints;
        str_of_ints.clear();
        if (i == 1)
            return w;
        // continue if we passed by the `i`th decimal
        // and couldn't find a suitable number
        // SO! We try to get something closer.
    }

    // If we did not find anything, we can just record it here
    // This is the bulkiest part of the compression, and is
    // used as a last resorvect_tbl_of_file.
    long double e_ = epiphany;
    uint64_t epic_ = e_;

    str_of_ints.push_back('?');
    str_of_ints.push_back('?');

    while (epic_ > 0)
    {
        str_of_ints.insert(str_of_ints.begin(), (unsigned char)(epic_) % 256);
        epic_ >>= 8;
    }
    for (unsigned char c : str_of_ints)
    {
        lng <<= 8;
        lng += (unsigned int)c;
    }
    // output if error in log
    if (epiphany != lng)
        cout << ".";

    return str_of_ints;

    // We are returning `v` or `w` which is the formatted
    // percentage, and the number of bits taken to
    // get it all in there.
}

string uncompress(string str_of_ints)
{

    int dec = str_of_ints[0];
    int offset = str_of_ints[1];

    int64_t x = 0;

    for (int c = 3; c < str_of_ints.length(); c++)
    {
        x <<= 8;
        x += (unsigned int)str_of_ints[c];
    }

    return pop_off(round(pow64.to_ullong() * (x / pow(10, dec))) + offset);
}

// Split 64 bits, into 8 bytes
// from uncompress()
string pop_off(uint64_t recovered_int)
{
    string y = "";
    int i = 8;

    while (i > 0 && end_file_len > 0)
    {
        bitset<8> a = recovered_int;
        recovered_int >>= 8;
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

vector<string> compress(vector<string> vect_tbl_of_file)
{

    int i = 0, int_cntr = 0;

    // We're looping through each segment
    // Moving with t[i] (i++ at the bottom)
    int j = 0;
    uint64_t inv_total = 0;
    string enc_str = "";
    // This is to make the loop for
    // continuous zipping; opt @cmdline argv[3]
    vector<string> s = {};
    while (vect_tbl_of_file.size() > i)
    {
        // tv is the current segment
        string str_of_ints = vect_tbl_of_file[i];

        uint64_t epiphany = 0;
        while (str_of_ints.length() > 0)
        {
            int_cntr = 0;

            // exciting is the 64 bit 8 byte
            // value of the sequences as they
            // are read in to the compressor
            uint64_t exciting = 0;

            // Let's go thru each char, sequencing 8 bytes
            // end to end. We'll
            // use this to compress with.
            for (unsigned int a : str_of_ints)
            {
                // Obvious, I think
                inv_total <<= 8;
                inv_total += a;
                int_cntr++;
                // 8 byte limit
                if (int_cntr == 8)
                    break;
            }

            // Shed the last ? bytes substr(?,->)
            if (int_cntr < str_of_ints.length())
                str_of_ints = str_of_ints.substr(int_cntr, str_of_ints.length() - 1);
            else
                str_of_ints.clear();

            int y = 0;
            if (inv_total == 0)
                enc_str += "JJM%";
            else
                enc_str += compRoutine(inv_total);

            inv_total = 0;

            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (enc_str.length() > 48000)
            {
                s.push_back(enc_str);
                file_len += enc_str.length();
                enc_str.clear();
            }
        }
        i++;
    }
    if (inv_total != 0)
    {
        enc_str += compRoutine(inv_total);
        s.push_back(enc_str);
        file_len += enc_str.length();
        enc_str.clear();
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

    short int zips = 0;
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
    string file_data_string = ifos.str();
    ifos.str("");

    // File length
    const double file_len = file_data_string.length();

    if (0 == strcmp(argv[1], "-c"))
    {
        // All of file in segments
        vector<string> vect_tbl_of_file{};
        int y = 0;
        // Segment size
        int bytes = 48000;
        if (bytes < 48000)
            bytes = file_len;
        // Segments are made to make reading the file in
        // much easier, and faster. We're only concentrating
        // on the little of the file at once.
        // Take to making segments
        vect_tbl_of_file = DIFSplitStringByNumber(file_data_string, bytes);
        file_data_string.clear();
        // File is loaded
        cout << ".." << flush;
        long double file_size = file_len;
        while (zips > 0)
        {
            // Use compress() to compress
            // record file_len in hex
            vect_tbl_of_file = compress(vect_tbl_of_file);

            string len_tmp = to_string(file_size);
            // Insert zip mark and file size
            vect_tbl_of_file = compress(vect_tbl_of_file);
            vect_tbl_of_file.insert(vect_tbl_of_file.begin(), "]");
            vect_tbl_of_file.insert(vect_tbl_of_file.begin(), std::to_string(std::stoul(len_tmp, nullptr, 16)));
            vect_tbl_of_file.insert(vect_tbl_of_file.begin(), "[");
            vect_tbl_of_file.insert(vect_tbl_of_file.begin(), "RXIVE");
            // draw segment line
            vect_tbl_of_file.push_back("XIV#");
            // approach 0 zip calls left to do
            zips--;
            file_size = 0;
            // total percent of original file size
            for (string i : vect_tbl_of_file)
                file_size += i.length();
            cout << round((file_size / file_len) * 100) << "% " << flush;
        }

        // Entropy of Compress output
        set<string> unique_chars = {};
        int i = 0;
        for (string c : vect_tbl_of_file)
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
        cout << unique_chars.size() << " ";
    }
    else if (0 == strcmp(argv[1], "-d"))
    {
        while (file_data_string.substr(0, 5) == "RXIVE")
        {
            file_data_string.erase(file_data_string.begin(), file_data_string.begin() + 5);
            int bytes = file_len;
            vector<string> total_of_ints = {};
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
                out_size_h.push_back(file_data_string[i]);
            } while (file_data_string[i + 1] != ']');

            // Decode file size
            end_file_len = strtol(out_size_h.c_str(), NULL, 16);
            file_data_string.erase(file_data_string.begin(), file_data_string.begin() + i + 2);
            cout << end_file_len << flush;
            file_data_string.clear();

            // Split file into original segments
            split4<vector<string>>(file_data_string, total_of_ints, "XIV#");
            vector<string> split_of_segments = {};
            // split into further segments to easily
            // give over to uncompress() and pop_off()
            for (string a : total_of_ints)
            {
                split4<vector<string>>(a, split_of_segments, "%");
            }
            string g = "", JJM_spaces = "";

            // Deconstruct file to decompress
            for (string j : split_of_segments)
            {

                if (string::npos != j.find("??"))
                {
                    vector<string> hj_split = {};
                    string delim = "??";
                    split4<vector<string>>(j, hj_split, delim);
                    j.clear();
                    regex const expression("[^??]+");
                    std::string const text(j);

                    std::ptrdiff_t const match_count(std::distance(
                        std::sregex_iterator(text.begin(), text.end(), expression),
                        std::sregex_iterator()));
                    file_data_string += uncompress(hj_split[0]);
                    for (int i = 1; i < hj_split.size(); i++)
                        file_data_string += pop_off(strtoull(hj_split[i].c_str(), NULL, 256));
                }
                else
                    file_data_string += uncompress(j);
            }
        }
        ofo << file_data_string;
    }
    cout << " " << b.size() << "b";
    // output last of file
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
