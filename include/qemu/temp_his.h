#ifndef QEMU_TEMP_HIS_H
#define QEMU_TEMP_HIS_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
//#include "Title.h"
typedef long unsigned int TypeU64;

//#define INTERVAL_RDD 20
//#define LOG_QEMU_RDD 0

//#define INTERVAL_SDD 20
//#define LOG_QEMU_SDD 0

//#define SAMPLE_RATE 10000  //Sampling Rate! (>= 1)

//#define LOG_LS_TRACE 0  // reference trace dump

#define SET_NUM 65537    //最大set数！8M/2W时
//#define L1D_SIZE 64      //64 KB
//#define CACHE_LINE 64    //64 Byte
//#define ASSOCIATE 1024      //关联度 4
//#define GET_SET (TypeU64)((L1D_SIZE*1024)/(CACHE_LINE*ASSOCIATE)) //获得组数
//#define GET_SET_BIT (TypeU64)(log((double)GET_SET)/log(2))        //获得组数所占bit数
//#define CACHE_LINE_BIT (TypeU64)(log((double)CACHE_LINE)/log(2))  //获得cache line所占bit数
//#define SET_ID(x) (TypeU64)(((TypeU64)(x) >> CACHE_LINE_BIT) & (GET_SET - 1))
#define PRINT_CONF_STATS printf("#######CONF#STATS####### \nL1_DCache_Size: %lu KB \nL1_CACHE_LINE: %lu Byte \nL1_ASSOCIATE: %lu Way\n(L1_SET_NUM: %lu Set) \nCut-off Distance:\n  RDD:%lu \n  SDD:%lu \n  RDD_SAMPLE:%lu \n  SDD_SAMPLE:%lu \n  RDD_SAMPLE_RATE:%lu \n  SDD_SAMPLE_RATE:%lu \n#######CONF#STATS#######\n",(TypeU64)L1D_SIZE,(TypeU64)CACHE_LINE,(TypeU64)ASSOCIATE,(TypeU64)GET_SET,(LOG_QEMU_RDD ? (TypeU64)INTERVAL_RDD : (TypeU64)0),(LOG_QEMU_SDD ? (TypeU64)INTERVAL_SDD : (TypeU64)0),(INTERVAL_RDD_SAMPLE ? (TypeU64)INTERVAL_RDD_SAMPLE : (TypeU64)0),(INTERVAL_SDD_SAMPLE ? (TypeU64)INTERVAL_SDD_SAMPLE : (TypeU64)0),(INTERVAL_RDD_SAMPLE ? (TypeU64)INTERVAL_RDD_SAMPLE_RATE : (TypeU64)0),(INTERVAL_SDD_SAMPLE ? (TypeU64)INTERVAL_SDD_SAMPLE_RATE : (TypeU64)0))

#define LOG_ASSOCIATE(x) (x += 1)
extern TypeU64 SET_NUM_LIST[]; 
//extern TypeU64 Sample_RDD[GET_SET],Sample_SDD[GET_SET];//ZYT 3-8
extern TypeU64 HIS_sample_RDD[];//ZYT 3-9
extern TypeU64 HIS_sample_SDD[];//ZYT 3-9
extern TypeU64 HIS_RDD[];
extern TypeU64 HIS_SDD[];
extern TypeU64 RDD_LS,SDD_LS;
extern TypeU64 Sample_RDD_LS,Sample_SDD_LS;
/*
TypeU64 Get_Set(TypeU64 L1D_SIZE, TypeU64 CACHE_LINE, TypeU64 ASSOCIATE)
{
    TypeU64 get_set=0;
    get_set = L1D_SIZE * 1024/(CACHE_LINE * ASSOCIATE);
    return get_set;
};

TypeU64 Get_Set_Bit(TypeU64 GET_SET)
{
    TypeU64 get_set_bit=0;
    get_set_bit = log((double)GET_SET)/log(2);
    return get_set_bit;
};

TypeU64 Cache_Line_Bit(TypeU64 CACHE_LINE)
{
    TypeU64 cache_line_bit=0;
    cache_line_bit = log((double)CACHE_LINE)/log(2);
    return cache_line_bit;
};

TypeU64 Set_Id(TypeU64 x)
{
    TypeU64 set_id = 0;
    set_id = ((TypeU64)(x) >> CACHE_LINE_BIT) & (GET_SET - 1);
    return set_id;
};
*/
//extern TypeU64 DI_num;
/*
static void LOG_ASSOCIATE(TypeU64 *SET_LIST)
{ 
    *SET_LIST += 1;
};
*/
//#if LOG_LS_TRACE
#define LINE_Z 1024

static void LOG_TRACE_PRINT(TypeU64 Addr)
{
    char line[LINE_Z];
    FILE *fp_qemu = fopen("LS_Trace.txt", "a+");
    assert(fp_qemu!=0);
    fseek(fp_qemu, 0, SEEK_END);
    sprintf(line,"%p\n",Addr);
    fwrite(line, strlen(line), 1, fp_qemu);
    memset(line,0,LINE_Z*sizeof(char));
    fclose(fp_qemu);
};

//#endif
#endif
