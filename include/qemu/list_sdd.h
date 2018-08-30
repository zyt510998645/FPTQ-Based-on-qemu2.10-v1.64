#ifndef QEMU_LIST_SDD_H
#define QEMU_LIST_SDD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qemu/temp_his.h"
#include "qemu/Title.h"
typedef struct node
{
	TypeU64 key;
	struct node *next;
}Node_sdd;

static Node_sdd * head[SET_NUM] = {NULL};
static Node_sdd * tail[SET_NUM] = {NULL};

static Node_sdd * sample_head[SET_NUM] = {NULL};//just for sample sdd! 3-14

static void sample_insert(TypeU64 set_id, TypeU64 num)
{
	Node_sdd * new_node, *current;
        int flag = 0;
	new_node = (Node_sdd*)malloc(sizeof(Node_sdd));
	new_node->key = num;
	if(sample_head[set_id] == NULL)
	{
		new_node->next = NULL;
		sample_head[set_id] = new_node;
	}
	else
	{
		current = sample_head[set_id];
		while(current != NULL)
		{
		    if(current->key == num)
		    {
			flag = 1;
			break;
		    }
		    current = current->next;
		}
		if(flag == 0)//join in
		{
		    new_node->next = sample_head[set_id];
		    sample_head[set_id] = new_node;
		}
		else
		{
		    free(new_node);
		}
	}
};
static TypeU64 getNums( TypeU64 sample_set_id)
{
    TypeU64 Numbers =0;
    Node_sdd * current ;
    current = sample_head[sample_set_id];
    while(current != NULL)
    {
	Numbers += 1;
	current = current->next;
    }
    return Numbers;
};
static void delSampleHead( TypeU64 sample_set_id)
{
    Node_sdd * current ;
    current = sample_head[sample_set_id];
    Node_sdd * ans;
    while(current != NULL)
    {
	ans = current;
	current = current->next;
	free(ans);
    }
    sample_head[sample_set_id] = NULL;
};
static void getSampleSdd(TypeU64 taddr, TypeU64 *H_SDD, TypeU64 *Sample_SDD, TypeU64 *Sample_SDD_taddr, TypeU64 *Sample_SDD_flag, TypeU64 *Sample_SDD_LS)
{
    TypeU64 set_id = Set_Id(taddr);
    //TypeU64 set_id = 0;
    TypeU64 stack = 0;
    TypeU64 kk = taddr >> CACHE_LINE_BIT;
    if((Sample_SDD[set_id]++) % INTERVAL_SDD_SAMPLE_RATE == 0)
    {
	*Sample_SDD_LS += 1;
	Sample_SDD_flag[set_id] = 0;//flag
	Sample_SDD_taddr[set_id] = kk;
	delSampleHead( set_id);
	sample_insert(set_id, kk);
    }
    else
    {
	if(Sample_SDD_flag[set_id] == 0)
	{
	    stack = getNums( set_id) - 1;
	    //if((stack <= INTERVAL_SDD) && ((Sample_SDD[set_id]%SAMPLE_RATE) <= SAMPLE_RATE))	
	    if((stack <= INTERVAL_SDD) && ((Sample_SDD[set_id]%INTERVAL_SDD_SAMPLE_RATE) != 0))	
	    {
	        if(Sample_SDD_taddr[set_id] != kk)
	        {
	    	sample_insert(set_id, kk);
	        }
	        else
	        {
	    	stack = getNums( set_id) - 1;
	    	*(H_SDD + stack) += 1;
	    	Sample_SDD_flag[set_id] = 1;//flag
	        }
	    }
	    else if(!(stack <= INTERVAL_SDD) || (Sample_SDD_taddr[set_id] == kk))
            {
		if(Sample_SDD_taddr[set_id] == kk)
		    { *(H_SDD + stack) += 1; }
		else
	            { *(H_SDD + INTERVAL_SDD) += 1; }
		Sample_SDD_flag[set_id] = 1;//flag
	    }
	    else
	    {
		*(H_SDD + INTERVAL_SDD) += 1;
	    }
	}
    }   
};

