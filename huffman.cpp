/*====================================================================
 * huffman.cpp
 * Authors: Bobby Craig, Ansel Schiavone, Chris Castillo
 * Proj4
 * CS271 - Dr. Jessen Havill
 *
 * A program to compress or decompress text using the Huffman compression
 * technique.
 *====================================================================*/

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h> 
#include <stdio.h>
#include "node.h"
#include "MPQ.h"
#include <math.h>
using namespace std;

/*====================================================================
 * GLOBAL ARRAYS
 *====================================================================*/

int FREQUENCY [256];//global array that tracks frequency of characters
string CODES [256];//global array that contains huffman codes of characters

/*====================================================================
 * bitConvert
 * A function to determine whether a char is a 1 or 0
 * Preconditions: a character of value 1 or 0
 * Postconditions: an int value corresponding to the character value
 *====================================================================*/

int bitConvert(char ch) {
	int binHold;
	if ( ch == '1' )
	{
		return 1;
	}
	else 
		return 0;
}

/*====================================================================
 * convert
 * A function to
 * Preconditions:
 * Postconditions: 
 *====================================================================*/

string convert(int val)
{
	   unsigned int mask = 1 << 8-1; //mask 1000000000000
	   string bin_string="";
	   for(int i=0; i<8; i++)
	   {
	   	   if ((val & mask)==0)
	   	   	   bin_string+="0";
	   	   else
	   	   	   bin_string+="1";
	   	   mask >>=1;
	   	   	   
	   }
	   return bin_string;
}

/*====================================================================
 * generate_code
 * A function to recursively steps down Huff Tree, generating Huffman codes
 * Preconditions:
 * Postconditions: 
 *====================================================================*/

void generate_code(string code, Node* node_ptr) {
	if(node_ptr->character == 0)
	{
		generate_code(code+"0", node_ptr->left);
		generate_code(code+"1", node_ptr->right);
	}
	if(node_ptr->character != 0) //if child, record code
		CODES[node_ptr->character]=code;
}

/*====================================================================
 * compress
 * A function to compress a text file into a .huff file
 * Preconditions:
 * Postconditions: 
 *====================================================================*/

void compress(char* text_file, char* huff_file)
{
	char ch;
	ifstream in_file;
	in_file.open(text_file);
	if(!in_file)
	{
		cout<<"Error opening file"<<endl;
		exit(0);
	}
	stringstream buffer;
	buffer << in_file.rdbuf();
	string decompress(buffer.str());
	for ( int i = 0; i < decompress.length(); i++ ) {
		FREQUENCY[decompress[i]]++;
	}
	in_file.close();
	MinPriorityQueue<Node> MPQ1;
	int count = 0;
	for(int i=0; i<256; i++)
	{
		if(FREQUENCY[i]>0)
		{
			Node *node = new Node(i);
			node->frequency=FREQUENCY[i];
			MPQ1.insert(node);
			count++;
			
		}
	}
	
	/*====================================================================
	* Create Huffman Tree for Huffman Prefix Values
	*====================================================================*/
	
	for(int i=1; i<count; i++)
	{
		Node* sum_node = new Node(0);
		Node* x;
		Node* y;
		sum_node->left= x = MPQ1.extractMin();
		sum_node->right= y = MPQ1.extractMin();
		
		sum_node->frequency=(x->frequency)+(y->frequency);	
		MPQ1.insert(sum_node);
	}
	Node* Huff = MPQ1.extractMin();
	generate_code("", Huff);
	
	/*====================================================================
	* Write Codes to out_string
	*====================================================================*/	
	
	// OPEN FILES
	ofstream out_file;
	out_file.open(huff_file);
	in_file.open(text_file);
	
	// CHECK FOR ERROR WHEN OPENING
	if(!in_file)
	{
		cout<<"Error opening file"<<endl;
		exit(0);
	}
	string out_string = "";
	
	// OUTPUT TRANSLATION TABLE
	for ( int i = 0; i < 256; i++ ) {
		if ( !CODES[i].empty() ) {
			out_string += convert(CODES[i].length());
			out_string += CODES[i];
			out_string += convert(i);
		}
	}
	// ADDITION OF 8 ZEROS TO INDICATE MOVE TO HUFF VALUES; ENDS TRANSLATION
	out_string += "00000000";
	
	// OUTPUT FILE CONTENTS
	stringstream buffer2;
	buffer2 << in_file.rdbuf();
	string decompress2(buffer2.str());
	for ( int i = 0; i < decompress2.length(); i++ ) {
		out_string += CODES[decompress2[i]];	// WRITE CODES TO OUT_STRING
	}
	
	// ADD 0s TO COMPLETE THE 8 BIT PATTERN
	// MAKES STRING A MULTIPLE OF 0
	int add = 8-(out_string.length() % 8);
	if ( out_string.length() % 8 != 0 ) {
		for ( int i = 0; i<add; i++ ) {
			out_string += "0";
		}
	}

	/*====================================================================
	* Write Codes to out_file
	*====================================================================*/
	
	char end_char = add;
	// ADD VALUE TO SUBTRACT FROM END
	out_file << add;
	// CONVETRT OUT_STRING TO BINARY, THEN CHAR, THEN PUT IN OUT_FILE
	for ( int i = 0; i < out_string.length(); i += 8 ) {
		int runningVal = 0;
		for ( int j = 0; j < 8; j++ ) {
			// CONVERT TO INT VALUE FROM BINARY
			runningVal += bitConvert(out_string[i+j]) * pow(2,7-j);
		}
		// CONVERT INT TO CHAR VALUE
		char toFile = runningVal;
		out_file << toFile;
	}
	
	in_file.close();
	out_file.close();

}

