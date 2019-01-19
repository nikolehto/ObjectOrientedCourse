#include <string>

#ifndef INTELEMENT_H
#define INTELEMENT_H
class IntElement
{
private:
	int intelement;

public: 
	IntElement();
	IntElement(int v);
	~IntElement();
	int getVal() const;
	void setVal(int v);
	
	IntElement& operator+=(const IntElement& i);
	IntElement& operator-=(const IntElement& i);
	IntElement& operator*=(const IntElement& i);
	friend std::ostream& operator<<(std::ostream& a, const IntElement& b);

	/* inline https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading
	IntElement& operator+(const IntElement& b);
	IntElement& operator-(const IntElement& b);
	IntElement& operator*(const IntElement& b);


	*/
};
#endif