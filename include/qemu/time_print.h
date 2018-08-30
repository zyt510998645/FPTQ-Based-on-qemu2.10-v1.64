#ifndef QEMU_TIME_PRINT_H
#define QEMU_TIME_PRINT_H
#include "qemu/temp_his.h"
#include <time.h>
#include <stdio.h>
#include "qemu/Title.h"
static void print_SET_LIST(TypeU64 *H)
{
  if(LOG_QEMU_RDD || LOG_QEMU_SDD)
  {
    TypeU64 i=0;
    printf("\nSET_NUM_LIST: 0 1 2 3...\n");
    for(i=0;i < GET_SET;i++)
    {
	printf("%lu ",*(H+i));
    }
  }
  else
    printf("RDD/SDD DISABLED!!");
  printf("\n\n");
}

//if(LOG_QEMU_RDD)
static void print_RDD(TypeU64 *H,TypeU64 *H_sample,TypeU64 *H_SET)
{
    TypeU64 i=0,ii=0;
    FILE *fp1 = fopen("Qemu_RDD_64_64_16.txt","w");
    fprintf(fp1,"#######CONF#STATS####### \nL1_DCache_Size: %lu KB \nL1_CACHE_LINE: %lu Byte \nL1_ASSOCIATE: %lu Way\n(L1_SET_NUM: %lu Set) \nCut-off Distance:\n  RDD:%lu \n  SDD:%lu \n  RDD_SAMPLE:%lu \n  SDD_SAMPLE:%lu \n#######CONF#STATS#######\n",(TypeU64)L1D_SIZE,(TypeU64)CACHE_LINE,(TypeU64)ASSOCIATE,(TypeU64)GET_SET,(LOG_QEMU_RDD ? (TypeU64)INTERVAL_RDD : (TypeU64)0),(LOG_QEMU_SDD ? (TypeU64)INTERVAL_SDD : (TypeU64)0),(INTERVAL_RDD_SAMPLE ? (TypeU64)INTERVAL_RDD_SAMPLE : (TypeU64)0),(INTERVAL_SDD_SAMPLE ? (TypeU64)INTERVAL_SDD_SAMPLE : (TypeU64)0));
    fprintf(fp1,"\nSET_NUM_LIST: 0 1 2 3...\n");
    for(ii=0;ii < GET_SET;ii++)
    {
	fprintf(fp1,"%lu ",*(H_SET+ii));
    }
    fprintf(fp1,"\n\nQemu_RDD_L/S: %lu \n\n",RDD_LS);
    for(i=0;i < (INTERVAL_RDD + 1);i++)
	fprintf(fp1,"%lu ",*(H + i));
    fclose(fp1);

if(INTERVAL_RDD)
{
    printf("Qemu_RDD_L/S: %lu \n",RDD_LS);   //ZYT
    for(i=0;i < (INTERVAL_RDD + 1);i++)
        printf("%lu ",*(H + i));
    printf("\n");
}

if(INTERVAL_RDD_SAMPLE)
{
    printf("Qemu_sample_RDD_L/S: %lu \n",Sample_RDD_LS);   //ZYT
    for(i=0;i < (INTERVAL_RDD_SAMPLE + 1);i++)
        printf("%lu ",*(H_sample + i));
    printf("\n");
}
};
//#endif
//#if LOG_QEMU_SDD
static void print_SDD(TypeU64 *H, TypeU64 *H_sample, TypeU64 *H_SET)
{
    TypeU64 i=0,ii=0;
    FILE *fp1 = fopen("Qemu_SDD_64_64_16.txt","w");
    fprintf(fp1,"#######CONF#STATS####### \nL1_DCache_Size: %lu KB \nL1_CACHE_LINE: %lu Byte \nL1_ASSOCIATE: %lu Way\n(L1_SET_NUM: %lu Set) \nCut-off Distance:\n  RDD:%lu \n  SDD:%lu \n#######CONF#STATS#######\n",(TypeU64)L1D_SIZE,(TypeU64)CACHE_LINE,(TypeU64)ASSOCIATE,(TypeU64)GET_SET,(LOG_QEMU_RDD ? (TypeU64)INTERVAL_RDD : (TypeU64)0),(LOG_QEMU_SDD ? (TypeU64)INTERVAL_SDD : (TypeU64)0));
    fprintf(fp1,"\nSET_NUM_LIST: 0 1 2 3...\n");
    for(ii=0;ii < GET_SET;ii++)
    {
	fprintf(fp1,"%lu ",*(H_SET+ii));
    }
    fprintf(fp1,"\n\nQemu_SDD_L/S: %lu \n\n",SDD_LS);
    for(i=0;i < (INTERVAL_SDD + 1);i++)
	fprintf(fp1,"%lu ",*(H + i));
    fclose(fp1);

if(INTERVAL_SDD)
{
    printf("Qemu_SDD_L/S: %lu \n",SDD_LS);   //ZYT
    for(i=0;i<(INTERVAL_SDD+1);i++)
        printf("%lu ",*(H + i));
    printf("\n");
}

if(INTERVAL_SDD_SAMPLE)
{
    printf("Qemu_sample_SDD_L/S: %lu \n",Sample_SDD_LS);   //ZYT
    for(i=0;i < (INTERVAL_SDD_SAMPLE + 1);i++)
        printf("%lu ",*(H_sample + i));
    printf("\n");
}
};
//#endif

static void get_time(void)
{
    //char* nowtime = NULL;//ZYT
    char nowtime[20];
    time_t rawtime;
    struct tm* ltime;
    time(&rawtime);
    ltime = localtime(&rawtime);
    strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
    printf("%s\n", nowtime);
};

#endif
