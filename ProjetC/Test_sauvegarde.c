#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "libCIPSI1.h"

#define PI acos(-1)


int main() {

	float tab1[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	float tab2[5] = { 6.0, 7.0, 8.0, 9.0, 10.0 };

	sauvegardeCSV(tab1, tab2, 5, "resultat.csv");
}