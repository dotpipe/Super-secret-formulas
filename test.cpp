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
using namespace std;

string epic(uint64_t epiphany);

string epic(uint64_t epiphany) {

    string v = "";
    // Deriving variable
    uint64_t fh = 0;
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
            fj = fj.to_ulong() + 1;
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
    uint8_t x = fg.to_ulong();
    
    // Proof of concept for debugging
    //if (fh > 256)
    //    cout << fh << " " << flush;
    //else
    //    cout << "?";
        
    while (fh > 0) {
        unsigned char f = fh%256;
        v.push_back(f);
        fh >>= 8;
    }
    v.push_back('[');
    //print first character to start off
    while (x > 0) {
        unsigned char f = x;
        v.push_back(f);
        x >>= 8;
    }
    v.push_back(']');
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
    int j = 0;
    uint64_t inv_total;
    string m = "";
    while (t.size() > i) {
        // tv is the current segment
        string tv = t[i];
        // `j` tells us what generation of
        // inversion we're on. We turn them
        // all into a large 64 bit numbre (3 8bytes/64bits)
        // epitome is the second generation of
        // the 3 generations that go into the 64 bits
        // Readers Note: we're using inversion
        //          x =  epitome
        // for instance, macompplished is the 3rd
        
        uint64_t epiphany = 0, epitome = 0, maccomplished = 0;
        while (tv.length() > 0) {
            z = 0;
            
            // epiphany is the first generation
            // it takes the value of exciting
            uint64_t exciting = 0;
            
            // Let's go thur each character in a 8 byte
            // sequence and put them end to end. We'll
            // use this to compress with.
            for (unsigned char a : tv) {
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
            else
                tv.clear();
            
            // This is for outputting the file
            // to `ofo` (output file object)
            m = "";
           
            /// Invert the 3 generations
            inv_total = pow(2,63) - exciting;
            
            int y = 0;
            m = epic(inv_total);
            if (m.length() == 0)
                m = m + "JM";
            // Write to file
            // & get output entropy inserts
            // entropy is n. How many different
            // chars are in the file.
            if (j%1 == 0) {
                for (int r : m)
                    n.insert(r);
                ofo << m;
                m.clear();
            }
            // generation counter
            j++;
        }
        
        ofo << "RxIv";
        i++;
    }
    //output last of file
    {
        m = epic(inv_total);
        for (int r : m)
            n.insert(r);
        ofo << m;
        m.clear();
    }
    cout << n.size() << " " << flush;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\nfinished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}