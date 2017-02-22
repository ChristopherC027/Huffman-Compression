/*====================================================================
 * node.h
 * Authors: Bobby Craig, Ansel Schiavone, Chris Castillo
 * Proj4
 * CS271 - Dr. Jessen Havill
 *====================================================================*/
 
#ifndef NODE_H
#define NODE_H

class Node
{
public:
	int frequency;
	char character;
	Node* left;
	Node* right;
	Node(char character1, Node *child = NULL)
	{
		frequency = 0;
		character = character1;
		left = child;
		right = child;
	};
	bool operator<(const Node& node)
	{
		return(this->frequency < node.frequency);
		
	}
	
};

std::ostream& operator<<(std::ostream& stream, const Node& node) // output operator
{
	stream<<"["<<node.character<<":"<<node.frequency<<"]";
	return stream;
}

#endif