/*
static void sample_insert(TypeU64 sample_set_id, TypeU64 sample_num)
{
	Node_sdd * new_node, *current;
        int flag = 0;
	new_node = (Node_sdd*)malloc(sizeof(Node_sdd));
	new_node->key = num;
	if(sample_head[set_id] == NULL)
	{
		new_node->next = NULL;
		sample_head[set_id] = new_node;
	}
	else
	{
		current = sample_head[set_id];
		while(current != NULL)
		{
		    if(current->key == num)
		    {
			flag = 1;
			break;
		    }
		    current = current->next;
		}
		if(flag == 0)//join in
		{
		    sample_head[set_id]->next = new_node;
		    new_node->next = NULL;
		}
		else
		{
		    free(new_node);
		}
	}
};
static TypeU64 getNums(Node_sdd *sample_head, TypeU64 sample_set_id)
{
    TypeU64 Numbers =0;
    Node_sdd * current = sample_head[sample_set_id];
    while(current != NULL)
    {
	Numbers += 1;
	current = current->next;
    }
    return Numbers;
};
static void delSampleHead(Node_sdd *sample_head, TypeU64 sample_set_id)
{
    Node_sdd * current = sample_head[sample_set_id];
    Node_sdd * ans;
    while(current != NULL)
    {
	ans = current;
	current = current->next;
	free(ans);
    }
};
static void getSampleSdd(TypeU64 taddr,TypeU64 load_store,TypeU64 *H_SDD, TypeU64 *Sample_SDD, TypeU64 *Sample_SDD_taddr)
{
    Node_sdd * current1;
    TypeU64 stack = 0;
    TypeU64 set_id = Set_Id(taddr);
    TypeU64 kk = taddr >> CACHE_LINE_BIT;
    current1 = sample_head[set_id];
    Sample_SDD_taddr[set_id] = 0;  //A
    if((Sample_SDD[set_id]++) % SAMPLE_RATE == 0)
    {
	Sample_SDD_taddr[set_id] = kk;
	delSampleHead(sample_head, set_id);
	sample_insert(set_id, kk);
    }
    else
    {
	stack = getNums(sample_head, set_id) - 1;
	if(stack <= INTERVAL_SDD && Sample_SDD[set_id] <= SAMPLE_RATE)	
	{
	    if(Sample_SDD_taddr[set_id] != kk)
	    {
		sample_insert(set_id, kk);
	    }
	    else
	    {
		stack = getNums(sample_head, set_id) - 1;
		*(H_SDD + stack) += 1;
	    }
	}
	else
        {
	    *(H_SDD + INTERVAL_SDD) += 1;
	}
    }   
};
*/


static void insert(TypeU64 set_id,TypeU64 num)
{
	Node_sdd * new_node, *current;
	new_node = (Node_sdd*)malloc(sizeof(Node_sdd));
	new_node->key = num;
	if(head[set_id] == NULL)
	{
		new_node->next = NULL;
		head[set_id] = new_node;
		tail[set_id] = new_node;
	}
	else
	{
		current = head[set_id];
		new_node -> next = current;
		head[set_id] = new_node;
	}
};

static Node_sdd * delete1(TypeU64 set_id,TypeU64 num)
{
	Node_sdd * current = head[set_id];
	Node_sdd * answer;
	if(head[set_id] != NULL && head[set_id]->key == num)
	{
		if(head[set_id]->next == NULL)
			tail[set_id] = NULL;
		head[set_id] = head[set_id]->next;
		if(current != NULL)
			free(current);
		return current;
	}
	while(current != NULL)
	{
		if(current->next != NULL && current->next->key == num)
		{
			if(current->next->next == NULL)
			{
				tail[set_id] = current;
			}
			answer = current->next;
			current->next = current->next->next;
			if(answer != NULL)
				free(answer);
			return answer;
		}
		current = current->next;
	}
    return NULL;
};

static void search_sdd(TypeU64 set_id,TypeU64 kk,TypeU64 load_store,TypeU64 *H_SDD)
{
	Node_sdd * current1;
	long unsigned int num_ls = 0,result=0;
	char flag = 0;
	current1 = head[set_id];
	if(current1 == NULL)
	{insert(set_id,kk);result = INTERVAL_SDD;flag = 1;}
    while((current1 != NULL) && (!flag))
	{
		num_ls++;
		if(current1->key != kk)
		{
		    if(num_ls >= INTERVAL_SDD+1)
			{delete1(set_id,tail[set_id]->key);insert(set_id,kk);result = INTERVAL_SDD;break;}
			else
			{result += 1;current1 = current1->next;}
		}
		else
		{delete1(set_id,kk);insert(set_id,kk);break;}
	}
	if((current1 == NULL) && !(num_ls >= INTERVAL_SDD+1))
	{insert(set_id,kk);result = INTERVAL_SDD;}
	*(H_SDD + result) +=1;
};
/*
static void getSampleSdd(TypeU64 taddr,TypeU64 load_store,TypeU64 *H_SDD, TypeU64 *Sample_SDD, TypeU64 *Sample_SDD_taddr)
{
	Node_sdd * current1;
        TypeU64 set_id = Set_Id(taddr);
        TypeU64 kk = taddr >> CACHE_LINE_BIT;
	long unsigned int num_ls = 0,result=0;
	char flag = 0, flag_r = 0 ;
	current1 = head[set_id];
        if((Sample_SDD[set_id]++) % SAMPLE_RATE == 0)
	{
	    Sample_SDD_taddr[set_id] = kk;
	    flag_r = 1;
	}
	if(current1 == NULL)
	{
	    insert(set_id,kk);
	    result = INTERVAL_SDD;
	    flag = 1;
	}
    	while((current1 != NULL) && (!flag))
	{
	    num_ls++;
	    if(current1->key != kk)
	    {
		if(num_ls >= INTERVAL_SDD+1)
		{
		    delete1(set_id,tail[set_id]->key);
		    insert(set_id,kk);
		    result = INTERVAL_SDD;
		    break;
		}
		else
		{
		    result += 1;
		    current1 = current1->next;
		}
	    }
	    else
	    {
		delete1(set_id,kk);
		insert(set_id,kk);
		break;
	    }
	}
	if((current1 == NULL) && !(num_ls >= INTERVAL_SDD+1))
	{
	    insert(set_id,kk);
	    result = INTERVAL_SDD;
	}
	if(((Sample_SDD_taddr[set_id] == kk) && (flag_r != 1)) || (num_ls >= INTERVAL_SDD+1))
	    *(H_SDD + result) +=1;
	
};
*/
#endif
