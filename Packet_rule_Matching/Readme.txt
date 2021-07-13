The objective of this task is to implement a simple firewall rule matching algorithm. The match will be done
a set of 6 fields, including source IP address, destination IP address, source port, destination port, protocol,
and payload data.
Here, rulefile.txt specifies the set of rules to be stored in the firewall database, and pktfile.txt contains relevant
packet field information for a set of packets. Each packet has to be compared against all the rules in the
database and the matching rules should be output by the program


You can compile it with the belo command:
"g++ lab5-fw.cpp -o lab5-fw"
YOu can execute the file with below command:
"lab5-fw rf1.txt pf1.txt"
---------------------------------------
As far as I know, it seems to work fine for all the test cases I could think of.