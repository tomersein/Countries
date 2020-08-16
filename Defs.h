//
// Created by tomer on 29/11/2018.
//

#ifndef EX2ADVANCEDCODING_DEFS_H
#define EX2ADVANCEDCODING_DEFS_H

#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false,true } bool;
typedef enum e_status { success, failure} status;

typedef void * Element;

typedef Element(*copyFunction) (Element);
typedef status(*freeFunction) (Element);
typedef status(*printFunction) (Element);
typedef int(*transformIntoNumberFunction) (Element);
typedef bool(*equalFunction) (Element, Element);

#endif /* DEFS_H_ */

#endif //EX2ADVANCEDCODING_DEFS_H
