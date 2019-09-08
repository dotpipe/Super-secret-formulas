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

using namespace std;

unsigned int gcd (unsigned int, unsigned int);

unsigned int gcd (unsigned int n1, unsigned int n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

int main(int c, char * argv[]) {

    // we can leave the segments in averages per csv line
    ifstream ifo (argv[1], std::ios_base::in | std::ios_base::binary);
    ofstream ofo ("test.txt", std::ios_base::out | std::ios_base::binary);

    string hexrem = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*";
    long x = 0, y = 0;
    string str = "";
    vector<int> ordered {};
    stringstream ifos;
    ifos << ifo.rdbuf();
    string gs = ifos.str();
    ifos.str("");
    double file_len = gs.length();
    while (gs.length() > 0) {
        vector<char> g {};
        string d = {};
        if (gs.length() >= 1525000) {
            d = gs.substr(0, 1525000);
            gs = gs.substr(1525000,gs.length()-1);
        }
        else
        {
            d = gs;
            gs.clear();
        }
        cout << std::setprecision(2) << (1 - (gs.length()/file_len))*100 << "%";
        cout << " " << flush;
    // Characters in front, and rear of file (pseudo-palindrome)
        int count = 520;
        vector<double> t = {};
        while (d.length() >= count*2) {
            string b = d.substr(0,count) + d.substr(d.length()-count,count);
            g.push_back(b.front());
            g.push_back(b.back());
            int i = 0;
            while (d.length() >= 2 && i < count) {
                d.pop_back();
                d.erase(d.begin());
                i++;
            }
        }
        int dc = d.length();
        if (d.length() > 0) {
            int e = 0;
            for (int a : d)
                e += a;
            t.push_back(e/d.length());
            g.push_back(d.front());
            g.push_back(d.back());
        }
        d.clear();
        y = g.size();
        /*
        vector<string> h {};
        int i = 0;
        string j = {};
        std::vector<string>::iterator usiter = g.begin();
        std::vector<string>::iterator rusiter = g.end()-1;
        while (g.size() > 1) {
            usiter = g.begin();
            rusiter = g.end()-1;
            j = *usiter;
            h.push_back(j);
            if (g.size() > 0)
                g.erase(usiter);
            j = *rusiter;
            if (g.size() > 0)
                g.erase(rusiter);
            h.push_back(j);
        }
        
        vector<string> out = {};
        while (h.size() > i) {
            auto k = find(out.begin(),out.end(),h[i]);
            if (k == out.end()) {
                out.push_back(h[i]);
                ordered.push_back(out.size());
            }
            else {
                int m = distance(out.begin(),k);
                ordered.push_back(m);
            }
            i++;
        }
        i = 0;
        
        ofo << "||**" << dc << "**||??" << y << "??||";
        while (out.size() > 0) {
            vector<string>::iterator witer = out.begin();
            string s = *witer;
            ofo.write(s.c_str(), s.length());
            out.erase(out.begin());
        }
        
        for (int a : t) {
            int u = round((a/70)-0.5);
            int n = round((u/70)-0.5);
            int f = a - (70 * u);
            ofo << std::hex << n << u << f;
        }
        */
        for (double x : t)
            ofo << std::hexfloat << x;
        for (char s : g)
            ofo << s;
        ordered.clear();
    }
    cout << x << endl << y << flush;
}