/*
 * =====================================================================================
 *
 *       Filename:  vsz_and_rss.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/25/2016 09:33:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gao Feng, gfree.wind@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<void*> mems;

static void alloc_mem(bool fill)
{
	int i;

	for (i = 0; i < 512; ++i) {
		void *p = malloc(1024*1024);
		if (fill) {
			memset(p, 0, 1024*1024);
		}
		mems.push_back(p);
	}

	printf("Mem is allocated\n");
}

int main(int argc, const char **argv)
{
	alloc_mem(argc >= 2);
	getchar();
	return 0;
}

