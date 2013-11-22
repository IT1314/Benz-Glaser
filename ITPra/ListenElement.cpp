#include "ListenElement.h"	
using namespace std;

ListenElement::ListenElement(){
	ListenElement::schaltwerkElement=NULL;	
	ListenElement::next=NULL;
}
ListenElement::~ListenElement(void){
}
	
SchaltwerkElement* ListenElement::getSchaltwerkElement(){
	return ListenElement::schaltwerkElement;
}

ListenElement* ListenElement::getNextElement(){
	return ListenElement::next;
}
void ListenElement::setSchaltwerkElement(SchaltwerkElement* schaltwerkEl){
	ListenElement::schaltwerkElement=schaltwerkEl;
}
void ListenElement::setNextElement(ListenElement* nextEl){
	ListenElement::next=nextEl;
}