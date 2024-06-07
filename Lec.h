#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct IDS{
    uint16_t id;
    uint16_t lid[3];

};

void lec(FILE *f);

void PID(FILE *f);
