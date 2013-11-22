#include "SchaltwerkElement.h"

class ListenElement{

	private:
		SchaltwerkElement* schaltwerkElement;
		ListenElement* next;
		ListenElement();
		~ListenElement();
	
	public:
		SchaltwerkElement* getSchaltwerkElement();
		ListenElement* getNextElement();
		void setSchaltwerkElement(SchaltwerkElement* schaltwerkEl);
		void setNextElement(ListenElement* nextEl);

};