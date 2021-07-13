#include<stdio.h>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;


class Rule {
    public:
        int num;
        string src_ip, dest_ip;
        int src_port_1, src_port_2;
        int dest_port_1, dest_port_2;
        string protocol;
        string data;
        bool isValid;
};

class Packet {
    public:
        int num;
        string src_ip;
        string dest_ip;
        int src_port;
        int dest_port;
        string protocol;
        string data;
        bool ValidPacket;
};

string bin_conversion(string xyz) {
    int d = stoi(xyz);
    int e[8] = {0};
    for(int i=0;d>0;i++) {
        e[i] = d%2;
        d= d/2;
    }
    string val = "";
    for(int i = 7; i >= 0; i--) {
        char c = e[i]+'0';
        val = val + c;
    }
    return val;
}

bool isPrefixMatch(string a, string b) {

    string ruleip_in_bin = "";
    string packetip_in_bin = "";

    stringstream ss(a);
    string ip, prefix;

    getline(ss, ip, '/');
    getline(ss, prefix, '/');
    int pre = stoi(prefix);

    stringstream ss2(ip);
    string s;
    while(getline(ss2, s, '.')) {
        ruleip_in_bin = ruleip_in_bin + bin_conversion(s);
    }

    stringstream ss3(b);
    while(getline(ss3, s, '.')) {
        packetip_in_bin = packetip_in_bin + bin_conversion(s);
    }

    for(int i = 0; i < pre; i++) {
        if(packetip_in_bin[i] != ruleip_in_bin[i]) {
            return false;
        }
    }
    return true;

}
// Checks the ports of packets are valid
bool PacketPortCheck(int a, int b) {
    if(a < 1 || a > 65535 || b < 1 || b > 65535) {
        return false;
    }
    return true;
}

