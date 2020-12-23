#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

enum class NODETYPE
{
	NUMBER,
	OPERAND,
	PARENTHESIS
};
struct ExpressionNode
{
	NODETYPE type;
	long long data;
	ExpressionNode* next;
	ExpressionNode* previous;
};

struct Expression
{
	ExpressionNode* root;
	ExpressionNode* tail;
	int count;
	Expression() : root(nullptr), tail(nullptr), count(0)
	{

	}
	~Expression()
	{
		while(root != nullptr)
		{
			ExpressionNode* tmp = root;
			root = root->next;
			delete tmp;
		}
	}
	void push_back(long long number)
	{
		if (root == nullptr)
		{
			root = new ExpressionNode({ NODETYPE::NUMBER, number, nullptr,nullptr });
			tail = root;
			count++;
			return;
		}

		tail->next = new ExpressionNode({ NODETYPE::NUMBER, number, nullptr,tail });
		tail = tail->next;
		count++;
	}
	void push_back(char character)
	{
		NODETYPE type;
		if (character == '(' || character == ')')
			type = NODETYPE::PARENTHESIS;
		else
			type = NODETYPE::OPERAND;

		if (root == nullptr)
		{
			root = new ExpressionNode({ type, character, nullptr, nullptr });
			tail = root;
			count++;
			return;
		}
		tail->next = new ExpressionNode({ type, character, nullptr,tail });
		tail = tail->next;
		count++;
	}
	void push_back(std::string str)
	{
		try
		{
			int val = std::stoi(str);
			push_back(static_cast<long long>(val));
		}
		catch (const std::invalid_argument& arg)
		{
			push_back(str[0]);
		}
	}

	std::vector<ExpressionNode*> FindNodes(NODETYPE type, char character)
	{
		std::vector<ExpressionNode*> nodes;
		ExpressionNode* current = root;
		while (current != nullptr)
		{
			if (current->type == type &&
				current->data == character)
				nodes.push_back(current);
			current = current->next;
		}
		return nodes;
	}
	ExpressionNode* FindNode(NODETYPE type, char character)
	{
		ExpressionNode* current = root;
		while (current != nullptr)
		{
			if (current->type == type &&
				current->data == character)
				return current;
			current = current->next;
		}
		return nullptr;

	}

	void RemoveNext(ExpressionNode* node, int count)
	{
		while (count > 0)
		{
			ExpressionNode* tmp = node->next;
			node->next = node->next->next;
			if (node->next != nullptr)
				node->next->previous = node;
			else
				if (tmp == tail)
					tail = node;
			delete tmp;
			count--;
			this->count--;
		}
	}
	void RemovePrevious(ExpressionNode* node, int count)
	{
		while (count > 0)
		{
			ExpressionNode* tmp = node->previous;
			node->previous = node->previous->previous;
			if (node->previous != nullptr)
				node->previous->next = node;
			else
				if (tmp == root)
					root = node;
			delete tmp;
			count--;
			this->count--;
		}
	}
	void RemoveAround(ExpressionNode* node)
	{
		ExpressionNode* tmp = node->previous;
		node->previous = node->previous->previous;
		if (node->previous != nullptr)
			node->previous->next = node;
		if (root == tmp)
			root = node;
		delete tmp;
		this->count--;
		tmp = node->next;
		node->next = node->next->next;
		if (node->next != nullptr)
			node->next->previous = node;
		delete tmp;
		this->count--;
	}

