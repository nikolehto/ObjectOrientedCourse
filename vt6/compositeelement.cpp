#include "catch.hpp"
#include "compositeelement.h"

/**
 *  @file compositeelement.cpp
 *  @brief Implementation of CompositeElement
 *  */

/**
 *  @class CompositeElement
 *  @version 3.0
 *  @brief Composite for element
 *  @author Niko Lehto
 *  */

/**
 *  \brief Parameterized constructor
 *  \param [in] e1 Element& initial value for CompositeElement
 *  \param [in] e2 Element& initial value for CompositeElement
 *  \param [in] opc std::function<int(int,int)>& initial value for CompositeElement
 *  \param [in] op char initial value for CompositeElement
 * */
CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc)
{
	opmd1 = e1.clone();
	opmd2 = e2.clone();
    op_fun = op;
    op_ch = opc;
}

/**
 *  \brief Clone constructor
 *  \param [in] i const CompositeElement& initial value for CompositeElement
 * */
CompositeElement::CompositeElement(const CompositeElement& i)
{
    *this = i;
}


/**
 *  \brief Default destructor
 * */
CompositeElement::~CompositeElement() = default;


/**
* \brief Evaluate variable with given Valuation mapping v, contained elements and operation
* \param [in] v const Valuation& contains symbol values
* \return int : result of operation(e<SUB>1</SUB>->evaluate(v), e<SUB>2</SUB>->evaluate(v))
*/
int CompositeElement::evaluate(const Valuation& v) const
{
    int a = this->opmd1->evaluate(v);
    int b = this->opmd2->evaluate(v);
    return op_fun(a,b);
}


/**
 *  \brief Assignment operator
 *  \param [in] m const CompositeElement& Element to Assign
 *  \return Reference to copied right side value
*/
CompositeElement& CompositeElement::operator=(const CompositeElement& m)
{
    // prevent self assignment
    if(this == &m)
    {
        return *this;
    }

    this->opmd1 = m.opmd1->clone();
    this->opmd2 = m.opmd2->clone();
    this->op_fun = m.op_fun;
    this->op_ch = m.op_ch;

    return *this;
}

/**
 *  \brief Write object to stream in form of (el<SUB>1</SUB><op>el<SUB>2</SUB>) where els are contained elements and <op> is operation char. i.e. '(x+y)'
 *  \return std::string object as a string
 *  */
std::string CompositeElement::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 * \brief returns the pointer to a copy of var
 * \return shared_ptr containing value of CompositeElement
 */
std::shared_ptr<Element> CompositeElement::clone() const
{
    return std::shared_ptr<Element>(new CompositeElement(*this));
}

/**
 *  \brief Write object to stream in form of (el<SUB>1</SUB><op>el<SUB>2</SUB>) where els are contained elements and <op> is operation char. i.e. '(x+y)'
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] e const CompositeElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const CompositeElement& e)
{
	o << "(" << *(e.opmd1) << e.op_ch << *(e.opmd2) << ")";
	return o;
}

/**
 *  \brief Overload of equal comparison
 *  \note Actual function comparison works with + - and * operations but not necessarily with any function. Tested with this->op_fun(3,5) == e.op_fun(3,5)
 *  \param [in] e const eElement& value
 *  \return true if this and m contains sane value
 */
bool CompositeElement::operator==(const Element& e) const
{
    std::shared_ptr<CompositeElement> e_e;

    if(e_e = std::dynamic_pointer_cast<CompositeElement>(e.clone()))
    {
        return *this == *e_e;
    }
    else
    {
        return false;
    }

}

/**
 *  \brief Equal comparison
 *  \note comparison of function works with + - and * operations but not necessarily detect any functions differences. Thats caused by function is only tested by this->op_fun(3,5) == e.op_fun(3,5)
 *  \param [in] e const CompositeElement& value
 *  \return true if this and e contains
 */
bool CompositeElement::operator==(const CompositeElement& e) const
{

	if( *(this->opmd1) == *(e.opmd1))
     if( *(this->opmd2) == *(e.opmd2))
      if(this->op_ch == e.op_ch)
       if(this->op_fun(3,5) == e.op_fun(3,5))
        return true;

    return false;
}

