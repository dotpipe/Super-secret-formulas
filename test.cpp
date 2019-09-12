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

string epic(long long int epiphany);

string epic(long long int epiphany) {

    string v = "";
    // Inversion
    uint64_t fh = 0;
    
    fh = pow(2,64) - epiphany;
    //create string
    while (fh > 0) {
        v.push_back((unsigned char)fh);
        fh >>= 8;
    }

    return v;
}

int main(int c, char * argv[]) {
    
    auto start = std::chrono::system_clock::now();
    // Start Timer
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << std::ctime(&start_time) << flush;
    
    // Input/Output
    ifstream ifo (argv[1], std::ios_base::in | std::ios_base::binary);
    ofstream ofo ("test.txt", std::ios_base::out | std::ios_base::binary);
    
    // Create Buffer
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    
    // File length
    double file_len = gs.length();
    
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
        t.push_back(gs.substr((y*bytes),bytes));
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
    int i = 0, z = 0;
    
    // Entropy of Compress output
    set<int> n = {};
    // We're looping through each segment
    // Moving with t[i] (i++ at the bottom)
    while (t.size() > i) {
        // tv is the current segment
        string tv = t[i];
        // `j` tells us what generation of
        // inversion we're on. We turn them
        // all into a large 64 bit numbre (3 8bytes/64bits)
        int j = 0;
        // epitome is the second generation of
        // the 3 generations that go into the 64 bits
        // Readers Note: we're using inversion
        //          x = pow(2,64) - epitome
        // for instance, macompplished is the 3rd
        uint64_t epitome = 0, maccomplished = 0;
        while (tv.length() > 0) {
            z = 0;
            
            // epiphany is the first generation
            // it takes the value of exciting
            long long int epiphany = 0, exciting = 0;
            
            // Let's go thur each character in a 8 byte
            // sequence and put them end to end. We'll
            // use this to compress with. but Inversion, later
            // readies the task so much further.
            for (unsigned char a : tv) {
            // If we go over 64 bits, this will tell us
                if ((epiphany << 8) + (int)a >= pow(2,63) + (int)a) {
                    cout << "?" << flush;
                }
            // NOTE we are not inverting the byte itself
            // too confusing I think.
                unsigned int h = a;
                
                // Obvious, I think
                exciting <<= 8;
                exciting += h;
                z++;
                // Kick out every 8 bytes
                if (z == 8)
                    break;
            }
            
            // Shed the last 8 bytes
            if (z < tv.length())
                tv = tv.substr(z,tv.length()-1);
            else tv.clear();
            
            // move to epiphany
            epiphany = exciting;
            
            // This is for outputting the file
            // to `ofo` (output file object)
            string m = "";
            
            // generation counter
            j++;
            
            /// Invert the 3 generations
            uint64_t inv_total = (pow(2,64) - epiphany);
            inv_total <<= 6;
            inv_total += (pow(2,64) - epitome);
            inv_total <<= 6;
            inv_total += (pow(2,64) - maccomplished);
            
            // if generation 3, and I haven't
            // blown the top off the 64 bit limit
            // then make the complete the compression
            // with epic.
            if (j%3 == 0 && inv_total < pow(2,64)) {
                m = epic(inv_total);
                epiphany = 0;
                maccomplished = 0;
                exciting = 0;
            }
            // if I did go over the 64 mark,
            // then there won't be 8 bits between
            // each byte, So I get to know that.
            else if (j%3 == 0) {
                m = epic(epitome);
                m += epic(exciting);
                m += epic(maccomplished);
                epitome = 0;
                maccomplished = 0;
                exciting = 0;
            }
            // Generation prelate
            else {
                maccomplished = epitome;
                epitome = exciting;
                exciting = 0;
            }
            // Write to file
            // & get output entropy inserts
            if (m.length() > 0) {
                for (int r : m)
                    n.insert(r);
                ofo << m;
                m.clear();
            }
        }
        i++;
    }
    cout << n.size() << " " << flush;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}