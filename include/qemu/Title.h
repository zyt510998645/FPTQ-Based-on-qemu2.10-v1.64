#ifndef QEMU_TITLE_H
#define QEMU_TITLE_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef long unsigned int TypeU64;
extern long unsigned int INTERVAL_RDD;
extern long unsigned int INTERVAL_RDD_SAMPLE;
extern long unsigned int INTERVAL_RDD_SAMPLE_RATE;
extern unsigned int LOG_QEMU_RDD;
extern long unsigned int INTERVAL_SDD;
extern long unsigned int INTERVAL_SDD_SAMPLE;
extern long unsigned int INTERVAL_SDD_SAMPLE_RATE;
extern unsigned int LOG_QEMU_SDD;
//extern unsigned int LOG_QEMU_SAMPLE;
extern long unsigned int SAMPLE_RATE;
extern unsigned int LOG_LS_TRACE;
//extern long unsigned int SET_NUM;
extern long unsigned int L1D_SIZE;
extern long unsigned int CACHE_LINE;
extern long unsigned int ASSOCIATE;
extern long unsigned int GET_SET;
extern long unsigned int GET_SET_BIT;
extern long unsigned int CACHE_LINE_BIT;
extern long unsigned int SET_ID;

extern TypeU64 Get_Set(TypeU64 L1D_SIZE, TypeU64 CACHE_LINE, TypeU64 ASSOCIATE);
extern TypeU64 Get_Set_Bit(TypeU64 GET_SET);
extern TypeU64 Cache_Line_Bit(TypeU64 CACHE_LINE);
extern TypeU64 Set_Id(TypeU64 x);
#endif