vector<Packet*> packets;
vector<Rule*> rules;
//This function compares lines of packets with corresponding lines of rules like Ports, DATA etc.,
bool isSatisfied(Packet pckt, Rule rule) {
    if(pckt.protocol != rule.protocol) {
        return false;
    }
    if(rule.src_port_1 != 0 || rule.src_port_2 != 0) {
        if(pckt.src_port > rule.src_port_2 || pckt.src_port < rule.src_port_1)
            return false;
    }
    if(rule.dest_port_1 != 0 || rule.dest_port_2 != 0) {
        if(pckt.dest_port > rule.dest_port_2 || pckt.dest_port < rule.dest_port_1)
            return false;
    }
    if(rule.data != "*") {
        size_t found = pckt.data.find(rule.data);
        if(found == string::npos) {
            return false;
        }
    }
    if(rule.src_ip != "0.0.0.0/0") {
        if(!isPrefixMatch(rule.src_ip, pckt.src_ip)) {
            return false;
        }
    }
    if(rule.dest_ip != "0.0.0.0/0") {
        if(!isPrefixMatch(rule.dest_ip, pckt.dest_ip)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    //  Reading rules file via the argument
    char rulelist[1000];
    strcpy(rulelist, argv[1]);
    // Dissecting and making list of rule records and storing them in vectors of rule classes to compare them with packet classes later.
    fstream rp;
    rp.open(rulelist);
    string r_line;
    Rule *rule;
    int read_count = 0;
    while(getline(rp, r_line))
    {
        stringstream s(r_line);
        string word;
        vector<string> r_line_words;
        while(s >> word) {
            r_line_words.push_back(word);
        }
        if(r_line_words[0] == "BEGIN") {
            rule = new Rule();
        }
        else if(r_line_words[0] == "NUM:") {
            rule -> num = stoi(r_line_words[1]);
        }
        else if(r_line_words[0] == "SRC" && r_line_words[1] == "IP" && r_line_words[2] == "ADDR:" ) {
            rule -> src_ip = r_line_words[3];
        }
        else if(r_line_words[0] == "DEST" && r_line_words[1] == "IP"  && r_line_words[2] == "ADDR:") {
            rule -> dest_ip = r_line_words[3];
        }
        else if(r_line_words[0] == "SRC" && r_line_words[1] == "PORT:") {
            stringstream ss(r_line_words[2]);
            string port_num_1, port_num_2;
            getline(ss, port_num_1, '-');
            getline(ss, port_num_2, '-');

            rule -> src_port_1 = stoi(port_num_1);
            rule -> src_port_2 = stoi(port_num_2);
        }
        else if(r_line_words[0] == "DEST" && r_line_words[1] == "PORT:") {
            stringstream ss(r_line_words[2]);
            string port_num_1, port_num_2;
            getline(ss, port_num_1, '-');
            getline(ss, port_num_2, '-');

            rule -> dest_port_1 = stoi(port_num_1);
            rule -> dest_port_2 = stoi(port_num_2);
        }
        else if(r_line_words[0] == "PROTOCOL:") {
            rule -> protocol = r_line_words[1];
        }
        else if(r_line_words[0] == "DATA:") {
            string str = "";

            for( int i = 1;i < r_line_words.size(); i++) {
                str = str + r_line_words[i] + " ";
            }
            str.pop_back(); // used to check if data field is empty
            rule -> data = str;
        }
        else if (r_line_words[0] == "END") {
            rules.push_back(rule);
        }
    }
    cout << "A total of " << rules.size() << " rules were read; ";
    // NEXT SECTION OF CODE COUNTS THE NUMBER OF VALID RULES BY CHECKING CONSTRAINS ON PORT NUMBERS. PORTS IS THE PARAMETER USED TO VALIDATE RULES.
    int count = 0;
    cout<< rules.size()<<endl;
    for(int i = 0; i < rules.size(); i++)
    {
        int int1,int2, int3, int4;
        int1 = rules[i]->src_port_1;
        int2 = rules[i]->src_port_2;
        int3 = rules[i]->dest_port_1;
        int4 = rules[i]->dest_port_2;
        if(int1 > int2 || int3 > int4)
        {
               rules[i] -> isValid = false;
        }
        else if(int1 < 1 || int1 > 65535 || int2 < 1 || int2 > 65535)
        {
            if(int1 != 0 || int2 != 0)
            {
                rules[i] -> isValid = false;
            }
        }
        else if(int3 < 1 || int3 > 65535 || int4 < 1 || int4 > 65535)
            {
                if(int3 != 0 || int4 != 0)
                {
                    rules[i] -> isValid = false;
                }
            }
        else{
            rules[i] -> isValid = true;
            count++;

        }


    }
    cout << count << " valid rules are stored" << endl;
    // This next section reads packet file and stores individual packets as vectors of packet classes.
    char packetfile[1000];
    strcpy(packetfile, argv[2]);
    fstream pp;
    pp.open(packetfile);
    string p_line;
    Packet *pckt;
    while(getline(pp, p_line))
    {
        stringstream s(p_line);
        string word;
        vector<string> p_words_line;
        while(s >> word)
        {
            p_words_line.push_back(word);
        }
        if(p_words_line[0] == "BEGIN")
        {
            pckt = new Packet();
        }
        else if(p_words_line[0] == "NUM:")
        {
            pckt -> num = stoi(p_words_line[1]);
        }
        else if(p_words_line[0] == "SRC" && p_words_line[1] == "IP") {
            pckt -> src_ip = p_words_line[3];
        }
        else if(p_words_line[0] == "DEST" && p_words_line[1] == "IP") {
            pckt -> dest_ip = p_words_line[3];
        }
        else if(p_words_line[0] == "SRC" && p_words_line[1] == "PORT:") {
            pckt -> src_port = stoi(p_words_line[2]);
        }
        else if(p_words_line[0] == "DEST" && p_words_line[1] == "PORT:") {
            pckt -> dest_port = stoi(p_words_line[2]);
        }
        else if(p_words_line[0] == "PROTOCOL:") {
            pckt -> protocol = p_words_line[1];
        }
        else if(p_words_line[0] == "DATA:") {
            string str = "";

            for(int i=1; i < p_words_line.size();i++) {
                str = str + p_words_line[i];
                str = str + " ";
            }
            str.pop_back(); // checks if data field is empty
            pckt -> data = str;
        }
        else if (p_words_line[0] == "END") {
            packets.push_back(pckt);
        }
    }
    // This next section validates packets using PORTS constraints and calling a function that compares the rules and packets.
    int total = 0;
    for(int i = 0; i < packets.size(); i++)
        {
            int int5, int6;
            cout << "Packet number " << packets[i]->num;
            auto start = chrono::high_resolution_clock::now();
            int5 = packets[i]->src_port;
            int6 = packets[i]->dest_port;
           if(!PacketPortCheck(int5,int6 )) {
            cout << " is invalid" << endl;;
        }
        else
        {
            vector<int> satRules;
            for(int j = 0; j < rules.size(); j++) {
                if(rules[j]->isValid == false) {
                    continue;
                }
                if( isSatisfied( *(packets[i]), *(rules[j]) ) ) {
                    satRules.push_back(rules[j]->num);
                }
            }
            cout << " matches " << satRules.size() << " rule(s):";
            for(int j = 0; j < satRules.size(); j++) {
                cout << " " << satRules[j];
            }
            cout << endl;
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
        total += duration.count();
    }
    int n = packets.size();
    cout << "A total of " << n << " packet(s) were read from the file and processed. Bye." << endl;
    float avg_time = total/(1.0*n);
    cout << "Average time taken per packet: " << avg_time << " microseconds." << endl;


    return 0;
}
