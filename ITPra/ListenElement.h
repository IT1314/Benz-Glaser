#ifndef LISTENELEMENT_H
#define LISTENELEMENT_H

#include "SchaltwerkElement.h"

class ListenElement{

	private:
		SchaltwerkElement* schaltwerkElement;
		ListenElement* next;
		
	
	public:
		ListenElement();
		~ListenElement();
		SchaltwerkElement* getSchaltwerkElement();
		ListenElement* getNextElement();
		void setSchaltwerkElement(SchaltwerkElement* schaltwerkEl);
		void setNextElement(ListenElement* nextEl);


};
#endif LISTENELEMENT_H