	void Print()
	{
		ExpressionNode* current = root;

		while (current != nullptr)
		{
			if (current->type == NODETYPE::NUMBER)
				printf("%d", current->data);
			if (current->type == NODETYPE::OPERAND)
				printf("%c", current->data);
			if (current->type == NODETYPE::PARENTHESIS)
				printf("%c", current->data);
			current = current->next;
		}
		printf("\n");
	}
	bool SolveExpression(ExpressionNode* node)
	{
		if (node->previous->type == NODETYPE::NUMBER &&
			node->type == NODETYPE::OPERAND &&
			node->next->type == NODETYPE::NUMBER)
		{
			switch (static_cast<int>(node->data))
			{
			case '+': node->previous->data += node->next->data; break;
			case '-': node->previous->data -= node->next->data; break;
			case '*': node->previous->data *= node->next->data; break;
			case '/': node->previous->data /= node->next->data; break;
			}
			RemoveNext(node->previous, 2);
			return true;
		}
		return false;
	}
	bool SolveForwards(ExpressionNode* start)
	{
		ExpressionNode* current = start;
		if (current != nullptr && current->next != nullptr && current->next->next != nullptr)
		{
			if (current->type == NODETYPE::NUMBER &&
				current->next->type == NODETYPE::OPERAND &&
				current->next->next->type == NODETYPE::NUMBER)
			{
				switch (static_cast<int>(current->next->data))
				{
				case '+': current->data += current->next->next->data; break;
				case '-': current->data -= current->next->next->data; break;
				case '*': current->data *= current->next->next->data; break;
				case '/': current->data /= current->next->next->data; break;
				}
				RemoveNext(current, 2);
				return true;
			}
			else if (current->type == NODETYPE::PARENTHESIS && current->data == '(')
			{
				if (current->next->next->type != NODETYPE::PARENTHESIS && current->next->next->data != ')')
				{
					return SolveForwards(current->next);
				}
				else if (current->next->next->type == NODETYPE::PARENTHESIS && current->next->next->data == ')')
				{
					RemoveAround(current->next);
					return true;
				}
				else
					return SolveForwards(current->next);
			}
			else
				return SolveForwards(current->next);
		}
		else
			return false;
	}
	bool SolveBackwards(ExpressionNode* start)
	{
		ExpressionNode* current = start;
		if (current != nullptr && current->previous != nullptr && current->previous->previous != nullptr)
		{
			if (current->type == NODETYPE::NUMBER &&
				current->previous->type == NODETYPE::OPERAND &&
				current->previous->previous->type == NODETYPE::NUMBER)
			{
				switch (static_cast<int>(current->previous->data))
				{
				case '+': current->data += current->previous->previous->data; break;
				case '-': current->data -= current->previous->previous->data; break;
				case '*': current->data *= current->previous->previous->data; break;
				case '/': current->data /= current->previous->previous->data; break;
				}
				RemovePrevious(current, 2);
				return true;
			}
			else if (current->type == NODETYPE::PARENTHESIS && current->data == ')')
			{
				if (current->previous->previous->type != NODETYPE::PARENTHESIS && current->previous->previous->data != '(')
				{
					return SolveBackwards(current->previous);
				}
				else if (current->previous->previous->type == NODETYPE::PARENTHESIS && current->previous->previous->data == '(')
				{
					RemoveAround(current->previous);
					return true;
				}
				else
					return SolveBackwards(current->previous);
			}
			else
				return SolveBackwards(current->previous);
		}
		else
			return false;
	}
	long double SolvePart2()
	{
		std::vector<ExpressionNode*> nodes = FindNodes(NODETYPE::OPERAND, '+');
		for (ExpressionNode* node : nodes)
		{
			SolveExpression(node);
		}
		ExpressionNode* node = FindNode(NODETYPE::PARENTHESIS, ')');
		while (node != nullptr)
		{
			SolveBackwards(node);
			nodes.clear();
			nodes = FindNodes(NODETYPE::OPERAND, '+');
			for (ExpressionNode* node : nodes)
			{
				SolveExpression(node);
			}
			node = FindNode(NODETYPE::PARENTHESIS, ')');
		}
		while (root->next != nullptr)
		{
			if (count == 3)
			{
				switch (static_cast<int>(root->next->data))
				{
				case '+': return static_cast<long double>(root->data + root->next->next->data); break;
				case '-': return static_cast<long double>(root->data - root->next->next->data); break;
				case '*': return static_cast<long double>(root->data * root->next->next->data); break;
				case '/': return static_cast<long double>(root->data / root->next->next->data); break;
				}
			}
			SolveForwards(root);
		}
		return root->data;
	}

	long double SolvePart1()
	{
		while (root->next != nullptr)
		{
			SolveForwards(root);
		}
		return root->data;
	}
};

void Dec18::Puzzle()
{
	std::ifstream file("Dec18_PuzzleInput.txt");
	long double sum = 0;

	if (file.is_open())
	{
		std::string line = "";
		std::vector<char> chars;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string s;
			Expression expression;
			while (ss >> s)
			{

				if (s.size() == 1)
				{
					expression.push_back(s);
				}
				else
				{
					while (s.size() > 0)
					{
						if (s[0] == '(' || s[0] == ')')
						{
							std::string substr = s.substr(0, 1);
							expression.push_back(substr);
							s.erase(s.begin());
						}
						else if (s[s.size() - 1] == ')')
						{
							std::string::iterator it = std::find(s.begin(), s.end(), ')');
							int position = std::distance(s.begin(), it);
							std::string substr = s.substr(0, position);
							s.erase(0, position);
							expression.push_back(substr);
						}
						else
						{
							expression.push_back(s);
							s.erase(s.begin(), s.end());
						}
					}
				}
			}
			long double answer = expression.SolvePart2();
			//std::cout << answer << "\n";
			sum += answer;
		}

		std::cout << sum << "\n";
	}
	return;
}