/*====================================================================
 * decompress
 * A function to decompress a .huff file into a .txt file
 * Preconditions: two locations of files
 * Postconditions: a decompressed file (text_file)
 *====================================================================*/
 
void decompress(char * huff_file, char * text_file)
{
	// OPEN FILES AND DECLARE VARIABLES
	char ch;
	ifstream in_file;
	ofstream out_file;
	in_file.open(huff_file);
	out_file.open(text_file);
	
	// CHECK FOR ERROR OPENING
	if(!in_file)
	{
		cout<<"Error opening file"<<endl;
		exit(0);
	}
	
	// READ FIRST CHAR FOR VALUE TO REMOVE FROM BACK OF BINARY STRING
	int remove_from_back;
	in_file >> remove_from_back;
	
	// MAKESHIFT WAY OF READING IN BINARY STRING FROM FILE
	stringstream buffer;
	buffer << in_file.rdbuf();
	string decompress(buffer.str());
	string binary = "";
	// CONVERT CHAR STRING TO BINARY STRING
	for ( int z=0; z < decompress.length(); z++ ) {
		binary += convert(decompress[z]);
	}
	// ERASE VALUES FROM BACK; NO NEED FOR STRING LENGTH TO BE MULTIPLE
	// OF 8 ANYMORE
	binary.erase(binary.end()-remove_from_back, binary.end());
	
	int index = 0;
	// ENCODE TRANSLATION TABLE
	while(1)
	{
		string code= "";
		int LEN = 0;
		int ascii =0;
		// FIND THE LENGTH OF THE HUFFMAN VALUE FOLLOWING
		for(int i=7; i>-1; i--)
		{
			ch = binary[index++];
			int binHold;
			if ( ch == '1' )
			{
				binHold = 1;
			}
			else 
				binHold = 0;
			LEN = LEN + binHold * pow(2,i);
		}
		// CHECK IF TERMINATOR TELLS US TO START TRANSLATING
		if(LEN==0)
			break;
		// ADDS NUMBER OF CHARACTERS FROM "FOR LOOP" ABOVE
		for(int j=0; j<LEN; j++)
		{
			ch = binary[index++];
			code=code+ch;
		}
		// ADDS THE ASCII VALUE
		for(int i=7; i>-1; i--)
		{
			ch = binary[index++];
			int binHold;
			if ( ch == '1' ) {
				binHold = 1;
			}
			else {
				binHold = 0;
			}
			ascii = ascii + binHold * pow(2,i);
		}
		// ADD THE VALUE TO THE GLOBAL ARRAY AT THE BEGINNING
		CODES[ascii]=code;
	}
	
	string newChar = "";
	// CONVERT THE HUFFMAN VALUES USING THE TRANSLATION TABLE
	// CREATED ABOVE.
	for (int j=index; j<binary.length(); j++) {
		newChar = newChar + binary[j];
		// LOOK THROUGH THE TRANSLATION TABLE
		for ( int i = 0; i < 256; i++ ) {
			if (!strcmp(newChar.c_str(),CODES[i].c_str()) && !CODES[i].empty()) {
				// IF VALUE FOUND, CONVERT TO CHAR, EMPTY STRING
				// FOR NEXT VALUE, AND ADD THE CHAR TO THE OUT_FILE
				char pushChar = i;
				out_file << "" << pushChar;
				newChar = "";
			}
		}	
	}
	
	out_file.close();
	in_file.close();
}

/*====================================================================
 * decompress
 * A function to decompress a .huff file into a .txt file
 * Preconditions: two locations of files
 * Postconditions: a decompressed file (text_file)
 *====================================================================*/
 
int main(int argc, char *argv[])
{
	string argv1(argv[1]);
	char * file_name1 = argv[2];
	char * file_name2 = argv[3];
	// PRINT HELP INFO IF USER NEEDS GUIDANCE
	if ( argv1 == "help" ) {
		cout << "help: ./huffman [-cd] [input] [output]\n";
		cout << "   Compress or decompress your file using the respective option.\n";
		cout << "   Using the Huffman Compression Technique, this program will\n";
		cout << "   compress or decompress an input file and return an output file\n";
		cout << "\n   Options:\n";
		cout << "     -c\tcompress a .txt file into a .huff file\n";
		cout << "     -d\tdecompress a .huff file into a .txt file\n";
		cout << "\n   Arguments:\n";
		cout << "     INPUT     for compression, .txt file; for decompression, .huff file\n";
		cout << "     OUTPUT    for compression, .huff file; for decompression, .txt file\n\n";
	}
	// CHECK FOR 4 ARGUMENTS TO PROCEED
	if ( argc != 4 )
	{
		exit(0);
	}
	// DIRECTIONAL CONTROL -- "-d" TO DECOMPRESS
	if ( argv1 == "-d")
	{
		decompress(file_name1, file_name2);
	}
	// DIRECTIONAL CONTROL -- "-c" TO COMPRESS
	else if ( argv1=="-c" )
	{
		compress(file_name1, file_name2);
	}
	// EXIT IF VALID COMMAND NOT GIVEN
	else
	{
		cout << "Valid command (-c or -d) not given." << endl;
		exit(0);

	}
}
