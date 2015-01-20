/*
 * Iterator.h
 *
 *  Created on: Jan 19, 2015
 *      Author: scho
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

template <class T> struct T;
class Iterator {

public:
	bool hasNext();
	T next();
};



#endif /* ITERATOR_H_ */
