/******************************************************************************

Solution for question 3. Converting string s to string t in k operations.

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <stdexcept>  

using namespace std; 

void read_input(string p_filepath, string& s, string& t, int& k) {
    /*
     * Reads the input file ans set strings s, t and integer k.
     */ 
     ifstream in_file (p_filepath);
     string l_buffer;
     string k_str;
     if (in_file.is_open()) {
         // todo: should handle errors here.
         getline (in_file, s);
         getline (in_file, t);
         getline (in_file, k_str); 
         k = atoi(k_str.c_str());
         s = s.substr(0,s.length()-1);
         t = t.substr(0,t.length()-1);
         
         for (int i=0; i<s.length(); ++i)
            if (!islower(s[i]))
                throw invalid_argument("Invalid file " + p_filepath);
                
         for (int i=0; i<t.length(); ++i)
            if (!islower(t[i]))
                throw invalid_argument("Invalid file " + p_filepath);


     }
     else
        throw invalid_argument("Invalid file " + p_filepath);
}

int check_prefix_size(const string& s, const string& t)
{
    /*
     * Checks the size of the prefix that is commom to s and t;
     *
     */
     
     unsigned short min_size = t.length();
     if (t.length() > s.length()) {
         min_size = s.length();
     }
     
     int p_size;
     for (p_size=0; p_size<min_size; ++p_size) {
         if (t[p_size] != s[p_size])
            break;
     }
     
     return p_size;
}


string ConcatERemove(string s, string t, int k)
{
    if (s.length() < 1 || s.length() > 100)
        throw domain_error("Invalid size for string parameter s.");
        
    if (t.length() < 1 || t.length() > 100)
        throw domain_error("Invalid size for string parameter t.");
    
    if (k < 1 || k > 100)
        throw domain_error("Invalid integer input for parameter k.");

    string l_result;
    if (k >= s.length() + t.length() )
        l_result = "sim";
    else {
        int prefix_size = check_prefix_size(s,t);
        int min_rem_operations = s.length() - prefix_size;
        int min_push_operations = t.length() - prefix_size;
        
        if (k < min_rem_operations + min_push_operations)
            l_result = "não";
        else if (((k-min_push_operations-min_rem_operations) % 2)==0) 
            l_result = "sim";
        else 
            l_result = "não";
    }
        
    return l_result;
}


int main(int argc, char *argv[])
{
    
    if (argc != 2) {
        cout << "Invalid number of arguments";
        return 0;
    }
    
    string s, t;
    int k;
    read_input (argv[1], s, t, k);
    
    try {
        cout << ConcatERemove(s, t, k);
    }
    catch( const exception& e ) {
        cout << "Error when executing ConcatERemove: " << e.what();
    }
    return 0;
}
