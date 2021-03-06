#include <stdlib.h>
#include <stdio.h>
#include "dampltup.h"

Tuple dampl_tup_new (int size, type_map* type){
	int i;

	Tuple tup = malloc(sizeof(tp_tup_struct));
	tup->size = size;
    tup->map = type;
    

	tup->values = malloc(size*sizeof(String));

	for(i = 0; i < size; i++){
        switch(type[i]){
            case real:
                tup->values[i] = dampl_str_copy("0.0");
                break;
            case integer:
                tup->values[i] = dampl_str_copy("0");
                break;
            case text:
                tup->values[i] = dampl_str_copy("");
                break;
        }
		
	}

	return tup;
}


/* Length function */

int dampl_tup_len(Tuple tup){
	return tup->size;
}

/* Tuple insertion method */

int dampl_tup_set__int(Tuple tup, int index, int data){

	/* Check border conditions */

	if (index >= tup->size || index < 0)
    {
        fprintf(stderr, "Out of bounds exception\n");
        exit(1);
    }

	char str[11];

	sprintf(str, "%d", data);

	tup->values[index] = dampl_str_copy(str);

	return data;
}

float dampl_tup_set__float(Tuple tup, int index, float data){

	/* Check border conditions */

	if (index >= tup->size || index < 0)
    {
        fprintf(stderr, "Out of bounds exception\n");
        exit(1);
    }

	char str[64];

	sprintf(str, "%g", data);

	tup->values[index] = dampl_str_copy(str);

	return data;
}

String dampl_tup_set__str(Tuple tup, int index, String data){
    char *eptr;
    double result_d;
    long result_l;


    switch(tup->map[index]){
        case real:
            /* Convert the provided value to a double */
            result_d = strtod(data, &eptr);
            dampl_tup_set__float(tup, index, (float)result_d);
            break;

        case integer:
            /* Convert the provided value to a long */
            result_l = strtol(data, &eptr, 10);
            dampl_tup_set__int(tup, index, (int)result_l);
            break;

        case text:
            /* Check border conditions */

            if (index >= tup->size || index < 0){
                fprintf(stderr, "Out of bounds exception\n");
                exit(1);
            }

            tup->values[index] = dampl_str_copy(data);
            break;
    }
    
	return tup->values[index];
}


int dampl_tup_get__int(Tuple tup, int index){
	String str;
	char *eptr;
    long result;

	/* Check border conditions */

    if (index >= tup->size || index < 0)
    {
        fprintf(stderr, "Out of bounds exception\n");
        exit(1);
    }

    str = tup->values[index];

    /* Convert the provided value to a decimal long long */
    result = strtol(str, &eptr, 10);

    return (int)result;
}

float dampl_tup_get__float(Tuple tup, int index){
	char *str;
	char *eptr;
    double result;

	/* Check border conditions */

    if (index >= tup->size || index < 0)
    {
        fprintf(stderr, "Out of bounds exception\n");
        exit(1);
    }

    str = tup->values[index];

    /* Convert the provided value to a double*/
    result = strtod(str, &eptr);

    return (float)result;	
}

String dampl_tup_get__str(Tuple tup, int index){

	/* Check border conditions */

	if (index >= tup->size || index < 0)
    {
        fprintf(stderr, "Out of bounds exception\n");
        exit(1);
    }

	return tup->values[index];
}