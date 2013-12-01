#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <iostream>
inline void clearscreen(void){
		//clearscreen();
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl ;
}
inline void getEnter(void)
{
	auto dummy = getchar();// lösche vorheriges Newline
	while (getchar() != '\n'){};
}
#endif // MAIN_H_INCLUDED
